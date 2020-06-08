// Windows application
// Abramov A.A., 1997

#ifndef __MYAPP_H
#define __MYAPP_H

class TMyMainWindow: public TDecoratedMDIFrame
{
  public:
	 TMyMainWindow(TMDIClient& client);
};

class TMyApp: public TApplication
{
  public:
	 TMyApp();
	 ~TMyApp();
	 void SetText1(char* s){ tg1->SetText(s);}
	 void SetText2(char* s){ tg2->SetText(s);}
	 void SetText3(char* s){ tg3->SetText(s);}
	 void SetMenu2();
  protected:
	 virtual void InitMainWindow();
	 TTextGadget *tg1,*tg2,*tg3;
	 TControlBar * cb;
	 TStatusBar * sb;
	 TMyMainWindow * frame;
	 bool StartState;
};

#endif


