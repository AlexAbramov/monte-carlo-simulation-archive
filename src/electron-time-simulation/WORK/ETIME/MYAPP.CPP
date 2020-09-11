#include <owl\controlb.h>
//#include <owl\messageb.h>
#include <owl\statusba.h>
#include <owl\buttonga.h>
#pragma hdrstop
#include "myapp.rh"
#include "myclient.h"
#include "myapp.h"

void
TMyApp::SetupSpeedBar(TDecoratedMDIFrame* frame)
{
  TControlBar* cb = new TControlBar(frame);
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
// Add fly-over help hints.
  cb->SetHintMode(TGadgetWindow::EnterHints);
  frame->Insert(*cb, TDecoratedFrame::Top);
}

void
TMyApp::InitMainWindow()
{
  EnableCtl3d();
  EnableBWCC();
  nCmdShow = SW_SHOWMAXIMIZED;
  TMyClient* client=new TMyClient();
  TDecoratedMDIFrame* frame = new TDecoratedMDIFrame("Electron avalanches (time model)","Menu",*client,TRUE);
  frame->Attr.Style |= WS_BORDER | WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME | WS_VISIBLE;
//  frame->Attr.Style |= WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE;
//  frame->Attr.Style &= ~(WS_CHILD);
//  frame->SetBkgndColor(::GetSysColor(COLOR_APPWORKSPACE));
  frame->SetIcon(this,"App");
//  frame->AssignMenu(ID_MENU);
//  frame->Attr.AccelTable = ID_MENU;
  SetupSpeedBar(frame);

  TStatusBar* sb = new TStatusBar(frame);
  sb->Insert(tg1);
  sb->Insert(tg2);
  frame->Insert(*sb, TDecoratedFrame::Bottom);

  SetMainWindow(frame);
//  frame->SetMenuDescr(TMenuDescr(MDI_MENU));
}

int OwlMain(int, char* [])
{
  TMyApp app;
  return app.Run();
}
