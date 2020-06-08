#include <pch.h>
#pragma hdrstop
#include <mylib.h>
#include <electron.h>
#include <param.h>
#include <flag.h>
#include <ris.h>
#include "mychild.h"

TRis risel("dat\\risel.dat");

TRis::TRis(char* filename)
{
  FILE * fp=handle_scan(filename);
	 fscanf(fp,"%i",&d);newline(fp);
	 fscanf(fp,"%i",&d1);newline(fp);
	 fscanf(fp,"%i",&i0);newline(fp);
	 fscanf(fp,"%i",&j0);newline(fp);
	 fscanf(fp,"%i",&smin);newline(fp);
	 fscanf(fp,"%i",&r1);newline(fp);
	 fscanf(fp,"%i",&r2);newline(fp);
	 fscanf(fp,"%i",&r3);newline(fp);
	 fscanf(fp,"%i",&r4);newline(fp);
	 fscanf(fp,"%i",&r5);newline(fp);
	 fscanf(fp,"%i",&r6);newline(fp);
  fclose(fp);
  if(smin<=0) smin=10;
  Destroy();// just init by default values
}

void TRis::Init(TMemoryDC* _pdc,void * _pwnd,TClientDC* _cdc)
{
  pdc=_pdc;
  pwnd=_pwnd;
  needClose=false;
  bitmap=0;
  cdc=_cdc;
}

void TRis::Destroy()
{
  pdc=0;
  flag_ris=0;
  painted=0;
  pwnd=0;
  lx=0;
  ly=0;
  rx=0.;
  ry=0.;
  if(bitmap){ delete bitmap; bitmap=0;}
  cdc=0;
  needUpdate=false;
  updateRect=TRect(0,0,0,0);
}

void
TRis::Update(TRect& _rect)
{
  needUpdate=true;
  updateRect=_rect;
}

void
TRis::Clear()
{
  painted=0;

  if(lx<smin||ly<smin){flag_ris=0; return;}
  else flag_ris=1;

  if(!CanPaint()) return;

  if(bitmap==0||bitmap->Width()!=rect.Width()||bitmap->Height()!=rect.Height())
  {

	 if(bitmap){ delete bitmap; bitmap=0;}
	 bitmap=new TBitmap(*cdc,rect.Width(),rect.Height());
	 pdc->SelectObject(*bitmap);
  }

  rx=lx/param.lx;
  ry=ly/param.ly;
  pdc->FillRect(rect,TBrush(TColor::White));
  pdc->SelectObject(TPen(TColor::Black));
  pdc->MoveTo(i0,j0);
  pdc->LineTo(i0,j0+ly);
  pdc->LineTo(i0+lx,j0+ly);
  pdc->LineTo(i0+lx,j0);
  pdc->LineTo(i0,j0);

/*
// grid
  pdc->SelectObject(TPen(TColor::LtGray));
  for(int n=0;n<=param.xsize;n++)
  {
	 int i=i0+lx*n/param.xsize;
	 pdc->MoveTo(i,j0);
	 pdc->LineTo(i,j0+ly);
  }
  for(int m=0;m<=param.ysize;m++)
  {
	 int j=j0+ly*m/param.ysize;
	 pdc->MoveTo(i0,j);
	 pdc->LineTo(i0+lx,j);
  }
*/
}

void
TRis::Move(float x,float y)
{
  if(!CanPaint()) return;
  i=i0+x*rx;
  j=j0+ly-y*ry;
  pdc->MoveTo(i,j);
}

void
TRis::Line(float x,float y,step_result result)
{
  if(!CanPaint()) return;

  switch(result.ptype)
  {
	 case ELECTRON:
		pdc->SelectObject(TPen(TColor::LtBlue));
		break;
  }

  i=i0+x*rx;
  j=j0+ly-y*ry;
  if(r1) pdc->LineTo(i,j);

  TRect rect0(i-d,j-d,i+d,j+d);
  TRect rect1(i-d1,j-d1,i+d1,j+d1);
  switch(result.event)
  {
	 case PARTICLE_OUT:
		if(r2)
		{
		  pdc->SelectObject(TBrush(TColor::LtGray));
		  pdc->Ellipse(rect0);
		}
	 break;
	 case NULL_COLLISION:
		if(r3)
		{
		  pdc->SelectObject(TBrush(TColor::White));
		  pdc->Ellipse(rect0);
		}
	 break;
	 case REAL_COLLISION:
		switch(result.ptype)
		{
		  case ELECTRON:
			 switch(result.rctype)
			 {
				case ELECTRON_ELASTIC:
				  if(r4)
				  {
					 pdc->SelectObject(TBrush(TColor::LtCyan));
					 pdc->Ellipse(i-d,j-d,i+d,j+d);
				  }
				break;
				case ELECTRON_EXCITED:
				  if(r5)
				  {
					 pdc->SelectObject(TBrush(TColor::LtRed));
					 pdc->Ellipse(rect1);
				  }
				break;
				case ELECTRON_IONIZED:
				  if(r6)
				  {
					 pdc->SelectObject(TBrush(TColor::LtGreen));
					 pdc->Ellipse(rect1);
				  }
				break;
			 }
		  break;
		}
	 break;
  }
}

void
TRis::Paint()
{
  if(!painted) painted=1;
  if(!CanPaint()) return;
  ((TElectronChild*)pwnd)->Paint();
}

bool TRis::CanPaint()
{
  if(needUpdate)
  {
	 rect=updateRect;
	 lx=rect.Width()-i0-i0;
	 ly=rect.Height()-j0-j0;
	 flag_ris=0;
	 needUpdate=false;
  }
  if(needClose)
  {
	 flag_ris=false;
	 flag.electron=0;
	 ((TElectronChild*)pwnd)->SendMessage(WM_CLOSE);
	 needClose=false;
  }
  if(flag_ris&&flag.electron) return true;
  else return false;
}
