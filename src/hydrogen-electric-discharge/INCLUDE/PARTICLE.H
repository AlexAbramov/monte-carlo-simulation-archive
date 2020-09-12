// Monte-Carlo particle
// Abramov A.A., 1997

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
  PARTICLE_DISABLE,
};

struct step_result// info about particle state after step
{
  float time;// time of particle step[mksec]
  float dx;// dx step [sm]
  float dy;// dy step [sm]
  float s;// way [sm]
  float sx;// x_way [sm]
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
	 float Move(float,float&,float&);
	 void Collision(float);
	 void NullCollision();
	 void SetResult(float,float,float,float);
	 void SetResult(float);
	 void Step1();
  protected:
	 float time;
	 int normal,i;
	 float dx,y;
	 float vx,vy,er;// velosity x- and y- proections, radial energy[eV]
	 float ss,sss;
	 void RandomVy();// set random vy by fixed er
	 void Step(float,float);// args: charge and mass in electron units
	 virtual void RealCollision(float)=0;
	 virtual float Ftot(float)=0;// collision frequance
  public:
	 void Init(int,int,float,float,float,float,float);// args: normal,i,dx,y,vx,vy,er
	 void Init(float,float,float,float,float);// args: x,y,vx,vy,er
	 void Init(TParticle&);
	 float GetI(){ return i;}
	 float GetVx(){ return vx;}
	 float GetX();// return x coord of particle
	 float GetY(){ return y;}
	 float GetTime(){ return time;}
	 float Energy();// energy[eV]=er+vx*vx
	 int IsOut();// is particle out box ?
	 virtual void Step()=0;
};

#endif
