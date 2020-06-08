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
#if !defined(OWL_CONTROLB_H)
  #include <owl\controlb.h>
#endif
#if !defined(OWL_BUTTONGA_H)
  #include <owl\buttonga.h>
#endif

extern bool F1Pressed;

class TMyMainWindow: public TDecoratedMDIFrame
{
  public:
	 TMyMainWindow(TMDIClient& client);
//  protected:
//	 void EvEnterIdle(UINT, HWND);
//	 DECLARE_RESPONSE_TABLE(TMyMainWindow);
};

class TMyApp: public TApplication
{
  public:
	 TMyApp();
	 ~TMyApp();
	 void SetText1(char* s){ tg1->SetText(s);}
	 void SetText2(char* s){ tg2->SetText(s);}
	 void SetMainMenu(bool);
	 void SetMenu2();
  protected:
	 virtual void InitMainWindow();
	 TTextGadget * tg1;
	 TTextGadget * tg2;
	 TButtonGadget * bg1;
	 TButtonGadget * bg2;
	 TButtonGadget * bg3;
	 TControlBar * cb;
	 TMyMainWindow * frame;
	 bool AppState;
	 bool StartState;
};

#endif


