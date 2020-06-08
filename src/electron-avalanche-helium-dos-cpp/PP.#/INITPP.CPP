#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<pparam.h>
#include<math.h>
const int narg=2;
char * varg[narg];
int main(int narg,char * varg[])
{
  system("..\\edit.com ..\\dat\\initpp.dat");
  fscan_par("..\\dat\\initpp.dat");
  printf("\n Инициализация параметров:");

  nc=0;
  ftime=0.;
  for(int i=0;i<imax;i++) ff[i]=f0*sin(M_PI*(i+i)/imax);

  ww=2*M_PI*fr; //10^6 Hz
  dt=1./fr/imax; //10^-6 sec
  df=2.*M_PI/imax;
  uu=29.65*f0/ww; //sqrt(eV)
  aa=kk*uu/ww; // sm

  x=0.;
  vx=0.;
  er=0.;
  ss=0.;
  sss=-log(.5)/conc;

  print_par();
  
  //print_param();
  FILE* fp=fopen(file_param,"w");
  fclose(fp);
  write_param();
  return 0;
}