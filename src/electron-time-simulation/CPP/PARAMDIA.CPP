#include <owl\validate.h>
#include <stdlib.h>
#include <stdio.h>
#pragma hdrstop
#include <param.h>
#include <mylib.h>
#include <paramdia.rh>
#include <paramdia.h>

DEFINE_RESPONSE_TABLE1 ( TParamDial, TDialog )
	EV_COMMAND ( IDOK, CmOK ),
END_RESPONSE_TABLE;

TParamDial :: TParamDial ( TWindow* parent)
	: TDialog ( parent,ID_DIALOG)
{
  ed_lx=new TEdit(this,IDC_LX);
  ed_lx->SetValidator( new TFilterValidator("0-9.") );
  ed_ly=new TEdit(this,IDC_LY);
  ed_ly->SetValidator( new TFilterValidator("0-9.") );
  ed_fd=new TEdit(this,IDC_FD);
  ed_fd->SetValidator( new TFilterValidator("0-9.") );
  ed_xem=new TEdit(this,IDC_XEM);
  ed_xem->SetValidator( new TFilterValidator("0-9.") );
  ed_dt=new TEdit(this,IDC_DT);
  ed_dt->SetValidator( new TFilterValidator("0-9.") );
  ed_tsize=new TEdit(this,IDC_TSIZE);
  ed_tsize->SetValidator( new TFilterValidator("0-9") );
  ed_de=new TEdit(this,IDC_DE);
  ed_de->SetValidator( new TFilterValidator("0-9.") );
  ed_esize=new TEdit(this,IDC_ESIZE);
  ed_esize->SetValidator( new TFilterValidator("0-9") );
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
  sprintf(buf,"%.1f",param.lx);
  ed_lx->SetText(buf);
  sprintf(buf,"%.1f",param.ly);
  ed_ly->SetText(buf);
  sprintf(buf,"%.2f",param.fd);
  ed_fd->SetText(buf);
  sprintf(buf,"%.1f",param.xem);
  ed_xem->SetText(buf);
  sprintf(buf,"%.4f",param.dt);
  ed_dt->SetText(buf);
  sprintf(buf,"%i",param.tsize);
  ed_tsize->SetText(buf);
  sprintf(buf,"%.1f",param.de);
  ed_de->SetText(buf);
  sprintf(buf,"%i",param.esize);
  ed_esize->SetText(buf);
}

void
TParamDial :: CmOK ()
{
  if(param.Status() == 0) error_message("TParamDial::CmOk");
  ed_lx->GetText(buf,sizeof(buf));
  param.lx=atof(buf);
  ed_ly->GetText(buf,sizeof(buf));
  param.ly=atof(buf);
  ed_fd->GetText(buf,sizeof(buf));
  param.fd=atof(buf);
  ed_xem->GetText(buf,sizeof(buf));
  param.xem=atof(buf);
  ed_dt->GetText(buf,sizeof(buf));
  param.dt=atof(buf);
  ed_tsize->GetText(buf,sizeof(buf));
  param.tsize=atoi(buf);
  ed_de->GetText(buf,sizeof(buf));
  param.de=atof(buf);
  ed_esize->GetText(buf,sizeof(buf));
  param.esize=atoi(buf);
  param.Update();
  param.Print();
  CloseWindow ( IDOK );
}
