// Class for working with Cd sequations and threasholds
// Abramov A.A., 1997

#ifndef __CD_H
#define __CD_H

#ifndef __MYLIB_H
  #include<mylib.h>
#endif

class TCd
{
  private:
	 float conc;// gas concentration [ 10^16/sm^3]
	 TTabFunc * selas;
	 TTabFunc * sex;
	 TTabFunc * sion;
  public:
	 TCd();
	 ~TCd();
	 float 	Pion();// ionisation threshold
	 float 	Pex();// lowest threshold of excitation
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

extern TCd cd;

#endif
