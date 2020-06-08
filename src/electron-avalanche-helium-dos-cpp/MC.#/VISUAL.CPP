#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<mygraph.h>
#include<param.h>
#include<se.h>
const int narg=2;
char* varg[2];
int main(int narg,char* varg[])
{
  int i;
  strcpy(file_param,varg[1]);
  read_param();
  float * xxx=new float[imax+1];
  float * yy=new float[imax+1];
  float * yyy=new float[imax+1];
  float rdx=.5*imax/dd;

  float kf,kf2;
  int cl1,cl2,cl3,cl4;
  FILE * fp=fopen("data","r");
    fscanf(fp,"%f%f",&kf,&kf2);
    fscanf(fp,"%i%i%i%i",&cl1,&cl2,&cl3,&cl4);
  fclose(fp);

  initgraph();
  TBox box("..\\gdat\\box.dat");  
  box.show();
//  TMenu menu("..\\gdat\\menuvis.dat");
  TGraph graph("..\\gdat\\graph.dat");

  while(1)
  {
    for(i=0;i<=imax;i++) xxx[i]=xx[i];
    for(i=0;i<=imax;i++) yy[i]=ff[i]*vvd[i]/mm[i];
    graph.show(imax,xxx,yy,"x,sm","Power");
    for(i=1;i<imax;i++) yyy[i]=rdx*(evx[i+1]/vvd[i+1]-evx[i-1]/vvd[i-1])*vvd[i]/mm[i]; 
    yyy[0]=yyy[1]; yyy[imax]=yyy[imax-1];
    graph.show(yyy,cl1);
    for(i=0;i<=imax;i++) yyy[i]=fex[i]*pex/mm[i]; 
    graph.show(yyy,cl2);
    for(i=0;i<=imax;i++) yyy[i]=fio[i]*pion/mm[i]; 
    graph.show(yyy,cl3);
    for(i=0;i<=imax;i++) yyy[i]=fio[i]*evx[i]/vvd[i]/mm[i];
    graph.show(yyy,cl4);
    if(getch()==27)break;
/*
    for(i=0;i<=imax;i++) yyy[i]=kf;
    graph.show(imax,xxx,yyy,"x,sm","Power");
    for(i=1;i<imax;i++) yyy[i]=rdx*(evx[i+1]/vvd[i+1]-evx[i-1]/vvd[i-1])*vvd[i]/mm[i]/yy[i]; 
    yyy[0]=yyy[1]; yyy[imax]=yyy[imax-1];
    graph.show(yyy,cl1);
    for(i=0;i<=imax;i++) yyy[i]=fex[i]*pex/mm[i]/yy[i];  
    graph.show(yyy,cl2);
    for(i=0;i<=imax;i++) yyy[i]=fio[i]*pion/mm[i]/yy[i]; 
    graph.show(yyy,cl3);
    for(i=0;i<=imax;i++) yyy[i]=fio[i]*evx[i]/vvd[i]/mm[i]/yy[i]; 
    graph.show(yyy,cl4);
    if(getch()==27)break;
*/
    for(i=0;i<=imax;i++) yyy[i]=kf2;
    graph.show(imax,xxx,yyy,"x,sm","Power");
    for(i=1;i<imax;i++) yy[i]=rdx*(evx[i+1]/vvd[i+1]-evx[i-1]/vvd[i-1])*vvd[i]/mm[i];
    yy[0]=yyy[1]; yy[imax]=yyy[imax-1];
    for(i=0;i<=imax;i++) yy[i]=ff[i]*vvd[i]/mm[i]-yy[i];
    for(i=0;i<=imax;i++) yyy[i]=fex[i]*pex/mm[i]/yy[i];  
    graph.show(yyy,cl2);
    for(i=0;i<=imax;i++) yyy[i]=fio[i]*pion/mm[i]/yy[i]; 
    graph.show(yyy,cl3);
    for(i=0;i<=imax;i++) yyy[i]=fio[i]*evx[i]/vvd[i]/mm[i]/yy[i]; 
    graph.show(yyy,cl4);
    if(getch()==27)break;
  }//end while

  closegraph();
  return 0;
}
