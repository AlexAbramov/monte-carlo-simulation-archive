#include <pch.h>
#pragma hdrstop
#include <heselas.h>
#include <hesex.h>
#include <hesion.h>
#include <mylib.h>
#include <hese.h>
#include "create.h"

static float deaprox(float,float*,float=0.);
static float deaprox(float pot,float *ps,float r)
{
  float de=pot-int(pot);
  return r+(r-*ps)*de/(1.-de);
}

void create(TDC& dc)
{
  const float emaxg=100.;
  int imaxg=eton(emaxg);
  const float rnu=1./float(NU-1);
  float r,e;
  float * ps;
  int i,j;
  char textx[]="Energy, [eV]";
  TGraph graph;

  alloc_se();
  THeSelas heselas;
  THeSex hesex;
  THeSion hesion;
// ELASTIC
  for(i=0;i<=NEMAX;i++)
  {
	 selas[i]=heselas.Total(energy[i]);
  }
  graph.Show(dc,1+imaxg,energy,selas,textx,"Elastic sequation [A*A]");

  for(i=0;i<=NEMAX;i++)
  {
	 e=energy[i];
	 ps=spelas+i*NU;
	 *ps=0.;
	 for(j=1;j<NU-1;j++)
	 {
		r=float(j)*rnu;
		*(ps+j)=heselas.Angle(e,r);
	 }
	 *(ps+NU-1)=M_PI;
  }

// EXCITATION
  for(i=IPEX1;i<=NEMAX;i++)
  {
	 e=energy[i];
	 spex[NEXP*i+0]=hesex.Sequation(0,2,e);
	 spex[NEXP*i+1]=hesex.Sequation(1,2,e);
	 spex[NEXP*i+2]=hesex.Sequation(2,2,e);
	 spex[NEXP*i+3]=hesex.Sequation(3,2,e);
	 spex[NEXP*i+4]=hesex.Sequation(3,e);
	 spex[NEXP*i+5]=hesex.Sequation(4,e);
	 spex[NEXP*i+6]=hesex.Sequation(5,e);
  }

  for(i=IPEX1;i<=NEMAX;i++)
  {
	 sex[i]=0.;
	 for(j=0;j<NEXP;j++)sex[i]+=spex[NEXP*i+j];
  }
  message("Press any key");
  graph.Show(dc,1+imaxg-IPEX1,energy+IPEX1,sex+IPEX1,textx,"Excitation [A*A]");

// IONISATION
  for(i=IPION1;i<=NEMAX;i++)
  {
	 sion[i]=hesion.Total(energy[i]);
  }

  for(i=IPION1;i<=NEMAX;i++)
  {
	 e=energy[i];
	 ps=spion+i*NU;
	 *ps=0.;
	 for(j=1;j<NU-1;j++)
	 {
		r=float(j)*rnu*.5;
		*(ps+j)=hesion.Share(e,r);
	 }
	 *(ps+NU-1)=.5;
  }
  message("Press any key");
  graph.Show(dc,1+imaxg-IPION1,energy+IPION1,sion+IPION1,textx,"Ionisation [A*A]");

//  for(i=IPEX1;i<=NEMAX;i++)for(j=0;j<NEXP;j++)
//	 spex[i*NEXP+j]=spex[i*NEXP+j]/sex[i];

// BORDER EFFECTS
  ps=sion+IPION;
  *ps=deaprox(PION,ps+1);//i=IPION
  ps=spion+IPION*NU;
  for(j=0;j<NU;j++)//i=IPION
  {
	 *(ps+j)=*(ps+j+NU);
	 //r=float(j)*rnu;
	 //*(ps+j)=deaprox(PION,ps+j+NU,r);
  }
  ps=sex+IPEX;
  *ps=deaprox(PEX,ps+1);
  ps=spex+IPEX*NEXP;
  for(j=0;j<NEXP;j++) *(ps+j)=0.;
  *ps=deaprox(pexi(1),ps+NEXP,1.);

// WRITE TO DISK
  write_se();
  dealloc_se();
  message("He binary data file created");
}
