// MDI child window
// Abramov A.A., 1997

#ifndef __MYCHILD_H
#define __MYCHILD_H

#if !defined(OWL_MDI_H)
  #include <owl\mdi.h>
#endif
#if !defined(OWL_MDICHILD_H)
  #include <owl\mdichild.h>
#endif
#ifndef __MYGRAPH_H
  #include <mygraph.h>
#endif

class TElectronChild: public TMDIChild
{
  protected:
	 TMemoryDC * mdc;
	 TClientDC * cdc;
	 void EvSize(uint, TSize&);
	 void EvClose();
	 void CmHelp();
	 void Paint(TDC&,bool,TRect&);
  public:
	 void Paint();
	 TElectronChild(TMDIClient&);
	 ~TElectronChild();
	 virtual bool Create();
	 DECLARE_RESPONSE_TABLE(TElectronChild);
};

/*
class TElectronChild: public TMDIChild
{
  protected:
	 TClientDC * pdc;
	 void EvSize(uint, TSize&);
	 void CmHelp();
	 void Paint(TDC&,bool,TRect&);
  public:
	 TElectronChild(TMDIClient&);
	 ~TElectronChild();
	 virtual bool Create();
	DECLARE_RESPONSE_TABLE(TElectronChild);
};*/

class TMyMDIChild: public TMDIChild
{
  protected:
	 void EvSize(uint, TSize&);
	 void CmHelp();
	 void SetupWindow();
	 bool CanClose();
	 virtual int GetContext()=0;
	 virtual int& GetFlag()=0;
	 virtual char* GetCaption()=0;
	 virtual void Paint1(TDC&)=0;
	 void Paint(TDC&,bool,TRect&);
  public:
	 TMyMDIChild(TMDIClient&);
	 DECLARE_RESPONSE_TABLE(TMyMDIChild);
};

class TFieldChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TFieldChild(TMDIClient& client): TMyMDIChild(client){}
};

class TCioChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TCioChild(TMDIClient& client): TMyMDIChild(client){}
};

class TBufChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TBufChild(TMDIClient& client): TMyMDIChild(client){}
};

class TParamChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TParamChild(TMDIClient& client): TMyMDIChild(client){}
};

class TGammaChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TGammaChild(TMDIClient& client): TMyMDIChild(client){}
};

class TCurrentChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TCurrentChild(TMDIClient& client): TMyMDIChild(client){}
};

class TVoltageChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TVoltageChild(TMDIClient& client): TMyMDIChild(client){}
};

#endif
