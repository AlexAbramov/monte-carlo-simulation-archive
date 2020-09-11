// Monte-Carlo particle
// ( for time model )
// Abramov A.A., 1997, april

#ifndef __PARTICLE_H
#define __PARTICLE_H

enum particle_event//event witch may be with particle after Step()
{
  NORMAL_PARTICLE,
  NULL_COLLISION,
  REAL_COLLISION,
  PARTICLE_OUT
};

enum particle_out
{
  PARTICLE_LEFT,
  PARTICLE_RIGHT,
  PARTICLE_UP,
  PARTICLE_DOWN,
  PARTICLE_END
};

struct step_result// info about particle state after step
{
  particle_event event;
  particle_out out;
  int rctype;// real collision type (determinate in derived classes)
  int ptype;// particle type (determinate in derived classes)
};

extern step_result result;

class TParticle
{
  private:
	 void InitSs();
	 void Collision(float);
	 void NullCollision();
	 void Step1();
  protected:
	 int normal,i;
	 float dt;
	 float x,y;
	 float vx,vy,er;// velosity x- and y- proections, radial energy[eV]
	 float ss,sss;
	 void RandomVy();// set random vy by fixed er
	 void Step(float,float);// args: charge and mass in electron units
	 virtual void RealCollision(float)=0;
	 virtual float Ftot1(float)=0;// collision frequance
  public:
	 void Init(int,int,float,float,float,float,float,float);// args: normal,i,dt,x,y,vx,vy,er
	 void Init(float,float,float,float,float,float);// args: time,x,y,vx,vy,er
	 void Init(TParticle&);
	 float GetI(){ return i;}
	 float GetVx(){ return vx;}
	 float GetX(){return x;}
	 float GetY(){ return y;}
	 float GetTime();
	 float Energy();// energy[eV]=er+vx*vx
	 int IsOut();// is particle out box ?
	 virtual void Step()=0;
};

#endif
