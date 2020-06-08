#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<param.h>
const double pex=19.82,pion=24.58;
const int narg=2;
char* varg[2];
int main(int narg,char* varg[])
{
  strcpy(file_param,varg[1]);
  read_param();
  print_par();
  int i1=imax*3/5;
  int i2=imax*4/5;
  int ii=i2-i1+1;
  
  printf("\n %.3f %.3f %.3f",vvd[i1-1],vvd[i1],vvd[i1+1]);
  printf("\n %.3f",fio[i1]);

  printf("\n %.3f %.3f %.3f",vvd[i2-1],vvd[i2],vvd[i2+1]);
  printf("\n %.3f",fio[i2]);
  
  double p1,p2,p3,p4,p5;
  double dx=dd/imax;
  int i=(i1+i2)/2;
  double rm=1./mm[i],vdr=vvd[i]*rm;
  p1=vdr*(evx[i+1]/vvd[i+1]-evx[i-1]/vvd[i-1])*.5/dx;
  p2=fex[i]*rm*pex; 
  double fion=fio[i]*rm;
  p3=fion*pion; 
  p4=fion*evx[i]/vvd[i]; 
  p5=vdr*field; 
  printf("\n\n p1=%f",p1); 
  printf("\n p2=%f",p2); 
  printf("\n p3=%f",p3); 
  printf("\n p4=%f",p4);
  printf("\n p5=%f",p5);
  double psum=p1+p2+p3+p4;
  printf("\n\n psum=%.3f",psum);
  printf("\n psum/p5=%.3f",psum/p5);
  p1=0.;
  p2=0.;
  p3=0.;
  p4=0.;
  p5=0.;
  //getch();
  for(i=i1;i<=i2;i++)
  { 
    rm=1./mm[i];
    vdr=vvd[i]*rm;
    p1=p1+vdr*(evx[i+1]/vvd[i+1]-evx[i-1]/vvd[i-1]);
    p2=p2+fex[i]*rm; 
    fion=fio[i]*rm;
    p3=p3+fion; 
    p4=p4+fion*evx[i]/vvd[i]; 
    p5=p5+vdr; 
  }
  double rii=.593/ii;  
  p1*=.5/dx*rii;
  p2*=pex*rii;
  p3*=pion*rii;
  p4*=rii;
  p5*=field*rii;
  psum=p1+p2+p3+p4;
  printf("\n\n p1=%.3f  %.3f",p1,p1/p5); 
  printf("\n p2=%.3f  %.3f",p2,p2/p5); 
  printf("\n p3=%.3f  %.3f",p3,p3/p5); 
  printf("\n p4=%.3f  %.3f",p4,p4/p5);
  printf("\n p5=%.3f",p5);
  printf("\n\n psum=%.3f",psum);
  printf("\n psum/p5=%.3f",psum/p5);
  getch();
  return 0;
}
