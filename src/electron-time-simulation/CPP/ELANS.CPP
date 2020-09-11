#include<math.h>
#pragma hdrstop
#include<mylib.h>
#include<ris.h>
#include<random.h>
#include<param.h>
#include<flag.h>
#include<elstat.h>
#include<elans.h>

TElectronAnsamble elans;

TElectronAnsamble::TElectronAnsamble(int _size)
{
  size=_size;
  number=0;
  long int s=size*sizeof(TElectron);
  if(s>64000L) error_message("size is too large in TElectronAnsamble::TElectronAnsamble");
  if(size<1) error_message("size is too small in TElectronAnsamble::TElectronAnsamble");
  pp=new TElectron[size];
  if(pp==0) error_message("No allocate in TElectronAnsamble::TElectronAnsamble");
}

TElectronAnsamble::~TElectronAnsamble()
{
  delete pp;
}

void
TElectronAnsamble::Step()
{
  if(flag.electron) risel.Clear();
  number=1;
  float x=param.xem;
  float y=param.ly*.5;
  pp[0].Init(0.,x,y,1.,.1,1.);

  while(number>0)
  {
	 TElectron * ptr=pp+number-1;
	 if(flag.electron) risel.Move(ptr->GetX(),ptr->GetY());
	 ptr->Step();
	 if(result.event==NORMAL_PARTICLE) elstat.Count(ptr->GetI(),ptr->GetVx(),ptr->Energy());
	 if(flag.electron) risel.Line(ptr->GetX(),ptr->GetY(),result);
	 if(result.event==PARTICLE_OUT) number--;
	 if(result.event==REAL_COLLISION&&
	 result.rctype==ELECTRON_IONISING)
	 {
		number++;
		if(number>size) error_message("Overflow in TElectron::Step");
		ptr=pp+number-1;
		ptr->Init(bufferElectron);
	 }
  }
}
