#include <pch.h>
#pragma hdrstop
#include "ctl3d.h"
#include "myapp.rh"
#include "myclient.h"
#include "myapp.h"

TMyMainWindow::TMyMainWindow(TMDIClient& client): TDecoratedMDIFrame("Self-consistent model of helium discharge","Menu1",client,TRUE)
{
  Attr.Style |= WS_BORDER | WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME | WS_VISIBLE;
  Attr.AccelTable = "Accelerators";
}

TMyApp::TMyApp()
{
  tg1=new TTextGadget();
  tg2=new TTextGadget();
  tg3=new TTextGadget();
  Ctl3dRegister(HInstance);
  Ctl3dAutoSubclass(HInstance);
  cb=0;
  sb=0;
}

TMyApp::~TMyApp()
{
  Ctl3dUnregister(HInstance);
}

void
TMyApp::SetMenu2()
{
  if(StartState)
  {
	 cb->Insert(*new TButtonGadget(CM_FILESAVE, CM_FILESAVE));
	 cb->Insert(*new TSeparatorGadget(6));
	 cb->Insert(*new TButtonGadget(CM_STEP, CM_STEP));
	 cb->Insert(*new TButtonGadget(CM_RUN, CM_RUN));
	 cb->Insert(*new TButtonGadget(CM_STOP, CM_STOP));
	 GetMainWindow()->AssignMenu("Menu2");
	 cb->LayoutSession();
	 StartState=false;
  }
}

void
TMyApp::InitMainWindow()
{
  StartState=true;
  EnableCtl3d();
  nCmdShow = SW_SHOWMAXIMIZED;
  TMyClient* client=new TMyClient();
  frame = new TMyMainWindow(*client);
//  frame->Attr.Style |= WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE;
//  frame->Attr.Style &= ~(WS_CHILD);
//  frame->SetBkgndColor(::GetSysColor(COLOR_APPWORKSPACE));
  frame->SetIcon(this,"App");
  cb = new TControlBar(frame);
  cb->Insert(*new TButtonGadget(CM_FILENEW, CM_FILENEW));
  cb->Insert(*new TButtonGadget(CM_FILEOPEN, CM_FILEOPEN));
  cb->SetHintMode(TGadgetWindow::EnterHints);// Add fly-over help hints.
  frame->Insert(*cb, TDecoratedFrame::Top);

  sb = new TStatusBar(frame);
  sb->Insert(*tg1);
  sb->Insert(*tg2);
  sb->Insert(*tg3);
  frame->Insert(*sb, TDecoratedFrame::Bottom);

  SetMainWindow(frame);
}

int OwlMain(int, char* [])
{
  TMyApp app;
  return app.Run();
}
