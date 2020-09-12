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
	 TMDIChild * densityChild;
	 TMDIChild * energyChild;
	 TMDIChild * eeChild;
	 TMDIChild * erChild;
	 TMDIChild * vdrChild;
	 TMDIChild * velChild;
	 TMDIChild * evxChild;
	 TMDIChild * felChild;
	 TMDIChild * fexChild;
	 TMDIChild * fioChild;
	 TMDIChild * fre1Child;
	 int iseq;
	 void SetText1();
	 void SetText2();
	 int ctxIndex;
  public:
	 TMyClient();
	 ~TMyClient();
  protected:
	 virtual void SetupWindow();
	 TOpenSaveDialog::TData * fileData;
	 void CmFileNew();
	 void CmFileOpen();
	 void CmFileSave();
	 void CmFileSave1(TCommandEnabler&);
	 void CmFileSaveAs();
	 void CmElectron();
	 void CmField();
	 void CmText();
	 void CmAbout();
	 void CmStep();
	 void CmRun();
	 void CmRun1(TCommandEnabler&);
	 void CmStop();
	 void EvTimer(uint);
	 void CmDensity();
	 void CmEnergy();
	 void CmEr();
	 void CmEe();
	 void CmVel();
	 void CmVdr();
	 void CmEvx();
	 void CmFel();
	 void CmFex();
	 void CmFio();
	 void CmFre();
	 void CmFre1();
	 void CmSet();
	 void CmRight();
	 void CmLeft();
	 void CmContents();
	 void CmContext();
	 virtual bool CanClose();
	 virtual void EvClose();
	 virtual void CmArrangeIcons();
	 virtual void CmCascadeChildren();
	 virtual void CmCloseChildren();
	 virtual void CmTileChildren();
	 void CmText1(TCommandEnabler&);
DECLARE_RESPONSE_TABLE(TMyClient);
};

#endif
