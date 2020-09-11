#include <math.h>
#pragma hdrstop
//#include <string.h>
//#include <mylib.h>
#include <param.h>
#include <ris.h>
#include <elstat.h>
#include <flag.h>
#include "discharg.h"
#include "mychild.h"

#define WINWIDTH 	300
#define WINHEIGHT	300

// ELECTRON
TElectronChild::TElectronChild(TMDIClient& client):
  TMDIChild(client,"Electron tracks")
{
  pdc=0;
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  Attr.Style |= WS_CHILD |WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_VISIBLE;
}

BOOL
TElectronChild::Create()
{
  BOOL b=TWindow::Create();
  pdc=new TClientDC(HWindow);
  risel.Setup(pdc);
  flag.electron=1;
  return b;
}

TElectronChild::~TElectronChild()
{
  risel.Destroy();
  delete pdc;
  flag.electron=0;
}

DEFINE_RESPONSE_TABLE1(TElectronChild, TMDIChild)
  EV_WM_SIZE,
END_RESPONSE_TABLE;

void
TElectronChild::EvSize(uint sizeType, TSize& size)
{
  TFrameWindow::EvSize(sizeType,size);
  Invalidate();
  risel.Update();
}

// TEXT

TTextChild::TTextChild(TMDIClient& client):
  TMDIChild(client,"Text info")
{
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  flag.text=1;
}

TTextChild::~TTextChild()
{
  flag.text=0;
}

void
TTextChild::Paint(TDC& dc,BOOL,TRect&)
{
  int i=20,j=20;
  char buf[40];
  sprintf(buf,"lx=%.1f",param.lx);
  dc.TextOut(i,j*1,buf);
  sprintf(buf,"ly=%.1f",param.ly);
  dc.TextOut(i,j*2,buf);
  sprintf(buf,"field=%.2f",param.fd);
  dc.TextOut(i,j*3,buf);
  sprintf(buf,"xem=%.1f",param.xem);
  dc.TextOut(i,j*4,buf);
  sprintf(buf,"dt=%.3f",param.dt);
  dc.TextOut(i,j*5,buf);
  sprintf(buf,"tsize=%i",param.tsize);
  dc.TextOut(i,j*6,buf);
  sprintf(buf,"de=%.1f",param.de);
  dc.TextOut(i,j*7,buf);
  sprintf(buf,"esize=%i",param.esize);
  dc.TextOut(i,j*8,buf);
}

// Energy
void
TEnergyChild::EvSize(uint sizeType, TSize& size)
{
  TFrameWindow::EvSize(sizeType,size);
  Invalidate();
  UpdateWindow();
}

DEFINE_RESPONSE_TABLE1(TEnergyChild, TMDIChild)
  EV_WM_SIZE,
END_RESPONSE_TABLE;

TEnergyChild::TEnergyChild(TMDIClient& client):
  TMDIChild(client,"Electron mean energy")
{
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  flag.energy=1;
}

TEnergyChild::~TEnergyChild()
{
  flag.energy=0;
}

void
TEnergyChild::Paint(TDC& /*dc*/,BOOL,TRect&)
{
  TClientDC dc(HWindow);
  graph.Show(dc, elstat.GetEnergy(), param.tmax,"t [mksec]","e [eV]");
}

// Vdr
void
TVdrChild::EvSize(uint sizeType, TSize& size)
{
  TFrameWindow::EvSize(sizeType,size);
  Invalidate();
  UpdateWindow();
}

DEFINE_RESPONSE_TABLE1(TVdrChild, TMDIChild)
  EV_WM_SIZE,
END_RESPONSE_TABLE;

TVdrChild::TVdrChild(TMDIClient& client):
  TMDIChild(client,"Electron drift velocity")
{
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  flag.vdr=1;
}

TVdrChild::~TVdrChild()
{
  flag.vdr=0;
}

void
TVdrChild::Paint(TDC& /*dc*/,BOOL,TRect&)
{
  TClientDC dc(HWindow);
  graph.Show(dc, elstat.GetVdr1(), param.tmax,"t [mksec]","Vdr [sm/mksec]");
}

// Evx
void
TEvxChild::EvSize(uint sizeType, TSize& size)
{
  TFrameWindow::EvSize(sizeType,size);
  Invalidate();
  UpdateWindow();
}

DEFINE_RESPONSE_TABLE1(TEvxChild, TMDIChild)
  EV_WM_SIZE,
END_RESPONSE_TABLE;

TEvxChild::TEvxChild(TMDIClient& client):
  TMDIChild(client,"Evx")
{
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  flag.evx=1;
}

TEvxChild::~TEvxChild()
{
  flag.evx=0;
}

void
TEvxChild::Paint(TDC& /*dc*/,BOOL,TRect&)
{
  TClientDC dc(HWindow);
  graph.Show(dc, elstat.GetEvx1(), param.tmax,"t [mksec]","Evx [eV*sm/mksec]");
}

// Fex
void
TFexChild::EvSize(uint sizeType, TSize& size)
{
  TFrameWindow::EvSize(sizeType,size);
  Invalidate();
  UpdateWindow();
}

DEFINE_RESPONSE_TABLE1(TFexChild, TMDIChild)
  EV_WM_SIZE,
END_RESPONSE_TABLE;

TFexChild::TFexChild(TMDIClient& client):
  TMDIChild(client,"Excited collision frequance")
{
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  flag.fex=1;
}

TFexChild::~TFexChild()
{
  flag.fex=0;
}

void
TFexChild::Paint(TDC& /*dc*/,BOOL,TRect&)
{
  TClientDC dc(HWindow);
  graph.Show(dc, elstat.GetFex1(), param.tmax,"t [mksec]","Fex [MHz]");
}

// Fio
void
TFioChild::EvSize(uint sizeType, TSize& size)
{
  TFrameWindow::EvSize(sizeType,size);
  Invalidate();
  UpdateWindow();
}

DEFINE_RESPONSE_TABLE1(TFioChild, TMDIChild)
  EV_WM_SIZE,
END_RESPONSE_TABLE;

TFioChild::TFioChild(TMDIClient& client):
  TMDIChild(client,"Ionising collision frequance")
{
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  flag.fio=1;
}

TFioChild::~TFioChild()
{
  flag.fio=0;
}

void
TFioChild::Paint(TDC& /*dc*/,BOOL,TRect&)
{
  TClientDC dc(HWindow);
  graph.Show(dc, elstat.GetFio1(), param.tmax,"t [mksec]","Fio [MHz]");
}

// FRE
void
TFreChild::EvSize(uint sizeType, TSize& size)
{
  TFrameWindow::EvSize(sizeType,size);
  Invalidate();
  UpdateWindow();
}

DEFINE_RESPONSE_TABLE1(TFreChild, TMDIChild)
  EV_WM_SIZE,
END_RESPONSE_TABLE;

TFreChild::TFreChild(TMDIClient& client):
  TMDIChild(client,"f(e,x) - electron distribution function")
{
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  flag.fre=1;
}

TFreChild::~TFreChild()
{
  flag.fre=0;
}

void
TFreChild::Paint(TDC& /*dc*/,BOOL,TRect&)
{
  TClientDC dc(HWindow);
  graphic.Show(dc, elstat.GetFre(), param.emax, param.tmax,"e [eV]","t [mksec]","f(e,x)");
}

// FRE1
void
TFre1Child::EvSize(uint sizeType, TSize& size)
{
  TFrameWindow::EvSize(sizeType,size);
  Invalidate();
  UpdateWindow();
}

DEFINE_RESPONSE_TABLE1(TFre1Child, TMDIChild)
  EV_WM_SIZE,
END_RESPONSE_TABLE;

TFre1Child::TFre1Child(TMDIClient& client, int _iseq):
  TMDIChild(client,"f(e) - electron distribution function")
{
  iseq=_iseq;
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  flag.fre1=1;
}

TFre1Child::~TFre1Child()
{
  flag.fre1=0;
}

static float raspred(float e, float esr)
{
  float d=2*esr/3;
  return 2.*sqrt(e/(3.1415*d*d*d))*exp(-e/d);
}

void
TFre1Child::Paint(TDC& /*dc*/,BOOL,TRect&)
{
  if(iseq<=0) return;
  TClientDC dc(HWindow);
  TSingleArray& sar=elstat.GetFre1(iseq);
  graph.Show(dc,sar,param.emax,"e [eV]","f(e)");
  float esr=( elstat.GetEnergy() )[iseq];
  int sz=sar.Size();
  TSingleArray sar1(sz);
  for(int i=0;i<sz;i++)
  {
	 float e=i*param.de;
	 sar1[i]=raspred(e,esr)*param.de;
  }
  graph.Show1(dc,sar1);
/*  char tt[40];
  sprintf(tt,"p=%.3f",param.de);
  message(tt);
  sprintf(tt,"iseq=%i",iseq);
  message(tt);*/
}
