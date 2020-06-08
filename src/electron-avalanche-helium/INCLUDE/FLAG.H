// Flag structure
// Abramov A.A., 1997

#ifndef __FLAG_H
#define __FLAG_H

class TFlag
{
  public:
	 int anisotrop;
	 int disablemin;
	 int electron;
	 int field;
	 int text;
	 int density;
	 int energy;
	 int vel;
	 int vdr;
	 int evx;
	 int ee;
	 int er;
	 int fel;
	 int fex;
	 int fio;
	 int fre;
	 int fre1;
	 int opened;
	 int saved;
	 int run;
	 TFlag();
};

extern TFlag flag;

#endif
