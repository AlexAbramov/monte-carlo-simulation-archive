#include <pch.h>
#pragma hdrstop
#include <stdlib.h>
#include <string.h>
#include <param.h>
#include <flag.h>
#include <paramdia.h>
#include <paramdia.rh>
#include <elstat.h>
#include <myrandom.h>
#include "count.h"
#include "mychild.h"
#include "myapp.rh"
#include "myapp.h"
#include "context.h"
#include "discharg.h"
#include "myclient.h"

string HelpPath;

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
	 ((TMyApp*) GetApplication())->SetText2(tt);
  }
}

TMyClient::TMyClient(): TMDIClient()
{
//  SetBkgndColor(RGB(0x40, 0xff, 0xff));
  fileData = new TOpenSaveDialog::TData(OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
	 "(*.ele)|*.ele|", 0, "","ele");
  const int ssize=500;
  char ss[ssize]="";
  int i=GetCurrentDirectory(ssize,ss);
  if(i>ssize) error_message("The path to current directory too long");
  HelpPath=ss;
  HelpPath+="\\electron.hlp";
  rnd.RegistrateDirectory(ss);
  param.RegistrateDirectory(ss);
  ctxIndex=__Contents_;
  F1Pressed=false;
}

void
TMyClient::SetupWindow()
{
  TMDIClient::SetupWindow();
  electronChild=0;
  fieldChild=0;
  textChild=0;
  densityChild=0;
  energyChild=0;
  eeChild=0;
  erChild=0;
  vdrChild=0;
  velChild=0;
  evxChild=0;
  felChild=0;
  fexChild=0;
  fioChild=0;
  fre1Child=0;
}

void TMyClient::UpdateChilds(BOOL b)
{
  if(b&&flag.electron&&electronChild)
  {
	 ((TElectronChild*)electronChild)->Clear();
  }
  if(b&&flag.field&&fieldChild) fieldChild->Invalidate();
  if(flag.text&&textChild) textChild->Invalidate();
  if(flag.density&&densityChild) densityChild->Invalidate();
  if(flag.energy&&energyChild) energyChild->Invalidate();
  if(flag.ee&&eeChild) eeChild->Invalidate();
  if(flag.er&&erChild) erChild->Invalidate();
  if(flag.vdr&&vdrChild) vdrChild->Invalidate();
  if(flag.vel&&velChild) velChild->Invalidate();
  if(flag.evx&&evxChild) evxChild->Invalidate();
  if(flag.fel&&felChild) felChild->Invalidate();
  if(flag.fex&&fexChild) fexChild->Invalidate();
  if(flag.fio&&fioChild) fioChild->Invalidate();
  if(flag.fre1&&fre1Child) fre1Child->Invalidate();
}

TMyClient::~TMyClient()
{
  delete fileData;
}

DEFINE_RESPONSE_TABLE1(TMyClient, TMDIClient)
  EV_WM_TIMER,
  EV_WM_CLOSE,
  EV_COMMAND(CM_STEP, CmStep),
  EV_COMMAND_ENABLE(CM_STEP, CmStep1),
  EV_COMMAND(CM_RUN, CmRun),
  EV_COMMAND_ENABLE(CM_RUN, CmRun1),
  EV_COMMAND(CM_STOP, CmStop),
  EV_COMMAND_ENABLE(CM_STOP, CmStop1),
  EV_COMMAND(CM_FILENEW, CmFileNew),
  EV_COMMAND(CM_FILEOPEN, CmFileOpen),
  EV_COMMAND(CM_FILESAVE, CmFileSave),
  EV_COMMAND(CM_FILESAVEAS, CmFileSaveAs),
  EV_COMMAND(CM_ELECTRON, CmElectron),
  EV_COMMAND_ENABLE(CM_ELECTRON, CmElectron1),
  EV_COMMAND(CM_FIELD, CmField),
  EV_COMMAND_ENABLE(CM_FIELD, CmField1),
  EV_COMMAND(CM_TEXT, CmText),
  EV_COMMAND_ENABLE(CM_TEXT, CmText1),
  EV_COMMAND(CM_ABOUT, CmAbout),
  EV_COMMAND(CM_DENSITY, CmDensity),
  EV_COMMAND_ENABLE(CM_DENSITY, CmDensity1),
  EV_COMMAND(CM_ENERGY, CmEnergy),
  EV_COMMAND_ENABLE(CM_ENERGY, CmEnergy1),
  EV_COMMAND(CM_ER, CmEr),
  EV_COMMAND_ENABLE(CM_ER, CmEr1),
  EV_COMMAND(CM_EE, CmEe),
  EV_COMMAND_ENABLE(CM_EE, CmEe1),
  EV_COMMAND(CM_VEL, CmVel),
  EV_COMMAND_ENABLE(CM_VEL, CmVel1),
  EV_COMMAND(CM_VDR, CmVdr),
  EV_COMMAND_ENABLE(CM_VDR, CmVdr1),
  EV_COMMAND(CM_EVX, CmEvx),
  EV_COMMAND_ENABLE(CM_EVX, CmEvx1),
  EV_COMMAND(CM_FEL, CmFel),
  EV_COMMAND_ENABLE(CM_FEL, CmFel1),
  EV_COMMAND(CM_FEX, CmFex),
  EV_COMMAND_ENABLE(CM_FEX, CmFex1),
  EV_COMMAND(CM_FIO, CmFio),
  EV_COMMAND_ENABLE(CM_FIO, CmFio1),
  EV_COMMAND(CM_FRE, CmFre),
  EV_COMMAND_ENABLE(CM_FRE, CmFre2),
  EV_COMMAND(CM_FRE1, CmFre1),
  EV_COMMAND_ENABLE(CM_FRE1, CmFre3),
  EV_COMMAND(CM_SET, CmSet),
  EV_COMMAND(CM_LEFT, CmLeft),
  EV_COMMAND(CM_RIGHT, CmRight),
  EV_COMMAND(CM_CONTENTS, CmContents),
  EV_COMMAND(CM_CONTEXT, CmContext),
  EV_COMMAND(CM_ARRANGEICONS, CmArrangeIcons),
  EV_COMMAND(CM_CASCADECHILDREN, CmCascadeChildren),
  EV_COMMAND(CM_CLOSECHILDREN, CmCloseChildren),
  EV_COMMAND(CM_TILECHILDREN, CmTileChildren),
END_RESPONSE_TABLE;

void
TMyClient::CmArrangeIcons()
{
  if(F1Pressed)
  {
	 ctxIndex=__Arrange_Icons;
	 CmContext();
  }
  else TMDIClient::CmArrangeIcons();
}

void
TMyClient::CmCascadeChildren()
{
  if(F1Pressed)
  {
	 ctxIndex=__Cascade;
	 CmContext();
  }
  else TMDIClient::CmCascadeChildren();
}

void
TMyClient::CmTileChildren()
{
  if(F1Pressed)
  {
	 ctxIndex=__Tile;
	 CmContext();
  }
  else TMDIClient::CmTileChildren();
}

void
TMyClient::CmCloseChildren()
{
  if(F1Pressed)
  {
	 ctxIndex=__Close_All;
	 CmContext();
  }
  else TMDIClient::CmCloseChildren();
}

bool
TMyClient::CanClose()
{
  if(F1Pressed)
  {
	 ctxIndex=__Exit;
	 CmContext();
	 return false;
  }
  else
  {
	 if(flag.run) CmStop();
	 return true;
  }
}

void
TMyClient::EvClose()
{
  TMDIClient::EvClose();
}

void
TMyClient::CmFileNew()
{
  if(F1Pressed)
  {
	 ctxIndex=__New;
	 CmContext();
  }
  else
  {
	 if( TParamDial(this).Execute() == IDOK )
	 {
		if(flag.run) CmStop();
		discharge.Scan();
		flag.opened=1;
		flag.saved=0;
		iseq=0;
		SetText1();
		((TMyApp*)GetApplication())->SetMainMenu(false);
		UpdateChilds(TRUE);
	 }
  }
}

void
TMyClient::CmFileOpen()
{
  if(F1Pressed)
  {
	 ctxIndex=__Open;
	 CmContext();
  }
  else
  if((TFileOpenDialog(this, *fileData)).Execute()==IDOK)
  {
	 if(flag.run) CmStop();
	 discharge.Read(fileData->FileName);
	 flag.opened=1;
	 flag.saved=0;
	 iseq=0;
	 SetText1();
	 if(param.nlav==0) ((TMyApp*)GetApplication())->SetMainMenu(false);
	 else ((TMyApp*)GetApplication())->SetMainMenu(true);
	 UpdateChilds(TRUE);
  }
}

void
TMyClient::CmFileSaveAs()
{
  if(F1Pressed)
  {
	 ctxIndex=__SaveAs;
	 CmContext();
	 return;
  }
  if(flag.opened==0) return;
  if((TFileSaveDialog(this,*fileData)).Execute()==IDOK)
  {
	 discharge.Write(fileData->FileName);
	 flag.saved=1;
  }
}

void
TMyClient::CmFileSave()
{
  if(F1Pressed)
  {
	 ctxIndex=__Save_;
	 CmContext();
	 return;
  }
  if(flag.opened==0) return;
  if(flag.saved==0) CmFileSaveAs();
  else discharge.Write(fileData->FileName);
}

void
TMyClient::CmElectron()
{
  if(F1Pressed)
  {
	 ctxIndex=__Electron_tracks;
	 CmContext();
  }
  else
  if(flag.opened==1 && flag.electron==0)
  {
	 electronChild=new TElectronChild(*this);
	 electronChild->Create();
  }
}

void
TMyClient::CmField()
{
  if(F1Pressed)
  {
	 ctxIndex=__Electric_field;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.field==0)
  {
	 fieldChild=new TFieldChild(*this);
	 fieldChild->Create();
  }
}

void
TMyClient::CmText()
{
  if(F1Pressed)
  {
	 ctxIndex=__Text_info;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.text==0)
  {
	 textChild=new TTextChild(*this);
	 textChild->Create();
  }
}

void
TMyClient::CmStep()
{
  if(F1Pressed)
  {
	 ctxIndex=__Step;
	 CmContext();
	 return;
  }
  if(flag.opened==1)
  {
	 discharge.Step();
	 if(param.nlav>0) ((TMyApp*)GetApplication())->SetMainMenu(true);
	 SetText1();
	 if(param.nlav%param.nshow==0) UpdateChilds();
  }
}

void
TMyClient::CmRun()
{
  if(F1Pressed)
  {
	 ctxIndex=__Run;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.run==0)
  {
	 flag.run=1;
	 SetTimer(ID_TIMER,TIMER_RATE);
  }
}

void
TMyClient::CmStop()
{
  if(F1Pressed)
  {
	 ctxIndex=__Stop;
	 CmContext();
	 return;
  }
  flag.run=0;
  KillTimer(ID_TIMER);
}

void
TMyClient::EvTimer(uint /*ID_TIMER*/)
{
  if(flag.run)
  {
	 if(count.Status()==1 && param.nlav>count.nlavmax) count.Update();
	 else CmStep();
  }
}

void
TMyClient::CmDensity()
{
  if(F1Pressed)
  {
	 ctxIndex=__Electron_density;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.density==0)
  {
	 densityChild=new TDensityChild(*this);
	 densityChild->Create();
  }
}

void
TMyClient::CmEnergy()
{
  if(F1Pressed)
  {
	 ctxIndex=__Mean_energy;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.energy==0)
  {
	 energyChild=new TEnergyChild(*this);
	 energyChild->Create();
  }
}

void
TMyClient::CmVdr()
{
  if(F1Pressed)
  {
	 ctxIndex=__Drift_velocity;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.vdr==0)
  {
	 vdrChild=new TVdrChild(*this);
	 vdrChild->Create();
  }
}

void
TMyClient::CmVel()
{
  if(F1Pressed)
  {
	 ctxIndex=__Mean_velocity;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.vel==0)
  {
	 velChild=new TVelChild(*this);
	 velChild->Create();
  }
}

void
TMyClient::CmEvx()
{
  if(F1Pressed)
  {
	 ctxIndex=__e_vx_;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.evx==0)
  {
	 evxChild=new TEvxChild(*this);
	 evxChild->Create();
  }
}

void
TMyClient::CmEr()
{
  if(F1Pressed)
  {
	 ctxIndex=__Radial_energy;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.er==0)
  {
	 erChild=new TErChild(*this);
	 erChild->Create();
  }
}

void
TMyClient::CmEe()
{
  if(F1Pressed)
  {
	 ctxIndex=__e_e_;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.ee==0)
  {
	 eeChild=new TEeChild(*this);
	 eeChild->Create();
  }
}

void
TMyClient::CmFel()
{
  if(F1Pressed)
  {
	 ctxIndex=__Elastic_frequency;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.fel==0)
  {
	 felChild=new TFelChild(*this);
	 felChild->Create();
  }
}

void
TMyClient::CmFex()
{
  if(F1Pressed)
  {
	 ctxIndex=__Excited_frequency;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.fex==0)
  {
	 fexChild=new TFexChild(*this);
	 fexChild->Create();
  }
}

void
TMyClient::CmFio()
{
  if(F1Pressed)
  {
	 ctxIndex=__Ionized_frequency;
	 CmContext();
	 return;
  }
  if(flag.opened==1 && flag.fio==0)
  {
	 fioChild=new TFioChild(*this);
	 fioChild->Create();
  }
}

void
TMyClient::CmFre()
{
  if(F1Pressed)
  {
	 ctxIndex=__f_e_x_;
	 CmContext();
	 return;
  }
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
  if(F1Pressed)
  {
	 ctxIndex=__f_e_;
	 CmContext();
	 return;
  }
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
  if(F1Pressed)
  {
	 ctxIndex=__Decrease_x;
	 CmContext();
	 return;
  }
  if(flag.opened==1&&param.nlav>0)
  {
	 if(flag.fre1==0) CmFre1();
	 iseq--;
	 if(iseq<1) iseq=param.xsize-1;
	 SetText2();
	 ((TFre1Child*) fre1Child)->Update(iseq);
  }
}

void
TMyClient::CmRight()
{
  if(F1Pressed)
  {
	 ctxIndex=__Increase_x;
	 CmContext();
	 return;
  }
  if(flag.opened==1&&param.nlav>0)
  {
	 if(flag.fre1==0) CmFre1();
	 iseq++;
	 if(iseq>=param.xsize) iseq=1;
	 ((TFre1Child*)fre1Child)->Update(iseq);
	 SetText2();
  }
}

void
TMyClient::CmSet()
{
  if(F1Pressed)
  {
	 ctxIndex=__Set_x;
	 CmContext();
	 return;
  }
  if(flag.opened==1&&param.nlav>0)
  {
	 iseq=param.xsize/2;
	 if(flag.fre1==0) CmFre1();
	 ((TFre1Child*) fre1Child)->Update(iseq);
	 SetText2();
  }
}

void
TMyClient::CmContents()
{
  if(F1Pressed)
  {
	 ctxIndex=__Contents1;
	 CmContext();
	 return;
  }
  WinHelp(HelpPath.c_str(), HELP_CONTENTS , 0);
}

void
TMyClient::CmContext()
{
  WinHelp(HelpPath.c_str(), HELP_CONTEXT, ctxIndex);
  F1Pressed=false;
}

void
TMyClient::CmAbout()
{
  if(F1Pressed)
  {
	 ctxIndex=__About_;
	 CmContext();
	 return;
  }
  TDialog(this,"About").Execute();
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
TMyClient::CmText1(TCommandEnabler& ce)
{
  ce.Enable(!flag.text);
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
TMyClient::CmDensity1(TCommandEnabler& ce)
{
  ce.Enable(!flag.density);
}

void
TMyClient::CmEnergy1(TCommandEnabler& ce)
{
  ce.Enable(!flag.energy);
}

void
TMyClient::CmEr1(TCommandEnabler& ce)
{
  ce.Enable(!flag.er);
}

void
TMyClient::CmEe1(TCommandEnabler& ce)
{
  ce.Enable(!flag.ee);
}

void
TMyClient::CmVel1(TCommandEnabler& ce)
{
  ce.Enable(!flag.vel);
}

void
TMyClient::CmVdr1(TCommandEnabler& ce)
{
  ce.Enable(!flag.vdr);
}

void
TMyClient::CmEvx1(TCommandEnabler& ce)
{
  ce.Enable(!flag.evx);
}

void
TMyClient::CmFel1(TCommandEnabler& ce)
{
  ce.Enable(!flag.fel);
}

void
TMyClient::CmFex1(TCommandEnabler& ce)
{
  ce.Enable(!flag.fex);
}

void
TMyClient::CmFio1(TCommandEnabler& ce)
{
  ce.Enable(!flag.fio);
}

void
TMyClient::CmFre2(TCommandEnabler& ce)
{
  ce.Enable(!flag.fre);
}

void
TMyClient::CmFre3(TCommandEnabler& ce)
{
  ce.Enable(!flag.fre1);
}
