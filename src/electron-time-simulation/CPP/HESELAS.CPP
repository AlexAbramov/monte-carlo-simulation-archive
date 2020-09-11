#include<stdio.h>
#include<math.h>
#include<heselas.h>

#define KDIF .5 // anisotropic coefficient

THeSelas::THeSelas(char* str)
{
  ptf=new TTabFunc(str);
}

THeSelas::~THeSelas()
{
  delete ptf;
}

float
THeSelas::Total(float e)
{
  return ptf->Ordinata(e);
}

float
THeSelas::Differential( float e, float angle)
{
  return exp(-KDIF*sqrt(e)*sin(angle*.5))*sin(angle);
}

float
THeSelas::Probability( float e, float angle)
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
	 x=KDIF*sqrt(e);
	 y=1./(1.-(1.+x)*exp(-x));
  }
  z=x*sin(angle*.5);
  return (1.-(1.+z)*exp(-z))*y;
}

float
THeSelas::Angle( float e, float p,int kit)
{
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