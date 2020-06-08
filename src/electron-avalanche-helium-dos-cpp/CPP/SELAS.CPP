// Функции для расчета сечений упругого соударения электрона с атомом гелия.
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<selas.h>

const float kper=1.;
const float kdif=.4;

float selasfn( float e)
{
  static int FirstCall=1;
  static int i,imax,ie;
  static float aa,bb;
  static int * ii;
  static float * ss;
  if(e<0.){printf("\n\a\a Energy < 0 in function selasfn !");exit(-1);}
  if(FirstCall==1)
  {
    FirstCall=0;
    FILE* fp=fopen("..\\dat\\selas.dat","r");
    if(fp==0){ printf("\n\a\a Не найден файл 'selas.dat'."); exit(-1); }
    fscanf(fp,"%i",&i);
    while(i>=0)
    {
      fscanf(fp,"%f",ss);
      imax++;   
      fscanf(fp,"%i",&i);
    }
    ii=new int[imax];  
    ss=new float[imax];
    imax--;
    fseek(fp,0,0);  
    for(i=0;i<=imax;i++)
    {
      fscanf(fp,"%i",ii+i);
      fscanf(fp,"%f",ss+i);
    }
    aa=(1./ss[imax]-1./ss[imax-1])/(ii[imax]-ii[imax-1]);
    bb=1./ss[imax]-aa*ii[imax];
  }
  ie=e;
  if(ie<ii[imax])
  {
    i=0;
    while(ie>ii[i]) i++;  
    return kper*(ss[i-1]+(ss[i]-ss[i-1])*(e-ii[i-1])/(ii[i]-ii[i-1]));     
  }
  else
  {
    return kper/(aa*e+bb);
  }
}

float spelasd( float e, float angle)
{
  return exp(-kdif*sqrt(e)*sin(angle*.5))*sin(angle);
}

float spelasp( float e, float angle)
{
  static float ef=0.;
  static float x,y,z;
  if(angle<0.){printf("\a\a\a\n Angle < 0 in function spelas !");exit(-1);}
  if(angle>pi){printf("\a\a\a\n Angle > pi in function spelas !");exit(-1);}
  if(e==0.)e=e+.001;
  if(e!=ef) 
  { 
    if(e<0.){printf("\a\a\a\n Energy < 0 in function spelas !");exit(-1);}
    ef=e;
    x=kdif*sqrt(e);
    y=1./(1.-(1.+x)*exp(-x));
  }
  z=x*sin(angle*.5);
  return (1.-(1.+z)*exp(-z))*y;
}

float spelasr( int kit, float e, float p)
{
  static int k;
  static float a0,a,a1;
  a0=0.;
  a1=pi;
  for(k=1;k<=kit;k++) 
  {
    a=(a0+a1)*.5;
    if(spelasp(e,a)<p)a0=a;
    else a1=a;
  }
  return (a0+a1)*.5;
}

static inline float aprox( float a, float b, float c, float d, float dx, float dy)
{
  return a+(b-a)*dx+(c-a)*dy+(d+a-b-c)*dx*dy;
} 
float spelaspl( float ener, float alfa)
{
  if(ener>=150.) return spelasp(ener,alfa);
  alfa*=180./3.1415;
  static int	FirstCall=0;
  int	i,j;
  const int	ii=15;	// Число строк
  const int	jj=29;	// Число столбцов
  static float angle[ii];	// Массив углов
  static float energy[jj];	// Массив энергий
  static float spelas[ii][jj];	// Массив дифф. сечений
  if(FirstCall==0)
  {
    FirstCall=1;
    FILE * fp=fopen("..\\dat\\spelas.dat","r");
      for( i=0; i<ii; i++) fscanf( fp,"%f",angle+i);
      for( j=0; j<jj; j++)
      {
        fscanf( fp,"%f",energy+j);
        for( i=0; i<ii; i++) fscanf( fp,"%f",&spelas[i][j]);
      }
    fclose(fp);
//    for( i=0; i<ii; i++) printf("\n %f",angle[i]);
//    for( j=0; j<jj; j++) printf("\n %.0f",energy[j]);
  }
  i=1;
  j=1;
  while(angle[i]<alfa) i++; 
  float x1=angle[i]; 
  i--; 
  float x0=angle[i];
  while(energy[j]<ener) j++; 
  float y1=energy[j]; 
  j--; 
  float y0=energy[j];
  //printf("\n i=%i x0=%f x1=%f",i,x0,x1);
  //printf("\n j=%i y0=%f y1=%f",j,y0,y1);
  float dx=(alfa-x0)/(x1-x0);
  float dy=(ener-y0)/(y1-y0);
  float a,b,c,d;
  a=spelas[i][j];
  b=spelas[i+1][j];
  c=spelas[i][j+1];
  d=spelas[i+1][j+1];
  return aprox(a,b,c,d,dx,dy);
}
float spelasrl( int kit, float e, float p)
{
  static int k;
  static float a0,a,a1;
  a0=0.;
  a1=pi;
  for(k=1;k<=kit;k++) 
  {
    a=(a0+a1)*.5;
    if(spelaspl(e,a)<p)a0=a;
    else a1=a;
  }
  return (a0+a1)*.5;
}
