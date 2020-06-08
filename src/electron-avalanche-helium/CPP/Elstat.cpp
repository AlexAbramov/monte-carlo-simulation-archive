#pragma hdrstop
#include <math.h>
#include <param.h>
#include <he.h>
#include <elstat.h>

TElStat elstat;

TElStat::TElStat()
{
  xsize=0;
  esize=0;
#ifdef __MAXPARAM
  msize=0;
  tsize=0;
  rdt=0.;
  rdl=0.;
#endif
}

static float elStatInitValue=.00001;

void
TElStat::Init()
{
  if(param.Status()==0) error_message("TElStat::Init()");
  xsize=param.xsize;
  esize=param.esize;
  stat.Init(xsize);
  stat+=elStatInitValue;
  energy.Init(xsize);
  vdr.Init(xsize);
  vel.Init(xsize);
  evx.Init(xsize);
  er.Init(xsize);
  ee.Init(xsize);
  fel.Init(xsize);
  fex.Init(xsize);
  fio.Init(xsize);
  buf.Init(xsize);
  bfr.Init(esize);
  fre.Init(xsize,esize);
  buffer.Init(xsize,esize);
#ifdef __MAXPARAM
  msize=param.msize;
  test0.Init(xsize);
  test1.Init(xsize);
  test2.Init(xsize);
  test3.Init(xsize);
  test4.Init(xsize);
  test5.Init(xsize);
  test6.Init(xsize);
  test7.Init(xsize);
  test8.Init(xsize);
  test9.Init(xsize);
  test10.Init(xsize);
  test11.Init(xsize);
  test12.Init(xsize);
  test13.Init(xsize);
  test14.Init(xsize);
  test15.Init(xsize);
  test16.Init(xsize);
  test17.Init(xsize);
  test18.Init(xsize);
  test19.Init(xsize);
  frem.Init(esize,msize);
  buffer1.Init(esize,msize);
  total_nion=0.;
  total_time=0.;
  total_s=0.;
  total_sx=0.;
  total_x=0.;
  tsize=param.tsize;
  TotalTime.Init(tsize);
  TotalS.Init(tsize);
  TotalSx.Init(tsize);
  TotalX.Init(tsize);
  buf2.Init(tsize);
  rdt=1./param.dt;
  rdl=1./param.dl;
#endif
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
	 float v=sqrt(e);
	 vel[i]+=m*v;
	 stat[i]+=m;
	 energy[i]+=m*e;
	 evx[i]+=m*e*vx;
	 er[i]+=m*(e-vx*vx);
	 ee[i]+=m*e*e;
	 fel[i]+=m*he.Felas(e);
	 if(e>he.Pex()) fex[i]+=m*he.Fex(e);
	 if(e>he.Pion()) fio[i]+=m*he.Fion(e);
	 if(e<param.emax)
	 {
		int j=e*param.rde+.5;
		if(j>=0&&j<esize)
		{
		  fre[i][j]+=m;
		}
	 }
#ifdef __MAXPARAM
	 float cosf=vx/v;
	 test0[i]+=m*e;
	 test1[i]+=m*e;
	 test2[i]+=m*e;
	 test3[i]+=m*e;
	 test4[i]+=m*e;
	 test5[i]+=m*e;
	 test6[i]+=m*e;
	 test7[i]+=m*e;
	 test8[i]+=m*e;
	 test9[i]+=m*e;
	 test10[i]+=m*e;
	 test11[i]+=m*e;
	 test12[i]+=m*e;
	 test13[i]+=m*e;
	 test14[i]+=m*e;
	 test15[i]+=m*e;
	 test16[i]+=m*e;
	 test17[i]+=m*e;
	 test18[i]+=m*e;
	 test19[i]+=m*e;
	 if(e<param.emax)
	 {
		int j=e*param.rde+.5;
		if(j>=0&&j<esize)
		{
		  if(i==param.im)
		  {
			 int k=((cosf+1.)*.5)*(msize-1.)+.5;
			 if(k>=0&&k<msize)
				frem[j][k]+=m;
		  }
		}
	 }
#endif
  }
}

void
TElStat::Read(int fd)
{
  stat.Read(fd);
  energy.Read(fd);
  vdr.Read(fd);
  vel.Read(fd);
  evx.Read(fd);
  er.Read(fd);
  ee.Read(fd);
  fel.Read(fd);
  fex.Read(fd);
  fio.Read(fd);
  fre.Read(fd);
#ifdef __MAXPARAM
  test0.Read(fd);
  test1.Read(fd);
  test2.Read(fd);
  test3.Read(fd);
  test4.Read(fd);
  test5.Read(fd);
  test6.Read(fd);
  test7.Read(fd);
  test8.Read(fd);
  test9.Read(fd);
  test10.Read(fd);
  test11.Read(fd);
  test12.Read(fd);
  test13.Read(fd);
  test14.Read(fd);
  test15.Read(fd);
  test16.Read(fd);
  test17.Read(fd);
  test18.Read(fd);
  test19.Read(fd);
  frem.Read(fd);
  int sf=sizeof(float);
  read(fd,&total_nion,sf);
  read(fd,&total_time,sf);
  read(fd,&total_s,sf);
  read(fd,&total_sx,sf);
  read(fd,&total_x,sf);
  TotalTime.Read(fd);
  TotalS.Read(fd);
  TotalSx.Read(fd);
  TotalX.Read(fd);
#endif
}

void
TElStat::Write(int fd)
{
  stat.Write(fd);
  energy.Write(fd);
  vdr.Write(fd);
  vel.Write(fd);
  evx.Write(fd);
  er.Write(fd);
  ee.Write(fd);
  fel.Write(fd);
  fex.Write(fd);
  fio.Write(fd);
  fre.Write(fd);
#ifdef __MAXPARAM
  test0.Write(fd);
  test1.Write(fd);
  test2.Write(fd);
  test3.Write(fd);
  test4.Write(fd);
  test5.Write(fd);
  test6.Write(fd);
  test7.Write(fd);
  test8.Write(fd);
  test9.Write(fd);
  test10.Write(fd);
  test11.Write(fd);
  test12.Write(fd);
  test13.Write(fd);
  test14.Write(fd);
  test15.Write(fd);
  test16.Write(fd);
  test17.Write(fd);
  test18.Write(fd);
  test19.Write(fd);
  frem.Write(fd);
  int sf=sizeof(float);
  write(fd,&total_nion,sf);
  write(fd,&total_time,sf);
  write(fd,&total_s,sf);
  write(fd,&total_sx,sf);
  write(fd,&total_x,sf);
  TotalTime.Write(fd);
  TotalS.Write(fd);
  TotalSx.Write(fd);
  TotalX.Write(fd);
#endif
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
TElStat::GetDensity()
{
  buf.Obnul();
  buf+=stat;
  buf.Normir(1.);
  return buf;
}

#ifdef __MAXPARAM
TDoubleArray&
TElStat::GetFrem()
{
  for(int i=0;i<esize;i++)
  {
//	 float r=1./fre[param.im][i];
	 int j;
	 float sum=elStatInitValue;
	 for(j=0;j<msize;j++) sum+=frem[i][j];
	 float rsum=1./sum;
	 for(j=0;j<msize;j++) buffer1[i][j]=frem[i][j]*rsum;
  }
  return buffer1;
}

TSingleArray&
TElStat::InitBuf2(TSingleArray& sar)
{
  buf2.Obnul();
  buf2+=sar;
  buf2.Normir(1.);
  return buf2;
}

void
TElStat::Add(float time,float s,float sx,float x)
{
  int i=time*rdt+.5;
  if(i<tsize) TotalTime[i]+=1.;
  i=s*rdl+.5;
  if(i<tsize) TotalS[i]+=1.;
  i=sx*rdl+.5;
  if(i<tsize) TotalSx[i]+=1.;
  i=.5*(x*rdl+tsize+1.);
  if(i<tsize&&i>=0) TotalX[i]+=1.;
}

#endif

