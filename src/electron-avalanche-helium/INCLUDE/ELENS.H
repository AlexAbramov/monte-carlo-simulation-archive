// Ensemble of electrons
// Abramov A.A., 1997

#ifndef __ELENS_H
#define __ELENS_H

#ifndef __ELECTRON_H
  #include <electron.h>
#endif

class TElectronEnsemble
{
  protected:
	 int size;// max size of ensemble
	 int number;// number of electrons
	 TElectron * pp;
  public:
	 TElectronEnsemble(int= 500);
	 ~TElectronEnsemble();
	 void Step();
};

extern TElectronEnsemble elens;

#endif
