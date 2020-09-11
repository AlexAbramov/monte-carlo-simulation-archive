// Painting particle's traectories
// Abramov A.A., 1997

#ifndef __RIS_H
#define __RIS_H

#if !defined(OWL_DC_H)
  #include<owl\dc.h>
#endif
#ifndef __PARTICLE_H
  #include<particle.h>
#endif

class TRis
{
  protected:
	 // keeping data
	 int d,d1,i0,j0,smin;
	 int r1,r2,r3,r4,r5,r6;
	 // calculate by InitDC()
	 TDC* pdc;
	 int lx,ly;
	 float rx,ry;
	 // ather
	 void Control();
	 int i,j;
	 int flag_ris;
  public:
	 TRis(char*);
	 void Setup(TDC*);
	 void Update();
	 void Destroy(){ pdc=0; flag_ris=0;}
	 void Clear();
	 void Move(float,float);
	 void Line(float,float,step_result);
};

extern TRis risel;// use Setup() for inicialization

#endif
