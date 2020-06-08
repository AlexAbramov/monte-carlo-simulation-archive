#pragma hdrstop
#include <math.h>
#include <mylib.h>
#include <ris.h>
#include <he.h>
#include <myrandom.h>
#include <param.h>
#include <flag.h>
#include <field.h>
#include <elans.h>

TElectronAnsamble elans;

TElectronAnsamble::TElectronAnsamble(int _size)
{
  cioIn=0.;
  size=_size;
  number=0;
  pp=new TElectron[size];
  if(pp==0) error_message("Couldn't allocate memory (ElectronEnsemble)");
}

TElectronAnsamble::~TElectronAnsamble()
{
  delete pp;
}

void
TElectronAnsamble::Step()
{
  flag.step=true;
  cioIn=0.;
  bool paint=flag.electron;
  if(paint) risel.Clear();

  for(int j=0;j<param.ysize;j++)
  {

  number=1;
  float x=0.;
  float y=param.dy*(j+.5);
  pp[0].Init(x,y,1.,.1,1.);

  while(number>0)
  {
	 TElectron * ptr=pp+number-1;
	 if(paint) risel.Move(ptr->GetX(),ptr->GetY());
	 ptr->Step();

	 if(result.event==REAL_COLLISION)
	 {
		if(prion>0.)
		{
		  float dcio=field.GetBuf(j)*field.Gamma(j)*prion;
		  cioIn+=dcio;
		  field.CioAdd(ptr->GetI(),ptr->GetY(),dcio);
		}
	 }

	 if(paint) risel.Line(ptr->GetX(),ptr->GetY(),result);
	 if(result.event==PARTICLE_OUT) number--;
	 if(result.event==REAL_COLLISION&&
	 result.rctype==ELECTRON_IONIZED)
	 {
		number++;
		if(number>size) error_message("Overflow in TElectron::Step");
		ptr=pp+number-1;
		ptr->Init(bufferElectron);
	 }
  }

  }
  flag.step=false;
  if(paint) risel.Paint();
}
