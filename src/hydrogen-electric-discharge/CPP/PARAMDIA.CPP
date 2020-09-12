#include <owl\validate.h>
#include <stdlib.h>
#include <stdio.h>
#pragma hdrstop
#include <param.h>
#include <mylib.h>
#include <paramdia.h>
#include <paramdia.rh>
#include "context.h"
#include "count.h"

extern string HelpPath;

DEFINE_RESPONSE_TABLE1 ( TParamDial, TDialog )
	EV_COMMAND( IDOK, CmOk ),
	EV_COMMAND( IDHELP, CmHelp ),
END_RESPONSE_TABLE;

TParamDial :: TParamDial ( TWindow* parent)
	: TDialog ( parent,ID_DIALOG)
{
  ((TWindow*)this)->Attr.AccelTable = "Acc1";
  ed_xsize=new TEdit(this,IDC_XSIZE);
  ed_xsize->SetValidator( new TFilterValidator("0-9") );
  ed_ysize=new TEdit(this,IDC_YSIZE);
  ed_ysize->SetValidator( new TFilterValidator("0-9") );
  ed_lx=new TEdit(this,IDC_LX);
  ed_lx->SetValidator( new TFilterValidator("0-9.") );
  ed_ly=new TEdit(this,IDC_LY);
  ed_ly->SetValidator( new TFilterValidator("0-9.") );
  ed_voltage=new TEdit(this,IDC_VOLTAGE);
  ed_voltage->SetValidator( new TFilterValidator("0-9") );
  ed_dk=new TEdit(this,IDC_DK);
  ed_dk->SetValidator( new TFilterValidator("0-9.") );
  ed_fd=new TEdit(this,IDC_FD);
  ed_fd->SetValidator( new TFilterValidator("0-9.") );
  ed_de=new TEdit(this,IDC_DE);
  ed_de->SetValidator( new TFilterValidator("0-9.") );
  ed_esize=new TEdit(this,IDC_ESIZE);
  ed_esize->SetValidator( new TFilterValidator("0-9") );
  ed_xem=new TEdit(this,IDC_XEM);
  ed_xem->SetValidator( new TFilterValidator("0-9.") );
}

TParamDial::~TParamDial()
{
  Destroy();
}

void
TParamDial::SetupWindow()
{
  TDialog::SetupWindow();
  ((TWindow*)this)->Attr.AccelTable = "Accelerators1";
  param.Scan();
  if(param.Status() == 0) error_message("TParamDial::SetupWindow");
  sprintf(buf,"%i",param.xsize);
  ed_xsize->SetText(buf);
  sprintf(buf,"%i",param.ysize);
  ed_ysize->SetText(buf);
  sprintf(buf,"%.1f",param.lx);
  ed_lx->SetText(buf);
  sprintf(buf,"%.1f",param.ly);
  ed_ly->SetText(buf);
  if(count.Status()==1)
  {
	 param.voltage=0.;
	 ed_voltage->SetReadOnly(1);
  }
  sprintf(buf,"%.0f",param.voltage);
  ed_voltage->SetText(buf);
  if(count.Status()==1)
  {
	 param.dk=0.;
	 ed_dk->SetReadOnly(1);
  }
  sprintf(buf,"%.2f",param.dk);
  ed_dk->SetText(buf);
  sprintf(buf,"%.2f",param.fd);
  ed_fd->SetText(buf);
  sprintf(buf,"%.1f",param.de);
  ed_de->SetText(buf);
  sprintf(buf,"%i",param.esize);
  ed_esize->SetText(buf);
  sprintf(buf,"%.1f",param.xem);
  ed_xem->SetText(buf);
}

void
TParamDial :: CmOk()
{
  if(param.Status() == 0) error_message("TParamDial::CmOk");
  ed_xsize->GetText(buf,sizeof(buf));
  param.xsize=atoi(buf);
  ed_ysize->GetText(buf,sizeof(buf));
  param.ysize=atoi(buf);
  ed_lx->GetText(buf,sizeof(buf));
  param.lx=atof(buf);
  ed_ly->GetText(buf,sizeof(buf));
  param.ly=atof(buf);
  ed_voltage->GetText(buf,sizeof(buf));
  param.voltage=atof(buf);
  ed_dk->GetText(buf,sizeof(buf));
  param.dk=atof(buf);
  ed_fd->GetText(buf,sizeof(buf));
  param.fd=atof(buf);
  ed_de->GetText(buf,sizeof(buf));
  param.de=atof(buf);
  ed_esize->GetText(buf,sizeof(buf));
  param.esize=atoi(buf);
  ed_xem->GetText(buf,sizeof(buf));
  param.xem=atof(buf);
  param.Update();
  param.Print();
  CloseWindow(IDOK);
}

void
TParamDial :: CmHelp()
{
  WinHelp(HelpPath.c_str(), HELP_CONTEXT, __New);
}
