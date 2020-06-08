#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<rnd.h>
int main()
{
  const double cnst=sqrt(M_PI*.5);
  printf("\n\n");
  read_rnd();
  long int n=0;
  double xsr=0.,xsred=0.;
  while(kbhit()==0)
  {
    double  dx, s=0., x=0., r=-log(rnd(1));
    xsred=xsred+sqrt(2.*r);
    int  normal=1, cont=1;
    while(cont)
    {
      if(normal==1) 
      { 
        x=x+1.;
        s=s+x;
      }
      else
      {
        x=x+dx;
        s=s+dx*x;
        normal=1;
      }
      if(s>r)
      {
        dx=(s-r)/x;
        if(dx>1.) printf("Error: dx>1.");
        if(rnd(2)*x>dx) cont=0;
        else
        {
          normal=0;
          r=-log(rnd(3));
          s=0.;
        }
        x=x-dx;
      }
    }
    xsr=xsr+x;
    n++;
    if(n%1000==0)printf("\n n=%li    xsr=%f",n,fabs(xsr/n-cnst));
    if(n%1000==0)printf("\n n=%li  xsred=%f\n",n,fabs(xsred/n-cnst));
  }
  return 0;
}