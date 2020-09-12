// Windows application
// Abramov A.A., 1997

#ifndef __MYAPP_H
#define __MYAPP_H

#if !defined(OWL_APPLICAT_H)
  #include <owl\applicat.h>
#endif
#if !defined(OWL_DECMDIFR_H)
  #include <owl\decmdifr.h>
#endif
#if !defined(OWL_TEXTGADG_H)
  #include <owl\textgadg.h>
#endif

class TMyMainWindow: public TDecoratedMDIFrame
{
  public:
	 TMyMainWindow(TMDIClient& client);
//	 virtual void EvEnterIdle(UINT source, HWND hWndDlg);
//DECLARE_RESPONSE_TABLE(TMyMainWindow);
};

class TMyApp: public TApplication
{
  public:
	 TMyApp(): TApplication("mc"){}
	 void SetText1(char* s){ tg1.SetText(s);}
	 void SetText2(char* s){ tg2.SetText(s);}
	 void SetMainMenu();
  protected:
	 virtual void InitMainWindow();
	 TTextGadget tg1,tg2;
};

extern bool F1Pressed;
extern bool StartMenu;

#endif


