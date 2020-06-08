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
	 void CmHelp();
	 void SetupWindow ();
	 TEdit *ed_xsize,
			 *ed_ysize,
			 *ed_eds,
			 *ed_resist,
			 *ed_gamma,
			 *ed_c0,
			 *ed_dt,
			 *ed_lx,
			 *ed_ly,
			 *ed_lz;
	DECLARE_RESPONSE_TABLE (TParamDial);
};

class TParDial : public TDialog
{
  public:
	 TParDial(TWindow*);
	 ~TParDial();
  protected:
	 char buf[20];
	 void CmOK();
	 void CmHelp();
	 void SetupWindow ();
	 TEdit *ed_resist;
	DECLARE_RESPONSE_TABLE (TParDial);
};

#endif