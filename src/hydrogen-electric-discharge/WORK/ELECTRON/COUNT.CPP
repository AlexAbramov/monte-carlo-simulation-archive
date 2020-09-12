#include <stdio.h>
#pragma hdrstop
#include <field.h>
#include <param.h>
#include <elstat.h>
#include "count.h"
#include "discharg.h"

TCount count;

TCount::TCount()
{
  FILE * fp=handle_scan("count.dat");
  fscanf(fp,"%i",&nlavmax); newline(fp);
  fscanf(fp,"%f",&df); newline(fp);
  fscanf(fp,"%f",&fmax); newline(fp);
  if(nlavmax<=1||df<1.||fmax<=1.) status=0;
  else
  {
	 message("There is automatical program mode.");
	 status=1;
  }
}

void
TCount::Update()
{
  if(status!=1) return;
  char tt[20];
  sprintf(tt,"%i.ele",int(param.fd));
  discharge.Write(tt);
  param.fd+=df;
  if(param.fd<=fmax)
  {
	 field.Init();
	 elstat.Init();
	 param.nlav=0;
  }
  else exit(0);
}
