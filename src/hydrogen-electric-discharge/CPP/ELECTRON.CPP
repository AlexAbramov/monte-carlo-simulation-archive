#include <math.h>
#pragma hdrstop
#include <mylib.h>
#include <myrandom.h>
#include <hydrogen.h>
#include <param.h>
#include <flag.h>
#include <electron.h>

static const float pi2=M_PI+M_PI;

TElectron bufferElectron;

void
TElectron::Step()
{
  TParticle::Step(1.,1.);
  result.ptype=ELECTRON;
}

void
TElectron::RealCollision(float r)// r{0,1}
{
  float e=Energy();
  if(e<hydrogen.Pex()) ElasticCollision();
  else
  {
	 float rstot=1./hydrogen.Stot(e);
	 float d=hydrogen.Selas(e)*rstot;
	 if(r<d) ElasticCollision();
	 else
	 {
		if(e<hydrogen.Pion()) ExcitedCollision();
		else
		{
		  d+=hydrogen.Sex(e)*rstot;
		  if(r<d) ExcitedCollision();
		  else IonizedCollision();
		}
	 }
  }
}

void
TElectron::ElasticCollision()
{
  float e=Energy();
  float angle;
  if( flag.anisotrop ) angle=hydrogen.Spelas(e,rnd[10]);//anisotrop collision
  else angle=acos(1.-2.*rnd[10]);//isotrop collision

  // lost electron energy
  const double kk=.00007;// 2.*m(e)/m(hydrogen)
  float cosan=cos(angle);
  float kf=1.-kk*(1.-cosan);
  er*=kf;
  vx*=sqrt(kf);
  e=vx*vx+er;

  vx=vx*cosan+sqrt(er)*sin(angle)*sin(rnd[11]*pi2);
  er=e-vx*vx;
  if(er<0.) er=0.;
  RandomVy();
  result.rctype=ELECTRON_ELASTIC;
}

void
TElectron::ExcitedCollision()
{
  float e=Energy();
  float dex=1.-hydrogen.Pex()/e;// one level
  float sdex=sqrt(dex);
  vx*=sdex;
  vy*=sdex;
  er*=dex;
  result.rctype=ELECTRON_EXCITED;
}

void
TElectron::IonizedCollision()
{
  float e=Energy();
  float dio=hydrogen.Spion(/*e,rnd[12]*/);
//  if(rnd[17]<.5) dio=1.-dio;
  float k=1.-hydrogen.Pion()/e;
  float k1=k*dio;
  float k2=k-k1;
  float sk1=sqrt(k1);
  float sk2=sqrt(k2);
  bufferElectron.Init(0,i,dx,y,vx*sk2,vy*sk2,er*k2);
  vx*=sk1;
  vy*=sk1;
  er*=k1;
  result.rctype=ELECTRON_IONIZED;
}

float
TElectron::Ftot(float e)
{
  return hydrogen.Ftot(e);
}
