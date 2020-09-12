#include <math.h>
#pragma hdrstop
#include <mylib.h>
#include <ris.h>
#include <myrandom.h>
#include <param.h>
#include <flag.h>
#include <elstat.h>
#include <elens.h>

TElectronEnsemble elens;

TElectronEnsemble::TElectronEnsemble(int _size)
{
  size=_size;
  number=0;
  if(size<1) error_message("size is too small in TElectronEnsemble::TElectronEnsemble");
  pp=new TElectron[size];
  if(pp==0) error_message("No allocate in TElectronEnsemble::TElectronEnsemble");
}

TElectronEnsemble::~TElectronEnsemble()
{
  delete pp;
}

void
TElectronEnsemble::Step()
{
  if(flag.electron) risel.Clear();
  number=1;
  float x=param.xem;
  float y=param.ly*rnd[30];
  pp[0].Init(x,y,1.,.1,1.);
#ifdef __MAXPARAM
  float count_time=0.;
  float count_s=0.;
  float count_sx=0.;
  float count_x=0.;
#endif

  while(number>0)
  {
	 TElectron * ptr=pp+number-1;
	 if(flag.electron) risel.Move(ptr->GetX(),ptr->GetY());

	 ptr->Step();

#ifdef __MAXPARAM
	 elstat.total_time+=result.time;
	 elstat.total_s+=result.s;
	 elstat.total_sx+=result.sx;
	 elstat.total_x+=result.dx;
	 count_time+=result.time;
	 count_s+=result.s;
	 count_sx+=result.sx;
	 count_x+=result.dx;
#endif
	 if(result.event==NORMAL_PARTICLE) elstat.Count(ptr->GetI(),ptr->GetVx(),ptr->Energy());
	 if(flag.electron) risel.Line(ptr->GetX(),ptr->GetY(),result);
	 if(result.event==PARTICLE_OUT)
	 {
		number--;
#ifdef __MAXPARAM
		count_time=0.;
		count_s=0.;
		count_sx=0.;
		count_x=0.;
#endif
	 }
	 if(result.event==REAL_COLLISION&&
	 result.rctype==ELECTRON_IONIZED)
	 {
#ifdef __MAXPARAM
		elstat.total_nion+=1.;
		elstat.Add(count_time,count_s,count_sx,count_x);
		count_time=0.;
		count_s=0.;
		count_sx=0.;
		count_x=0.;
#endif
		number++;
		if(number>size) error_message("Overflow in TElectron::Step");
		ptr=pp+number-1;
		ptr->Init(bufferElectron);
	 }
  }
}
