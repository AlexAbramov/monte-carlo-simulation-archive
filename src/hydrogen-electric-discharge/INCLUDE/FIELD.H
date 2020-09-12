// Two-dimensional electric field ( x-component )
// Stationary case
// Abramov A.A., 1997

#ifndef __FIELD_H
#define __FIELD_H

#ifndef __MYLIB_H
  #include <mylib.h>
#endif

class TField
{
  protected:
	 TDoubleArray ff;
	 int status;
	 void Control();
  public:
	 int Status(){ return status;}
	 TField(){ status=0;}
	 ~TField(){}
	 void Init();// from param
	 float Get(int,int);// return ff[j][i]; args: j,i
	 float Get(float,int);// return ff[y][i]; args: y,i
	 TDoubleArray & GetField(){ return ff;}
};

extern TField field;// use Init() for object initialization

#endif
