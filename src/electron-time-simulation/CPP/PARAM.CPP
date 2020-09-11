#include <math.h>
#include <stdio.h>
#include <io.h>
#pragma hdrstop
#include <param.h>

#define PARAM_TEXT_FILE "..\\..\\dat\\param.dat"

TParam param;

void
TParam::Update()
{
  tmax=tsize*dt;
  emax=esize*de;
  rde=1./de;
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
  fscanf(fp,"%f",&lx);newline(fp);
  fscanf(fp,"%f",&ly);newline(fp);
  fscanf(fp,"%f",&fd);newline(fp);
  fscanf(fp,"%f",&xem);newline(fp);
  fscanf(fp,"%f",&dt);newline(fp);
  fscanf(fp,"%i",&tsize);newline(fp);
  fscanf(fp,"%f",&de);newline(fp);
  fscanf(fp,"%i",&esize);newline(fp);
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
  fprintf(fp,"%f \t-lx\n",lx);
  fprintf(fp,"%f \t-ly\n",ly);
  fprintf(fp,"%f \t-field\n",fd);
  fprintf(fp,"%f \t-xem\n",xem);
  fprintf(fp,"%f \t-dt\n",dt);
  fprintf(fp,"%i \t-tsize\n",tsize);
  fprintf(fp,"%f \t-de\n",de);
  fprintf(fp,"%i \t-esize\n",esize);
  fclose(fp);
}

void
TParam::Read(int id)
{
  int si=sizeof(int);
  int sf=sizeof(float);
  int sli=sizeof(long int);
  read(id,&lx,sf);
  read(id,&ly,sf);
  read(id,&fd,sf);
  read(id,&xem,sf);
  read(id,&dt,sf);
  read(id,&tsize,si);
  read(id,&de,sf);
  read(id,&esize,si);
  read(id,&nlav,sli);
  Update();
  status=1;
}

void TParam::Write(int id)
{
  int si=sizeof(int);
  int sf=sizeof(float);
  int sli=sizeof(long int);
  write(id,&lx,sf);
  write(id,&ly,sf);
  write(id,&fd,sf);
  write(id,&xem,sf);
  write(id,&dt,sf);
  write(id,&tsize,si);
  write(id,&de,sf);
  write(id,&esize,si);
  write(id,&nlav,sli);
}
