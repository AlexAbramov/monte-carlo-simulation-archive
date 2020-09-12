#include <math.h>
#include <stdio.h>
#include <io.h>
#pragma hdrstop
#include <param.h>

#define PARAM_TEXT_FILE "..\\..\\dat\\param.dat"
#define VOLTAGE_MIN 10.

TParam param;

void
TParam::Update()
{
  dx=lx/xsize; dy=ly/ysize+.00001;
  emax=esize*de; rde=1./de;
}

TParam::TParam()
{
  status=0;
}

TParam::~TParam()
{
}

void
TParam::Scan()
{
  FILE * fp=fopen(PARAM_TEXT_FILE,"r");
  if(fp==0) error_message("Error in TParam::Scan()");
  fscanf(fp,"%i",&xsize);newline(fp);
  fscanf(fp,"%i",&ysize);newline(fp);
  fscanf(fp,"%f",&lx);newline(fp);
  fscanf(fp,"%f",&ly);newline(fp);
  fscanf(fp,"%f",&voltage);newline(fp);
  fscanf(fp,"%f",&dk);newline(fp);
  fscanf(fp,"%f",&fd);newline(fp);
  fscanf(fp,"%f",&de);newline(fp);
  fscanf(fp,"%i",&esize);newline(fp);
  fscanf(fp,"%f",&xem);newline(fp);
  fclose(fp);
  Update();
  nlav=0;
  status=1;
}

void
TParam::Print()
{
  FILE * fp=fopen(PARAM_TEXT_FILE,"w");
  if(fp==0) error_message("Error in TParam::Print()");
  fprintf(fp,"%i \t-xsize\n",xsize);
  fprintf(fp,"%i \t-ysize\n",ysize);
  fprintf(fp,"%f \t-lx\n",lx);
  fprintf(fp,"%f \t-ly\n",ly);
  fprintf(fp,"%f \t-voltage\n",voltage);
  fprintf(fp,"%f \t-dk\n",dk);
  fprintf(fp,"%f \t-fd\n",fd);
  fprintf(fp,"%f \t-de\n",de);
  fprintf(fp,"%i \t-esize\n",esize);
  fprintf(fp,"%f \t-xem\n",xem);
  fclose(fp);
}

void
TParam::Read(int id)
{
  int si=sizeof(int);
  int sf=sizeof(float);
  int sli=sizeof(long int);
  read(id,&xsize,si);
  read(id,&ysize,si);
  read(id,&lx,sf);
  read(id,&ly,sf);
  read(id,&voltage,sf);
  read(id,&dk,sf);
  read(id,&fd,sf);
  read(id,&nlav,sli);
  read(id,&de,sf);
  read(id,&esize,si);
  read(id,&xem,sf);
  Update();
  status=1;
}

void TParam::Write(int id)
{
  int si=sizeof(int);
  int sf=sizeof(float);
  int sli=sizeof(long int);
  write(id,&xsize,si);
  write(id,&ysize,si);
  write(id,&lx,sf);
  write(id,&ly,sf);
  write(id,&voltage,sf);
  write(id,&dk,sf);
  write(id,&fd,sf);
  write(id,&nlav,sli);
  write(id,&de,sf);
  write(id,&esize,si);
  write(id,&xem,sf);
}


