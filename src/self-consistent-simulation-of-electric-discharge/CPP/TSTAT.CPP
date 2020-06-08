#pragma hdrstop
#include <param.h>
#include <tstat.h>

TTStat tstat;

void
TTStat::Init()
{
  if(param.Status()==0) error_message("TTStat::Init()");
  current.Init(param.tsize);
  voltage.Init(param.tsize);
  status=1;
}

void
TTStat::Step()
{
  if(status==0||param.Status()==0) return;
  int i=param.time/param.dt;
  if(i%param.ntimes==0)
  {
	 i/=param.ntimes;
	 i%=param.tsize;
         if(i>=0 && i<param.tsize)
	 {
	   current[i]=param.current;
	   voltage[i]=param.voltage;
	 }
  }
}

void
TTStat::Read(int fd)
{
  if(status==0) return;
  current.Read(fd);
  voltage.Read(fd);
}

void
TTStat::Write(int fd)
{
  if(status==0) return;
  current.Write(fd);
  voltage.Write(fd);
}

float
TTStat::GetTime()
{
  return param.dt*param.ntimes*param.tsize;
}

void
TTStat::Clear()
{
  current.Obnul();
  voltage.Obnul();
}
