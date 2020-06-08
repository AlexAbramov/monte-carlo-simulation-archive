#include <pch.h>
#pragma hdrstop
#include <stdlib.h>
#include <string.h>
#include <param.h>
#include <flag.h>
#include <tstat.h>
#include <paramdia.h>
#include <paramdia.rh>
#include "discharg.h"
#include "mychild.h"
#include "myapp.rh"
#include "myapp.h"
#include "count.h"
#include "myrandom.h"
#include "myclient.h"
#include "context.h"

string HelpPath;

void
TMyClient::SetText()
{
  if(param.Status()==1)
  {
	 char tt[20];
	 sprintf(tt,"time=%.2f",param.time);
	 ((TMyApp*)GetApplication())->SetText1(tt);
	 sprintf(tt,"U=%.0f",param.voltage);
	 ((TMyApp*)GetApplication())->SetText2(tt);
	 sprintf(tt,"I=%.3f",param.current);
	 ((TMyApp*)GetApplication())->SetText3(tt);
  }
}

TMyClient::TMyClient(): TMDIClient()
{
//  SetBkgndColor(RGB(0x40, 0xff, 0xff));
  fileData = new TOpenSaveDialog::TData(OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
	 "(*.sms)|*.sms|", 0, "","sms");
  const int ssize=500;
  char ss[ssize]="";
  int i=GetCurrentDirectory(ssize,ss);
  if(i>ssize) error_message("The path to current directory too long");
  HelpPath=ss;
  HelpPath+="\\samos.hlp";
  rnd.RegistrateDirectory(ss);
  param.RegistrateDirectory(ss);
  ctxIndex=__Contents_;
//  HANDLE h=GetCurrentProcess();
//  SetPriorityClass(h,HIGH_PRIORITY_CLASS);
}

void
TMyClient::SetupWindow()
{
  TMDIClient::SetupWindow();
  fieldChild=0;
  cioChild=0;
  bufChild=0;
  currentChild=0;
  voltageChild=0;
  paramChild=0;
}

DEFINE_RESPONSE_TABLE1(TMyClient, TMDIClient)
  EV_COMMAND(CM_FILENEW, CmFileNew),
  EV_COMMAND(CM_FILEOPEN, CmFileOpen),
  EV_COMMAND(CM_FILESAVE, CmFileSave),
  EV_COMMAND(CM_FILESAVEAS, CmFileSaveAs),
  EV_COMMAND(CM_ELECTRON, CmElectron),
  EV_COMMAND_ENABLE(CM_ELECTRON, CmElectron1),
  EV_COMMAND(CM_FIELD, CmField),
  EV_COMMAND_ENABLE(CM_FIELD, CmField1),
  EV_COMMAND(CM_CIO, CmCio),
  EV_COMMAND_ENABLE(CM_CIO, CmCio1),
  EV_COMMAND(CM_BUF, CmBuf),
  EV_COMMAND_ENABLE(CM_BUF, CmBuf1),
  EV_COMMAND(CM_CURRENT, CmCurrent),
  EV_COMMAND_ENABLE(CM_CURRENT, CmCurrent1),
  EV_COMMAND(CM_VOLTAGE, CmVoltage),
  EV_COMMAND_ENABLE(CM_VOLTAGE, CmVoltage1),
  EV_COMMAND(CM_PARAM, CmParam),
  EV_COMMAND_ENABLE(CM_PARAM, CmParam1),
  EV_COMMAND(CM_ABOUT, CmAbout),
  EV_COMMAND(CM_STEP, CmStep),
  EV_COMMAND_ENABLE(CM_STEP, CmStep1),
  EV_COMMAND(CM_RUN, CmRun),
  EV_COMMAND_ENABLE(CM_RUN, CmRun1),
  EV_COMMAND(CM_STOP, CmStop),
  EV_COMMAND_ENABLE(CM_STOP, CmStop1),
//  EV_COMMAND(CM_GAMMA, CmGamma),
//  EV_COMMAND_ENABLE(CM_GAMMA, CmGamma1),
  EV_COMMAND(CM_EDIT, CmEdit),
  EV_COMMAND(CM_CONTENTS, CmContents),
  EV_WM_TIMER,
END_RESPONSE_TABLE;

bool
TMyClient::CanClose()
{
  if(flag.run) CmStop();
  return true;
}

void
TMyClient::CmFileNew()
{
  if( TParamDial(this).Execute() == IDOK )
  {
	 if(flag.run) CmStop();
	 discharge.Scan();
	 flag.opened=1;
	 flag.saved=0;
	 SetText();
	 ((TMyApp*)GetApplication())->SetMenu2();
	 CmUpdate();
  }
}

void
TMyClient::CmEdit()
{
  if(flag.opened==0) return;
  if( TParDial(this).Execute() == IDOK )
  {
	 flag.saved=0;
	 if(flag.param) paramChild->Invalidate();
  }
}

void
TMyClient::CmFileOpen()
{
  if((TFileOpenDialog(this, *fileData)).Execute() == IDOK)
  {
	 if(flag.run) CmStop();
	 discharge.Read(fileData->FileName);
	 flag.opened=1;
	 flag.saved=0;
	 SetText();
	 ((TMyApp*)GetApplication())->SetMenu2();
	 CmUpdate();
  }
}

void
TMyClient::CmFileSaveAs()
{
  if(flag.opened==0) return;
  if((TFileSaveDialog(this,*fileData)).Execute() == IDOK)
  {
	 discharge.Write(fileData->FileName);
	 flag.saved=1;
  }
}

void
TMyClient::CmFileSave()
{
  if(flag.opened==0) return;
  if(flag.saved==0) CmFileSaveAs();
  else discharge.Write(fileData->FileName);
}

void
TMyClient::CmElectron()
{
  if(flag.opened==1 && flag.electron==0)
  {
	 TElectronChild* child=new TElectronChild(*this);
	 child->Create();
  }
}

void
TMyClient::CmField()
{
  if(flag.opened==1 && flag.field==0)
  {
	 fieldChild=new TFieldChild(*this);
	 fieldChild->Create();
  }
}

void
TMyClient::CmCio()
{
  if(flag.opened==1 && flag.cio==0)
  {
	 cioChild=new TCioChild(*this);
	 cioChild->Create();
  }
}

void
TMyClient::CmParam()
{
  if(flag.opened==1 && flag.param==0)
  {
	 paramChild=new TParamChild(*this);
	 paramChild->Create();
  }
}

void
TMyClient::CmBuf()
{
  if(flag.opened==1 && flag.buf==0)
  {
	 bufChild=new TBufChild(*this);
	 bufChild->Create();
  }
}

void
TMyClient::CmCurrent()
{
  if(flag.opened==1 && flag.current==0)
  {
	 currentChild=new TCurrentChild(*this);
	 currentChild->Create();
  }
}

void
TMyClient::CmVoltage()
{
  if(flag.opened==1 && flag.voltage==0)
  {
	 voltageChild=new TVoltageChild(*this);
	 voltageChild->Create();
  }
}

void
TMyClient::CmGamma()
{
  if(flag.opened==1 && flag.gamma==0)
  {
	 TGammaChild* child=new TGammaChild(*this);
	 child->Create();
  }
}

void
TMyClient::CmAbout()
{
  TDialog(this,"About").Execute();
}

void
TMyClient::CmUpdate()
{
  if(flag.opened==1)
  {
	 if(flag.field) fieldChild->Invalidate();
	 if(flag.cio) cioChild->Invalidate();
	 if(flag.current) currentChild->Invalidate();
	 if(flag.voltage) voltageChild->Invalidate();
	 if(flag.buf) bufChild->Invalidate();
	 if(flag.param) paramChild->Invalidate();
  }
}

static DWORD threadId=0;
static HANDLE hThread=0;
static bool continueThread=true;
static bool oneStep=false;

static DWORD WINAPI ThreadFunction(LPVOID lpParameter)
{
  while(continueThread)
  {
	 if(flag.run && count.Status()==1 && param.time>count.Time()) count.Update();
	 discharge.Step();
	 ((TMyClient*)lpParameter)->UpdateAfterStep();
	 if(oneStep) SuspendThread(hThread);
  }
  DWORD res;
  ExitThread(res);
  return res;
}

void
TMyClient::UpdateAfterStep()
{
  SetText();
  int i=param.time/param.dt;
  if(i%param.ntimes == 0) CmUpdate();
}

void
TMyClient::CmRun()
{
  if(flag.opened==1 && flag.run==0)
  {
	 flag.run=1;
//	 SetTimer(ID_TIMER,TIMER_RATE);
	 oneStep=false;
	 if(!hThread) hThread=CreateThread(0,0,ThreadFunction,this,0,&threadId);
	 else ResumeThread(hThread);
//	 SetThreadPriority(hThread,THREAD_PRIORITY_HIGHEST);
  }
}

void
TMyClient::CmStep()
{
  if(flag.opened==1)
  {
	 oneStep=true;
	 if(!hThread) hThread=CreateThread(0,0,ThreadFunction,this,0,&threadId);
	 else ResumeThread(hThread);
  }
}

void
TMyClient::CmStop()
{
  flag.run=0;
//  KillTimer(ID_TIMER);
  if(hThread) SuspendThread(hThread);
}

void
TMyClient::EvTimer(uint /*ID_TIMER*/)
{
  if(flag.run)
  {
//	 if(count.Status()==1 && param.time>count.Time()) count.Update();
//	 CmStep();
  }
}

void
TMyClient::CmElectron1(TCommandEnabler& ce)
{
  ce.Enable(!flag.electron);
}

void
TMyClient::CmField1(TCommandEnabler& ce)
{
  ce.Enable(!flag.field);
}

void
TMyClient::CmParam1(TCommandEnabler& ce)
{
  ce.Enable(!flag.param);
}

void
TMyClient::CmStep1(TCommandEnabler& ce)
{
  ce.Enable(!flag.run);
}

void
TMyClient::CmRun1(TCommandEnabler& ce)
{
  ce.Enable(!flag.run);
}

void
TMyClient::CmStop1(TCommandEnabler& ce)
{
  ce.Enable(flag.run);
}

void
TMyClient::CmCurrent1(TCommandEnabler& ce)
{
  ce.Enable(!flag.current);
}

void
TMyClient::CmVoltage1(TCommandEnabler& ce)
{
  ce.Enable(!flag.voltage);
}

void
TMyClient::CmCio1(TCommandEnabler& ce)
{
  ce.Enable(!flag.cio);
}

void
TMyClient::CmBuf1(TCommandEnabler& ce)
{
  ce.Enable(!flag.buf);
}

void
TMyClient::CmGamma1(TCommandEnabler& ce)
{
  ce.Enable(!flag.gamma);
}

void
TMyClient::CmContents()
{
  WinHelp(HelpPath.c_str(), HELP_CONTENTS , 0);
}

TMyClient::~TMyClient()
{
  continueThread=false;
  delete fileData;
}
