// class of gas discharge parameters
// Abramov A.A., 1997

#ifndef __PARAM_H
#define __PARAM_H

#ifndef __MYLIB_H
  #include <mylib.h>
#endif

#ifndef __CSTRING_H
  #include <cstring.h>
#endif

class TParam
{
  protected:
	 int status;
	 string path;
  public:
// keeping in text file data
	 int xsize;
	 int ysize;
	 float eds;
	 float resist;
	 float gamma;
	 float c0;// [pikoCulon/sm^3]
	 float dt;
	 float lx;
	 float ly;
	 float lz;
	 int tsize;
	 int ntimes;
// derived, init by Update()
	 float dx;
	 float dy;
	 float dvol;
	 void Update();
// derived, init by Step()
	 float current;
	 float voltage;
	 float time;
	 void Step();
	 // constructor
	 TParam();
	 ~TParam();
// methods
	 void Scan();// from text file
	 void Print();// to text file
	 void Read(int);// from binary file
	 void Write(int);
	 int Status(){ return status;}
	 void RegistrateDirectory(string);
};

extern TParam param; // use Scan() and Read() for initialisation

#endif
