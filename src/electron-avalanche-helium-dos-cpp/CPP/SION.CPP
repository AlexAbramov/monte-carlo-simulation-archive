//	”“Š–ˆˆ „‹Ÿ €‘—…’€ ‘…—…ˆ‰ ˆˆ‡€–ˆˆ ƒ…‹ˆŸ
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sion.h>
const float	rb=13.595, rrb=1./rb, pia2=.878;
const float	pion=1.808, m2=.49, d=1.6, c1=.15 ,w=67.7;

static float x;

static float ff( float e)// e[rb]
{
  const float  a=5.34, b=.027;
  static float x,y;
  x=a/e;
  y=b*e;
  return 1.+x*(1.+x)/(1.+y*y*y);
}

float sionfn( float e)//e[eV]
{
  static float x,y;
  e=e*rrb;
  if(e<pion) return 0.;
  x=pion/e;
  y=(1.-x)/pion+log(x)/(e+w)+(1.-x*x)*m2*log(d+sqrt(c1*(e-pion)));
  y=8./e/ff(e)*y*pia2;
  return y;
}

float spiond( float enr, float r)
{
  static float x,y;
  const float mpion=2.*m2*pion*pion;
  static float ef=-1.,e,ed,a,b,c,xx,yy; 
  if(enr!=ef)
  {
    ef=enr;
    e=enr*rrb;
    if(e<pion) return 0.;
    a=4./e/ff(e)*pia2;
    b=1./(e+w);
    c=mpion*log(d+sqrt(c1*(e-pion)));
  }
  ed=e-(e-pion)*r;
  x=1./ed;
  xx=x*x;
  y=1./(e+pion-ed);
  yy=y*y;
  return a*(xx+yy-b*(x+y)+c*(x*xx+y*yy));
}

float spionp( float enr, float r)
{
  const float mpion=2.*m2*pion*pion;
  static float x,y;
  static float ef=-1.,e,ed,a,b,c; 
  if(enr!=ef)
  {
    ef=enr;
    e=enr*rrb;
    if(e<pion) return 0.;
    x=1./e;
    y=1./pion;
    b=1./(e+w);
    c=mpion*log(d+sqrt(c1*(e-pion)));
    a=.5/(y-x-b*log(y/x)+c*(y*y-x*x));
  }
  ed=pion+(e-pion)*r;
  x=1./ed;
  y=1./(e+pion-ed);
  return .5+a*(y-x-b*log(y/x)+c*(y*y-x*x));
}

float spionr(int kit,float e,float p)
{
  static float r0,r1,r;
  r0=0.;
  r1=1.;
  for(int k=1;k<=kit;k++)
  {
    r=(r0+r1)*.5;
    if(spionp(e,r)<p)r0=r;
    else r1=r;
  }
  return (r0+r1)*.5;
}

