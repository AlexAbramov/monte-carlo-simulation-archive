#pragma hdrstop
#include <param.h>
#include <field.h>

TField field;

void
TField::Control()
{
  if(status==0) error_message("TField::Control()");
}

void
TField::Init()
{
  if(param.Status()==0) error_message("TField::Init()");
  ff.Init(param.ysize,param.xsize);

// Field inicialization

  if(param.voltage<=1. || param.dk<=0. || param.dk>=param.lx)
  {
	 ff+=param.fd;
  }
  else
  {
	 for(int i=0;i<param.xsize;i++)
	 {
		float x=i*param.lx/(param.xsize-1.);
		float f=(param.voltage+param.voltage)*(1.-x/param.dk);
		if(f<param.fd) f=param.fd;
		for(int j=0;j<param.ysize;j++) ff[j][i]=f;
	 }
  }
  status=1;
}

float
TField::Get(int j,int i)
{
  Control();
  return ff[j][i];
}

float
TField::Get(float y,int i)
{
  Control();
  int j=y/param.dy;
  return ff[j][i];
}
