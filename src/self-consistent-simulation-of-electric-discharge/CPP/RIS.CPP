#include <pch.h>
#pragma hdrstop
#include <mylib.h>
#include <electron.h>
#include <param.h>
#include <ris.h>

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
  pdc=0;
  flag_ris=0;
  painted=FALSE;
}

void
TRis::Update(TRect& _rect)
{
  painted=FALSE;
  rect=_rect;
  lx=rect.Width()-i0-i0;
  ly=rect.Height()-j0-j0;
  if(lx<smin||ly<smin){ flag_ris=0; return;}
  else flag_ris=1;
  if(param.Status()!=1) error_message("TRis::Update");
}

void
TRis::Clear()
{
  painted=FALSE;
  if(flag_ris==0) return;
  rx=lx/param.lx;
  ry=ly/param.ly;
  Control();
  pdc->FillRect(rect,TBrush(TColor::White));
  pdc->SelectObject(TPen(TColor::Black));
  pdc->Rectangle(i0,j0,i0+lx,j0+ly);
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
  if(flag_ris==0) return;
  Control();
  i=i0+x*rx;
  j=j0+ly-y*ry;
  pdc->MoveTo(i,j);
}

void
TRis::Line(float x,float y,step_result result)
{
  if(flag_ris==0) return;
  Control();
  if(painted==FALSE) painted=TRUE;

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
  pdc->RestorePen();
  pdc->RestoreBrush();
}

void
TRis::Control()
{
  if(pdc==0) error_message("TRis::Control (1)");
  if(rx<=0.||ry<=0.) error_message("TRis::Control (2)");
}

void
TRis::Paint()
{
  SendMessage(hwnd,WM_PAINT,0,0);
}

