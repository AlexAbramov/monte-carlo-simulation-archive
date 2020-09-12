#include <math.h>
#include <string.h>
#pragma hdrstop
#include <mygraph.h>

static void line(TDC& dc,int i0,int j0,int i1,int j1)
{
  dc.MoveTo(i0,j0);
  dc.LineTo(i1,j1);
}

static void polygon(TDC& dc,int y,int xp,int zp,int x,int z)
{
  int zmin,zmax,xmax;
  if(z>zp)
  {
	 zmax=z;
	 zmin=zp;
	 xmax=x;
  }
  else
  {
	 zmax=zp;
	 zmin=z;
	 xmax=xp;
  }
  const int count=3;
  TPoint p1(xp,y-zmin),p2(x,y-zmin),p3(xmax,y-zmax);
  TPoint pp[count]={p1,p2,p3};
  TPoint p0(xp,y);
  dc.Rectangle(p0,p2);
  dc.Polygon(pp,count);
}

static float okrug(float xmax)
{
  float x=log10(xmax*.99);
  int i;
  if(x>0.) i=x;
  else i=x-1;
  float xp=pow(10.,i);
  i=xmax/xp+.99;
  return i*xp;
}

static float maxel(int size,float* yy)
{
  float y,ymax=yy[0];
  for(int i=1;i<size;i++)
  {
	 y=*(yy+i);
	 if(y>ymax) ymax=y;
  }
  return ymax;
}

TGraph::TGraph(char * ss)
{
  FILE * fp=handle_scan(ss);
	 fscanf(fp,"%i%i",&nx,&ny);newline(fp);
	 fscanf(fp,"%f%f",&x0,&x1);newline(fp);
	 fscanf(fp,"%f%f",&y0,&y1);newline(fp);
	 fscanf(fp,"%s",formatx);newline(fp);
	 fscanf(fp,"%s",formaty);newline(fp);
	 fscanf(fp,"%i%i",&size1,&size2);newline(fp);
  fclose(fp);
}

void
TGraph::Clear(TDC& dc)
{
  TRect rect;
  dc.GetClipBox(rect);
  dc.FillRect(rect,TBrush(TColor::White));
}

int
TGraph::Update(TDC& dc)
{
  TRect rect;
  dc.GetClipBox(rect);
  ii=rect.right;
  jj=rect.bottom;
  if(ii<size1||jj<size1) return 0;
  else
  {
	 if(ii<size2||jj<size2) textStatus=0;
	 else textStatus=1;
	 i0=ii*x0;
	 j0=jj*(1.-y0);
	 lx=ii*(x1-x0);
	 ly=jj*(y1-y0);
	 return 1;
  }
}

void
TGraph::Common(TDC& dc,float xmax, float ymax,char* textx,char* texty)
{
  Clear(dc);
  TPen pen1(TColor::Black);
  dc.SelectObject(pen1);
  int i,j,n;
  line(dc,i0,j0,i0+lx,j0);
  line(dc,i0,j0,i0,j0-ly);
  const int ss=3;
  char buf[20];

  dc.SetTextAlign(TA_CENTER);
  for(n=1;n<=nx;n++)
  {
	 i=i0+lx*n/nx;
	 line(dc,i,j0+ss,i,j0-ss);
	 if(textStatus)
	 {
		sprintf(buf,formatx,xmax*n/nx);
		dc.TextOut(i,j0+ss,buf);
	 }
  }

  dc.SetTextAlign(TA_RIGHT|TA_BASELINE);
  for(n=1;n<=ny;n++)
  {
	 j=j0-ly*n/ny; line(dc,i0-ss,j,i0+ss,j);
	 if(textStatus)
	 {
		sprintf(buf,formaty,ymax*n/ny);
		dc.TextOut(i0-ss,j,buf);
	 }
  }

  if(textStatus)
  {
	 TEXTMETRIC metric;
	 dc.GetTextMetrics(metric);
	 int dy=metric.tmHeight;
	 if(textx!=0)
	 {
		dc.SetTextAlign(TA_TOP|TA_RIGHT);
		dc.TextOut(i0+lx,j0+dy,textx);
	 }
	 if(texty!=0)
	 {
		dc.SetTextAlign(TA_BOTTOM|TA_LEFT);
		dc.TextOut(i0,j0-ly-dy,texty);
	 }
  }
}

void
TGraph::Show(TDC& dc,TSingleArray & sar,float xmax,char * textx, char * texty)
{
  if(Update(dc)==0) return;
  float ymax=sar.Max();
  if(xmax<=0.||ymax<=0.) return;
  ymax=okrug(ymax);
  Common(dc,xmax,ymax,textx,texty);

  TPen pen1(TColor(0,0,255));
  dc.SelectObject(pen1);
  rx=lx/float(sar.Size()-1);
  ry=ly/ymax;
  int i,j,n;
  j=j0-ry*sar[0];
  dc.MoveTo(i0,j);
  for(n=1;n<sar.Size();n++)
  {
	 i=i0+rx*n;
	 j=j0-ry*sar[n];
	 dc.LineTo(i,j);
  }
}

void
TGraph::Show(TDC & dc,int size,float* yy,float xmax,char* textx,char* texty)
{
  if(Update(dc)==0) return;
  float ymax=maxel(size,yy);
  if(xmax<=0.||ymax<=0.) return;
  ymax=okrug(ymax);
  Common(dc,xmax,ymax,textx,texty);

  TPen pen1(TColor(0,0,255));
  dc.SelectObject(pen1);
  rx=lx/float(size-1);
  ry=ly/ymax;
  int i,j,n;
  j=j0-ry*yy[0];
  dc.MoveTo(i0,j);
  for(n=1;n<size;n++)
  {
	 i=i0+rx*n;
	 j=j0-ry*yy[n];
	 dc.LineTo(i,j);
  }
}

void
TGraph::Show(TDC & dc,int size,float* xx,float* yy,char* textx,char* texty)
{
  if(Update(dc)==0) return;
  float xmax=maxel(size,xx);
  float ymax=maxel(size,yy);
  if(xmax<=0.||ymax<=0.) return;
  xmax=okrug(xmax);
  ymax=okrug(ymax);
  Common(dc,xmax,ymax,textx,texty);

  TPen pen1(TColor(0,0,255));
  dc.SelectObject(pen1);
  rx=lx/xmax;
  ry=ly/ymax;
  int i,j,n;
  i=i0+rx*xx[0];
  j=j0-ry*yy[0];
  dc.MoveTo(i,j);
  for(n=1;n<size;n++)
  {
	 i=i0+rx*xx[n];
	 j=j0-ry*yy[n];
	 dc.LineTo(i,j);
  }
}

TGraphic::TGraphic(char * string)
{
  FILE * fp=handle_scan(string);
	 fscanf(fp,"%i%i%i",&nx,&ny,&nz);newline(fp);
	 fscanf(fp,"%i",&angle);newline(fp);
	 fscanf(fp,"%f%f",&x0,&y0);newline(fp);
	 fscanf(fp,"%f%f%f",&sx,&sy,&sz);newline(fp);
	 fscanf(fp,"%s",formatx);newline(fp);
	 fscanf(fp,"%s",formaty);newline(fp);
	 fscanf(fp,"%s",formatz);newline(fp);
	 fscanf(fp,"%i%i",&size1,&size2);newline(fp);
  fclose(fp);
  float a=angle*M_PI/180.;
  xx0=sy*cos(a);
  yy0=sy*sin(a);
}

void
TGraphic::Clear(TDC& dc)
{
  TRect rect;
  dc.GetClipBox(rect);
  dc.FillRect(rect,TBrush(TColor::White));
}

int
TGraphic::Update(TDC& dc)
{
  TRect rect;
  dc.GetClipBox(rect);
  ii=rect.right;
  jj=rect.bottom;
  if(ii<size1||jj<size1) return 0;
  else
  {
	 if(ii<size2||jj<size2) textStatus=0;
	 else textStatus=1;
	 i0=ii*x0;
	 j0=jj*(1.-y0);
	 lx=ii*sx;
	 lz=jj*sz;
	 xx=xx0*ii;
	 yy=yy0*jj;
	 return 1;
  }
}

void
TGraphic::Common(TDC& dc,float xmax,float ymax,float zmax,char* textx,char* texty,char* textz)
{
  Clear(dc);
  TPen pen1(TColor::Black);
  dc.SelectObject(pen1);
  int i,j,n;
  const int ss=3;
  char buf[20];

  dc.SetTextAlign(TA_CENTER);
  for(n=1;n<=nx;n++)
  {
	 i=i0+lx*n/nx;
	 line(dc,i,j0+ss,i,j0-ss);
	 if(textStatus)
	 {
		sprintf(buf,formatx,xmax*n/nx);
		dc.TextOut(i,j0+ss,buf);
	 }
  }

  dc.SetTextAlign(TA_LEFT);
  for(n=1;n<=ny;n++)
  {
	 i=i0+lx+n*float(xx)/ny;
	 j=j0-n*float(yy)/ny;
	 if(textStatus)
	 {
		sprintf(buf,formaty,ymax*n/ny);
		dc.TextOut(i,j,buf);
	 }
	 line(dc,i,j-ss,i,j+ss);
  }

  dc.SetTextAlign(TA_RIGHT|TA_BASELINE);
  for(n=1;n<=nz;n++)
  {
	 j=j0-lz*n/nz;
	 line(dc,i0-ss,j,i0+ss,j);
	 if(textStatus)
	 {
		sprintf(buf,formatz,zmax*n/nz);
		dc.TextOut(i0-ss,j,buf);
	 }
  }

  if(textStatus)
  {
	 TEXTMETRIC metric;
	 dc.GetTextMetrics(metric);
	 int dy=metric.tmHeight;
	 if(textx!=0)
	 {
		dc.SetTextAlign(TA_TOP|TA_RIGHT);
		dc.TextOut(i0+lx,j0+dy,textx);
	 }
	 if(texty!=0)
	 {
		dc.SetTextAlign(TA_BOTTOM|TA_LEFT);
		dc.TextOut(i0+lx+xx,j0-yy-dy,texty);
	 }
	 if(textz!=0)
	 {
		dc.SetTextAlign(TA_BOTTOM|TA_RIGHT);
		dc.TextOut(i0,j0-lz-dy,textz);
	 }
  }

  line(dc,i0,j0,i0,j0-lz);
  line(dc,i0,j0,i0+lx,j0);
  line(dc,i0+lx,j0,i0+lx+xx,j0-yy);
  line(dc,i0,j0,i0+xx,j0-yy);
//  line(dc,i0+xx,j0-yy,i0+xx+lx,j0-yy);
}

void
TGraphic::Show(TDC& dc,TDoubleArray & dar,float xmax,float ymax,char* textx,char* texty,char* textz)
{
  if(Update(dc)==0) return;
  float zmax=dar.Max();
  if(xmax<=0.||ymax<=0.||zmax<=0.) return;
  zmax=okrug(zmax);
  Common(dc,xmax,ymax,zmax,textx,texty,textz);

  int i,j;
  float rx=float(lx)/(dar.XSize()-1);
  float ry=1./(dar.YSize()-1);
  float rz=lz/zmax;

  dc.SelectObject(TBrush(TColor::White));
  TPen pen0(TColor::White);
  TPen pen1(TColor(0,0,255));
  int xp,zp;
  for(j=dar.YSize()-1;j>=0;j--)
  {
	 int x=i0+ry*j*xx;
	 int y=j0-ry*j*yy;
	 int z=rz*dar[j][0];
	 for(i=1;i<dar.XSize();i++)
	 {
		xp=x;zp=z;
		x=i0+rx*i+ry*j*xx;
		z=rz*dar[j][i];
		dc.SelectObject(pen0);
		polygon(dc,y,xp,zp,x,z);
		dc.SelectObject(pen1);
		line(dc,xp,y-zp,x,y-z);
	 }
  }
  dc.SelectObject(TPen(TColor::Black));
  line(dc,i0,j0,i0,j0-lz);
  dc.RestorePen();
  dc.RestoreBrush();
}

void
TGraph::Show1(TDC& dc,TSingleArray & sar)
{
  if(sar.Max()<=0.|| rx<=0.|| ry<=0.) return;
  int i,j,n;
  j=j0-ry*sar[0];
  dc.MoveTo(i0,j);
  TPen pen1(TColor(255,0,0));
  dc.SelectObject(pen1);
  for(n=1;n<sar.Size();n++)
  {
	 i=i0+rx*n;
	 j=j0-ry*sar[n];
	 dc.LineTo(i,j);
  }
}
