#include <owl/applicat.h>
#include <owl/framewin.h>
#include <math.h>
#pragma hdrstop
#include <mygraph.h>
#include <mylib.h>
#include "testgr.rh"

float func(float x,float y)
{
  x*=2.*M_PI;
  y*=2.*M_PI;
  float z=sin(x)*sin(y);
  if(z<0.) z=-z;
  return z;
}

const int xsize=51,ysize=31;
const float xmax=xsize-1.,ymax=ysize-1.;

class TMyWindow : public TFrameWindow
{
  public:
	 TMyWindow(TWindow * parent,char * title) : TFrameWindow(parent,title)
	 {
		Attr.H=500;
		Attr.W=700;
		this->AssignMenu("COMMANDS");
	 }

  protected:
	 void CmEdit();
	 void CmView();

  DECLARE_RESPONSE_TABLE(TMyWindow);
};

DEFINE_RESPONSE_TABLE1(TMyWindow, TWindow)
  EV_COMMAND(CM_EDIT, CmEdit),
  EV_COMMAND(CM_VIEW, CmView),
END_RESPONSE_TABLE;

void
TMyWindow::CmEdit()
{
  Invalidate();
}

void
TMyWindow::CmView()
{

  TClientDC dc(HWindow);
  int i,j;

  TSingleArray sar(xsize);
  float xx[xsize];
  float yy[xsize];
  for(i=0;i<xsize;i++)
  {
	 float x=i;x*=x;
	 sar[i]=x;
	 xx[i]=x;
	 yy[i]=x;
  }
  TGraph graph;
  graph.Show(dc,sar,xmax,"x","y");
  message("Pause");
  graph.Show(dc,xsize,yy,xmax,"x","y");
  message("Pause");
  graph.Show(dc,xsize,xx,yy,"x","y");
  message("Pause");

  TDoubleArray dar(ysize,xsize);
  for(i=0;i<dar.XSize();i++)
  for(j=0;j<dar.YSize();j++)
  {
	 float x=i/float(dar.XSize()-1);
	 float y=j/float(dar.YSize()-1);
	 dar[j][i]=func(x,y);
  }
  TGraphic graphic;
  graphic.Show(dc,dar,xmax,ymax);
}

class TMyApp : public TApplication
{
  public:
	 TMyApp() : TApplication() {}

	 void InitMainWindow()
	 {
		MainWindow = new TMyWindow(0, "MainWindow");
	 }
};

int
OwlMain(int /*argc*/, char* /*argv*/ [])
{
  return TMyApp().Run();
}
