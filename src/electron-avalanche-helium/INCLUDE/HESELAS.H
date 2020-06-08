// e-He elastic collision
// differential and total cross sections
// Abramov A.A., 1996

#ifndef __HESELAS_H
#define __HESELAS_H
#include <mylib.h>

class THeSelas
{
  private:
	 TTabFunc * ptf;
  public:
	 THeSelas(char* ="dat\\heselas.dat");
	 ~THeSelas();
	 float Total(float);// return total elastic sequation [A*A]
							  // arguments: energy [eV]
	 float Differential(float,float);// return differencial cross section
												// arguments: energy [eV], angle[rad]
	 float Probability(float,float); // return probability of e-He elastic scattering
												// in angle witch less then pointed
												// arguments: energy[eV], angle[rad]
	 float Angle(float,float,int=15);// return angle [rad]
												// arguments: energy [eV], probability, iteration number
};

#endif


