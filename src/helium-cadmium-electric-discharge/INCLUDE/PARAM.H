// Class of gas discharge parameters 
// Electron avalanches discription
// Abramov A.A., 1997

#ifndef __PARAM_H
#define __PARAM_H

#ifndef __MYLIB_H
  #include<mylib.h>
#endif

class TParam
{
  protected:
	 int status;
  public:
// keeping in text file data
	 int xsize;
	 int ysize;
	 float lx;
	 float ly;
	 float voltage;
	 float dk;
	 float fd;// field after dk
	 int   esize;
	 float de;
	 float xem;
// derived, init by Update()
	 float dx;
	 float dy;
	 float emax;
	 float rde;
	 void Update();
//  init by Step()
	 long int nlav;// number of electron avalanches
	 void Step(){nlav++;}
// constructor
	 TParam();
	 ~TParam();
// methods
	 void Scan();// from text file
	 void Print();// to text file
	 void Read(int);// from binary file
	 void Write(int);
	 int Status(){ return status;}
};

extern TParam param; // use Scan() and Read() for initialisation

#endif
