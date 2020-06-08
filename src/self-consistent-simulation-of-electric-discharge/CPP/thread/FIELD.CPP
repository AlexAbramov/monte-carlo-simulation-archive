#pragma hdrstop
#include <math.h>
#include <param.h>
#include <myrandom.h>
#include <field.h>

TField field;
#define INIT_CIO_RANDOM

static const float koef=11.31;

TField::TField()
{
  FILE * fp=handle_scan("dat\\gamma.dat");
	 fscanf(fp,"%f",&g0); newline(fp);
	 fscanf(fp,"%f",&f1); newline(fp);
	 fscanf(fp,"%f",&rz); newline(fp);
	 fscanf(fp,"%f",&kup); newline(fp);
	 fscanf(fp,"%f",&kdown); newline(fp);
  fclose(fp);
  status=0;
}

float
TField::Gamma(float f)
{
  float g1=param.gamma;
  float g;
  if(g0<0.||f1<=0.) g=g1;
  else
  {
	 if( f<f1 ) g=g0+(g1-g0)*f/f1;
	 else g=g1;
  }
  return g;
}

float
TField::Gamma(int j)
{
  Control();
  return Gamma(ff[j][0]);
}

void
TField::Control()
{
  if(status==0) error_message("TField::Control()");
}

void
TField::Init()
{
  if(param.Status()==0) error_message("TField::Init()");
  ff.Init(param.ysize,param.xsize);
  cio.Init(param.ysize,param.xsize);
  buf.Init(param.ysize);
  buf1.Init(param.ysize);
// Field inicialization
//  ff+=param.eds/param.lx;

#ifdef INIT_CIO_RANDOM
  for(int j=0;j<cio.YSize();j++)
  {
	 float d=param.c0*(1.+rz*rnd[5]);
	 for(int i=0;i<cio.XSize();i++) cio[j][i]+=d;
  }
#else
  cio+=param.c0;//!!!
#endif
  status=1;
  Step();
}

float
TField::Get(int j,int i)
{
  Control();
  return ff[j][i];
}

float
TField::Get(float y,int i)
{
  Control();
  int j=y/param.dy;
  return ff[j][i];
}

void
TField::CioAdd(int i,float y,float dcio)
{
  Control();
  int j=int(y/param.dy);
  cio[j][i]+=dcio;
}

float vdi(float f)// return in units [sm/mksec]
{	//checked
  if(f<0.) error_message("Error in vdi");
  if(f<25.) return .008*f;
  else return .04*sqrt(f);
}

void
TField::CioStep()
{
// cio
  int j;
  for(j=0;j<param.ysize;j++) buf[j]=CioStep1(ff[j],cio[j]);
  if(cio.Min()<0.) error_message("Error in TField::CioStep(): cio.Min()<0");

  // buf1
  for(j=0;j<param.ysize;j++) buf1[j]=buf[j]*(1.+Gamma(j))*param.dx/param.dt;
}

float
TField::CioStep1(float * f1,float * c1)
{
  float ret;
  float ii=param.xsize;
  float dx=param.dx;
  float dt=param.dt;
  for(int i=0;i<ii;i++)
  {
	 float f=f1[i];
	 if(f>0.)
	 {
		float k=vdi(f)*dt/dx;
		if(k>.5)// k=.5;
		{
		  char tt[50];
		  sprintf(tt,"Overflow: k=%f, fd=%f",k,f);
		  error_message(tt);
		}
		float d=c1[i]*k;
		if(i==0) ret=d;
		else c1[i-1]+=d;
		c1[i]-=d;
	 }
	 else break;
  }
//  while(i<ii){ c1[i]=0.; i++;}//!!!!!
  return ret;
}

void
TField::FieldStep()
{
  Control();
  if(cio.Min()<0.) error_message("TField::Step");
  for(int j=0;j<param.ysize;j++) FieldStep1( ff[j],cio[j] );
}

void
TField::FieldStep1(float * f1,float * c1)
{
  int ii=param.xsize;
  float dx=param.dx;
  float u=param.voltage;
  float s=0.;
  int i=1;
  int ik;
  f1[0]=0.;
  while(1)
  {
	 s+=f1[i-1]*dx;
	 float d=koef*c1[i]*dx;
	 f1[i]=f1[i-1]-d;
	 float du=s-f1[i]*i*dx-u;
	 float df;
	 if(du>0.)
	 {
		ik=i-1;
		df=-f1[i]-du/(dx*i);
		for(i=0;i<=ik;i++) f1[i]+=df;
		for(i=ik+1;i<ii;i++) f1[i]=0.;
		break;
	 }
	 if(i==ii-1)
	 {
		df=-f1[i]-du/(dx*(ii-1));
		for(i=0;i<ii;i++) f1[i]+=df;
		break;
	 }
	 i++;
  }
  for(i=0;i<ii;i++) if(f1[i]<0.) error_message("field<0.");
}

void
TField::Read(int id)
{
  cio.Read(id);
  Step();
}

void
TField::Write(int id)
{
  cio.Write(id);
}

float
TField::CioOut()
{
  Control();
  float s=0.;
  for(int j=0;j<param.ysize;j++) s+=buf[j];
  return s;
}

// NEW !!!

void TField::Step()
{
  const int kit=10;// iteration number
  float xmin=0.;
  float xmax=param.eds;
  float ymin=-param.eds;
  float ymax=param.resist*Current(xmax);
  for(int i=0;i<kit;i++)
  {
	 float x=.5*(xmin+xmax);
	 float y=x+param.resist*Current(x)-param.eds;// y function !!!
	 if(y<0.) xmin=x;
	 else xmax=x;
	 if(y<ymin||y>ymax)error_message("Error in TField::Step() - y out range");
  }
  param.voltage=.5*(xmin+xmax);
  if(param.voltage<0.) error_message("voltage<0");
  if(param.voltage>param.eds) error_message("voltage>eds");
  param.current=Current(param.voltage);
  if(param.current<0.) error_message("current<0");
  FieldStep();
  CioStep();
  param.Step();
}

float TField::Current(float u)
{
//  Control();
//  if(cio.Min()<0.) error_message("TField::Step");
  float s=0.;
  for(int j=0;j<param.ysize;j++) s+=Current1( u,cio[j] )*(1.+Gamma(j));
  return s*param.dy*param.lz;
}

float
TField::Current1(float u,float * c1)
{
  int ii=param.xsize;
  float dx=param.dx;
  float s=0.;
  float f=0.;
  int i=1;
  while(1)
  {
	 s+=f*dx;
	 float d=koef*c1[i]*dx;
	 f-=d;
	 float du=s-f*i*dx-u;
	 if(du>0.||i==ii-1)
	 {
		f=-f-du/(dx*i);
		break;
	 }
	 i++;
  }
  return c1[0]*vdi(f);
}

