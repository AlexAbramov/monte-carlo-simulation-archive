#pragma hdrstop
#include <math.h>
#include <param.h>
#include <flag.h>
#include <field.h>
#include <mylib.h>
#include <myrandom.h>
#include <particle.h>

#define FIELD_MIN .1 // the value of electric field in negative glow when we can neglect the electron acceleration

static const float pi2=M_PI+M_PI;
step_result result;

void
TParticle::InitSs()
{
  ss=0.;
  sss=-log(rnd[0]);
}

float
TParticle::Energy()
{
  return vx*vx+er;
}

void
TParticle::RandomVy()
{
  vy=sqrt(er)*cos(pi2*rnd[1]);
}

float
TParticle::GetX()
{
  if(normal==1) return i*param.dx;
  else return dx+i*param.dx;
}

void
TParticle::Init(TParticle& p)
{
  normal=p.normal;
  i=p.i;
  dx=p.dx;
  y=p.y;
  vx=p.vx;
  vy=p.vy;
  er=p.er;
  ss=p.ss;
  sss=p.sss;
  time=0.;
}

float
TParticle::Move(float f,float& ddx,float& vvx)
{
  float e=Energy();
  float e1=e+f*(param.dx-ddx);
  float ftot,vx1,dx1;
  float a=f*.5;
  if(e1>er)
  {
	 ftot=Ftot(e);
	 vx1=sqrt(e1-er);
	 dx1=param.dx;
  }
  else// return
  {
	 e1=e-f*ddx;
	 ftot=Ftot(er);
	 vx1=-sqrt(e1-er);
	 dx1=0.;
  }
  float ftotmax=fmax(ftot,Ftot(e1));
  float ss1=ss+ftotmax*(vx1-vvx)/a;
  if(ss1<sss)// no collision
  {
	 normal=1;
	 ss=ss1;
  }
  else// collision
  {
	 normal=0;
	 vx1=vvx+(sss-ss)*a/ftotmax;
	 e1=er+vx1*vx1;
	 dx1=ddx+(e1-e)/f;
  }
  SetResult(dx1-ddx,vx1,vvx,f);
  vvx=vx1;
  ddx=dx1;
  return ftotmax;
}

void
TParticle::Step(float charge,float mass)
{
  result.time=.01686*mass;
  float f;
  if(normal==1&&vx<0.) f=field.Get(y,i-1);
  else f=field.Get(y,i);
  if(fabs(f)<FIELD_MIN)
  {
	 if(flag.disablemin)
	 {
		result.event=PARTICLE_OUT;
		result.out=PARTICLE_DISABLE;
		return;
	 }
	 else
	 {
		Step1();
		return;
	 }
  }
  f*=charge;
  int returned=0;
  float ddx;
  if(normal==1&&vx<0.)
  {
	 ddx=0.;
	 returned=1;
  }
  else
  {
	 if(normal==1) ddx=0.;
	 else
	 {
		if(vx>0.) ddx=dx;
		else
		{
		  ddx=param.dx-dx;
		  returned=1;
		}
	 }
  }
  int normal0=normal;
  float vx0=vx;
  float vvx=fabs(vx);
  float fotn;
  if(returned==1) fotn=-f;
  else fotn=f;
  float ftotmax=Move(fotn,ddx,vvx);
  if(returned==1)
  {
	 vx=-vvx;
	 dx=param.dx-ddx;
  }
  else
  {
	 vx=vvx;
	 dx=ddx;
  }
  if(normal0==1&&vx0<0.)
  {
	 if(normal==0) i--;
	 if(normal==1&&vx<0.) i--;
  }
  else if(normal==1&&vx>0.) i++;
  if(IsOut()==0)
  {
	 if(normal==1)
	 {
		result.event=NORMAL_PARTICLE;
		dx=0.;
	 }
	 else Collision(ftotmax);
  }
}

void
TParticle::Step1()
{
  float e=Energy();
  float ftot=Ftot(e);
  float ddx;
  if(normal==1) ddx=param.dx;
  else
  {
	 if(vx>0.) ddx=param.dx-dx;
	 else ddx=dx;
  }
  float ss1=ss+ftot*ddx/fabs(vx);
  if(ss1<sss)// no collision
  {
	 result.event=NORMAL_PARTICLE;
	 if(normal==1&&vx<0.) i--;
	 if(vx>0.) i++;
	 dx=0.;
	 normal=1;
	 ss=ss1;
	 SetResult(ddx);
  }
  else// collision
  {
	 ddx=(sss-ss)*fabs(vx)/ftot;
	 if(normal==1&&vx<0.)
	 {
		i--;
		dx=param.dx-ddx;
	 }
	 else
	 {
		if(vx>0.) dx+=ddx;
		else dx-=ddx;
	 }
	 normal=0;
	 result.event=REAL_COLLISION;
	 SetResult(ddx);
	 RealCollision(rnd[2]);
	 InitSs();
  }
  IsOut();
}

void
TParticle::Collision(float ftotmax)
{
  float e=Energy();
  float r1=Ftot(e)/ftotmax;
  float r=rnd[3];
  if(r<r1)
  {
	 result.event=REAL_COLLISION;
	 RealCollision(r/r1);
  }
  else result.event=NULL_COLLISION;
  InitSs();
}

int
TParticle::IsOut()
{
  int index=0;
//  if(y<0.){ index=1; result.out=PARTICLE_DOWN;}// absorption by wall
//  if(y>param.ly){ index=1; result.out=PARTICLE_UP;}// absorption by wall
  if(y<0.)
  {
	 y=-y;
	 vy=-vy;
	 if(y>=param.ly)// very rare case, but we must count it
	 {
		y=param.ly;
		vy=-fabs(vy);
	 }
  }
  else
  {
	 if(y>param.ly)
	 {
		y=param.ly+param.ly-y;
		vy=-vy;
		if(y<0.)// very rare case, but we must count it
		{
		  y=0.;
		  vy=fabs(vy);
		}
	 }
  }
  if(normal==1&&i==0&&vx<0.){ index=1; result.out=PARTICLE_LEFT;}
  if(i<0){ index=1; result.out=PARTICLE_LEFT;}
  if(i>=param.xsize){ index=1; result.out=PARTICLE_RIGHT;}
  if(index==1) result.event=PARTICLE_OUT;
  return index;
}

void
TParticle::Init(int _normal,int _i,float _dx,float _y,float _vx,float _vy,float _er)
{
  normal=_normal;
  i=_i;
  dx=_dx;
  y=_y;
  vx=_vx;
  vy=_vy;
  er=_er;
  InitSs();
  time=0.;
}

void
TParticle::Init(float _x,float _y,float _vx,float _vy,float _er)
{
  i=_x/param.dx;
  if(i<0||i>=param.xsize) error_message("TParticle::Init (i out range)");
  dx=_x-i*param.dx;
  if(dx<0||dx>=param.dx) error_message("TParticle::Init (dx out range)");
  if(dx==0.) normal=1;
  else normal=0;
  y=_y;
  vx=_vx;
  vy=_vy;
  er=_er;
  InitSs();
  time=0.;
}

void
TParticle::SetResult(float ddx,float vx1,float vx0,float f)
{
  float rf=1./fabs(f);

  float t=2.*fabs(vx1-vx0)*rf;
  time+=result.time;
  result.time*=t;

  if(vx>0.) result.dx=ddx;
  else result.dx=-ddx;

  float dy=vy*t;
  y+=dy;
  result.dy=dy;

  float ex0=vx0*vx0;
  float ex1=vx1*vx1;
  float v0=sqrt(ex0+er);
  float v1=sqrt(ex1+er);

  if(vx>0) result.s=(vx1*v1-vx0*v0+er*log((v1+vx1)/(v0+vx0)))*rf;
  else    result.s=(-vx1*v1+vx0*v0+er*log((v1-vx1)/(v0-vx0)))*rf;

  if(vx1>0.) result.sx=fabs(ddx);
  else
  {
	 result.sx=(ex0+ex1)*rf;
  }
}

void
TParticle::SetResult(float ddx)
{
  float t=fabs(ddx/vx);
  time+=result.time;
  result.time*=t;

  if(vx>0.) result.dx=ddx;
  else result.dx=-ddx;

  float dy=vy*t;
  y+=dy;
  result.dy=dy;

  result.s=sqrt(Energy())*t;

  result.sx=ddx;

}
