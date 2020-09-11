// Dialog for data modifying in TParam class
// ( time model )
// Abramov A.A., 1997, april

#ifndef __PARAMDIA_H
#define __PARAMDIA_H

#if !defined(OWL_DIALOG_H)
  #include <owl\dialog.h>
#endif
#if !defined(OWL_EDIT_H)
  #include <owl\edit.h>
#endif

class TParamDial : public TDialog
{
  public:
	 TParamDial(TWindow*);
	 ~TParamDial();
  protected:
	 char buf[20];
	 void CmOK();
	 void SetupWindow ();
	 TEdit
			 *ed_lx,
			 *ed_ly,
			 *ed_fd,
			 *ed_xem,
			 *ed_dt,
			 *ed_tsize,
			 *ed_de,
			 *ed_esize;
	DECLARE_RESPONSE_TABLE (TParamDial);
};

#endif