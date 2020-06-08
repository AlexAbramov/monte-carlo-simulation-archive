#pragma hdrstop
#include <math.h>
#include <mylib.h>
#include <myrandom.h>
#include <he.h>
#include <param.h>
#include <flag.h>
#include <electron.h>

static const float pi2=M_PI+M_PI;
float prion;

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
  prion=0.;

  float e=Energy();
  if(e<he.Pex()) ElasticCollision();
  else
  {
	 float rstot=1./he.Stot(e);

	 if(e>he.Pion()) prion=he.Sion(e)*rstot;

	 float d=he.Selas(e)*rstot;
	 if(r<d) ElasticCollision();
	 else
	 {
		if(e<he.Pion()) ExcitedCollision();
		else
		{
//		  d+=he.Sex(e)*rstot;
//		  if(r<d) ExcitedCollision();
//		  else IonisingCollision();
		  d+=prion;
		  if(r<d)IonisingCollision();
		  else ExcitedCollision();
		}
	 }
  }
}

void
TElectron::ElasticCollision()
{
  float e=Energy();
  float angle;
  if( flag.anisotrop ) angle=he.Spelas(e,rnd[10]);//anisotrop collision
  else angle=acos(1.-2.*rnd[10]);//isotrop collision
  float cosan=cos(angle);
  vx=vx*cosan+sqrt(er)*sin(angle)*sin(rnd[11]*pi2);
  er=e-vx*vx;
  if(er<0.) er=0.;// error_message("er<0 in TElectron::Elastic()");
  RandomVy();
  result.rctype=ELECTRON_ELASTIC;
}

void
TElectron::ExcitedCollision()
{
  float e=Energy();
  float dex=1.-he.Pex()/e;// one level
  float sdex=sqrt(dex);
  vx*=sdex;
  vy*=sdex;
  er*=dex;
  result.rctype=ELECTRON_EXCITED;
}

void
TElectron::IonisingCollision()
{
  float e=Energy();
  float dio=he.Spion(e,rnd[12]);
//  if(rnd[17]<.5) dio=1.-dio;//!!!!!!
  float k=1.-he.Pion()/e;
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
  return he.Ftot(e);
}
