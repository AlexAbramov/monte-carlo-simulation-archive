//	circle.cpp
#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<se.h>
#include<pparam.h>
#include<rnd.h>
const double pi2=M_PI*2.;
// „…Š‹€€–ˆŸ ”“Š–ˆ‰ 

void		circle();

static void	count();
static void	normal_step();
static void	anormal_step();
static void	collision();
static void	real_collision();
static void	elastic_collision();
static void	exciting_collision();
static void	ionising_collision();

double dmax(double x,double y)
{
  if(x>y) return x;
  else return y;
}

// „€›… ’…Š“™…ƒŽ ‘Ž‘’ŽŸˆŸ ‹…Š’Ž€ 
static int	i;
static double	e,fz;
static double	fzb;
static double	smax;
static double   x0,vx0,e0,fz0,ss0;

static int	normal=1;
static double	r;
static double	xx0;

// Ž…„…‹…ˆ… ”“Š–ˆ‰

void circle()
{
  fz=0.;
  i=0;
  xx0=x;
  while(1)
  {
    //printf("\n%i\t%i\t%f\t%f\t%f\t%f",normal,i,x,vx,e,fz);
    fz0=fz; x0=x; vx0=vx; e0=e; ss0=ss;
    if(normal)
    {
      if(i==imax) break;
      count();
      normal_step();
    }
    else anormal_step();
    if(ss>sss) collision();
    else normal=1;
  }
}

static void count()
{
  xx[i]+=x-xx0;
  vvd[i]+=vx; 
  evx[i]+=e*vx;
  static double	v;
  v=sqrt(e);
  vvx[i]+=fabs(vx);
  vvr[i]+=sqrt(er);
  vvv[i]+=v;
  eex[i]+=vx*vx;
  eer[i]+=er;
  eee[i]+=e;
  static float ftot;
  ftot=stotf(e);
  fto[i]+=ftot;
  fel[i]+=ftot*selasf(e);
  if(e>pex) fex[i]+=ftot*sexf(e);
  if(e>pion) fio[i]+=ftot*sionf(e);
}

static void normal_step()//i,fz,x,vx,e,ss
{  
  i++;
  fz+=df;
  x=x0+aa*(sin(fz)-sin(fz0))+(kk*vx0/ww-aa*cos(fz0))*df;
  vx=vx0+uu*(cos(fz)-cos(fz0));
  e=er+vx*vx;
  smax=dmax(stotf(e0),stotf(e));
  ss+=smax*dt;
}

static void anormal_step()//
{
  fz=fzb+df;
  x=x0+aa*(sin(fz)-sin(fz0))+(kk*vx0/ww-aa*cos(fz0))*(fz-fz0);
  vx=vx0+uu*(cos(fz)-cos(fz0));
  e=er+vx*vx;
  smax=dmax(stotf(e0),stotf(e));
  ss+=smax*(fz-fz0)/ww;
}

static void collision()
{
  if(normal)
  {
    fzb=fz0;
    normal=0;
  }
  fz-=ww*(ss-sss)/smax;
  x=x0+aa*(sin(fz)-sin(fz0))+(kk*vx0/ww-aa*cos(fz0))*(fz-fz0);
  vx=vx0+uu*(cos(fz)-cos(fz0));
  e=er+vx*vx;
  smax=dmax(stotf(e0),stotf(e));
  if(fz<fzb||fz>fzb+df){printf("\n\a\a Error: faza.");exit(-1);}//control
  ss=0.;
  sss=-log(rnd(1))/conc;
  r=smax/stotf(e);
  if(r<1.){printf("\n\a\a Error: snul %f",r);}//control
  r*=rnd(2);
  if(r<1.) real_collision();
}

static void real_collision()//r,e
{
  if( e<pex||r<selasf(e) ) elastic_collision();
  else
  {
    if( e<pion||(1.-r)<sexf(e) ) exciting_collision(); 
    else ionising_collision();
  }
}

static void elastic_collision()//e,vx,er;
{
  static double angle;  
  angle=spelasf(e,rnd(3));//anisotrop collision
  //angle=acos(1.-2.*rnd(4));//isotrop collision
  //lost electron energy
  const double kk=.000272;// 2.*m(e)/m(he)
  static double cosan,kf;
  cosan=cos(angle);
  kf=1.-kk*(1.-cosan);
  er*=kf;
  vx*=sqrt(kf);
  e=vx*vx+er;
  vx=vx*cosan+sqrt(er)*sin(angle)*sin(rnd(5)*pi2);
  er=e-vx*vx;
  if(er<0.){ printf("\n\a\a Error: er<0"); exit(-1);}//control
}

static void exciting_collision()//e,vx,er;
{
  static double dex;
  static int n; n=spexf(e,rnd(6)); dex=(e-pexi(n))/e; // many levels
//  dex=(e-pex)/e;// one level                
  vx*=sqrt(dex);
  er*=dex;
  e=vx*vx+er;
}

static void ionising_collision()//e,vx,er;
{
  static double dio,k;
  dio=spionf(e,rnd(7));
  k=(e-pion)/e;
  vx*=sqrt(k);
  e*=k*dio;
  vx=vx*dio+sqrt(er*k*(1.-dio)*dio)*sin(rnd(8)*pi2);
  er=e-vx*vx;
  if(er<0.){ printf("\n\a\a Error: er<0 in io2"); exit(-1);}//control
}