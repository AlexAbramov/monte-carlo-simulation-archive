#include <math.h>
#pragma hdrstop
#include <he.h>
#include <param.h>
#include <elstat.h>

TElStat elstat;

void
TElStat::Init()
{
  if(param.Status()==0) error_message("TElStat::Init()");
  xsize=param.xsize;
  esize=param.esize;
  stat.Init(xsize);
  stat+=.00001;
  energy.Init(xsize);
  vdr.Init(xsize);
  evx.Init(xsize);
  fex.Init(xsize);
  fio.Init(xsize);
  buf.Init(xsize);
  bfr.Init(esize);
  fre.Init(xsize,esize);
  buffer.Init(xsize,esize);
  nion=0.;
}

TSingleArray&
TElStat::InitBuf(TSingleArray& sar)
{
  for(int i=0;i<xsize;i++) buf[i]=sar[i]/stat[i];
  return buf;
}

TSingleArray&
TElStat::InitBuf1(TSingleArray& sar)
{
  for(int i=0;i<xsize;i++) buf[i]=he.Kper()*sar[i]/stat[i];
  return buf;
}

void
TElStat::Count(int i,float vx,float e)
{
  if(xsize<=0||esize<=0) error_message("TElStat::Count()");
  if(i>=0&&i<xsize)
  {
	 if(vx>0.) vdr[i]++;
	 if(vx<0.) vdr[i]--;
	 float m=1./fabs(vx);
	 stat[i]+=m;
	 energy[i]+=m*e;
	 evx[i]+=m*e*vx;
//	 if(e>he.Pex()) fex[i]+=m*he.Fex(e);
//	 if(e>he.Pion()) fio[i]+=m*he.Fion(e);
	 if(e<param.emax)
	 {
		int j=e*param.rde+.5;
		if(j>=0&&j<esize)
		{
		  fre[i][j]+=m;
		}
	 }
  }
}

void
TElStat::Read(int fd)
{
  stat.Read(fd);
  energy.Read(fd);
  vdr.Read(fd);
  evx.Read(fd);
  fex.Read(fd);
  fio.Read(fd);
  fre.Read(fd);
  read(fd,&nion,sizeof(float));
}

void
TElStat::Write(int fd)
{
  stat.Write(fd);
  energy.Write(fd);
  vdr.Write(fd);
  evx.Write(fd);
  fex.Write(fd);
  fio.Write(fd);
  fre.Write(fd);
  write(fd,&nion,sizeof(float));
}

TDoubleArray&
TElStat::GetFre()
{
  for(int i=0;i<xsize;i++)
  {
	 float r=1./stat[i];
	 for(int j=0;j<esize;j++)
	 {
		buffer[i][j]=r*fre[i][j];
	 }
  }
  return buffer;
}

TSingleArray&
TElStat::GetFre1(int i)
{
  if(i<0||i>xsize) error_message("i out range in TElStat::GetFre1");
  float r=1./stat[i];
  for(int j=0;j<esize;j++)
  {
	 bfr[j]=r*fre[i][j];
  }
  return bfr;
}

TSingleArray&
TElStat::InitBuf2(TSingleArray& sar)
{
  long int nlav=param.nlav;
  if(nlav==0L) nlav=1;
  float r=1./nlav;
  for(int i=0;i<xsize;i++) buf[i]=sar[i]*r;
  return buf;
}

void
TElStat::Add1(int i,float prex)
{
  if(xsize<=0||esize<=0) error_message("TElStat::Count()");
  if(i>=0&&i<xsize) fex[i]+=prex;
}

void
TElStat::Add2(int i,float prion)
{
  if(xsize<=0||esize<=0) error_message("TElStat::Count()");
  if(i>=0&&i<xsize) fio[i]+=prion;
}

float
TElStat::Get1()
{
  long int nlav=param.nlav;
  if(nlav==0L) nlav=1;
  float r=1./nlav;
  return fex.Sum()*r;
}

float
TElStat::Get2()
{
  long int nlav=param.nlav;
  if(nlav==0L) nlav=1;
  float r=1./nlav;
  return fio.Sum()*r;
}

float
TElStat::GetNion()
{
  long int nlav=param.nlav;
  if(nlav==0L) nlav=1;
  float r=1./nlav;
  return nion*r;
}

