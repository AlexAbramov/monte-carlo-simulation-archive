// MDI client window
// Abramov A.A., 1997

#ifndef __MYCLIENT_H
#define __MYCLIENT_H

class TMyClient: public TMDIClient
{
  private:
	 TMDIChild * fieldChild;
	 TMDIChild * cioChild;
	 TMDIChild * bufChild;
	 TMDIChild * currentChild;
	 TMDIChild * voltageChild;
	 TMDIChild * textChild;
	 TMDIChild * paramChild;
	 void SetText();
	 int ctxIndex;
  public:
	 TMyClient();
	 ~TMyClient();
	 void UpdateAfterStep();
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
	 void CmCio();
	 void CmCio1(TCommandEnabler&);
	 void CmBuf();
	 void CmBuf1(TCommandEnabler&);
	 void CmCurrent();
	 void CmCurrent1(TCommandEnabler&);
	 void CmVoltage();
	 void CmVoltage1(TCommandEnabler&);
	 void CmParam();
	 void CmParam1(TCommandEnabler&);
	 void CmAbout();
	 void CmStep();
	 void CmStep1(TCommandEnabler&);
	 void CmRun();
	 void CmRun1(TCommandEnabler&);
	 void CmStop();
	 void CmStop1(TCommandEnabler&);
	 void CmEdit();
	 void CmGamma();
	 void CmGamma1(TCommandEnabler&);
	 void CmUpdate();
	 void CmContents();
	 virtual bool CanClose();
	 void EvTimer(uint);
DECLARE_RESPONSE_TABLE(TMyClient);
};

#endif
