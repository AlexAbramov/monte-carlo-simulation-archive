// MDI child windows
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
	 TBitmap* bitmap;
	 void EvSize(uint, TSize&);
	 void CmHelp();
	 void Paint(TDC&,bool,TRect&);
  public:
	 TElectronChild(TMDIClient&);
	 ~TElectronChild();
	 virtual bool Create();
	 void Clear();
	DECLARE_RESPONSE_TABLE(TElectronChild);
};

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

class TTextChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TTextChild(TMDIClient& client): TMyMDIChild(client){}
};

class TEnergyChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TEnergyChild (TMDIClient& client): TMyMDIChild(client){}
};

class TVdrChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TVdrChild(TMDIClient& client): TMyMDIChild(client){}
};

class TEvxChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TEvxChild(TMDIClient& client): TMyMDIChild(client){}
};

class TFexChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TFexChild(TMDIClient& client): TMyMDIChild(client){}
};

class TFioChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TFioChild(TMDIClient& client): TMyMDIChild(client){}
};

class TFreChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TFreChild(TMDIClient& client): TMyMDIChild(client){}
};

class TFre1Child: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
	 int iseq;
  public:
	 void Update(int _iseq){ iseq=_iseq; Invalidate(); UpdateWindow();}
	 TFre1Child(TMDIClient& client,int i=0): TMyMDIChild(client){iseq=i;}
};

class TDensityChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TDensityChild(TMDIClient& client): TMyMDIChild(client){}
};

class TVelChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TVelChild(TMDIClient& client): TMyMDIChild(client){}
};

class TEeChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TEeChild(TMDIClient& client): TMyMDIChild(client){}
};

class TFelChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TFelChild(TMDIClient& client): TMyMDIChild(client){}
};

class TErChild: public TMyMDIChild
{
  protected:
	 int GetContext();
	 int& GetFlag();
	 char* GetCaption();
	 void Paint1(TDC&);
  public:
	 TErChild(TMDIClient& client): TMyMDIChild(client){}
};

#endif
