#include<conio.h>
#include<stdio.h>
#include<mygraph.h>
const int narg=2;
char* varg[2];
int main(int narg,char* varg[])
{
  FILE * fp=fopen(varg[1],"r");
    int imax,jmax;
    fscanf(fp,"%i%i",&imax,&jmax);  
    //printf("\n %i %i",imax,jmax);
    const int ichar=10;
    char * name=new char[imax*ichar];
    float * xx=new float[jmax];
    float * yy=new float[jmax];
    float * ff=new float[imax*jmax];
    for( int i=0; i<imax; i++)
    { 
      fscanf(fp,"%s",name+i*ichar); 
      //printf("\n %s",name+i*ichar); 
    }
    for( int j=0; j<jmax; j++)for( i=0; i<imax; i++) 
    { 
      fscanf(fp,"%f",ff+j*imax+i); 
      //printf(" %f",*(ff+j*imax+i)); 
    }  
  fclose(fp);
  //getch();
  initgraph();
  TBox box("..\\gdat\\box.dat");  
  TMenu menu("..\\gdat\\menuvt.dat");
  TGraph graph("..\\gdat\\graph.dat");
  box.show();

  while(1)
  {
    int i1=menu.show();
    if( 0<=i1 && i1<imax)
    {
      int i2=0;//menu2.show()-1;
      if( 0<=i2 && i2<imax)
      {
        for( int j=0; j<jmax; j++)
        {
          xx[j]=ff[j*imax+i2];
          yy[j]=ff[j*imax+i1];
        } 
        graph.show(jmax-1,xx,yy,name+i2*ichar,name+i1*ichar);
        if(getch()==27) break;
      }
      else break;
    }
    else break;
  }
  closegraph();
  return 0;
}