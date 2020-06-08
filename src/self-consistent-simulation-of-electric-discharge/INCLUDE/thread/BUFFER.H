// Buffer (for registration falling ions on the kathode and emitting electrons)
// Abramov A.A., 1997

#ifndef __BUFFER_H
#define __BUFFER_H

#ifndef __MYLIB_H
  #include <mylib.h>
#endif

class TBuffer
{
  protected:
	 float time;
	 float nion;
	 float nel;
	 TSingleArray ionar;// counter for falling ions
	 TSingleArray elar;
	 TSingleArray genar;// for electron emitting
	 int status;
	 void Control();
  public:
	 int Status(){return status;}
	 TBuffer(){ status=0;}
	 ~TBuffer(){}
	 void Init();// init buffer from TParam object
	 void Clear();// clear sar
	 void Add(float,float,float);// count of falling ion on the cathode; args: y_coord,ion_energy,way_time
	 void Step();
	 float Nion(){ return nion;}
	 float Nel(){ return nel;}
	 float TimeSred(){ return time/nion;}
	 float Emit(float);// return y, arg - random
	 void Write(int);// write array to binary file
	 void Read(int);// read array from binary file
	 TSingleArray& IonArray(){ return ionar;}
	 TSingleArray& ElectronArray(){ return elar;}
	 TSingleArray& GenArray(){ return genar;}
};

extern TBuffer buffer;// use Init() for initialization

#endif
