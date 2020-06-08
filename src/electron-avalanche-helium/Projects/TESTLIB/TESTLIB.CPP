#include<mylib.h>
#include<stdio.h>

void main()
{
  int i,j;

  TSingleArray sar;
  sar.Init(3);
  sar.Init(2);
  sar+=7.;
  sar*=7.;
  for(i=0;i<sar.Size();i++) sar[i]=i;
  for(i=0;i<sar.Size();i++) printf("\n %i %f",i,sar[i]);


  TDoubleArray dar;
  dar.Init(2,5);
  dar.Init(2,3);
  dar+=2.;
  dar*=3.;
  for(j=0;j<dar.YSize();j++)
  for(i=0;i<dar.XSize();i++)
  {
    dar[j][i]=j*1000.+i;
  }
  for(j=0;j<dar.YSize();j++)
  for(i=0;i<dar.XSize();i++)
  {
	 printf("\n %i %i %f",j,i,dar[j][i]);
  }

}

