#include <pch.h>
#pragma hdrstop
#include <stdlib.h>
#include <stdio.h>
#include <param.h>
#include <mylib.h>
#include <paramdia.rh>
#include <paramdia.h>
#include "context.h"
#include "count.h"

extern string HelpPath;

DEFINE_RESPONSE_TABLE1 ( TParamDial, TDialog )
	EV_COMMAND ( IDOK, CmOK ),
	EV_COMMAND( IDHELP, CmHelp ),
END_RESPONSE_TABLE;

TParamDial :: TParamDial ( TWindow* parent)
	: TDialog ( parent,ID_DIALOG)
{
  ed_xsize=new TEdit(this,IDC_XSIZE);
  ed_xsize->SetValidator( new TFilterValidator("0-9") );
  ed_ysize=new TEdit(this,IDC_YSIZE);
  ed_ysize->SetValidator( new TFilterValidator("0-9") );
  ed_eds=new TEdit(this,IDC_EDS);
  ed_eds->SetValidator( new TFilterValidator("0-9.") );
  ed_resist=new TEdit(this,IDC_RESIST);
  ed_resist->SetValidator( new TFilterValidator("0-9.") );
  ed_gamma=new TEdit(this,IDC_GAMMA);
  ed_gamma->SetValidator( new TFilterValidator("0-9.") );
  ed_c0=new TEdit(this,IDC_C0);
  ed_c0->SetValidator( new TFilterValidator("0-9.") );
  ed_dt=new TEdit(this,IDC_DT);
  ed_dt->SetValidator( new TFilterValidator("0-9.") );
  ed_lx=new TEdit(this,IDC_LX);
  ed_lx->SetValidator( new TFilterValidator("0-9.") );
  ed_ly=new TEdit(this,IDC_LY);
  ed_ly->SetValidator( new TFilterValidator("0-9.") );
  ed_lz=new TEdit(this,IDC_LZ);
  ed_lz->SetValidator( new TFilterValidator("0-9.") );
}

TParamDial::~TParamDial()
{
//  Destroy();
}

void
TParamDial::SetupWindow()
{
  TDialog::SetupWindow();
  param.Scan();
  if(param.Status() == 0) error_message("TParamDial::SetupWindow");
  sprintf(buf,"%i",param.xsize);
  ed_xsize->SetText(buf);
  sprintf(buf,"%i",param.ysize);
  ed_ysize->SetText(buf);
  sprintf(buf,"%.0f",param.eds);
  ed_eds->SetText(buf);
  if(count.Status()==1)
  {
	 param.resist=count.GetFirst();
	 ed_resist->SetReadOnly(1);
  }
  sprintf(buf,"%.2f",param.resist);
  ed_resist->SetText(buf);
  sprintf(buf,"%.2f",param.gamma);
  ed_gamma->SetText(buf);
  sprintf(buf,"%.3f",param.c0);
  ed_c0->SetText(buf);
  sprintf(buf,"%.3f",param.dt);
  ed_dt->SetText(buf);
  sprintf(buf,"%.1f",param.lx);
  ed_lx->SetText(buf);
  sprintf(buf,"%.1f",param.ly);
  ed_ly->SetText(buf);
  sprintf(buf,"%.1f",param.lz);
  ed_lz->SetText(buf);
}

void
TParamDial :: CmOK ()
{
  if(param.Status() == 0) error_message("TParamDial::CmOk");
  ed_xsize->GetText(buf,sizeof(buf));
  param.xsize=atoi(buf);
  ed_ysize->GetText(buf,sizeof(buf));
  param.ysize=atoi(buf);
  ed_eds->GetText(buf,sizeof(buf));
  param.eds=atof(buf);
  ed_resist->GetText(buf,sizeof(buf));
  param.resist=atof(buf);
  ed_gamma->GetText(buf,sizeof(buf));
  param.gamma=atof(buf);
  ed_c0->GetText(buf,sizeof(buf));
  param.c0=atof(buf);
  ed_dt->GetText(buf,sizeof(buf));
  param.dt=atof(buf);
  ed_lx->GetText(buf,sizeof(buf));
  param.lx=atof(buf);
  ed_ly->GetText(buf,sizeof(buf));
  param.ly=atof(buf);
  ed_lz->GetText(buf,sizeof(buf));
  param.lz=atof(buf);
  param.Update();
  param.Print();
  CloseWindow ( IDOK );
}

//****************************************************

DEFINE_RESPONSE_TABLE1 ( TParDial, TDialog )
	EV_COMMAND ( IDOK, CmOK ),
	EV_COMMAND( IDHELP, CmHelp ),
END_RESPONSE_TABLE;

TParDial :: TParDial ( TWindow* parent)
	: TDialog ( parent,ID_DIAL)
{
  ed_resist=new TEdit(this,IDC_RESIST);
  ed_resist->SetValidator( new TFilterValidator("0-9.") );
}

TParDial::~TParDial()
{
//  Destroy();
}

void
TParDial::SetupWindow()
{
  TDialog::SetupWindow();
  if(param.Status() == 0) error_message("TParDial::SetupWindow");
  sprintf(buf,"%.0f",param.resist);
  ed_resist->SetText(buf);
}

void
TParDial :: CmOK ()
{
  if(param.Status() == 0) error_message("TParDial::CmOk");
  ed_resist->GetText(buf,sizeof(buf));
  param.resist=atof(buf);
  CloseWindow ( IDOK );
}

void
TParamDial :: CmHelp ()
{
  WinHelp(HelpPath.c_str(), HELP_CONTEXT, __New);
}

void
TParDial :: CmHelp ()
{
  WinHelp(HelpPath.c_str(), HELP_CONTEXT, __Edit);
}
