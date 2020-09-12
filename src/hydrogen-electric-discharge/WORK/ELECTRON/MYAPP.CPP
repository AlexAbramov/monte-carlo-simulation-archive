#include <owl\controlb.h>
#include <owl\statusba.h>
#include <owl\buttonga.h>
#pragma hdrstop
#include <mylib.h>
#include "myapp.rh"
#include "myclient.h"
#include "myapp.h"

bool F1Pressed;
bool StartMenu;

/*
void
TMyApp::SetMainMenu()
{
  if(StartMenu)
  {
	 StartMenu=false;
  }
}*/

TMyMainWindow::TMyMainWindow(TMDIClient& client): TDecoratedMDIFrame("Electron avalanches in hydrogen discharge","Menu",client,TRUE)
{
  Attr.Style |= WS_BORDER | WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME | WS_VISIBLE;
  Attr.AccelTable = "Accelerators";
  F1Pressed=false;
  StartMenu=false;
}

/*
DEFINE_RESPONSE_TABLE1(TMyMainWindow, TDecoratedMDIFrame)
  EV_WM_ENTERIDLE,
END_RESPONSE_TABLE;

void
TMyMainWindow::EvEnterIdle(UINT source, HWND )
{

  // if the keystate high bit is set, then the key is pressed
  if(source == MSGF_MENU && (::GetKeyState(VK_F1) & 0x8000))
  {
	 F1Pressed = true;
	 PostMessage(WM_KEYDOWN, VK_RETURN);
	 return;
  }
  else
  DefaultProcessing();
}
*/

void
TMyApp::InitMainWindow()
{
  EnableCtl3d();
  EnableBWCC();
  nCmdShow = SW_SHOWMAXIMIZED;
  TMyClient* client=new TMyClient();
  TMyMainWindow * frame = new TMyMainWindow(*client);

  TControlBar * cb = new TControlBar(frame);
  cb->Insert(*new TButtonGadget(CM_FILENEW, CM_FILENEW));
  cb->Insert(*new TButtonGadget(CM_FILEOPEN, CM_FILEOPEN));
  cb->Insert(*new TButtonGadget(CM_FILESAVE, CM_FILESAVE));
  cb->Insert(*new TSeparatorGadget(6));
  cb->Insert(*new TButtonGadget(CM_STEP, CM_STEP));
  cb->Insert(*new TButtonGadget(CM_RUN, CM_RUN));
  cb->Insert(*new TButtonGadget(CM_STOP, CM_STOP));
  cb->Insert(*new TSeparatorGadget(6));
  cb->Insert(*new TButtonGadget(CM_LEFT, CM_LEFT));
  cb->Insert(*new TButtonGadget(CM_SET, CM_SET));
  cb->Insert(*new TButtonGadget(CM_RIGHT, CM_RIGHT));
  cb->SetHintMode(TGadgetWindow::EnterHints);// Add fly-over help hints.
  frame->Insert(*cb, TDecoratedFrame::Top);

  TStatusBar* sb = new TStatusBar(frame);
  sb->Insert(tg1);
  sb->Insert(tg2);
  frame->SetIcon(this,"App");
  frame->Insert(*sb, TDecoratedFrame::Bottom);

  SetMainWindow(frame);
}

int OwlMain(int, char* [])
{
  TMyApp app;
  return app.Run();
}
