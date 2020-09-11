#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<hesion.h>

THeSion::THeSion()
{
  ef1=-1.23;
  ef2=ef1;
}

const float	rb=13.595, rrb=1./rb, pia2=.878;
const float	pion=1.808, m2=.49, d=1.6, c1=.15 ,w=67.7;

static float ff(float e)// e[rb]
{
  float x=5.34/e;
  float y=.027*e;
  return 1.+x*(1.+x)/(1.+y*y*y);
}

float
THeSion::Total(float e)//e[eV]
{
  e*=rrb;
  if(e<pion) return 0.;
  float x=pion/e;
  float y=(1.-x)/pion+log(x)/(e+w)+(1.-x*x)*m2*log(d+sqrt(c1*(e-pion)));
  y=8./e/ff(e)*y*pia2;
  return y;
}

float
THeSion::Differential( float e, float r)//e[eV]
{
  const float mpion=2.*m2*pion*pion;
  if(e!=ef1)
  {
	 ef1=e;
	 e1=e*rrb;
	 if(e1<pion) return 0.;
	 aa1=4./e1/ff(e1)*pia2;
	 bb1=1./(e1+w);
	 cc1=mpion*log(d+sqrt(c1*(e1-pion)));
  }
  float ed=e1-(e1-pion)*r;
  float x=1./ed;
  float y=1./(e1+pion-ed);
  float xx=x*x;
  float yy=y*y;
  return aa1*(xx+yy-bb1*(x+y)+cc1*(x*xx+y*yy));
}

float
THeSion::Probability(float e, float r)
{
  const float mpion=2.*m2*pion*pion;
  float x,y;
  if(e!=ef2)
  {
	 ef2=e;
	 e2=e*rrb;
	 if(e2<pion) return 0.;
	 x=1./e2;
	 y=1./pion;
	 bb2=1./(e2+w);
	 cc2=mpion*log(d+sqrt(c1*(e2-pion)));
	 aa2=.5/(y-x-bb2*log(y/x)+cc2*(y*y-x*x));
  }
  float ed=pion+(e2-pion)*r;
  x=1./ed;
  y=1./(e2+pion-ed);
  return .5+aa2*(y-x-bb2*log(y/x)+cc2*(y*y-x*x));
}

float
THeSion::Share(float e,float p,int kit)
{
  float r0=0.;
  float r1=1.;
  for(int k=1;k<=kit;k++)
  {
	 float r=(r0+r1)*.5;
	 if(Probability(e,r)<p) r0=r;
	 else r1=r;
  }
  return (r0+r1)*.5;
}

