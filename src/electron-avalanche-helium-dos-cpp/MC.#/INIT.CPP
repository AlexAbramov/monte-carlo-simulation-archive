#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<param.h>
const int narg=2;
char * varg[narg];
int main(int narg,char * varg[])
{
  system("..\\edit.com ..\\dat\\init.dat");
  fscan_par("..\\dat\\init.dat");
  printf("\n Инициализация параметров:");
  print_par();

  int i;
  double f;
  int ik=int(dk*double(imax)/dd);

  for(i=0;i<=imax;i++) xx[i]=i*dd/imax;
  if(voltage>0. && ik>0 && ik<=imax)
  {
    dk=double(ik)*dd/double(imax);
    double f0=2.*voltage/dk-field;
    printf("\n\n ik=%i  dk=%f  f0=%f\n",ik,dk,f0);
    double rf=(f0-field)/double(ik);
    if(voltage<field*dk){ printf("\n\a\a Error: voltage < field*dk");exit(-1);}
    for(i=0;i<ik;i++)
    {
      ff[i]=f0-double(i)*rf;
    }
    for(i=ik;i<=imax;i++)
    {
      ff[i]=field;
    }
  }
  else  for(i=0;i<=imax;i++) ff[i]=field;
  for(i=0;i<imax;i++) { de[i]=.5*(ff[i]+ff[i+1])*(xx[i+1]-xx[i]);}
  de[imax]=0.;
  printf("\n %i %f %f",imax,de[imax],mm[imax]);
  print_param();
  FILE* fp=fopen(file_param,"w");
  fclose(fp);
  write_param();
  return 0;
}