#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<mygraph.h>
#include<pparam.h>
#include<math.h>
const int narg=2;
char* varg[2];
int main(int narg,char* varg[])
{
  int i;
  strcpy(file_param,varg[1]);
  read_param();
  print_par();
  double xsr=0.;
  double vdr=0.;
  double esr=0.;
  double ftosr=0.;
  double fexsr=0.;
  double fion=0.;
  double rnc=1./nc;
  for(i=0;i<imax;i++)
  { 
//    printf("\n%i\t%f\t%f",i,xx[i],vvd[i]);
    xsr+=xx[i]; 
    vdr+=vvd[i]; 
    esr+=eee[i]; 
    ftosr+=fto[i]; 
    fion+=fio[i]; 
    fexsr+=fex[i]; 
  }
  double kf=rnc/imax;
  xsr*=kf;
  vdr*=kf;
  esr*=kf;
  ftosr*=kf;
  fion*=kf;
  fexsr*=kf;
  printf("\n xsr=%.3f",xsr); 
  printf("\n vdr=%.3f",vdr); 
  printf("\n esr=%.3f",esr); 
  printf("\n ftot=%.3f",ftosr); 
  printf("\n fio=%.3f",fion); 
  printf("\n fex=%.3f",fexsr); 
//  printf("\n alfa=%.3f",alfa); 
  double ko=ftosr*conc/ww;
  double ddf=atan(ko);
  double ksr=1./sqrt(1.+ko*ko);
  printf("\n\n ko=%.3f",ko); 
  printf("\n ddf=%.1f [grad]",ddf*180./3.1415); 
  printf("\n k=%.2f",1./ksr); 

  if(getch()==27) return 0;
  
  initgraph();
  TBox box("..\\gdat\\box.dat");  
  TMenu menu1("..\\gdat\\menuvpp1.dat");
  TMenu menu2("..\\gdat\\menuvpp2.dat");
  TGraph graph("..\\gdat\\graph.dat");
  box.show();

  float * xxx=new float[imax+1];
  float * yyy=new float[imax+1];
  for(i=0;i<imax;i++) xxx[i]=xx[i];
  char textx[20]="x";
  char texty[20]="y";

  int cont=1;
  int m2;
  while(cont)
  {
    switch( menu1.show() )
    {
      case 1:
	for(i=0;i<=imax;i++) xxx[i]=360.*i/imax;
	strcpy(textx,"faza [grad]");
        break;
      case 2:
	for(i=0;i<imax;i++) xxx[i]=xx[i]*rnc-xsr;
	xxx[imax]=xxx[0];
	strcpy(textx,"xx [sm]");
        break;
      case 3:
	for(i=0;i<imax;i++) xxx[i]=ff[i];
	xxx[imax]=xxx[0];
	strcpy(textx,"ff [V/sm]");
        break;
      case 4:
	for(i=0;i<imax;i++) xxx[i]=vvx[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"vx [sqev]");
	break;
      case 5:
	for(i=0;i<imax;i++) xxx[i]=vvd[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"vd [sqev]");
        break;
      case 6:
	for(i=0;i<imax;i++) xxx[i]=vvr[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"vr [sqev]");
        break;
      case 7:
	for(i=0;i<imax;i++) xxx[i]=vvv[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"v [sqev]");
        break;
      case 8:
	for(i=0;i<imax;i++) xxx[i]=eex[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"ex [eV]");
        break;
      case 9:
	for(i=0;i<imax;i++) xxx[i]=eer[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"er [eV]");
        break;
      case 10:
	for(i=0;i<imax;i++) xxx[i]=eee[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"e [eV]");
        break;
      case 11:
	for(i=0;i<imax;i++) xxx[i]=evx[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"evx [eV*sqev]");
        break;
      case 12:
	for(i=0;i<imax;i++) xxx[i]=fto[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"ftot [MHz]");
        break;
      case 13:
	for(i=0;i<imax;i++) xxx[i]=fel[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"felas [MHz]");
        break;
      case 14:
	for(i=0;i<imax;i++) xxx[i]=fex[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"fex [MHz]");
        break;
      case 15:
	for(i=0;i<imax;i++) xxx[i]=fio[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"fion [MHz]");
        break;
      case 16:
	for(i=0;i<imax;i++) xxx[i]=fio[i]/vvd[i];
	xxx[imax]=xxx[0];
	strcpy(textx,"alfa [1/sm]");
        break;
      default:
        cont=0;
    }//end switch
    if(cont!=0)switch( m2=menu2.show() )
    {
      case 1:
	for(i=0;i<=imax;i++) yyy[i]=1.*i/imax;
	strcpy(texty,"faza [grad]");
        break;
      case 2:
	for(i=0;i<imax;i++) yyy[i]=xx[i]*rnc-xsr;
	yyy[imax]=yyy[0];
	strcpy(texty,"xx [sm]");
        break;
      case 3:
	for(i=0;i<imax;i++) yyy[i]=ff[i];
	yyy[imax]=yyy[0];
	strcpy(texty,"ff [V/sm]");
        break;
      case 4:
	for(i=0;i<imax;i++) yyy[i]=vvx[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"vx [sqev]");
	break;
      case 5:
	for(i=0;i<imax;i++) yyy[i]=vvd[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"vd [sqev]");
        break;
      case 6:
	for(i=0;i<imax;i++) yyy[i]=vvr[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"vr [sqev]");
        break;
      case 7:
	for(i=0;i<imax;i++) yyy[i]=vvv[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"v [sqev]");
        break;
      case 8:
	for(i=0;i<imax;i++) yyy[i]=eex[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"ex [eV]");
        break;
      case 9:
	for(i=0;i<imax;i++) yyy[i]=eer[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"er [eV]");
        break;
      case 10:
	for(i=0;i<imax;i++) yyy[i]=eee[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"e [eV]");
        break;
      case 11:
	for(i=0;i<imax;i++) yyy[i]=evx[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"evx [eV*sqev]");
        break;
      case 12:
	for(i=0;i<imax;i++) yyy[i]=fto[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"ftot [MHz]");
        break;
      case 13:
	for(i=0;i<imax;i++) yyy[i]=fel[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"felas [MHz]");
        break;
      case 14:
	for(i=0;i<imax;i++) yyy[i]=fex[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"fex [MHz]");
        break;
      case 15:
	for(i=0;i<imax;i++) yyy[i]=fio[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"fion [MHz]");
        break;
      case 16:
	for(i=0;i<imax;i++) yyy[i]=fio[i]/vvd[i];
	yyy[imax]=yyy[0];
	strcpy(texty,"alfa [1/sm]");
        break;
      default:
        cont=0;
    }//end switch
    if(cont) 
    {
        graph.show(imax,xxx,yyy,textx,texty);
	if(m2==2)
	{
  	  for(i=0;i<imax;i++) yyy[i]=aa*ksr*sin(6.283*i/imax+ddf);
  	  yyy[imax]=yyy[0];
          graph.show(yyy,4);
	}
	if(m2==5)
	{
  	  for(i=0;i<imax;i++) yyy[i]=uu*ksr*cos(6.283*i/imax+ddf);
  	  yyy[imax]=yyy[0];
          graph.show(yyy,4);
	}
      	if(getch()==27)break;
    }
  }//end while

  closegraph();
  delete xxx,yyy;
  return 0;
}
//  ddx=(evx[i2]/vvd[i2]-evx[i1]/vvd[i1])*(imax-1)/(dd*ii);
//	for(i=0;i<imax;i++)if(yyy[i]>yyymax)yyy[i]=yyymax;
//      graph.show(imax,xxx,yyy,"","");
/*
  	strcpy(file_param,"030.x5");
  	read_param();
	for(i=0;i<=imax;i++) yyy[i]=eee[i]*rnc;
      	graph.show(yyy,0);
*/
