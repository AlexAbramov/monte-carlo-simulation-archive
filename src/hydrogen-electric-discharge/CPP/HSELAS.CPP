#include <math.h>
#pragma hdrstop
#include <mylib.h>
#include <hselas.h>

static float kdif=0.;// anisotropic coefficient

static float Probability( float e, float angle)
{
  static float ef=0.;
  static float x,y,z;
  if(angle<0.) error_message("Angle < 0 in spelasp");
  if(angle>M_PI) error_message("Angle > pi in spelasp");
  if(e==0.)e+=.001;
  if(e!=ef)
  {
	 if(e<0.) error_message("Energy < 0 in spelasp");
	 ef=e;
	 x=kdif*sqrt(e);
	 y=1./(1.-(1.+x)*exp(-x));
  }
  z=x*sin(angle*.5);
  return (1.-(1.+z)*exp(-z))*y;
}

float Angle( float e, float p,int kit)
{
  static int FirstCall=1;
  if(FirstCall==1)
  {
	 FILE * fp=handle_scan("kdif.dat");
	 fscanf(fp,"%f",&kdif);
	 fclose(fp);
	 FirstCall=0;
  }
  int k;
  float a0,a,a1;
  a0=0.;
  a1=M_PI;
  for(k=1;k<=kit;k++)
  {
	 a=(a0+a1)*.5;
	 if(Probability(e,a)<p)a0=a;
	 else a1=a;
  }
  return (a0+a1)*.5;
}