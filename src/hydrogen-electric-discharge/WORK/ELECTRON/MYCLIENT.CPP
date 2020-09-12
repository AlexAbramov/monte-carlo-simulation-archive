#include <owl\inputdia.h>
#include <stdlib.h>
#include <string.h>
#pragma hdrstop
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
  SetBkgndColor(RGB(0x40, 0xff, 0xff));
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
}

void
TMyClient::SetupWindow()
{
  TMDIClient::SetupWindow();
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

TMyClient::~TMyClient()
{
  delete fileData;
}

DEFINE_RESPONSE_TABLE1(TMyClient, TMDIClient)
  EV_WM_TIMER,
  EV_WM_CLOSE,
  EV_COMMAND(CM_STEP, CmStep),
  EV_COMMAND(CM_RUN, CmRun),
  EV_COMMAND_ENABLE(CM_RUN, CmRun1),
  EV_COMMAND(CM_STOP, CmStop),
  EV_COMMAND(CM_FILENEW, CmFileNew),
  EV_COMMAND(CM_FILEOPEN, CmFileOpen),
  EV_COMMAND(CM_FILESAVE, CmFileSave),
  EV_COMMAND_ENABLE(CM_FILESAVE, CmFileSave1),
  EV_COMMAND(CM_FILESAVEAS, CmFileSaveAs),
  EV_COMMAND(CM_ELECTRON, CmElectron),
  EV_COMMAND(CM_FIELD, CmField),
  EV_COMMAND(CM_TEXT, CmText),
  EV_COMMAND_ENABLE(CM_TEXT, CmText1),
  EV_COMMAND(CM_ABOUT, CmAbout),
  EV_COMMAND(CM_DENSITY, CmDensity),
  EV_COMMAND(CM_ENERGY, CmEnergy),
  EV_COMMAND(CM_ER, CmEr),
  EV_COMMAND(CM_EE, CmEe),
  EV_COMMAND(CM_VEL, CmVel),
  EV_COMMAND(CM_VDR, CmVdr),
  EV_COMMAND(CM_EVX, CmEvx),
  EV_COMMAND(CM_FEL, CmFel),
  EV_COMMAND(CM_FEX, CmFex),
  EV_COMMAND(CM_FIO, CmFio),
  EV_COMMAND(CM_FRE, CmFre),
  EV_COMMAND(CM_FRE1, CmFre1),
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
	 F1Pressed=false;
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
	 F1Pressed=false;
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
	 F1Pressed=false;
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
	 F1Pressed=false;
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
	 F1Pressed=false;
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
	 F1Pressed=false;
  }
  else
  if( TParamDial(this).Execute() == IDOK )
  {
	 discharge.Scan();
	 flag.opened=true;
	 flag.saved=false;
	 iseq=0;
	 SetText1();
  }
}

void
TMyClient::CmFileOpen()
{
  if(F1Pressed)
  {
	 ctxIndex=__Open;
	 CmContext();
	 F1Pressed=false;
  }
  else
  if((TFileOpenDialog(this, *fileData)).Execute()==IDOK)
  {
	 discharge.Read(fileData->FileName);
	 flag.opened=true;
	 flag.saved=false;
	 iseq=0;
	 SetText1();
  }
}

void
TMyClient::CmFileSaveAs()
{
  if(F1Pressed)
  {
	 ctxIndex=__SaveAs;
	 CmContext();
	 F1Pressed=false;
	 return;
  }
  if(flag.opened==false) return;
  if((TFileSaveDialog(this,*fileData)).Execute()==IDOK);
  {
	 discharge.Write(fileData->FileName);
	 flag.saved=true;
  }
}

void
TMyClient::CmFileSave()
{
  if(F1Pressed)
  {
	 ctxIndex=__Save_;
	 CmContext();
	 F1Pressed=false;
	 return;
  }
  if(!flag.opened) return;
  if(!flag.saved) CmFileSaveAs();
  else discharge.Write(fileData->FileName);
}

void
TMyClient::CmElectron()
{
  if(F1Pressed)
  {
	 ctxIndex=__Electron_tracks;
	 CmContext();
	 F1Pressed=false;
  }
  else
  if(flag.opened && !flag.electron)
  {
	 TElectronChild* child=new TElectronChild(*this);
	 child->Create();
  }
}

void
TMyClient::CmField()
{
  if(F1Pressed)
  {
	 ctxIndex=__Electric_field;
	 CmContext();
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.field)
  {
	 TFieldChild* child=new TFieldChild(*this);
	 child->Create();
  }
}

void
TMyClient::CmText()
{
  if(F1Pressed)
  {
	 ctxIndex=__Text_info;
	 CmContext();
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.text)
  {
	 TTextChild* child=new TTextChild(*this);
	 child->Create();
  }
}

void
TMyClient::CmStep()
{
  static int counter=0;
  if(F1Pressed)
  {
	 ctxIndex=__Step;
	 CmContext();
	 F1Pressed=false;
	 return;
  }
  if(flag.opened)
  {
	 discharge.Step();
	 SetText1();
	 {
		if(counter==10)
		{
		  if(flag.density)densityChild->Invalidate();
		  if(flag.vel)		velChild->Invalidate();
		  if(flag.vdr)		vdrChild->Invalidate();
		  if(flag.energy)	energyChild->Invalidate();
		  if(flag.er) 		erChild->Invalidate();
		  if(flag.evx) 	evxChild->Invalidate();
		  if(flag.ee) 		eeChild->Invalidate();
		  if(flag.fel) 	felChild->Invalidate();
		  if(flag.fex) 	fexChild->Invalidate();
		  if(flag.fio) 	fioChild->Invalidate();
		  if(flag.fre1)	fre1Child->Invalidate();
		  counter=0;
		}
		else counter++;
	 }
  }
}

void
TMyClient::CmRun()
{
  if(F1Pressed)
  {
	 ctxIndex=__Run;
	 CmContext();
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.run)
  {
	 flag.run=true;
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
	 F1Pressed=false;
	 return;
  }
  flag.run=false;
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.density)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.energy)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.vdr)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.vel)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.evx)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.er)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.ee)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.fel)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.fex)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.fio)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.fre)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened && !flag.fre1)
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened)
  {
	 if(!flag.fre1) CmFre1();
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened)
  {
	 if(!flag.fre1) CmFre1();
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
	 F1Pressed=false;
	 return;
  }
  if(flag.opened)
  {
	 iseq=param.xsize/2;
	 if(!flag.fre1) CmFre1();
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
	 F1Pressed=false;
	 return;
  }
  WinHelp(HelpPath.c_str(), HELP_CONTENTS , 0);
}

void
TMyClient::CmContext()
{
  WinHelp(HelpPath.c_str(), HELP_CONTEXT, ctxIndex);
}

void
TMyClient::CmAbout()
{
  if(F1Pressed)
  {
	 ctxIndex=__About_;
	 CmContext();
	 F1Pressed=false;
	 return;
  }
  TDialog(this,"About").Execute();
}

void
TMyClient::CmText1(TCommandEnabler& ce)
{
  ce.Enable(!flag.text);
}

void
TMyClient::CmRun1(TCommandEnabler& ce)
{
  ce.Enable(!flag.run);
}

void
TMyClient::CmFileSave1(TCommandEnabler& ce)
{
  ce.Enable(flag.opened);
}

// GetMenu
