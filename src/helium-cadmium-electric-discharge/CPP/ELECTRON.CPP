#include<math.h>
#pragma hdrstop
#include<mylib.h>
#include<random.h>
#include<he.h>
#include<cd.h>
#include<param.h>
#include<flag.h>
#include<elstat.h>
#include<electron.h>

static const float pi2=M_PI+M_PI;
TElectron bufferElectron;
float prion,prex;

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
  float fcd=cd.Ftot(e);
  float fhe=he.Ftot(e);
  float ftot=fcd+fhe;

  float rftot=1./ftot;
  if(e>he.Pex())
  {
	 prex=he.Fex(e,4)*rftot;// 2s3 level
	 elstat.Add1(i,prex);
  }
  if(e>he.Pion())
  {
	 prion=he.Fion(e)*rftot;
	 elstat.Add2(i,prion);
  }

  float r1=r*ftot;
  if(r1<fhe) HeCollision(r1/fhe);
  else CdCollision((r1-fhe)/fcd);
}

void
TElectron::ElasticCollision()
{
  float e=Energy();
  float angle;
  if( flag.anisotrop ) angle=he.Spelas(e,rnd[10]);//anisotrop collision
  else angle=acos(1.-2.*rnd[10]);//isotrop collision

  // lost electron energy
  const double kk=.000272;// 2.*m(e)/m(he)
  float cosan=cos(angle);
  float kf=1.-kk*(1.-cosan);
  er*=kf;
  vx*=sqrt(kf);
  e=vx*vx+er;

//  float cosan=cos(angle);
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
  elstat.AddNion();
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
  result.rctype=ELECTRON_IONISING;
}

float
TElectron::Ftot(float e)
{
  return he.Ftot(e)+cd.Ftot(e);
}

void
TElectron::HeCollision(float r)
{
  float e=Energy();
  if(e<he.Pex()) ElasticCollision();
  else
  {
	 float rstot=1./he.Stot(e);
	 float d=he.Selas(e)*rstot;
	 if(r<d) ElasticCollision();
	 else
	 {
		if(e<he.Pion()) ExcitedCollision();
		else
		{
		  d+=he.Sion(e)*rstot;
		  if(r<d)IonisingCollision();
		  else ExcitedCollision();
		}
	 }
  }
}

// Added methods
void
TElectron::CdCollision(float r)
{
  float e=Energy();
  if(e<cd.Pex()) CdElasticCollision();
  else
  {
	 float rstot=1./cd.Stot(e);
	 float d=cd.Selas(e)*rstot;
	 if(r<d) CdElasticCollision();
	 else
	 {
		if(e<cd.Pion()) CdExcitedCollision();
		else
		{
		  d+=cd.Sion(e)*rstot;
		  if(r<d)CdIonisingCollision();
		  else CdExcitedCollision();
		}
	 }
  }
}

void
TElectron::CdElasticCollision()
{
  float e=Energy();
  float angle;
//  if( flag.anisotrop ) angle=he.Spelas(e,rnd[10]);//anisotrop collision
//  else angle=acos(1.-2.*rnd[10]);//isotrop collision
  angle=acos(1.-2.*rnd[10]);//isotrop collision

  // lost electron energy
  const double kk=.000011;// 2.*m(e)/m(Cd)
  float cosan=cos(angle);
  float kf=1.-kk*(1.-cosan);
  er*=kf;
  vx*=sqrt(kf);
  e=vx*vx+er;

//  float cosan=cos(angle);
  vx=vx*cosan+sqrt(er)*sin(angle)*sin(rnd[11]*pi2);
  er=e-vx*vx;
  if(er<0.) er=0.;// error_message("er<0 in TElectron::Elastic()");
  RandomVy();
  result.rctype=ELECTRON_ELASTIC;
}

void
TElectron::CdExcitedCollision()
{
  float e=Energy();
  float dex=1.-cd.Pex()/e;// one level
  float sdex=sqrt(dex);
  vx*=sdex;
  vy*=sdex;
  er*=dex;
  result.rctype=ELECTRON_EXCITED;
}

void
TElectron::CdIonisingCollision()
{
  float e=Energy();
//  float dio=he.Spion(e,rnd[12]);
  float dio=.1;
//  if(rnd[17]<.5) dio=1.-dio;//!!!!!!
  float k=1.-cd.Pion()/e;
  float k1=k*dio;
  float k2=k-k1;
  float sk1=sqrt(k1);
  float sk2=sqrt(k2);
  bufferElectron.Init(0,i,dx,y,vx*sk2,vy*sk2,er*k2);
  vx*=sk1;
  vy*=sk1;
  er*=k1;
  result.rctype=ELECTRON_IONISING;
}
