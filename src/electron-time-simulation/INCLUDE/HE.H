// Class for working with He sequations and threasholds
// Abramov A.A., 1997

#ifndef __HE_H
#define __HE_H

#ifndef __MYLIB_H
  #include<mylib.h>
#endif

class THe
{
  private:
	 float conc;// gas concentration [ 10^16/sm^3]
  public:
	 THe(char* =0);// from binary file
	 ~THe();
	 int 		LevelMax();// max level of excitaton
	 float 	Pion();// ionisation threshold
	 float 	Pex();// lowest threshold of excitation
	 float 	Pex(int);// excitation thresholds; arg - level
	 float 	Spelas(float,float);// return angle [rad] of elastic differential collision; args: energy [eV], random[0,1]
	 int 	   Spex(float,float);// return number of level in excited collision; args: energy [eV], random[0,1]
	 float 	Spion(float,float);// return d[0,1] in ionising differential collision; args: energy [eV], random[0,1]
	 float 	Selas(float);// return elastic sequation [1/sm]; arg - energy [eV]
	 float 	Sex(float);// return excited sequation [1/sm]; arg - energy [eV]
	 float 	Sion(float);// return ionising sequation [1/sm]; arg - energy [eV]
	 float	Stot(float);// total sequation [1/sm]; arg - energy [eV]
	 float 	Fex(float);// return excited collision frequense [sqev/sm]; arg - energy [eV]
	 float 	Fion(float);// return ionising collision frequense [sqev/sm]; arg - energy [eV]
	 float	Ftot(float);// return collision frequense [sqev/sm]; arg - energy [eV]
	 float 	Fex1(float);// return excited collision frequense [10^6 Hz]; arg - energy [eV]
	 float 	Fion1(float);// return ionising collision frequense [10^6 Hz]; arg - energy [eV]
	 float	Ftot1(float);// return collision frequense [10^6 Hz]; arg - energy [eV]
	 float 	Kper();
	 float 	Conc();
};

extern THe he;

#endif
