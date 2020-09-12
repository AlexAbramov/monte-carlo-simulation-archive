#include<flag.h>

TFlag flag;

TFlag::TFlag()
{
  anisotrop=1;
  disablemin=1;//1 - delete slow electrons 
  electron=0;
  field=0;
  text=0;
  energy=0;
  vdr=0;
  evx=0;
  fex=0;
  fio=0;
  fre=0;
  fre1=0;
  opened=0;
  saved=0;
  run=0;
  hc=0;//hollow cathode
}



