#include <pch.h>
#pragma hdrstop
#include <owl\framewin.h>
#include <mygraph.h>
#include "create.h"
#include "createse.rh"

int status;
TGraph graph;

class TMyWindow : public TFrameWindow
{
  public:
	 TMyWindow(TWindow *, const char *);
	 ~TMyWindow();
  protected:
	 void CmExit();
	 void CmCreate();
    bool flag;
    virtual void Paint(TDC&, bool, TRect&);
	 DECLARE_RESPONSE_TABLE(TMyWindow);
};

DEFINE_RESPONSE_TABLE1(TMyWindow, TWindow)
  EV_COMMAND(CM_CREATE, CmCreate),
  EV_COMMAND(CM_EXIT, CmExit),
END_RESPONSE_TABLE;

void
TMyWindow::Paint(TDC& dc, bool, TRect&)
{
  if(graph.status) graph.P
}

TMyWindow::TMyWindow(TWindow * parent, const char * title)
  : TFrameWindow(parent,title)
{
  Attr.X=0;
  Attr.Y=0;
  Attr.W=700;
  Attr.H=500;
  AssignMenu(ID_MENU);
  Attr.Style&=WS_BORDER;
  flag=0;
}

TMyWindow::~TMyWindow()
{}

//  TPaintDC dc(HWindow);

void
TMyWindow::CmCreate()
{
  create(TClientDC(HWindow));
}

void
TMyWindow::CmExit()
{
  CloseWindow();
}

class TMyApp : public TApplication
{
  public:
	 TMyApp() : TApplication(){}
  private:
	 void InitMainWindow()
	 {
		TMyWindow * MyWindow=new TMyWindow(0,"Creating He data file");
		EnableBWCC();
		MainWindow=MyWindow;
	 }
};

int OwlMain(int,char*[])
{
  TMyApp MyApp;
  return MyApp.Run();
}
