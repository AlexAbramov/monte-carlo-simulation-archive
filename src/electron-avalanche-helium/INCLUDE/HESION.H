// e-He ionising collision
// differential and total cross sections
// Abramov A.A., 1996

#ifndef __HESION_H
#define __HESION_H

class THeSion
{
  private:
	 float aa1,bb1,cc1,aa2,bb2,cc2;
	 float ef1,ef2,e1,e2;
  public:
	 THeSion();
	 float Total(float);// return total ionising cross section [A*A]
							  // arguments : energy [eV]
	 float Differential(float,float);// return differencial cross section
												// arguments : energy [eV]
	 float Probability(float,float);// return probability
											  // arguments : energy [eV], share of energy

	 float Share(float,float,int=15);// return share of energy
												// arguments : energy [eV],probability,iteration number
};

#endif

// functions taked from paper "Effective cross sections...",JTP,v15,N1,97-107
// energy range from 24.58 eV to 20 KeV.
// e0 - kinetic energy of electron before ionization
// e - kinetic energy after ionization
// pion - ionization threshold
// e/(e0-pion) -share of energy, range from 0 to 1
