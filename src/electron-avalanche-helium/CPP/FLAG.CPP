#pragma hdrstop
#include <flag.h>
 
TFlag flag;

TFlag::TFlag()
{
  anisotrop=1;	// 1 - anisotrop elastic collision, 0 - isotrop
  disablemin=0;// 1 - remove slow electrons (e<pex) from negative glow, 0 - don't remove
  electron=0;
  field=0;
  text=0;
  density=0;
  energy=0;
  vdr=0;
  vel=0;
  ee=0;
  er=0;
  fel=0;
  fex=0;
  fio=0;
  fre=0;
  fre1=0;
  opened=0;
  saved=0;
  run=0;
}
