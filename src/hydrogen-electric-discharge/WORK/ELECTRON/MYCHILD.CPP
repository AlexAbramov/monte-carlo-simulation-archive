#include <math.h>
#pragma hdrstop
#include <param.h>
#include <field.h>
#include <ris.h>
#include <elstat.h>
#include <flag.h>
#include "context.h"
#include "discharg.h"
#include "mychild.rh"
#include "mychild.h"

#define WINWIDTH 	300
#define WINHEIGHT	300

//#define __DOUBLE_BUFFER

extern string HelpPath;
static TGraph graph;
static TGraphic graphic;

// ELECTRON
TElectronChild::TElectronChild(TMDIClient& client):
  TMDIChild(client,"Electron tracks")
{
  pdc=0;
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  Attr.Style |= WS_CHILD |WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_VISIBLE;
  Attr.AccelTable="AccHelp";
}

bool
TElectronChild::Create()
{
  bool b=TWindow::Create();
  pdc=new TClientDC(HWindow);
  risel.Setup(pdc);
  flag.electron=true;
  return b;
}

TElectronChild::~TElectronChild()
{
  risel.Destroy();
  delete pdc;
  flag.electron=false;
}

DEFINE_RESPONSE_TABLE1(TElectronChild, TMDIChild)
  EV_WM_SIZE,
  EV_COMMAND(CM_HELP, CmHelp),
END_RESPONSE_TABLE;

void
TElectronChild::EvSize(uint sizeType, TSize& size)
{
  TFrameWindow::EvSize(sizeType,size);
  Invalidate();
  risel.Update();
}

void
TElectronChild::Paint(TDC& /*dc*/,bool,TRect&)
{
//  Invalidate();
}

void
TElectronChild::CmHelp()
{
  WinHelp(HelpPath.c_str(), HELP_CONTEXT, __Electron_tracks);
}

// TMyMDIChild
DEFINE_RESPONSE_TABLE1(TMyMDIChild, TMDIChild)
  EV_WM_SIZE,
  EV_COMMAND(CM_HELP, CmHelp),
END_RESPONSE_TABLE;

void
TMyMDIChild::EvSize(uint sizeType, TSize& size)
{
  TFrameWindow::EvSize(sizeType,size);
  Invalidate();
  UpdateWindow();
}

void
TMyMDIChild::CmHelp()
{
  int index=GetContext();
  WinHelp(HelpPath.c_str(), HELP_CONTEXT, index);
}

TMyMDIChild::TMyMDIChild(TMDIClient& client):
  TMDIChild(client)
{
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  Attr.AccelTable="AccHelp";
}

void
TMyMDIChild::SetupWindow()
{
  SetCaption(GetCaption());
  GetFlag()=1;
  TMDIChild::SetupWindow();
}

bool
TMyMDIChild::CanClose()
{
  GetFlag()=0;
  return TMDIChild::CanClose();
}

void
TMyMDIChild::Paint(TDC& /*dc*/,bool,TRect&)
{
  TClientDC dc(HWindow);
#ifdef __DOUBLE_BUFFER
  TRect rect;
  dc.GetClipBox(rect);
  TBitmap bitmap(dc,rect.Width(),rect.Height());
//  BITMAP bm;
//  bitmap.GetObject(bm);
  TMemoryDC mdc(dc);
  mdc.SelectObject(bitmap);
  mdc.FillRect(rect,TBrush(TColor::White));
  Paint1(mdc);
  dc.BitBlt(rect, mdc,TPoint(0,0));
#else
  Paint1(dc);
#endif
}

// FIELD
int TFieldChild::GetContext(){return __Electric_field;}
int& TFieldChild::GetFlag(){return flag.field;}
char* TFieldChild::GetCaption(){return "Electric field";}
void TFieldChild::Paint1(TDC& dc)
{
  graphic.Show(dc, field.GetField(), param.lx, param.ly, "x [sm]","y [sm]","E [V/sm]");
}

// TEXT
int TTextChild::GetContext(){return __Text_info;}
int& TTextChild::GetFlag(){return flag.text;}
char* TTextChild::GetCaption(){return "Parameters";}
void TTextChild::Paint1(TDC& dc)
{
  int i=20,j=20;
  char buf[40];
  sprintf(buf,"xsize=%i",param.xsize);
  dc.TextOut(i,j*1,buf);
  sprintf(buf,"ysize=%i",param.ysize);
  dc.TextOut(i,j*2,buf);
  sprintf(buf,"lx=%.1f",param.lx);
  dc.TextOut(i,j*3,buf);
  sprintf(buf,"ly=%.1f",param.ly);
  dc.TextOut(i,j*4,buf);
  sprintf(buf,"voltage=%.0f",param.voltage);
  dc.TextOut(i,j*5,buf);
  sprintf(buf,"dk=%.2f",param.dk);
  dc.TextOut(i,j*6,buf);
  sprintf(buf,"field=%.2f",param.fd);
  dc.TextOut(i,j*7,buf);
  sprintf(buf,"de=%.1f",param.de);
  dc.TextOut(i,j*8,buf);
  sprintf(buf,"esize=%i",param.esize);
  dc.TextOut(i,j*9,buf);
  sprintf(buf,"xem=%.1f",param.xem);
  dc.TextOut(i,j*10,buf);
}

// Energy
int TEnergyChild::GetContext(){return __Mean_energy;}
int& TEnergyChild::GetFlag(){return flag.energy;}
char* TEnergyChild::GetCaption(){return "Mean energy";}
void TEnergyChild::Paint1(TDC& dc)
{
  graph.Show(dc, elstat.GetEnergy(), param.lx,"x [sm]","e [eV]");
}

// Vdr
int TVdrChild::GetContext(){return __Drift_velocity;}
int& TVdrChild::GetFlag(){return flag.vdr;}
char* TVdrChild::GetCaption(){return "Drift velocity";}
void TVdrChild::Paint1(TDC& dc)
{
  graph.Show(dc, elstat.GetVdr1(), param.lx,"x [sm]","Vdr [sm/mksec]");
}

// Evx
int TEvxChild::GetContext(){return __e_vx_;}
int& TEvxChild::GetFlag(){return flag.evx;}
char* TEvxChild::GetCaption(){return "<e*vx>";}
void TEvxChild::Paint1(TDC& dc)
{
  graph.Show(dc, elstat.GetEvx1(), param.lx,"x [sm]","Evx [eV*sm/mksec]");
}

// Fex
int TFexChild::GetContext(){return __Excited_frequency;}
int& TFexChild::GetFlag(){return flag.fex;}
char* TFexChild::GetCaption(){return "Excited collision frequency";}
void TFexChild::Paint1(TDC& dc)
{
  graph.Show(dc, elstat.GetFex1(), param.lx,"x [sm]","Fex [MHz]");
}

// Fio
int TFioChild::GetContext(){return __Ionized_frequency;}
int& TFioChild::GetFlag(){return flag.fio;}
char* TFioChild::GetCaption(){return "Ionized collision frequency";}
void TFioChild::Paint1(TDC& dc)
{
  graph.Show(dc, elstat.GetFio1(), param.lx,"x [sm]","Fio [MHz]");
}

// FRE
int TFreChild::GetContext(){return __f_e_x_;}
int& TFreChild::GetFlag(){return flag.fre;}
char* TFreChild::GetCaption(){return "f(e,x) - electron distribution function";}
void TFreChild::Paint1(TDC& dc)
{
  graphic.Show(dc, elstat.GetFre(), param.emax, param.lx,"e [eV]","x [sm]","f(e,x)");
}

// FRE1
int TFre1Child::GetContext(){return __f_e_x_;}
int& TFre1Child::GetFlag(){return flag.fre1;}
char* TFre1Child::GetCaption(){return "f(e) - electron distribution function";}
static float raspred(float e, float esr)
{
  float d=2*esr/3;
  return 2.*sqrt(e/(3.1415*d*d*d))*exp(-e/d);
}
void TFre1Child::Paint1(TDC& dc)
{
  if(iseq<=0) return;
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
}

// Density
int TDensityChild::GetContext(){return __Electron_density;}
int& TDensityChild::GetFlag(){return flag.density;}
char* TDensityChild::GetCaption(){return "Electron density";}
void TDensityChild::Paint1(TDC& dc)
{
  graph.Show(dc, elstat.GetDensity(), param.lx,"x [sm]","density");
}

// Velocity
int TVelChild::GetContext(){return __Mean_velocity;}
int& TVelChild::GetFlag(){return flag.vel;}
char* TVelChild::GetCaption(){return "Electron mean velocity";}
void TVelChild::Paint1(TDC& dc)
{
  graph.Show(dc, elstat.GetVel1(), param.lx,"x [sm]","v [sm/mksec]");
}

// <e*e>
int TEeChild::GetContext(){return __e_e_;}
int& TEeChild::GetFlag(){return flag.vel;}
char* TEeChild::GetCaption(){return "<e*e>";}
void TEeChild::Paint1(TDC& dc)
{
  graph.Show(dc, elstat.GetEe(), param.lx,"x [sm]","<e*e> [eV*eV]");
}

// Elastic frequency
int TFelChild::GetContext(){return __Elastic_frequency;}
int& TFelChild::GetFlag(){return flag.fel;}
char* TFelChild::GetCaption(){return "Elastic collision frequency";}
void TFelChild::Paint1(TDC& dc)
{
  graph.Show(dc, elstat.GetFel1(), param.lx,"x [sm]","Fel [MHz]");
}

// Electron radial energy
int TErChild::GetContext(){return __Radial_energy;}
int& TErChild::GetFlag(){return flag.er;}
char* TErChild::GetCaption(){return "Radial energy";}
void TErChild::Paint1(TDC& dc)
{
  graph.Show(dc, elstat.GetEr(), param.lx,"x [sm]","Radial energy [eV]");
}

