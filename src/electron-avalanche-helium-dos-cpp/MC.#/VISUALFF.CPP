#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mygraph.h>
#include<paramff.h>
const int narg=2;
char* varg[2];
int main(int narg,char* varg[])
{
  double rmm;
  int nseq;
  int i,j,status_fre=0;
  strcpy(file_param,varg[1]);
  read_param();
  print_par();
  int i1=2*imax/5;
  int i2=4*imax/5;
  int ii=i2-i1+1;
  double ener=0.;
  double vdr=0.;
  double esr=0.;
  double fexsr=0.;
  double evxsr=0.;
  double fion=0.;
  double alfa=0.;
  for(i=i1;i<=i2;i++)
  { 
    rmm=1./mm[i];
    ener+=eer[i]*rmm;
    vdr+=vvd[i]*rmm; 
    esr+=eee[i]*rmm; 
    fion+=fio[i]*rmm; 
    fexsr+=fex[i]*rmm; 
    evxsr+=evx[i]*rmm; 
    alfa+=fio[i]/vvd[i];
  }
  double ddx=(evx[i2]/vvd[i2]-evx[i1]/vvd[i1])*(imax-1)/(dd*ii);
  double rii=1./double(ii);
  ener*=rii;
  vdr*=rii;
  esr*=rii;
  fion*=rii;
  fexsr*=rii;
  evxsr*=rii;
  alfa*=rii;
  printf("\n vdr=%.3f",vdr); 
  printf("\n esr=%.3f",esr); 
  printf("\n ee=%.3f",ener); 
  printf("\n err=%.4f",esr*esr*5./(3.*ener)-1.); 
  printf("\n fio=%.3f",fion); 
  printf("\n fex=%.3f",fexsr); 
  printf("\n evx=%.3f",evxsr); 
  printf("\n ddx=%.3f",ddx); 
  printf("\n alfa=%.3f",alfa); 
/*
  printf("\n\n");
  const int isequ=18;
  for(i=0;i<2*frem-1;i++)  
  for(j=0;j<frem;j++)
  printf("\n %i %f",i,fre[isequ*fremax+i*frem+j]);  
  if(getch()==27) return 0;
*/  
  initgraph();
  TBox box("..\\gdat\\box.dat");  
  TMenu menu("..\\gdat\\menuvff.dat");
  TDialog dialog("..\\gdat\\dialogn.dat");
  TDialog dialogf("..\\gdat\\dialogf.dat");
  TGraph graph("..\\gdat\\graph.dat");
  box.show();

  float * xxx=new float[imax+1];
  float * yy=new float[imax+1];
  for(i=0;i<=imax;i++) xxx[i]=xx[i];
  char textx[]="x,[sm]";
  char texty[50];
  texty[49]=0;

  int cont=1;

  while(1)
  {
    switch( menu.show() )
    {
      case 1:
	for(i=0;i<=imax;i++) yy[i]=vvx[i];
	strcpy(texty,"n");
        break;
      case 2:
	for(i=0;i<=imax;i++) yy[i]=ff[i];
	strcpy(texty,"E");
        break;
      case 3:
	for(i=0;i<=imax;i++) yy[i]=de[i];
	strcpy(texty,"de");
        break;
      case 4:
	for(i=0;i<=imax;i++) yy[i]=mm[i];
	strcpy(texty,"mm");
        break;
      case 5:
	for(i=0;i<=imax;i++) yy[i]=vvx[i]/mm[i];
	strcpy(texty,"vx");
	break;
      case 6:
	for(i=0;i<=imax;i++) yy[i]=vvd[i]/mm[i];
	strcpy(texty,"vd");
        break;
      case 7:
	for(i=0;i<=imax;i++) yy[i]=vvr[i]/mm[i];
	strcpy(texty,"vr");
        break;
      case 8:
	for(i=0;i<=imax;i++) yy[i]=vvv[i]/mm[i];
	strcpy(texty,"v");
        break;
      case 9:
	for(i=0;i<=imax;i++) yy[i]=eex[i]/mm[i];
	strcpy(texty,"ex");
        break;
      case 10:
	for(i=0;i<=imax;i++) yy[i]=eer[i]/mm[i];
	strcpy(texty,"er");
        break;
      case 11:
	for(i=0;i<=imax;i++) yy[i]=eee[i]/mm[i];
	strcpy(texty,"e");
        break;
      case 12:
	for(i=0;i<=imax;i++) yy[i]=evx[i]/mm[i];
	strcpy(texty,"<e*vx>");
        break;
      case 13:
	for(i=0;i<=imax;i++) yy[i]=fto[i]/mm[i];
	strcpy(texty,"ftot");
        break;
      case 14:
	for(i=0;i<=imax;i++) yy[i]=fel[i]/mm[i];
	strcpy(texty,"felas");
        break;
      case 15:
	for(i=0;i<=imax;i++) yy[i]=fex[i]/mm[i];
	strcpy(texty,"fex");
        break;
      case 16:
	for(i=0;i<=imax;i++) yy[i]=fio[i]/mm[i];
	strcpy(texty,"fion");
        break;
      case 17:
	for(i=0;i<=imax;i++) yy[i]=fio[i]/vvd[i];
	strcpy(texty,"alfa");
        break;
      case 18:
	double ss,sss;
	int index;

	int iseq=atoi(dialog.show());
	printf("\n iseq=%i",iseq);
	index=iseq*fremax;
	ss=0.;
	sss=0.;
 	rmm=1./mm[iseq];
	for(i=0;i<2*frem-1;i++)
	for(j=0;j<frem;j++)
	{ 
	  double f=fre[index+i*frem+j]*rmm;
	  double r=float(j); if(j==0) r=.25;
	  ss+=f;
	  if(f>.00001)sss-=f*log(f*.159/r);
	}
	printf("\n n=%.0f ss=%f sss=%f esr=%f",vvx[iseq],ss,sss,eee[iseq]*rmm);	
	getch();

	for(int is=0;is<=imax;is++)
	{
	  index=is*fremax;
	  sss=0.;
 	  rmm=1./mm[is];
	  for(i=0;i<2*frem-1;i++)
	  for(j=0;j<frem;j++)
	  { 
	    double f=fre[index+i*frem+j]*rmm;
	    double r=float(j); if(j==0) r=.25;
	    if(f>.00001)sss-=f*log(f*.159/r);
	  }
  	  yy[is]=sss;
	  printf("\n %i %f",is,sss);
	}	
	strcpy(texty,"S");
        break;
      default:
        cont=-1;      
      break; 
   }//end switch
    if(cont==1)graph.show(imax,xxx,yy,textx,texty);
    if(cont==-1)break;
    if(getch()==27)break;    
    cont=1;
  }//end while
  closegraph();
  return 0;
}