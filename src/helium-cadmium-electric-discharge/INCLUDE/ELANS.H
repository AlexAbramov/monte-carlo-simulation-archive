// Ansamble of electrons
// Abramov A.A., 1997

#ifndef __ELANS_H
#define __ELANS_H

#ifndef __ELECTRON_H
  #include<electron.h>
#endif

class TElectronAnsamble
{
  protected:
    float e0;
	 int size;// max size of ansamble
	 int number;// number of electrons
	 TElectron * pp;
  public:
	 TElectronAnsamble(int= 500);
	 ~TElectronAnsamble();
	 void Step();
};

extern TElectronAnsamble elans;

#endif
