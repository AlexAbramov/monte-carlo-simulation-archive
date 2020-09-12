#include <owl\owlpch.h>
#pragma hdrstop
#include <string.h>
#include <mygraph.h>
#include <mylib.h>
#include <he.h>
#include <cd.h>
#include "testse2.rh"

class TMyWindow : public TFrameWindow
{
  public:
	 TMyWindow(TWindow *, const char *);
	 ~TMyWindow();
	 TSingleArray * psar;
	 TGraph * pgraph;
	 TDoubleArray * pdar;
	 TGraphic * pgraphic;
  protected:
	 int xsize;
	 int ysize;
	 int sxsize;
	 void CmSelas();
	 void CmSex();
	 void CmSion();
	 void CmSpelas();
	 void CmSpex();
	 void CmSpion();
	 void CmStot();
	 void CmFtot();
	 void CmFtot1();
	 void CmExit();
	 void MyPaint(int);
//	 void EvSize(UINT,TSize&);
	 DECLARE_RESPONSE_TABLE(TMyWindow);
};

DEFINE_RESPONSE_TABLE1(TMyWindow, TWindow)
  EV_COMMAND(CM_SELAS, CmSelas),
  EV_COMMAND(CM_SEX, CmSex),
  EV_COMMAND(CM_SION, CmSion),
  EV_COMMAND(CM_SPELAS, CmSpelas),
  EV_COMMAND(CM_SPEX, CmSpex),
  EV_COMMAND(CM_SPION, CmSpion),
  EV_COMMAND(CM_STOT, CmStot),
  EV_COMMAND(CM_FTOT, CmFtot),
  EV_COMMAND(CM_FTOT1, CmFtot1),
  EV_COMMAND(CM_EXIT, CmExit),
END_RESPONSE_TABLE;

TMyWindow::TMyWindow(TWindow * parent, const char * title)
  : TFrameWindow(parent,title)
{
  Attr.X=0;
  Attr.Y=0;
  Attr.W=700;
  Attr.H=500;
  AssignMenu(ID_MENU);
  Attr.Style&=WS_BORDER;
  pgraph=new TGraph();
  pgraphic=new TGraphic();
  FILE * fp=handle_scan("xysize.inp");
	 fscanf(fp,"%i%i%i",&xsize,&ysize,&sxsize);
  fclose(fp);
  psar=new TSingleArray(sxsize);
  pdar=new TDoubleArray(ysize,xsize);
}

TMyWindow::~TMyWindow()
{
  delete psar,pgraph,pdar,pgraphic;
}


void
TMyWindow::MyPaint(int flag)
{
  int aa=0;
  int bb=0;
  if(flag>=1&&flag<=6) aa=1;
  if(flag>=11&&flag<=13) bb=1;
  if(aa==0 && bb==0) return;
  Invalidate();
  TPaintDC dc(HWindow);
  char textx[]="energy [eV]";
  char texty[70];
  if(aa)
  {
	 if(flag==1) sprintf(texty,"%s","Elastic sequation [1/sm]");
	 if(flag==2) sprintf(texty,"%s","Excited sequation [1/sm]");
	 if(flag==3) sprintf(texty,"%s","Ionising sequation [1/sm]");
	 if(flag==4) sprintf(texty,"%s","Total sequation [1/sm]");
	 if(flag==5) sprintf(texty,"%s","Total frequence [sqev/sm]");
	 if(flag==6) sprintf(texty,"%s","Total frequence [MHz]");
	 for(int i=0;i<sxsize;i++)
	 {
		float e=i;
		float s;
		if(flag==1)s=he.Spex1(e,0);//s=he.Selas(e);
		if(flag==2)s=he.Spex1(e,1);//s=he.Sex(e);
		if(flag==3)s=he.Spex1(e,2);//s=he.Sion(e);
		if(flag==4)s=he.Spex1(e,3);//s=he.Stot(e);
		if(flag==5)s=he.Ftot(e);
		if(flag==6)s=he.Ftot1(e);
		(*psar)[i]=s;
	 }
	 float emax=sxsize-1;
	 pgraph->Show(dc,*psar,emax,textx,texty);
  }
  if(bb==1)
  {
	 if(flag==11) sprintf(texty,"%s","Angle,rad (elastic)");
	 if(flag==12) sprintf(texty,"%s","Level (excited)");
	 if(flag==13) sprintf(texty,"%s","Share (ionising)");
	 for(int j=0;j<ysize;j++)
	 for(int i=0;i<xsize;i++)
	 {
		float e=i;
		float r=j/float(ysize-1);
		float s;
		if(flag==11)s=he.Spelas(e,r);
		if(flag==12)s=he.Spex(e,r);
		if(flag==13)s=he.Spion(e,r);
		(*pdar)[j][i]=s;
	 }
	 float emax=xsize-1;
	 float rmax=1.;
	 pgraphic->Show(dc,*pdar,emax,rmax,texty);
  }
}

void
TMyWindow::CmExit()
{
  CloseWindow();
}

void
TMyWindow::CmSelas()
{
//  char tt[30];
//  sprintf(tt,"conc=%f",he.Conc());
//  message(tt);
  MyPaint(1);
}

void
TMyWindow::CmSex()
{
//  message("Features not implemented");
  MyPaint(2);
}

void
TMyWindow::CmSion()
{
  MyPaint(3);
}

void
TMyWindow::CmStot()
{
  MyPaint(4);
}

void
TMyWindow::CmFtot()
{
  MyPaint(5);
}

void
TMyWindow::CmFtot1()
{
  MyPaint(6);
}

void
TMyWindow::CmSpelas()
{
  MyPaint(11);
}

void
TMyWindow::CmSpex()
{
//  message("Features not implemented");
  MyPaint(12);
}

void
TMyWindow::CmSpion()
{
  MyPaint(13);
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
