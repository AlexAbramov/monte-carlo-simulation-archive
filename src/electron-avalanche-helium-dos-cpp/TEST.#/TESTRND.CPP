#include<conio.h>
#include<rnd.h>
#include<mygraph.h>
int main()
{
  read_rnd();
  initgraph();
  int imax=getmaxx(),jmax=getmaxy();
  int *jj=new int[imax];
  for(int i=0;i<=imax;i++)jj[i]=0; 
  while(kbhit()==0)
  {
    i=rnd(0)*imax;
    jj[i]++;
    int j=jj[i];
    putpixel(i,j,j%8+8);      
  }   
  write_rnd(); 
  cleardevice();
  return 0;
}