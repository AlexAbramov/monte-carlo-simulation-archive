// Class of gas discharge parameters
// Abramov A.A., 1997

#ifndef __PARAM_H
#define __PARAM_H

#ifndef __MYLIB_H
  #include <mylib.h>
#endif

#ifndef __CSTRING_H
  #include <cstring.h>
#endif

#ifndef __ELSTAT_H
  #include <elstat.h>
#endif

class TParam
{
  protected:
	 string path;
	 int status;
  public:
// data keeping in text file
	 int xsize;
	 int ysize;
	 float lx;
	 float ly;
	 float voltage;
	 float dk;// length of cathode falling region [sm]
	 float fd;// electric field in negative glow [V/sm]
	 int   esize;
	 float de;
	 float xem;
	 int msize;
	 float xm;
	 int tsize;
	 float dt;
	 float dl;
	 int nshow;
// derived, init by Update method:
	 float dx;
	 float dy;
	 float emax;
	 float rde;
#ifdef __MAXPARAM
	 int im;
#endif
	 void Update();
//  init by Step()
	 long int nlav;// number of electron avalanches
	 void Step(){nlav++;}
// constructor
	 TParam();
	 ~TParam();
// methods
	 void Scan();// from text file
	 void Print(FILE * fp=0);// to text file
	 void Read(int);// from binary file
	 void Write(int);// to binary file
	 int Status(){ return status;}
	 void RegistrateDirectory(string);
};

extern TParam param; // use Scan() and Read() for initialization

#endif
