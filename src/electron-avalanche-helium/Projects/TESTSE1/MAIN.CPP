#include <owl\owlpch.h>
#pragma hdrstop
#include <mygraph.h>
#include <mylib.h>
#include <string.h>
#include <heselas.h>
#include <hesex.h>
#include <hesion.h>
#include "main.rh"

const int ar_size=501;

class TMyWindow : public TFrameWindow
{
  public:
	 TMyWindow(TWindow *, const char *);
	 ~TMyWindow();
	 TSingleArray * psar;
	 TGraph * pgr;
	 THeSelas * pheselas;
	 THeSex * phesex;
	 THeSion * phesion;
  protected:
	 void CmElastic();
	 void CmExcited();
	 void CmIonising();
	 void CmExit();
	 void MyPaint(int);
//	 void EvSize(UINT,TSize&);
	 DECLARE_RESPONSE_TABLE(TMyWindow);
};

DEFINE_RESPONSE_TABLE1(TMyWindow, TWindow)
  EV_COMMAND(CM_ELASTIC, CmElastic),
  EV_COMMAND(CM_EXCITED, CmExcited),
  EV_COMMAND(CM_IONISING, CmIonising),
  EV_COMMAND(CM_EXIT, CmExit),
END_RESPONSE_TABLE;

TMyWindow::TMyWindow(TWindow * parent, const char * title)
  : TFrameWindow(parent,title)
{
  Attr.X=0;
  Attr.Y=0;
  Attr.W=600;
  Attr.H=400;
  AssignMenu(ID_MENU);
  Attr.Style&=WS_BORDER;
  psar=new TSingleArray(ar_size);
  pgr=new TGraph("..\\..\\dat\\graph.dat");
  pheselas=new THeSelas();
  phesex=new THeSex();
  phesion=new THeSion();
}

TMyWindow::~TMyWindow()
{
  delete psar,pgr,pheselas,phesex,phesion;
}


void
TMyWindow::MyPaint(int flag)
{
//  dc.TextOut(100,100,"Hallo girls & boys!");
  if(flag<1||flag>3) return;
  Invalidate();
  TPaintDC dc(HWindow);
  char textx[]="energy [eV]";
  char texty[50];
  if(flag==1) sprintf(texty,"%s","Elastic sequation [A*A]");
  if(flag==2) sprintf(texty,"%s","Excited sequation [A*A]");
  if(flag==3) sprintf(texty,"%s","Ionising sequation [A*A]");
  for(int i=0;i<ar_size;i++)
  {
	 float e=i;
	 float s;
	 if(flag==1)s=pheselas->Total(e);
	 if(flag==2)s=phesex->Sequation(0,3,e);
	 if(flag==3)s=phesion->Total(e);
	 (*psar)[i]=s;
  }
  float emax=ar_size-1;
  pgr->Show(dc,*psar,emax,textx,texty);
}

void
TMyWindow::CmExit()
{
  CloseWindow();
}

void
TMyWindow::CmElastic()
{
  MyPaint(1);
}

void
TMyWindow::CmExcited()
{
//  message("Features not implemented");
  MyPaint(2);
}

void
TMyWindow::CmIonising()
{
  MyPaint(3);
}

class TMyApp : public TApplication
{
  public:
	 TMyApp() : TApplication(){}
  private:
	 void InitMainWindow()
	 {
		TMyWindow * MyWindow=new TMyWindow(0,"Sequations");
		EnableBWCC();
		MainWindow=MyWindow;
	 }
};

int OwlMain(int,char*[])
{
  TMyApp MyApp;
  return MyApp.Run();
}
