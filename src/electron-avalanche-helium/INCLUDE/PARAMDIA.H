// Dialog for data modifying in TParam class
// Abramov A.A., 1997

#ifndef __PARAMDIA_H
#define __PARAMDIA_H

class TParamDial : public TDialog
{
  public:
	 TParamDial(TWindow*);
	 ~TParamDial();
  protected:
	 char buf[20];
	 void SetupWindow ();
	 TEdit *ed_xsize,
			 *ed_ysize,
			 *ed_lx,
			 *ed_ly,
			 *ed_voltage,
			 *ed_dk,
			 *ed_fd,
			 *ed_de,
			 *ed_esize,
			 *ed_xem;
	void CmOk();
	void CmHelp();
	DECLARE_RESPONSE_TABLE (TParamDial);
};

#endif