// MDI client window
// Abramov A.A., 1997

#ifndef __MYCLIENT_H
#define __MYCLIENT_H

#if !defined(OWL_MDI_H)
  #include <owl\mdi.h>
#endif
#if !defined(OWL_OPENSAVE_H)
  #include <owl\opensave.h>
#endif

class TMyClient: public TMDIClient
{
  private:
	 TMDIChild * energyChild;
	 TMDIChild * vdrChild;
	 TMDIChild * evxChild;
	 TMDIChild * fexChild;
	 TMDIChild * fioChild;
	 TMDIChild * fre1Child;
	 int iseq;
	 void SetText1();
	 void SetText2();
  public:
	 TMyClient();
	 ~TMyClient();
  protected:
	 virtual void SetupWindow();
	 TOpenSaveDialog::TData * fileData;
	 void CmFileNew();
	 void CmFileOpen();
	 void CmFileSave();
	 void CmFileSaveAs();
//	 void CmFileClose();
	 void CmElectron();
	 void CmText();
	 void CmAbout();
	 void CmStep();
	 void CmRun();
	 void CmStop();
	 void CmAll();
	 void CmAllStat();
	 void EvTimer(uint);
	 void CmEnergy();
	 void CmVdr();
	 void CmEvx();
	 void CmFex();
	 void CmFio();
	 void CmFre();
	 void CmFre1();
	 void CmSet();
	 void CmRight();
	 void CmLeft();
	 virtual bool CanClose();
DECLARE_RESPONSE_TABLE(TMyClient);
};

#endif
