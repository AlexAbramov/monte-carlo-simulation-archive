#include<conio.h>
#include<mygraph.h>
int main()
{
  initgraph();
  TBox Box("..\\gdat\\box.dat");
  TGraph Graph("..\\gdat\\graph.dat");
  const int imax=100;
  float xx[imax+1];
  float yy[imax+1];
  for(int i=0;i<=imax;i++)
  { 
    float x=float(i);
    xx[i]=x;
    yy[i]=(1.+x)/(10.+2.2*x);
  }
  Box.show();
  Graph.show(imax,xx,yy,"x","y");
  getch();  
  cleardevice();
  return 0;
}
