// Electron
// Abramov A.A., 1997

#ifndef __ELECTRON_H
#define __ELECTRON_H

#ifndef __PARTICLE_H
  #include<particle.h>
#endif

enum electron_event
{
  ELECTRON=100,
  ELECTRON_ELASTIC,
  ELECTRON_EXCITED,
  ELECTRON_IONISING
};

class TElectron: public TParticle
{
  protected:
	 void ElasticCollision();
	 void ExcitedCollision();
	 void IonisingCollision();
	 virtual void RealCollision(float);
	 virtual float Ftot(float);
// Added methods
	 void HeCollision(float);
	 void CdCollision(float);
	 void CdElasticCollision();
	 void CdExcitedCollision();
	 void CdIonisingCollision();
  public:
	 virtual void Step();
};

extern TElectron bufferElectron;

#endif
