#include<math.h>
#pragma hdrstop
#include<param.h>
#include<flag.h>
#include<mylib.h>
#include<random.h>
#include<particle.h>

#define FIELD_MIN .1

#define KOEFV 59.3
#define KOEFA 29.65

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
TParticle::GetTime()
{
  if(normal==1) return i*param.dt;
  else return dt+i*param.dt;
}

void
TParticle::Init(TParticle& p)
{
  normal=p.normal;
  i=p.i;
  dt=p.dt;
  x=p.x;
  y=p.y;
  vx=p.vx;
  vy=p.vy;
  er=p.er;
  ss=p.ss;
  sss=p.sss;
}

void
TParticle::Init(int _normal,int _i,float _dt,float _x,float _y,float _vx,float _vy,float _er)
{
  normal=_normal;
  i=_i;
  dt=_dt;
  x=_x;
  y=_y;
  vx=_vx;
  vy=_vy;
  er=_er;
  InitSs();
}

void
TParticle::Init(float _t,float _x,float _y,float _vx,float _vy,float _er)
{
  i=_t/param.dt;
  if(i<0||i>=param.tsize) error_message("TParticle::Init (i out range)");
  dt=_t-i*param.dt;
  if(dt<0||dt>=param.dt) error_message("TParticle::Init (dt out range)");
  if(dt==0.) normal=1;
  else normal=0;
  x=_x;
  y=_y;
  vx=_vx;
  vy=_vy;
  er=_er;
  InitSs();
}

void
TParticle::Step(float charge,float mass)
{
  float f=param.fd;
  if(fabs(f)<FIELD_MIN)
  {
	 Step1();
	 return;
  }
  f*=charge;
  float a=KOEFA*f/mass;

  float e=Energy();
  float ddt;
  if(normal==1) ddt=param.dt;
  else ddt=param.dt-dt;
  float vx1=vx+a*ddt;
  float e1=er+vx1*vx1;
  float ftotmax=fmax(Ftot1(e),Ftot1(e1));
  float ss1=ss+ftotmax*ddt;
  if(ss1<sss)//no collision
  {
	 normal=1;
	 ss=ss1;
	 i++;
	 dt=0.;
  }
  else//collision
  {
	 normal=0;
	 vx1=vx+(sss-ss)*a/ftotmax;
	 ddt=(vx1-vx)/a;
	 dt+=ddt;
	 if(dt>param.dt) error_message("dt overflow in TParticle::Step()");
  }
  y+=KOEFV*vy*ddt;
  vx=vx1;
  e1=Energy();
  x+=(e1-e)/f;

  if(IsOut()==0)
  {
	 if(normal==1)	result.event=NORMAL_PARTICLE;
	 else Collision(ftotmax);
  }
}

void
TParticle::Step1()
{
  float e=Energy();
  float ftot=Ftot1(e);
  float ddt;
  if(normal==1) ddt=param.dt;
  else ddt=param.dt-dt;
  float ss1=ss+ftot*ddt;
  if(ss1<sss)//no collision
  {
	 normal=1;
	 ss=ss1;
	 i++;
	 dt=0.;
  }
  else//collision
  {
	 normal=0;
	 ddt=(sss-ss)/ftot;
	 dt+=ddt;
	 if(dt>param.dt) error_message("dt overflow in TParticle::Step1()");
  }
  y+=KOEFV*vy*ddt;
  x+=KOEFV*vx*ddt;

  if(IsOut()==0)
  {
	 if(normal==1)	result.event=NORMAL_PARTICLE;
	 else
	 {
		RealCollision(rnd[2]);
		InitSs();
	 }
  }
}

void
TParticle::Collision(float ftotmax)
{
  float e=Energy();
  float r1=Ftot1(e)/ftotmax;
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
//  if(y<0.){ index=1; result.out=PARTICLE_DOWN;}
//  if(y>param.ly){ index=1; result.out=PARTICLE_UP;}
  if(y<0.){ y=-y; vy=-vy;}
  if(y>param.ly){ y=param.ly+param.ly-y; vy=-vy;}
  if(x<0.){ index=1; result.out=PARTICLE_LEFT;}
  if(x>param.lx){ index=1; result.out=PARTICLE_RIGHT;}
  if(normal==1&&i>=param.tsize){ index=1; result.out=PARTICLE_END;}
  if(index==1) result.event=PARTICLE_OUT;
  return index;
}


