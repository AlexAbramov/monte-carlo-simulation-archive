#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<se.h>
#include<param.h>
#include<rnd.h>
#include<timer.h>
extern void lav1();
extern int ik;
const int narg=2;
char * varg[narg];
int main(int narg,char* varg[])
{
  const float fftime=30.;
  alloc_se();
  read_se();
  strcpy(file_param,varg[1]);
  read_param();
  read_rnd();
  printf("\n Программа расчета параметров электронных лавин методом Монте-Карло. \n\n");
  print_par();
  istat=vvx[imax];

  ik=nstat;
  float ftime0=ftime; 
  start_timer();
  while(ftime<fftime)
  {
    ilav++;
    printf("\r ilav=%li  istat=%li  ",ilav,istat);
    lav1();
    ftime=ftime0+stop_timer();
    istat=vvx[imax];
    
    if(kbhit()!=0)
    {
      int kl=getch();
      if(kl==27) break;
      if(kl==0) getch();
    }
  }
  printf("\n ftime=%f",ftime);

  write_param();
  write_rnd();
  dealloc_se();
  return 0;
}