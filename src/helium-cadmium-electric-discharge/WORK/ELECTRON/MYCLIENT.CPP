#include <owl\inputdia.h>
#include <stdlib.h>
#include <string.h>
#pragma hdrstop
#include <param.h>
#include <flag.h>
#include <paramdia.h>
#include <paramdia.rh>
#include "discharg.h"
#include "mychild.h"
#include "myapp.rh"
#include "myapp.h"
#include "myclient.h"

void
TMyClient::SetText1()
{
  if(param.Status()==1)
  {
	 char tt[20];
	 sprintf(tt,"nlav=%li",param.nlav);
	 ((TMyApp*)GetApplication())->SetText1(tt);
  }
}

void
TMyClient::SetText2()
{
  if(param.Status()==1)
  {
	 char tt[20];
	 sprintf(tt,"x=%.2f",iseq*param.dx);
	 ((TMyApp*)GetApplication())->SetText2(tt);
  }
}

TMyClient::TMyClient(): TMDIClient()
{
  SetBkgndColor(RGB(0x40, 0xff, 0xff));
  fileData = new TOpenSaveDialog::TData(OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
	 "(*.ele)|*.ele|", 0, "","ele");
}

void
TMyClient::SetupWindow()
{
  TMDIClient::SetupWindow();
  energyChild=0;
  vdrChild=0;
  evxChild=0;
  fexChild=0;
  fioChild=0;
  fre1Child=0;
}

TMyClient::~TMyClient()
{
  delete fileData;
}

DEFINE_RESPONSE_TABLE1(TMyClient, TMDIClient)
  EV_COMMAND(CM_FILENEW, CmFileNew),
  EV_COMMAND(CM_FILEOPEN, CmFileOpen),
  EV_COMMAND(CM_FILESAVE, CmFileSave),
  EV_COMMAND(CM_FILESAVEAS, CmFileSaveAs),
//  EV_COMMAND(CM_FILECLOSE, CmFileClose),
  EV_COMMAND(CM_ELECTRON, CmElectron),
  EV_COMMAND(CM_FIELD, CmField),
  EV_COMMAND(CM_TEXT, CmText),
  EV_COMMAND(CM_ALL, CmAll),
  EV_COMMAND(CM_ABOUT, CmAbout),
  EV_COMMAND(CM_STEP, CmStep),
  EV_COMMAND(CM_RUN, CmRun),
  EV_COMMAND(CM_STOP, CmStop),
  EV_COMMAND(CM_ENERGY, CmEnergy),
  EV_COMMAND(CM_VDR, CmVdr),
  EV_COMMAND(CM_EVX, CmEvx),
  EV_COMMAND(CM_FEX, CmFex),
  EV_COMMAND(CM_FIO, CmFio),
  EV_COMMAND(CM_ALLSTAT, CmAllStat),
  EV_COMMAND(CM_FRE, CmFre),
  EV_COMMAND(CM_FRE1, CmFre1),
  EV_COMMAND(CM_SET, CmSet),
  EV_COMMAND(CM_LEFT, CmLeft),
  EV_COMMAND(CM_RIGHT, CmRight),
  EV_WM_TIMER,
END_RESPONSE_TABLE;

bool
TMyClient::CanClose()
{
  return true;
}

void
TMyClient::CmFileNew()
{
  if( TParamDial(this).Execute() == IDOK )
  {
	 discharge.Scan();
	 flag.opened=1;
	 flag.saved=0;
	 iseq=0;
	 SetText1();
  }
}

void
TMyClient::CmFileOpen()
{
  if((TFileOpenDialog(this, *fileData)).Execute() == IDOK)
  {
	 discharge.Read(fileData->FileName);
	 flag.opened=1;
	 flag.saved=0;
	 iseq=0;
	 SetText1();
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
	 TFieldChild* child=new TFieldChild(*this);
	 child->Create();
  }
}

void
TMyClient::CmText()
{
  if(flag.opened==1 && flag.text==0)
  {
	 TTextChild* child=new TTextChild(*this);
	 child->Create();
  }
}

void
TMyClient::CmAbout()
{
  TDialog(this,"About").Execute();
}

void
TMyClient::CmStep()
{
  if(flag.opened==1)
  {
	 discharge.Step();
	 SetText1();
	 if(flag.energy) energyChild->Invalidate();
	 if(flag.vdr) vdrChild->Invalidate();
	 if(flag.evx) evxChild->Invalidate();
	 if(flag.fex) fexChild->Invalidate();
	 if(flag.fio) fioChild->Invalidate();
	 if(flag.fre1) fre1Child->Invalidate();
  }
}

void
TMyClient::CmRun()
{
  if(flag.opened==1 && flag.run==0)
  {
	 flag.run=1;
	 SetTimer(ID_TIMER,TIMER_RATE);
  }
}

void
TMyClient::CmStop()
{
  flag.run=0;
  KillTimer(ID_TIMER);
}

void
TMyClient::EvTimer(uint /*ID_TIMER*/)
{
  if(flag.run)
  {
	 CmStep();
  }
}

void
TMyClient::CmAll()
{
  if(flag.opened)
  {
	 CmElectron();
	 CmField();
	 CmText();
  }
}

void
TMyClient::CmAllStat()
{
  if(flag.opened)
  {
	 CmEnergy();
	 CmVdr();
	 CmEvx();
	 CmFex();
	 CmFio();
  }
}

void
TMyClient::CmEnergy()
{
  if(flag.opened==1 && flag.energy==0)
  {
	 energyChild=new TEnergyChild(*this);
	 energyChild->Create();
  }
}

void
TMyClient::CmVdr()
{
  if(flag.opened==1 && flag.vdr==0)
  {
	 vdrChild=new TVdrChild(*this);
	 vdrChild->Create();
  }
}

void
TMyClient::CmEvx()
{
  if(flag.opened==1 && flag.evx==0)
  {
	 evxChild=new TEvxChild(*this);
	 evxChild->Create();
  }
}

void
TMyClient::CmFex()
{
  if(flag.opened==1 && flag.fex==0)
  {
	 fexChild=new TFexChild(*this);
	 fexChild->Create();
  }
}

void
TMyClient::CmFio()
{
  if(flag.opened==1 && flag.fio==0)
  {
	 fioChild=new TFioChild(*this);
	 fioChild->Create();
  }
}

void
TMyClient::CmFre()
{
  if(flag.opened==1 && flag.fre==0)
  {
	 TFreChild* child=new TFreChild(*this);
	 child->Create();
	 SetText2();
  }
}

void
TMyClient::CmFre1()
{
  if(flag.opened==1 && flag.fre1==0)
  {
	 fre1Child=new TFre1Child(*this,iseq);
	 fre1Child->Create();
	 SetText2();
  }
}

void
TMyClient::CmLeft()
{
  if(flag.opened==1)
  {
	 if(flag.fre1==1)
	 {
		iseq--;
		if(iseq<0) iseq=param.xsize-1;
		SetText2();
		((TFre1Child*)fre1Child)->Update(iseq);
	 }
	 else CmFre1();
  }
}

void
TMyClient::CmRight()
{
  if(flag.opened==1)
  {
	 if(flag.fre1==1)
	 {
		iseq++;
		if(iseq>=param.xsize) iseq=0;
		((TFre1Child*)fre1Child)->Update(iseq);
		SetText2();
	 }
	 else CmFre1();
  }
}

void
TMyClient::CmSet()
{
  if(flag.opened==1)
  {
/*	 char text[15];
	 float xseq=iseq*param.dx;
	 sprintf(text, "%.1f", xseq);
	 TInputDialog dial(this, "Input","Input x:",
		text, sizeof(text));
	 if(dial.Execute() == IDOK)
	 {
		xseq=atof(text);
		iseq=xseq/param.dx;
		if(iseq<0)iseq=0;
		if(iseq>param.xsize-1) iseq=param.xsize-1;
	 }
*/
	 iseq=param.xsize/2;
	 if(flag.fre1==1)
	 {
		((TFre1Child*)fre1Child)->Update(iseq);
		SetText2();
	 }
	 else CmFre1();
  }
}

/*
void
TMyClient::CmFileClose()
{
  flag.opened=0;
  iseq=0;
}
*/

