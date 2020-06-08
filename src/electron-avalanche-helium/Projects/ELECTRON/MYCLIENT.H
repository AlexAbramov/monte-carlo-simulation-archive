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
	 TMDIChild * electronChild;
	 TMDIChild * fieldChild;
	 TMDIChild * textChild;
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
	 void UpdateChilds(BOOL b=FALSE);
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
	 void CmElectron();
	 void CmElectron1(TCommandEnabler&);
	 void CmField();
	 void CmField1(TCommandEnabler&);
	 void CmText();
	 void CmText1(TCommandEnabler&);
	 void CmAbout();
	 void CmStep();
	 void CmStep1(TCommandEnabler&);
	 void CmRun();
	 void CmRun1(TCommandEnabler&);
	 void CmStop();
	 void CmStop1(TCommandEnabler&);
	 void EvTimer(uint);
	 void CmDensity();
	 void CmDensity1(TCommandEnabler&);
	 void CmEnergy();
	 void CmEnergy1(TCommandEnabler&);
	 void CmEr();
	 void CmEr1(TCommandEnabler&);
	 void CmEe();
	 void CmEe1(TCommandEnabler&);
	 void CmVel();
	 void CmVel1(TCommandEnabler&);
	 void CmVdr();
	 void CmVdr1(TCommandEnabler&);
	 void CmEvx();
	 void CmEvx1(TCommandEnabler&);
	 void CmFel();
	 void CmFel1(TCommandEnabler&);
	 void CmFex();
	 void CmFex1(TCommandEnabler&);
	 void CmFio();
	 void CmFio1(TCommandEnabler&);
	 void CmFre();
	 void CmFre2(TCommandEnabler&);
	 void CmFre1();
	 void CmFre3(TCommandEnabler&);
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
DECLARE_RESPONSE_TABLE(TMyClient);
};

#endif
