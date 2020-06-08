#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mygraph.h>
#include<paramf.h>
const int narg=2;
char* varg[2];
float raspred(float e, float d, float k=1.);//d=2*esr/3
float raspred(float e, float d, float k)
{
  return (k+k)*sqrt(e/(3.1415*d*d*d))*exp(-e/d);
}
#define kit 10
float frer(float d, float k, float * mas)
{
  const int imax=36;
  float sum=0.;
  for( int i=0; i<=imax; i++)
  {
    float x=mas[i];
    float e=float(i);
    float y=raspred(e,d,k);
    float d=(x-y)*(x-y);
    sum+=d;
  }
  return sum;
}
int main(int narg,char* varg[])
{
  int nseq;
  int i,status_fre=0;
  strcpy(file_param,varg[1]);
  read_param();
  print_par();
  int i1=2*imax/5;
  int i2=4*imax/5;
  int ii=i2-i1+1;
  double ener=0.;
  double vdr=0.;
  double esr=0.;
  double fexsr=0.;
  double evxsr=0.;
  double fion=0.;
  double alfa=0.;
  for(i=i1;i<=i2;i++)
  { 
    double rmm=1./mm[i];
    ener+=eer[i]*rmm;
    vdr+=vvd[i]*rmm; 
    esr+=eee[i]*rmm; 
    fion+=fio[i]*rmm; 
    fexsr+=fex[i]*rmm; 
    evxsr+=evx[i]*rmm; 
    alfa+=fio[i]/vvd[i];
  }
  double ddx=(evx[i2]/vvd[i2]-evx[i1]/vvd[i1])*(imax-1)/(dd*ii);
  double rii=1./double(ii);
  ener*=rii;
  vdr*=rii;
  esr*=rii;
  fion*=rii;
  fexsr*=rii;
  evxsr*=rii;
  alfa*=rii;
  printf("\n vdr=%.3f",vdr); 
  printf("\n esr=%.3f",esr); 
  printf("\n ee=%.3f",ener); 
  printf("\n err=%.4f",esr*esr*5./(3.*ener)-1.); 
  printf("\n fio=%.3f",fion); 
  printf("\n fex=%.3f",fexsr); 
  printf("\n evx=%.3f",evxsr); 
  printf("\n ddx=%.3f",ddx); 
  printf("\n alfa=%.3f",alfa); 
  printf("\n Press any key:");
  if(getch()==27) return 0;
  
  initgraph();
  TBox box("..\\gdat\\box.dat");  
  TMenu menu("..\\gdat\\menuvisf.dat");
  TDialog dialog("..\\gdat\\dialogn.dat");
  TDialog dialogf("..\\gdat\\dialogf.dat");
  TGraph graph("..\\gdat\\graph.dat");
  box.show();

  float * xxx=new float[imax+1];
  float * yy=new float[imax+1];
  float * xfre=new float[fremax1];
  float * yfre=new float[fremax1];
  float * yyfre=new float[fremax1];
  for(i=0;i<=imax;i++) xxx[i]=xx[i];
  for(i=0;i<=fremax;i++)
  {  
    xfre[i]=float(i);
    yfre[i]=0.;
    yyfre[i]=0.;
  }
  char textx[]="coord_x,[sm]";
  char texty[50];
  texty[49]=0;

  int cont=1;

  while(cont)
  {
    switch( menu.show() )
    {
      case 1:
	for(i=0;i<=imax;i++) yy[i]=xx[i];
	strcpy(texty,"xx");
        break;
      case 2:
	for(i=0;i<=imax;i++) yy[i]=ff[i];
	strcpy(texty,"Электрическое поле");
        break;
      case 3:
	for(i=0;i<=imax;i++) yy[i]=de[i];
	strcpy(texty,"Приращение энергии на i-м промежутке");
        break;
      case 4:
	for(i=0;i<=imax;i++) yy[i]=mm[i];
	strcpy(texty,"Статистический вес");
        break;
      case 5:
	for(i=0;i<=imax;i++) yy[i]=vvx[i]/mm[i];
	strcpy(texty,"vx");
	break;
      case 6:
	for(i=0;i<=imax;i++) yy[i]=vvd[i]/mm[i];
	strcpy(texty,"Скорость дрейфа");
        break;
      case 7:
	for(i=0;i<=imax;i++) yy[i]=vvr[i]/mm[i];
	strcpy(texty,"vr");
        break;
      case 8:
	for(i=0;i<=imax;i++) yy[i]=vvv[i]/mm[i];
	strcpy(texty,"Средняя скорость");
        break;
      case 9:
	for(i=0;i<=imax;i++) yy[i]=eex[i]/mm[i];
	strcpy(texty,"ex");
        break;
      case 10:
	for(i=0;i<=imax;i++) yy[i]=eer[i]/mm[i];
	strcpy(texty,"er");
        break;
      case 11:
	for(i=0;i<=imax;i++) yy[i]=eee[i]/mm[i];
	strcpy(texty,"Средняя энергия");
        break;
      case 12:
	for(i=0;i<=imax;i++) yy[i]=evx[i]/mm[i];
	strcpy(texty,"<e*vx>");
        break;
      case 13:
	for(i=0;i<=imax;i++) yy[i]=fto[i]/mm[i];
	strcpy(texty,"ftot");
        break;
      case 14:
	for(i=0;i<=imax;i++) yy[i]=fel[i]/mm[i];
	strcpy(texty,"felas");
        break;
      case 15:
	for(i=0;i<=imax;i++) yy[i]=fex[i]/mm[i];
	strcpy(texty,"fex");
        break;
      case 16:
	for(i=0;i<=imax;i++) yy[i]=fio[i]/mm[i];
	strcpy(texty,"fion");
        break;
      case 17:
	for(i=0;i<=imax;i++) yy[i]=fio[i]/vvd[i];
	strcpy(texty,"alfa");
        break;
      case 18:
	nseq=atoi(dialog.show());
	int iseq=nseq;
printf("\n iseq=%i",iseq);
	int index=iseq*fremax1;
	float rmm=1./mm[iseq];
	float hh=0.;
	float ss=0.;
	float sss=0.;
	for(i=0;i<=fremax;i++)
	{
	  float  hh0=hh;
	  hh=.5*fre[index+i]*rmm;
	  float f=hh0+hh;
	  yfre[i]=f;
//	printf("\n %i %f %f",i,f,log(f));
	  float s;
	  if(f>0.) 
	  { 
	    s=-f*log(f);
  	    ss+=s;
	    sss+=f;
	  }
	  else s=0.;
          yyfre[i]=s;
	}
	float sen=ss/log( eee[iseq]/mm[iseq] );
        printf("%.3f  %.3f  %f",ss,sss,sen); getch();
	status_fre=1;
	strcpy(texty,"ФРЭЭ");
	break;
      case 19:
	iseq=atoi(dialog.show());
	index=iseq*fremax1;
	for(i=0;i<=fremax;i++)
	{
	  int k=index+i;
	  if(fre[k]>0.) yfre[i]=mdr[k]/fre[k];
	  else yfre[i]=0.;
	}
	status_fre=2;
	strcpy(texty,"mdr");
        break;
      default:
        cont=0;
    }//end switch
    if(cont) 
    {
      if(status_fre>0)
      {
        graph.show(fremax,xfre,yfre,"energy,[eV]",texty);
//	getch();
//        graph.show(fremax,xfre,yyfre,"energy,[eV]","entropy");
        if(status_fre)
//	if(0)
        {
//          float d=2.*esr/3.;
          float d=2.*eee[nseq]/3./mm[nseq];
  	  for(i=0;i<=fremax;i++)
	  {
	    float e=float(i);
	    yyfre[i]=raspred(e,d);
 	  }          
	  setlinestyle(1,0,1);
          graph.show(yyfre,0);
        }
        status_fre=0;
      }
      else graph.show(imax,xxx,yy,textx,texty);
      if(getch()==27)break;
    }
  }//end while
  closegraph();
  delete yy;
  return 0;
}