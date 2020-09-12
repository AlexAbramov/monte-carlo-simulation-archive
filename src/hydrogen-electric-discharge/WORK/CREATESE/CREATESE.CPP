#include <math.h>
#include <stdio.h>
#include <conio.h>
#pragma hdrstop
#include <mylib.h>
#include <hse.h>
#include <hselas.h>

static float deaprox(float,float*,float=0.);
static float deaprox(float pot,float *ps,float r)
{
  float de=pot-int(pot);
  return r+(r-*ps)*de/(1.-de);
}

int main()
{
  const float rnu=1./float(NU-1);
  float r,e;
  float * ps;
  int i,j;
  alloc_se();
// ELASTIC
  for(i=0;i<=NEMAX;i++)
  {
	 e=energy[i];
	 ps=spelas+i*NU;
	 *ps=0.;
	 for(j=1;j<NU-1;j++)
	 {
		r=float(j)*rnu;
		*(ps+j)=Angle(e,r);
	 }
	 *(ps+NU-1)=M_PI;
  }

// WRITE TO DISK
  write_se();
  dealloc_se();
  printf("\n Hydrogen binary data file is created");
  printf("\n Press any key to exit");
  getch();
}
