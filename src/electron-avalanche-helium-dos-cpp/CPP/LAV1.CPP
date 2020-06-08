// 		ПОДПРОГРАММА: ГЕНЕРАЦИЯ ЭЛЕКТРОННОЙ ЛАВИНЫ
//		( for nonuniform electric field & fast count OS)
#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<se.h>
#include<param.h>
#include<rnd.h>
const double pi2=M_PI*2.;
// ДЕКЛАРАЦИЯ ФУНКЦИЙ 
int ik;
void		lav1();
static void	init_lav();
static void	init_electron();
static void	count();
static void	normal_step();
static void	anormal_step();
static void	anormal_step1();
static void	collision();
static void	collision1();
static void	real_collision();
static void	elastic_collision();
static void	exciting_collision();
static void	ionising_collision();

// ДАННЫЕ ОБ АНСАМБЛЕ ЭЛЕКТРОНОВ
static int		kele;
static const int	kelemax=137;

static int		ihr[kelemax];
static double		vxhr[kelemax];
static double		erhr[kelemax];
static double		dechr[kelemax];

// ДАННЫЕ ТЕКУЩЕГО СОСТОЯНИЯ ЭЛЕКТРОНА 
static int	i;
static double	vx,ex,er,e;
static int	normal;
static int	normal0;
static double	dec;

static double	ss,sss; // Когда ss=sss - столкновение.
static int	primary;

static double	ss0,vx0,e0;
static double	r,mi;

static int zone;
static double dx;
static double ddk;
static double ddx;

// ОПРЕДЕЛЕНИЕ ФУНКЦИЙ
void lav1()
{
  dx=dd/imax;
  init_lav();	// Инициализация лавины:
  while(kele>=0)//Учет всех электронов лавины.
  {
    init_electron();// Инициализация электрона
    while(1)//Отслеживание одного электрона
    {
//printf(" %i",i);
      ss0=ss;
      vx0=vx;
      e0=e;
      normal0=normal;
      if(normal==1)
      {
        count();//Учет статистики электронов
        if(i==0 && vx<0.) break;//Поглощение электрона катодом
  	if(i==imax) break;//Поглощение электрона анодом
	if(i<ik)zone=0;
	else
	{
	  if(i==ik)
	  {
	    if(vx>0.)
	    {
	      zone=1;
              ddk=sqrt(e)*stotf(e)/fabs(vx);
              ddx=ddk*dx;
	    }
	    else zone=0;
	  }
	  else zone=1;
	}
	if(zone==0) normal_step();
	else 
	{
	  if(vx>0.) i++;
	  else i--;
	  ss+=ddx;
	}
      }
      else 
      {
	if(i<ik)zone=0;
	else zone=1;
	if(zone==0) anormal_step();
	else anormal_step1();
      }
//	printf(" %i",zone);
      if(zone==0)ss+=(mi+mi)*fabs(vx-vx0);
      if(ss>sss) 
      {
	if(zone==0)collision();
	else collision1();
      }
    }//Конец отслеживания одного электрона
  }//Конец отслеживания электронов лавины
}

static void init_lav()
{
  kele=0;
  *ihr=0;
  static float e,cosf;
  e=4.+rnd(0);
  cosf=rnd(1);
  *vxhr=sqrt(e)*cosf;
  *erhr=e*(1.-cosf*cosf);
  primary=1;
}

static void init_electron()
{
  i=ihr[kele];
  vx=vxhr[kele];
  er=erhr[kele];
  if(primary==1) { normal=1; primary=0; sss=-log(rnd(2));}
  else { normal=0; dec=dechr[kele]; sss=-log(rnd(3));} 
  kele--;
  ex=vx*vx;
  e=ex+er;
  ss=0.;
}

static void count()
{
  //printf(" %i",i);
  static double m;
  if(vx>0.){ vvd[i]+=1.; m=1./vx; /*evx[i]+=e;*/ }
  else{ vvd[i]-=1.; m=-1./vx; /*evx[i]-=e;*/ }
  mm[i]+=m;
//  static double	vm;
//  vm=sqrt(e)*m;
  vvx[i]+=1.;
//  vvr[i]+=sqrt(er)*m;
//  vvv[i]+=vm;
//  eex[i]+=ex*m;
//  eer[i]+=er*m;
  eee[i]+=e*m;
//  static float stvm;
//  stvm=vm*stotf(e);
//  fto[i]+=stvm;
//  fel[i]+=stvm*selasf(e);
//  if(e>pex) fex[i]+=stvm*sexf(e);
  if(e>pion) fio[i]+=ftotf(e)*sionf(e)*m;
}

static void normal_step()
{ 
  if(vx>0.)//Вперед.
  { 
    ex+=de[i];  
    vx=sqrt(ex);
    e=ex+er;
    i++; 
    mi=sqrt(e)/ff[i]*stotf(e0);
  }
  else //vx<0.
  {
    static double d;
    d=de[i-1];
    if(ex>d)//Назад
    { 
      ex-=d; 
      vx=-sqrt(ex);
      e=er+ex;
      mi=sqrt(e0)/ff[i]*stotf(e);
      i--; 
    }
    else //Разворот
    { 
      vx=-vx;
      mi=sqrt(e)/ff[i]*stotf(er);
    }
  }
}

static void anormal_step()
{ 
  if(vx<0. && ex>dec)//Назад.
  { 
    ex-=dec; 
    vx=-sqrt(ex);
    e=ex+er;
    mi=sqrt(e0)/ff[i+1]*stotf(e);
  }
  else//Вперед.
  { 
    ex+=(de[i]-dec);
    e=ex+er; 
    i++; 
    if(vx<0.) mi=sqrt(e)/ff[i]*stotf(er);
    else mi=sqrt(e)/ff[i]*stotf(e0);
    vx=sqrt(ex);
  }
  normal=1;
}

static void anormal_step1()
{ 
  if(vx<0.)//Назад.
  { 
    ss+=dec*ddk;
  }
  else//Вперед.
  { 
    ss+=(dx-dec)*ddk;
    i++; 
  }
  normal=1;
}

static void collision1()
{
  if(normal0==1)
  {  
    if(vx>0.)dec=(sss-ss0)/ddk;
    else dec=(ss-sss)/ddk;
  }
  else
  {
    if(vx>0.)dec+=(sss-ss0)/ddk;
    else dec=(ss-sss)/ddk;
  }
  normal=0;
  if(vx>0.)i--;
  ss=0.;
  sss=-log(rnd(6));
  if(dec<0.){printf("\n\a\a Error: dec=%f<0",dec);exit(-1);}//control
  r=rnd(7);
  real_collision();
  ddk=sqrt(e)*stotf(e)/fabs(vx);
  ddx=ddk*dx;
}

static void collision()
{
  static double fc,vx1,e1;
  normal=0;
  vx1=vx;
  e1=e;
  if(vx>0.)i--;
  vx=vx0+(sss-ss0)/(mi+mi);
  ex=vx*vx;
  e=ex+er;
  ss=0.;
  sss=-log(rnd(4));
  if(vx1>0.) dec=e+de[i]-e1; 
  else dec=e-e1; 
  fc=etof(i,dec);
  if(dec<0.){printf("\n\a\a Error: dec=%f<0",dec);exit(-1);}//control
  r=mi*fc/sqrt(e)/stotf(e);
  if(r<1.){printf("\n\a\a Error: snul=%f<0",r-1.);exit(-1);}//control
  r*=rnd(5);
  if(r<1.) real_collision();
}


static void real_collision()
{
  if( e<pex||r<selasf(e) ) elastic_collision();
  else
  {
    if( e<pion||(1.-r)<sexf(e) ) exciting_collision(); 
    else ionising_collision();
  }
}

static void elastic_collision()
{
  static double angle;  
  angle=spelasf(e,rnd(8));//anisotrop collision
//  angle=acos(1.-2.*rnd(8));//isotrop collision
//  printf(" *");
  // lost electron energy
  const double kk=.000272;// 2.*m(e)/m(he)
  static double cosan,kf;
  cosan=cos(angle);
  kf=1.-kk*(1.-cosan);
  er*=kf;
  vx*=sqrt(kf);
  e=vx*vx+er;

  vx=vx*cosan+sqrt(er)*sin(angle)*sin(rnd(9)*pi2);
  ex=vx*vx;
  er=e-ex;
  if(er<0.){ printf("\n\a\a Error: er<0"); exit(-1);}//control
}

static void exciting_collision()
{
  static double dex;
  static int n; n=spexf(e,rnd(10)); dex=(e-pexi(n))/e; // many levels
//  dex=(e-pex)/e;// one level                
  ex*=dex;
  er*=dex;
  e=ex+er;
  if(vx>0.)vx=sqrt(ex); 
  else vx=-sqrt(ex);
}

static void ionising_collision()
{
 // printf(" ***");
  kele++;
  if(kele>=kelemax){printf("\n\a\a Error kele>kelemax !"); exit(-1); }//control
  ihr[kele]=i;
  dechr[kele]=dec;
  static double dio,k,vx1,vx2,e1,e2;
  dio=spionf(e,rnd(11));
  k=(e-pion)/e;
  vx*=sqrt(k);
  e*=k;
  e1=e*dio;
  e2=e-e1;
  vx1=vx*dio+sqrt(er*k*(1.-dio)*dio)*sin(rnd(12)*pi2);
  vx2=vx-vx1;
  vxhr[kele]=vx2;
  erhr[kele]=e2-vx2*vx2;
  if(erhr[kele]<0.){ printf("\n\a\a Error: er<0 in io1"); exit(-1);}//control
  vx=vx1;
  e=e1;
  ex=vx*vx;
  er=e-ex;
  if(er<0.){ printf("\n\a\a Error: er<0 in io2"); exit(-1);}//control
}