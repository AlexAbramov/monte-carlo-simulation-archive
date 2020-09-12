#include <math.h>
#include <stdio.h>
#include <io.h>
#pragma hdrstop
#include <param.h>
#include <cstring.h>

#define VOLTAGE_MIN 10.

TParam param;

void
TParam::Update()
{
  dx=lx/xsize;
  dy=ly/ysize+.00001;// don't neglect this string, it may be important for rare cases
  emax=esize*de; rde=1./de;
#ifdef __MAXPARAM
  im=xm/dx;
  if(im<0||im>=xsize) error_message("Error in TParam::Update(): no valid im");
  if(msize<1) error_message("Invalid parameter 'msize', check param.dat file");
  if(tsize<1) error_message("Invalid parameter 'tsize', check param.dat file");
  if(dt<=0.) error_message("Invalid parameter 'dt', check param.dat file");
  if(dl<=0.) error_message("Invalid parameter 'dl', check param.dat file");
#endif
}

TParam::TParam()
{
  status=0;
  path="..\\..\\dat\\param.dat";
}

void TParam::RegistrateDirectory(string s)
{
  path=s+"\\..\\..\\dat\\param.dat";
}

TParam::~TParam()
{
}

void
TParam::Scan()
{
  FILE * fp=fopen(path.c_str(),"r");
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
  fscanf(fp,"%i",&msize);newline(fp);
  fscanf(fp,"%f",&xm);newline(fp);
  fscanf(fp,"%i",&tsize);newline(fp);
  fscanf(fp,"%f",&dt);newline(fp);
  fscanf(fp,"%f",&dl);newline(fp);
  fclose(fp);
  Update();
  nlav=0;
  status=1;
}

void
TParam::Print(FILE * fp)
{
  int pflag=0;
  if(fp==0) fp=fopen(path.c_str(),"w");
  else pflag=1;
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
  fprintf(fp,"%i \t-msize\n",msize);
  fprintf(fp,"%f \t-xm\n",xm);
  fprintf(fp,"%i \t-tsize\n",tsize);
  fprintf(fp,"%f \t-dt\n",dt);
  fprintf(fp,"%f \t-dl\n",dl);
  if(pflag==0) fclose(fp);
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
  read(id,&msize,si);
  read(id,&xm,sf);
  read(id,&tsize,si);
  read(id,&dt,sf);
  read(id,&dl,sf);
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
  write(id,&msize,si);
  write(id,&xm,sf);
  write(id,&tsize,si);
  write(id,&dt,sf);
  write(id,&dl,sf);
}


