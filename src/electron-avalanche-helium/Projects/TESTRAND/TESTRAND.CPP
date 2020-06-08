#include <owl/applicat.h>
#include <owl/framewin.h>
#include <math.h>
#pragma hdrstop
#include <mygraph.h>
#include <mylib.h>
#include <myrandom.h>
#include "testrand.rh"

const int xsize=100;

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
	 void CmTest();
	 TGraph graph;
	 TSingleArray sar;
	 TClientDC * pdc;
	 virtual void SetupWindow();
  DECLARE_RESPONSE_TABLE(TMyWindow);
};

void
TMyWindow::SetupWindow()
{
  pdc=new TClientDC(HWindow);
  sar.Init(xsize);
}

DEFINE_RESPONSE_TABLE1(TMyWindow, TWindow)
  EV_COMMAND(CM_TEST, CmTest),
END_RESPONSE_TABLE;

void
TMyWindow::CmTest()
{
  Invalidate();
  for(long int i=0;i<=50000L;i++)
  {
	 float r=rnd[0];
	 int ir=r*xsize;
	 if(ir>=xsize) ir=xsize-1;
	 sar[ir]++;
	 if(i%10000==0)
	 {
		TRect rect;
		pdc->GetClipBox(rect);
		HDC hdc=HDC(*pdc);
		TBitmap bitmap(*pdc,rect.Width(),rect.Height());
		BITMAP bm;
		bitmap.GetObject(bm);
		TMemoryDC mdc(*pdc);
		mdc.SelectObject(bitmap);
//		mdc.FillRect(rect,TBrush(TColor::White));
		mdc.SetBkColor(TColor::White);
		graph.Show(mdc,sar,1.,"x","y");
		pdc->BitBlt(rect, mdc,TPoint(0,0));
	 }
  }
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
