// e-He collision
// excited sequations and thresholds for s,p,d
// (triplet and singlet) levels
// Abramov A.A., 1996

#ifndef __HESEX_H
#define __HESEX_H

class THeSex
{
  public:
	 THeSex();
	 float Threshold(int,int);// return threshold [eV]
									  // arguments: type, level
	 float Sequation(int,int,float);// return sequation [A*A]
											  // arguments: type, level, energy [eV]
	 float Sequation(int,float,int=0);// return sequation [A*A] of level
	 char* TypeName(int);// return type name; arguments: type
	 int TypeMax();		// return max type number
	 int LevelMax();     // max level for thresholds
	 int LevelMin(int);	// return lowest level; arguments: type
};

#endif

// functions taked from paper "Effective sequations...",JTP,v15,N1,97-107
// threholds taked from "Physical values",Energyatomizdat,1991
