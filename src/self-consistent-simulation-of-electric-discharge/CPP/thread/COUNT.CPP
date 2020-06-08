#include <string.h>
#include <count.h>
#include "discharge.h"

TCount count;

TCount::TCount()
{
  FILE * fp=handle_scan("data");
  fscanf(fp,"%f",&time);
  if(time<=0.)
  {
	 status=0;
	 return;
  }
  fscanf(fp,"%i",&size);
  if(size<1) error_message("error size in file 'data'");
  rr.Init(size);
  for(int i=0;i<size;i++)
  {
	 float r;
	 if(fscanf(fp,"%f",&r))
	 {
		if( r<=0. || r>1000000.) error_message("error resist in file 'data'");
		rr[i]=r;
	 }
	 else error_message("Error reading from file 'data'");
  }
  nomer=0;
  status=1;
}

void
TCount::Update()
{
  if(status!=1) return;
  char ss[20];
  Control();
  sprintf(ss,"%i.sms",nomer);
  discharge.Write(ss);
  nomer++;
  if(nomer<size)
  {
	 param.resist=rr[nomer];
	 param.time=0.;
//	 ( (TMyClient*) GetApplication()->GetMainWindow()->GetClientWindow() )->CmRun();
  }
  else exit();
}

void
TCount::Control()
{
  int found=0;
  for(int i=0;i<size;i++)
  {
	 if(param.resist==rr[i])
	 {
		nomer=i;
		found=1;
		break;
	 }
  }
  if(found==0) error_message("TCount::Control()");
}

