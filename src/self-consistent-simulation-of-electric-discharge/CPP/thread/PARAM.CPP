#pragma hdrstop
#include <math.h>
#include <stdio.h>
#include <io.h>
#include <param.h>

#define PARAM_TEXT_FILE "dat\\param.dat"
#define VOLTAGE_MIN 50.

TParam param;

void
TParam::Update()
{
  voltage=eds;
  dx=lx/xsize; dy=ly/ysize+.00001;
  dvol=dx*dy*param.lz;
}

TParam::TParam()
{
  status=0;
  path="dat\\param.dat";
}

TParam::~TParam()
{
}

void
TParam::Scan()
{
  FILE * fp=handle_scan(PARAM_TEXT_FILE);
  fscanf(fp,"%i",&xsize);newline(fp);
  fscanf(fp,"%i",&ysize);newline(fp);
  fscanf(fp,"%f",&eds);newline(fp);
  fscanf(fp,"%f",&resist);newline(fp);
  fscanf(fp,"%f",&gamma);newline(fp);
  fscanf(fp,"%f",&c0);newline(fp);
  fscanf(fp,"%f",&dt);newline(fp);
  fscanf(fp,"%f",&lx);newline(fp);
  fscanf(fp,"%f",&ly);newline(fp);
  fscanf(fp,"%f",&lz);newline(fp);
  fscanf(fp,"%i",&tsize);newline(fp);
  fscanf(fp,"%i",&ntimes);newline(fp);
  fclose(fp);
  Update();
  time=0.;
  current=0.;
  status=1;
}

void
TParam::Print()
{
  FILE * fp=fopen(PARAM_TEXT_FILE,"w");
  if(fp==0) error_message("Error in TParam::Print()");
  fprintf(fp,"%i \t-xsize\n",xsize);
  fprintf(fp,"%i \t-ysize\n",ysize);
  fprintf(fp,"%f \t-eds\n",eds);
  fprintf(fp,"%f \t-resist\n",resist);
  fprintf(fp,"%f \t-gamma\n",gamma);
  fprintf(fp,"%f \t-c0\n",c0);
  fprintf(fp,"%f \t-dt\n",dt);
  fprintf(fp,"%f \t-lx\n",lx);
  fprintf(fp,"%f \t-ly\n",ly);
  fprintf(fp,"%f \t-lz\n",lz);
  fprintf(fp,"%i \t-tsize\n",tsize);
  fprintf(fp,"%i \t-ntimes\n",ntimes);
  fclose(fp);
}

void
TParam::Read(int fd)
{
  int si=sizeof(int);
  int sf=sizeof(float);
  read(fd,&xsize,si);
  read(fd,&ysize,si);
  read(fd,&eds,sf);
  read(fd,&resist,sf);
  read(fd,&gamma,sf);
  read(fd,&c0,sf);
  read(fd,&dt,sf);
  read(fd,&lx,sf);
  read(fd,&ly,sf);
  read(fd,&lz,sf);
  read(fd,&time,sf);
  read(fd,&current,sf);
  read(fd,&voltage,sf);
  read(fd,&tsize,si);
  read(fd,&ntimes,si);
  Update();
  status=1;
}

void TParam::Write(int fd)
{
  int si=sizeof(int);
  int sf=sizeof(float);
  write(fd,&xsize,si);
  write(fd,&ysize,si);
  write(fd,&eds,sf);
  write(fd,&resist,sf);
  write(fd,&gamma,sf);
  write(fd,&c0,sf);
  write(fd,&dt,sf);
  write(fd,&lx,sf);
  write(fd,&ly,sf);
  write(fd,&lz,sf);
  write(fd,&time,sf);
  write(fd,&current,sf);
  write(fd,&voltage,sf);
  write(fd,&tsize,si);
  write(fd,&ntimes,si);
}

void
TParam::Step()
{
  time+=dt;
//  const float kper=.08842;
//  current=kper*charge/timeSred;
//  if(voltage<VOLTAGE_MIN) voltage=VOLTAGE_MIN;
}

void TParam::RegistrateDirectory(string s)
{
  path=s+"\\dat\\param.dat";
}

