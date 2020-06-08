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
  nstat=ik;

  for(i=0;i<=imax;i++) xx[i]=i*dd/imax;
  if(voltage>0. && ik>0 && ik<=imax)
  {
    dk=double(ik)*dd/double(imax);
    double f0=2.*voltage/dk-field;
    printf("\n\n ik=%i  dk=%f  f0=%f\n",ik,dk,f0);
    double rf=(f0-field)/double(ik);
    for(i=0;i<=ik;i++)
    {
      ff[i]=f0-double(i)*rf;
    }
    for(i=ik+1;i<=imax;i++)
    {
      ff[i]=0.;
    }
    ff[ik]=.1;
  }
  else return -1;

  for(i=0;i<ik;i++) { de[i]=.5*(ff[i]+ff[i+1])*(xx[i+1]-xx[i]);}
  for(i=ik;i<=imax;i++) de[i]=0.;
  printf("\n %i %f",imax,de[imax]);
  print_param();
  FILE* fp=fopen(file_param,"w");
  fclose(fp);
  write_param();
  return 0;
}