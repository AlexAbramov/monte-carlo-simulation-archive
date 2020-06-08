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
	 bool cio;
	 bool buf;
	 bool text;
	 bool param;
	 bool opened;
	 bool saved;
	 bool run;
	 bool gamma;
	 bool current;
	 bool voltage;
    bool step;
	 TFlag();
};

extern TFlag flag;

#endif
