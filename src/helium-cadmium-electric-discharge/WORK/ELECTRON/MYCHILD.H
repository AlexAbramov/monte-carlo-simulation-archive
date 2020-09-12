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
  #include<mygraph.h>
#endif

class TElectronChild: public TMDIChild
{
  protected:
	 TClientDC * pdc;
	 void EvSize(uint, TSize&);
  public:
	 TElectronChild(TMDIClient&);
	 ~TElectronChild();
	 virtual BOOL Create();
	DECLARE_RESPONSE_TABLE(TElectronChild);
};

class TFieldChild: public TMDIChild
{
  protected:
	 TGraphic graphic;
	 void EvSize(uint, TSize&);
	 virtual void Paint(TDC&,BOOL,TRect&);
  public:
	 TFieldChild(TMDIClient&);
	 ~TFieldChild();
	DECLARE_RESPONSE_TABLE(TFieldChild);
};

class TTextChild: public TMDIChild
{
  public:
	 TTextChild(TMDIClient&);
	 ~TTextChild();
	 virtual void Paint(TDC&,BOOL,TRect&);
};

class TEnergyChild: public TMDIChild
{
  protected:
	 TGraph graph;
	 void EvSize(uint, TSize&);
  public:
	 virtual void Paint(TDC&,BOOL,TRect&);
	 TEnergyChild(TMDIClient&);
	 ~TEnergyChild();
	DECLARE_RESPONSE_TABLE(TEnergyChild);
};

class TVdrChild: public TMDIChild
{
  protected:
	 TGraph graph;
	 void EvSize(uint, TSize&);
  public:
	 virtual void Paint(TDC&,BOOL,TRect&);
	 TVdrChild(TMDIClient&);
	 ~TVdrChild();
	DECLARE_RESPONSE_TABLE(TVdrChild);
};

class TEvxChild: public TMDIChild
{
  protected:
	 TGraph graph;
	 void EvSize(uint, TSize&);
  public:
	 virtual void Paint(TDC&,BOOL,TRect&);
	 TEvxChild(TMDIClient&);
	 ~TEvxChild();
	DECLARE_RESPONSE_TABLE(TEvxChild);
};

class TFexChild: public TMDIChild
{
  protected:
	 TGraph graph;
	 void EvSize(uint, TSize&);
  public:
	 virtual void Paint(TDC&,BOOL,TRect&);
	 TFexChild(TMDIClient&);
	 ~TFexChild();
	DECLARE_RESPONSE_TABLE(TFexChild);
};

class TFioChild: public TMDIChild
{
  protected:
	 TGraph graph;
	 void EvSize(uint, TSize&);
  public:
	 virtual void Paint(TDC&,BOOL,TRect&);
	 TFioChild(TMDIClient&);
	 ~TFioChild();
	DECLARE_RESPONSE_TABLE(TFioChild);
};

class TFreChild: public TMDIChild
{
  protected:
	 TGraphic graphic;
	 void EvSize(uint, TSize&);
	 virtual void Paint(TDC&,BOOL,TRect&);
  public:
	 TFreChild(TMDIClient&);
	 ~TFreChild();
	DECLARE_RESPONSE_TABLE(TFreChild);
};

class TFre1Child: public TMDIChild
{
  protected:
	 int iseq;
	 TGraph graph;
	 void EvSize(uint, TSize&);
	 virtual void Paint(TDC&,BOOL,TRect&);
  public:
	 void Update(int _iseq){ iseq=_iseq; Invalidate(); UpdateWindow();}
	 TFre1Child(TMDIClient&,int =0);
	 ~TFre1Child();
	DECLARE_RESPONSE_TABLE(TFre1Child);
};

#endif
