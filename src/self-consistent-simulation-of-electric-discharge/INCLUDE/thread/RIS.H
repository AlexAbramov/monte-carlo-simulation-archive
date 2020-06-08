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
	 TMemoryDC* pdc;
	 TClientDC* cdc;
	 TBitmap* bitmap;
	 void* pwnd;
	 TRect rect;
	 int lx,ly;
	 float rx,ry;
	 // others:
	 bool CanPaint();
	 int i,j;
	 bool needUpdate;
    TRect updateRect;
  public:
	 int flag_ris;
	 bool painted;
	 bool needClose;
	 TRis(char*);
	 void Init(TMemoryDC* _pdc,void * _pwnd,TClientDC* _cdc);
	 void Update(TRect& _rect);
	 void Paint();
	 void Destroy();
	 void Clear();
	 void Move(float,float);
	 void Line(float,float,step_result);
	 void Test(TMemoryDC* dc);
};

extern TRis risel;// use Setup() for initialization

#endif
