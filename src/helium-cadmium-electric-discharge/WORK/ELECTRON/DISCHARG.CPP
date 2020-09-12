#include <mylib.h>
#include <param.h>
#include <field.h>
#include <elstat.h>
#include <elans.h>
#include <ris.h>
#include "discharg.h"

TDischarge discharge;

TDischarge::TDischarge()
{
  status=0;
//  flag.anisotrop=0;
}

void
TDischarge::Scan()
{
  param.Scan();
  elstat.Init();
  field.Init();
  status=1;
}

void
TDischarge::Read(char* filename)
{
  int id=handle_read(filename);
  param.Read(id);
  elstat.Init();
  elstat.Read(id);
  close(id);
  field.Init();
  status=1;
}

void
TDischarge::Write(char* filename)
{
  Control();
  int id=handle_write(filename);
  param.Write(id);
  elstat.Write(id);
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
  elans.Step();
  param.Step();
}
