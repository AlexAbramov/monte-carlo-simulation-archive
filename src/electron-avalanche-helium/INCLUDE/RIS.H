// Particle's traectories painting
// Abramov A.A., 1997

#ifndef __RIS_H
#define __RIS_H

#if !defined(OWL_DC_H)
  #include <owl\dc.h>
#endif
#ifndef __PARTICLE_H
  #include <particle.h>
#endif

class TRis
{
  protected:
	 // keeping data:
	 int d,d1,i0,j0,smin;
	 int r1,r2,r3,r4,r5,r6;
	 // calculate by InitDC method:
	 TDC* pdc;
	 HWND hwnd;
	 BOOL painted;
	 TRect rect;
	 int lx,ly;
	 float rx,ry;
	 // others:
	 void Control();
	 int i,j;
	 int flag_ris;
  public:
    BOOL Painted(){return painted;}
	 TRis(char*);
	 void Init(TDC* _pdc,HWND _hwnd){pdc=_pdc; hwnd=_hwnd;}
	 void Update(TRect& _rect);
	 void Paint();
	 void Destroy(){ pdc=0; flag_ris=0; hwnd=0;}
	 void Clear();
	 void Move(float,float);
	 void Line(float,float,step_result);
};

extern TRis risel;// use Setup() for initialization

#endif
