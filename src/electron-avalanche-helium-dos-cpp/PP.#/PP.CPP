#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<math.h>
#include<se.h>
#include<pparam.h>
#include<rnd.h>
#include<timer.h>
void circle();
const int narg=2;
char * varg[narg];
int main(int narg,char* varg[])
{
  const float fftime=30.;
  read_rnd();
  alloc_se();
  read_se();
  for(int i=0;i<=nemax;i++) stot[i]*=kk*sqrt(float(i));// Now stot is ftot [MHz]
  strcpy(file_param,varg[1]);
  read_param();
  printf("\n The Monte-Carlo researching. \n\n");
  print_par();
  float ftime0=ftime; 
  start_timer();
  while(ftime<fftime)
  {
    circle();
    nc++;
    printf("\r %li",nc);
    ftime=ftime0+stop_timer();
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