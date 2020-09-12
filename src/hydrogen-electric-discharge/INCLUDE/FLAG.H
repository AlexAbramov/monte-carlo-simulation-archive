// Flag structure
// Abramov A.A., 1997

#ifndef __FLAG_H
#define __FLAG_H

#if !defined( CLASSLIB_DEFS_H )
  #include <classlib\defs.h>
#endif

class TFlag
{
  public:
	 bool anisotrop;
	 bool disablemin;
	 bool electron;
	 bool field;
	 bool text;
	 bool density;
	 bool energy;
	 bool vel;
	 bool vdr;
	 bool evx;
	 bool ee;
	 bool er;
	 bool fel;
	 bool fex;
	 bool fio;
	 bool fre;
	 bool fre1;
	 bool opened;
	 bool saved;
	 bool run;
	 TFlag();
};

extern TFlag flag;

#endif
