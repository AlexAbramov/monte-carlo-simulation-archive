#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<se.h>
#include<param.h>
#include<rnd.h>
#include<timer.h>
#include<lav.h>
const float fftime=30.;
const int narg=2;
char * varg[narg];
int main(int narg,char* varg[])
{
  alloc_se();
  read_se();
  strcpy(file_param,varg[1]);
  read_param();
  read_rnd();
  //for(int i=0;i<=imax;i++)printf("\n %f",mm[i]);
  printf("\n Программа расчета параметров электронных лавин методом Монте-Карло. \n\n");
//  print_par();
  FILE * fpp=fopen("time","w");
  istat=vvx[imax];
  int i1=imax*2/5, i2=imax*4/5; double rii=1./double(i2-i1+1);

  float ftime0=ftime; 
  start_timer();
  while(ftime<fftime)
  {
    ilav++;
    printf("\r ilav=%li  istat=%li  ",ilav,istat);
    lav();
    ftime=ftime0+stop_timer();
    istat=vvx[imax];
    
    if(kbhit()!=0)
    {
      int kl=getch();
      if(kl==27) break;
      if(kl==0) getch();
    }
    {
//      if(kl==32)
//      if(ilav)
      {	
        double vdr=0.,esr=0.,alfa=0.,rmm;
        for( int i=i1; i<=i2; i++)
        { 
          rmm=mm[i];
          if(rmm>0.)
          {
            rmm=1./rmm;
            vdr+=vvd[i]*rmm;
            esr+=eee[i]*rmm;
            alfa+=fio[i]/vvd[i];
          }
        }
        vdr*=rii;esr*=rii;alfa*=rii;
//        printf("\n vdr=%.3f  esr=%.3f  alfa=%.3f \n",vdr,esr,alfa);
        fprintf(fpp,"\n%li\t%.3f\t%.3f\t%.3f",ilav,vdr,esr,alfa);
      }
    }
  }
  printf("\n ftime=%f",ftime);
  fclose(fpp);  
  write_param();
  write_rnd();
  dealloc_se();
  return 0;
}
