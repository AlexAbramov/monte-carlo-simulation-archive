#include<param.h>
#include<field.h>
#include<buffer.h>

TBuffer buffer;

float gamma(float e,float f)
{
  return param.gamma;
/*
  if(f<500.) return f*.001;
  else return .5;
*/
}

void
TBuffer::Init()
{
  if(param.Status()==0) error_message("TBuffer::Init");
  elar.Init(param.bufferSize);
  ionar.Init(param.bufferSize);
  genar.Init(param.bufferSize);
  status=1;
  Clear();
  Step();
}

void
TBuffer::Control()
{
  if(status==0) error_message("status=0 in TBuffer::Control");
}

void
TBuffer::Clear()
{
  const float fmin=.00001;
  Control();
  ionar.Obnul();
  elar.Obnul();
  ionar+=fmin;
  elar+=fmin;
  nion=fmin;
  nel=0.;
  time=0.;
}

void
TBuffer::Add(float y,float enr,float t)
{
  Control();
  time+=t;
  if(param.Status()!=1) error_message("TBuffer::Add");
  int j=y/param.dy;
  float f=field.Get(j,0);
  float g=gamma(enr,f);
  j=y*param.bufferSize/param.ly;
  if(j>=param.bufferSize)j=param.bufferSize-1;
  ionar[j]++;
  nion++;
  elar[j]+=g;
  nel+=g;
}

void
TBuffer::Step()
{
  Control();
  genar.Obnul();
  genar+=elar;
  genar.Normir();
  genar.Integral();
}

float
TBuffer::Emit(float r)
{
  Control();
  int size=genar.Size();
  for(int j=0;j<size;j++) if( r<genar[j] ) break;
  if( j >= size ) j=size-1;
  float y=(j+.5)*param.ly/size;
  if(y<0.||y>param.ly) error_message("TBuffer::Emit");
  return y;
}

void
TBuffer::Write(int fd)
{
  Control();
  int sf=sizeof(float);
  write(fd,&time,sf);
  write(fd,&nion,sf);
  write(fd,&nel,sf);
  ionar.Write(fd);
  elar.Write(fd);
}

void
TBuffer::Read(int fd)
{
  Control();
  int sf=sizeof(float);
  read(fd,&time,sf);
  read(fd,&nion,sf);
  read(fd,&nel,sf);
  ionar.Read(fd);
  elar.Read(fd);
  Step();
}
