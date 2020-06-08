#include <pch.h>
#pragma hdrstop
#include <mylib.h>
#include <conio.h>
#include "myapp.rh"
#include "myclient.h"
#include "myapp.h"
#include "Ctl3d.h"

bool F1Pressed;

TMyMainWindow::TMyMainWindow(TMDIClient& client): TDecoratedMDIFrame("Electron Avalanches in Helium Discharge","Menu1",client,TRUE)
{
  Attr.Style |= WS_BORDER | WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME | WS_VISIBLE;
  Attr.AccelTable = "Accelerators";
  F1Pressed=false;
}

/*DEFINE_RESPONSE_TABLE1(TMyMainWindow, TDecoratedMDIFrame)
  EV_WM_ENTERIDLE,
END_RESPONSE_TABLE;

void
TMyMainWindow::EvEnterIdle(UINT source, HWND)
{
  // if the keystate high bit is set, then the key is pressed
  if(!F1Pressed && source == MSGF_MENU && (::GetKeyState(VK_F1) & 0x8000))
  {
	 F1Pressed = true;
	 PostMessage(WM_KEYDOWN, VK_RETURN);
  }
  else DefaultProcessing();
}*/

TMyApp::TMyApp(): TApplication("Monte-Carlo")
{
  tg1=new TTextGadget();
  tg2=new TTextGadget();
  bg1=new TButtonGadget(CM_LEFT, CM_LEFT);
  bg2=new TButtonGadget(CM_SET, CM_SET);
  bg3=new TButtonGadget(CM_RIGHT, CM_RIGHT);
  Ctl3dRegister(HInstance);
  Ctl3dAutoSubclass(HInstance);
}

TMyApp::~TMyApp()
{
  if(!AppState) delete bg1,bg2,bg3;
  Ctl3dUnregister(HInstance);
}

void
TMyApp::SetMainMenu(bool NewState)
{
  if(StartState)
  {
	 cb->Insert(*new TButtonGadget(CM_FILESAVE, CM_FILESAVE));
	 cb->Insert(*new TSeparatorGadget(6));
	 cb->Insert(*new TButtonGadget(CM_STEP, CM_STEP));
	 cb->Insert(*new TButtonGadget(CM_RUN, CM_RUN));
	 cb->Insert(*new TButtonGadget(CM_STOP, CM_STOP));
	 cb->Insert(*new TSeparatorGadget(6));
	 StartState=false;
	 if(NewState)
	 {
		cb->Insert(*bg1);
		cb->Insert(*bg2);
		cb->Insert(*bg3);
		GetMainWindow()->AssignMenu("Menu");
		cb->LayoutSession();
	 }
	 else
	 {
		GetMainWindow()->AssignMenu("Menu2");
		cb->LayoutSession();
	 }
  }
  else
  {
	 if(!AppState&&NewState)
	 {
		cb->Insert(*bg1);
		cb->Insert(*bg2);
		cb->Insert(*bg3);
		GetMainWindow()->AssignMenu("Menu");
		cb->LayoutSession();
	 }
	 if(AppState&&!NewState)
	 {
		cb->Remove(*bg1);
		cb->Remove(*bg2);
		cb->Remove(*bg3);
		GetMainWindow()->AssignMenu("Menu2");
		cb->LayoutSession();
		cb->Invalidate();
	 }
  }
  AppState=NewState;
}

void
TMyApp::InitMainWindow()
{
  StartState=true;
  AppState=false;
  nCmdShow = SW_SHOWMAXIMIZED;
  TMyClient* client=new TMyClient();
  frame = new TMyMainWindow(*client);

  cb = new TControlBar(frame);
  cb->Insert(*new TButtonGadget(CM_FILENEW, CM_FILENEW));
  cb->Insert(*new TButtonGadget(CM_FILEOPEN, CM_FILEOPEN));
  cb->SetHintMode(TGadgetWindow::EnterHints);// Add fly-over help hints.
  frame->Insert(*cb, TDecoratedFrame::Top);

  TStatusBar* sb = new TStatusBar(frame);
  sb->Insert(*tg1);
  sb->Insert(*tg2);
  frame->SetIcon(this,"App");
  frame->Insert(*sb, TDecoratedFrame::Bottom);

  SetMainWindow(frame);
}

int OwlMain(int, char* [])
{
  TMyApp app;
  return app.Run();
}
