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
  tsize=param.tsize;
  esize=param.esize;
  stat.Init(tsize);
  stat+=.00001;
  energy.Init(tsize);
  vdr.Init(tsize);
  evx.Init(tsize);
  fex.Init(tsize);
  fio.Init(tsize);
  buf.Init(tsize);
  bfr.Init(esize);
  fre.Init(tsize,esize);
  buffer.Init(tsize,esize);
}

TSingleArray&
TElStat::InitBuf(TSingleArray& sar)
{
  for(int i=0;i<tsize;i++) buf[i]=sar[i]/stat[i];
  return buf;
}

TSingleArray&
TElStat::InitBuf1(TSingleArray& sar)
{
  for(int i=0;i<tsize;i++) buf[i]=he.Kper()*sar[i]/stat[i];
  return buf;
}

void
TElStat::Count(int i,float vx,float e)
{
  if(tsize<=0||esize<=0) error_message("TElStat::Count()");
  if(i>=0&&i<tsize)
  {
	 stat[i]+=1.;
	 vdr[i]+=vx;
	 energy[i]+=e;
	 evx[i]+=e*vx;
	 if(e>he.Pex()) fex[i]+=he.Fex(e);
	 if(e>he.Pion()) fio[i]+=he.Fion(e);
	 if(e<param.emax)
	 {
		int j=e*param.rde+.5;
		if(j>=0&&j<esize)
		{
		  fre[i][j]+=1.;
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
}

TDoubleArray&
TElStat::GetFre()
{
  for(int i=0;i<tsize;i++)
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
  if(i<0||i>tsize) error_message("i out range in TElStat::GetFre1");
  float r=1./stat[i];
  for(int j=0;j<esize;j++)
  {
	 bfr[j]=r*fre[i][j];
  }
  return bfr;
}
