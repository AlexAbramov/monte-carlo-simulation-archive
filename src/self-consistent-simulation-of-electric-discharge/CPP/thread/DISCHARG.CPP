#pragma hdrstop
#include <mylib.h>
#include <param.h>
#include <field.h>
#include <elans.h>
#include <ris.h>
#include <tstat.h>
#include "discharg.h"

TDischarge discharge;

TDischarge::TDischarge()
{
  status=0;
}

void
TDischarge::Scan()
{
  param.Scan();
  field.Init();
  tstat.Init();
  status=1;
}

void
TDischarge::Read(char* filename)
{
  int id=handle_read(filename);
  param.Read(id);
  field.Init();
  tstat.Init();
  field.Read(id);
  tstat.Read(id);
  close(id);
  status=1;
}

void
TDischarge::Write(char* filename)
{
  Control();
  int id=handle_write(filename);
  param.Write(id);
  field.Write(id);
  tstat.Write(id);
  close(id);
}

void
TDischarge::Control()
{
  if(status==0) error_message("status=0 in TDischarge");
}

void TDischarge::Step()
{
  Control();
  field.Step();
  tstat.Step();
  elans.Step();
}
