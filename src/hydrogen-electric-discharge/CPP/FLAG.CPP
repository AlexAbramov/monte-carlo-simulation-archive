#include <flag.h>

TFlag flag;

TFlag::TFlag()
{
  anisotrop=true;	// true - anisotrop elastic collision, false - isotrop
  disablemin=false;// true - remove slow electrons (e<pex) from negative glow, false - don't remove
  electron=false;
  field=false;
  text=false;
  density=false;
  energy=false;
  vdr=false;
  vel=false;
  ee=false;
  er=false;
  fel=false;
  fex=false;
  fio=false;
  fre=false;
  fre1=false;
  opened=false;
  saved=false;
  run=false;
}
