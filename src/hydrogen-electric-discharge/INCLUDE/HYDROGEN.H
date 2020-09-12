// Class for working with hydrogen sequations and threasholds
// Abramov A.A., Kushnarev A., 1997

#ifndef __HYDROGEN_H
#define __HYDROGEN_H

#ifndef __MYLIB_H
  #include <mylib.h>
#endif

#define HYDROGEN_CONC_FILE "..\\..\\dat\\conc.dat"
#define HYDROGEN_SELAS_FILE "..\\..\\dat\\selas.dat"
#define HYDROGEN_SEX_FILE "..\\..\\dat\\sex.dat"
#define HYDROGEN_SION_FILE "..\\..\\dat\\sion.dat"

class THydrogen
{
  private:
	 float conc;// gas concentration [ 10^16/sm^3]
	 float pex;// excitation threshold
	 float pion;// ionisation threshold
	 float dio;
	 TTabFunc * pselas;
	 TTabFunc * psex;
	 TTabFunc * psion;
  public:
	 THydrogen();
	 ~THydrogen();
	 float 	Pion();// ionisation threshold
	 float 	Pex();// lowest threshold of excitation
	 float 	Selas(float);// return elastic sequation [1/sm]; arg - energy [eV]
	 float 	Sex(float);// return excited sequation [1/sm]; arg - energy [eV]
	 float 	Sion(float);// return ionising sequation [1/sm]; arg - energy [eV]
	 float	Stot(float);// total sequation [1/sm]; arg - energy [eV]
	 float 	Felas(float);// return elastic collision frequense [sqev/sm]; arg - energy [eV]
	 float 	Fex(float);// return excited collision frequense [sqev/sm]; arg - energy [eV]
	 float 	Fion(float);// return ionising collision frequense [sqev/sm]; arg - energy [eV]
	 float	Ftot(float);// return collision frequense [sqev/sm]; arg - energy [eV]
	 float 	Fex1(float);// return excited collision frequense [10^6 Hz]; arg - energy [eV]
	 float 	Fion1(float);// return ionising collision frequense [10^6 Hz]; arg - energy [eV]
	 float	Ftot1(float);// return collision frequense [10^6 Hz]; arg - energy [eV]
	 float 	Spion();// arg - energy [eV]
	 float 	Kper();
	 float 	Conc();
	 float	Spelas(float,float);
};

extern THydrogen hydrogen;

#endif
