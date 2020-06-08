#include <pch.h>
#pragma hdrstop
#include <param.h>
#include <field.h>
#include <ris.h>
#include <flag.h>
#include <elans.h>
#include <tstat.h>
#include "discharg.h"
#include "mychild.rh"
#include "context.h"
#include "mychild.h"

#define WINWIDTH 	300
#define WINHEIGHT	300

#define __DOUBLE_BUFFER

extern string HelpPath;
static TGraph graph;
static TGraphic graphic;

// ELECTRON
TElectronChild::TElectronChild(TMDIClient& client):
  TMDIChild(client,"Electron tracks")
{
  cdc=0;
  mdc=0;
  Attr.H=WINHEIGHT;
  Attr.W=WINWIDTH;
  Attr.Style |= WS_CHILD |WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_VISIBLE;
  Attr.AccelTable="AccHelp";
  flag.electron=1;
}

bool
TElectronChild::Create()
{
  bool b=TMDIChild::Create();
  cdc=new TClientDC(HWindow);
  cdc->SetBkColor(TColor::White);
  cdc->SetBkMode(OPAQUE);
  mdc=new TMemoryDC(*cdc);
  mdc->SetBkColor(TColor::White);
  mdc->SetBkMode(OPAQUE);
  risel.Init(mdc,this,cdc);
  return b;
}

TElectronChild::~TElectronChild()
{
  flag.electron=0;
  risel.Destroy();
  delete cdc;
  delete mdc;
}

DEFINE_RESPONSE_TABLE1(TElectronChild, TMDIChild)
  EV_WM_SIZE,
  EV_WM_CLOSE,
  EV_COMMAND(CM_HELP, CmHelp),
END_RESPONSE_TABLE;

void
TElectronChild::EvSize(uint sizeType, TSize& size)
{
  TMDIChild::EvSize(sizeType,size);
  TRect rect;
  GetClientRect(rect);
  risel.Update(rect);
  UpdateWindow();
}

void TElectronChild::EvClose()
{
  if((flag.run||flag.step)&&!risel.needClose)
  {
	 risel.needClose=true;
	 return;
  }
  TMDIChild::EvClose();
}

void
TElectronChild::Paint(TDC& dc,bool,TRect& rect)
{
  if(risel.painted) Paint();
  else dc->FillRect(rect,TBrush(TColor::White));
}

void
TElectronChild::Paint()
{
  TRect rect;
  GetClientRect(rect);
  cdc->BitBlt(rect, *mdc, TPoint(0,0));
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
  GetClientRect(rect);
  TBitmap bitmap(dc,rect.Width(),rect.Height());
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

// CIO
int TCioChild::GetContext(){return __Cio;}
int& TCioChild::GetFlag(){return flag.cio;}
char* TCioChild::GetCaption(){return "Ion concentration";}
void TCioChild::Paint1(TDC& dc)
{
  graphic.Show(dc, field.GetCio(), param.lx, param.ly, "x [sm]","y [sm]","Conc");
}

// BUF
int TBufChild::GetContext(){return __Buf;}
int& TBufChild::GetFlag(){return flag.buf;}
char* TBufChild::GetCaption(){return "Cathode ion current density";}
void TBufChild::Paint1(TDC& dc)
{
  graph.Show(dc, field.GetBuf1(), param.ly, "y [sm]","j(y)");
}

// PARAM
int TParamChild::GetContext(){return __Param;}
int& TParamChild::GetFlag(){return flag.param;}
char* TParamChild::GetCaption(){return "Gas discharge parameters";}
void TParamChild::Paint1(TDC& dc)
{
  int i=20,j=20;
  char buf[40];
  sprintf(buf,"xsize=%i",param.xsize);
  dc.TextOut(i,j*1,buf);
  sprintf(buf,"ysize=%i",param.ysize);
  dc.TextOut(i,j*2,buf);
  sprintf(buf,"eds=%.0f",param.eds);
  dc.TextOut(i,j*3,buf);
  sprintf(buf,"resist=%.1f",param.resist);
  dc.TextOut(i,j*4,buf);
  sprintf(buf,"gamma=%.2f",param.gamma);
  dc.TextOut(i,j*5,buf);
  sprintf(buf,"c0=%.3f",param.c0);
  dc.TextOut(i,j*6,buf);
  sprintf(buf,"dt=%.3f",param.dt);
  dc.TextOut(i,j*7,buf);
  sprintf(buf,"lx=%.1f",param.lx);
  dc.TextOut(i,j*8,buf);
  sprintf(buf,"ly=%.1f",param.ly);
  dc.TextOut(i,j*9,buf);
  sprintf(buf,"lz=%.1f",param.lz);
  dc.TextOut(i,j*10,buf);
}

// GAMMA
int TGammaChild::GetContext(){return __Gamma;}
int& TGammaChild::GetFlag(){return flag.gamma;}
char* TGammaChild::GetCaption(){return "Gamma function";}
void TGammaChild::Paint1(TDC& dc)
{
  static const int XSIZE=101;
  static const int DFD=10.;
  static TSingleArray sar(XSIZE);
  static bool firstCall=true;
  if(firstCall)
  {
	 for(int i=0; i<XSIZE; i++) sar[i]=field.Gamma(i*DFD);
	 firstCall=false;
  }
  graph.Show(dc, sar, DFD*(XSIZE-1), "E [V/sm]","gamma");
}

// CURRENT
int TCurrentChild::GetContext(){return __Current;}
int& TCurrentChild::GetFlag(){return flag.current;}
char* TCurrentChild::GetCaption(){return "Current";}
void TCurrentChild::Paint1(TDC& dc)
{
  graph.Show(dc, tstat.GetCurrent(), tstat.GetTime(), "t [mksec]","I [mkA]");
}

// VOLTAGE
int TVoltageChild::GetContext(){return __Voltage;}
int& TVoltageChild::GetFlag(){return flag.voltage;}
char* TVoltageChild::GetCaption(){return "Voltage";}
void TVoltageChild::Paint1(TDC& dc)
{
  graph.Show(dc, tstat.GetVoltage(), tstat.GetTime(), "t [mksec]","U [V]");
}

