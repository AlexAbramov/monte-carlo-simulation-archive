// Abramov A.
// Normal distribution function and mean parameters

#include<conio.h>
#include<stdio.h>
#include<mygraph.h>
#include<math.h>
#include<se.h>

float raspred(float e, float esr) // normal distribution, esr - mean energy
{
  float d=(esr+esr)/3.;// dispersion
  return 2.*sqrt(e/(3.1415*d*d*d))*exp(-e/d);
}

int main()
{
  alloc_se();
  read_se();
  int i;
  FILE * fp=fopen("data","r");
    int imax;// maximum index for arrays
    float esr;// mean energy for normal distribution
    float koef;// koefficient: energy=index*koef
    fscanf(fp,"%i%f%f",&imax,&esr,&koef);  
    float * xx=new float[imax+1];
    float * yy=new float[imax+1];
  fclose(fp);


  float sum=0.;// integral f(e) de ( must be =1. )
  float enr=0.;// energy
  float vel=0.;// velosity
  float stot=0.; // total sequation
  float sel=0.; // elastic sequation
  float sex=0.; // excited sequation
  float sion=0.; // ionising sequation
  float ftot=0.; // total frequance
  float fel=0.; // elastic frequance
  float fex=0.; // excited frequance
  float fion=0.; // ionising frequance
  for(i=0;i<=imax;i++) 
  {
    float e=i*koef;
    float f=raspred(e,esr);
    xx[i]=e;
    yy[i]=f;

    sum+=f;
    enr+=e*f;
    vel+=sqrt(e)*f;
    stot+=stotf(e)*f;
    sel+=selasf(e)*stotf(e)*f;
    ftot+=ftotf(e)*f;
    fel+=selasf(e)*ftotf(e)*f;
    if(e>pex)
    {
      sex+=sexf(e)*stotf(e)*f;
      fex+=sexf(e)*ftotf(e)*f;      
    }
    if(e>pion)
    {
      sion+=sionf(e)*stotf(e)*f;
      fion+=sionf(e)*ftotf(e)*f;
    }
  }

  sum*=koef;
  enr*=koef;
  vel*=koef*kk;
  stot*=koef;
  sel*=koef;
  sex*=koef;
  sion*=koef;
  ftot*=koef;
  fel*=koef;
  fex*=koef;
  fion*=koef;

  printf("\n Error=%.3f ",fabs(1.-sum));
  printf("\n enr=%.3f [eV]",enr);
  printf("\n vel=%.3f [sm/mksec]",vel);
  printf("\n stot=%.3f [1/sm]",stot);
  printf("\n sel=%.3f [1/sm]",sel);
  printf("\n sex=%.3f [1/sm]",sex);
  printf("\n sion=%.3f [1/sm]",sion);
  printf("\n ftot=%.3f [MHz]",ftot);
  printf("\n fel=%.3f [MHz]",fel);
  printf("\n fex=%.3f [MHz]",fex);
  printf("\n fion=%.3f [MHz]",fion);
  getch();

  initgraph();
  TBox box("..\\gdat\\box.dat");  
  TGraph graph("..\\gdat\\graph.dat");
  box.show();

  graph.show(imax,xx,yy,"e [eV]","f");
  getch();
  closegraph();
  return 0;
}