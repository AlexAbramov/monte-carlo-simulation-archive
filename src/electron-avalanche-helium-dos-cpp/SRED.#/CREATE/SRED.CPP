#include<string.h>
#include<conio.h>
#include<mygraph.h>
const int narg=2;
char* varg[narg];
int main(int narg,char* varg[])
{
  FILE * fp=fopen(varg[1],"r");
    int imax,jmax;
    fscanf(fp,"%i",&imax);
    fscanf(fp,"%i",&jmax);
//    printf("\n imax=%i jmax=%i\n\n",imax,jmax);
    int cmax=20;
    char * ss=new char[imax*cmax]; if(ss==0) return -1;
    for(int i=0; i<imax; i++) fscanf(fp,"%s",ss+cmax*i);
//    for(i=0; i<imax; i++) printf("%s",ss+cmax*i);
    float * ff=new float[imax*jmax]; if(ff==0) return -1;
    for(i=0; i<imax*jmax; i++) fscanf(fp,"%f",ff+i);
//    for(i=0; i<imax*jmax; i++) printf("%f ",ff[i]);
  fclose(fp);

  initgraph();
  TGraph Graph("..\\gdat\\graph.dat"); 
  float * xx=new float[jmax]; if(xx==0) return -1;
  float * yy=new float[jmax]; if(yy==0) return -1;
  int numx=0;
  for(i=0; i<jmax; i++) xx[i]=ff[numx+imax*i];

  int numy=imax-1;
  for(i=0; i<jmax; i++) yy[i]=ff[numy+imax*i];
//  Graph.show(jmax-1,xx,yy,ss+numx*cmax,ss+numy*cmax);
  Graph.show(jmax-1,xx,yy,"","");
  getch();

  for(numy=2; numy<imax-1; numy++)
  {
    for(i=0; i<jmax; i++) yy[i]=ff[numy+imax*i];
    Graph.show(yy,0);
    getch();
  }

  cleardevice();
  return 0;    
}