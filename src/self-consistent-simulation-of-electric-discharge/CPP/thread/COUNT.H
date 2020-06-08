// Count
// Abramov A.A., 1997

#ifndef __COUNT_H
#define __COUNT_H

#ifndef __MYLIB_H
  #include <mylib.h>
#endif

const int ssize=50;

class TCount
{
  protected:
	 char fstring[ssize];
	 float time;
	 int size;
	 TSingleArray rr;
	 int status;
	 int nomer;
	 void Control();
  public:
	 int Status(){return status;}
	 TCount();
	 float GetFirst(){ return rr[0];}
	 void Update();
	 float Time(){return time;}
};

extern TCount count;

#endif