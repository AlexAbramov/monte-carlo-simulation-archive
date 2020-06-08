#pragma hdrstop
#include <flag.h>

TFlag flag;

TFlag::TFlag()
{
  anisotrop=true;
  disablemin=true;
  electron=false;
  field=false;
  buf=false;
  cio=false;
  text=false;
  param=false;
  opened=false;
  saved=false;
  run=false;
  gamma=false;
  current=false;
  voltage=false;
  step=false;
}
