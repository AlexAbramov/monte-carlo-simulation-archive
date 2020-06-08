#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<mygraph.h>
#include<pparam.h>
const int narg=2;
char* varg[2];
int main(int narg,char* varg[])
{
  int i;
  strcpy(file_param,varg[1]);
  read_param();
  print_par();
  double vdr=0.;
  double esr=0.;
  double fexsr=0.;
  double fion=0.;
  double alfa=0.;
  double rnc=1./nc;
  for(i=0;i<imax;i++)
  { 
    vdr+=vvd[i]*rnc; 
    esr+=eee[i]*rnc; 
    fion+=fio[i]*rnc; 
    fexsr+=fex[i]*rnc; 
//    alfa+=fio[i]/vvd[i];
  }
  vdr=vdr/imax;
  esr=esr/imax;
  fion=fion/imax;
  fexsr=fexsr/imax;
//  alfa=alfa/imax;
  printf("\n vdr=%.3f",vdr); 
  printf("\n esr=%.3f",esr); 
  printf("\n fio=%.3f",fion); 
  printf("\n fex=%.3f",fexsr); 
//  printf("\n alfa=%.3f",alfa); 
  if(getch()==27) return 0;
  
  initgraph();
  TBox box("..\\gdat\\box.dat");  
  TMenu menu("..\\gdat\\menuvpp.dat");
  TGraph graph("..\\gdat\\graph.dat");
  box.show();

  float * xxx=new float[imax+1];
  float * yyy=new float[imax+1];
  for(i=0;i<imax;i++) xxx[i]=xx[i];
  char textx[20]="x";
  char texty[20]="y";

  int cont=1;
  while(cont)
  {
    switch( menu.show() )
    {
      case 1:
	for(i=0;i<=imax;i++) xxx[i]=1.*i/imax;
	strcpy(textx,"faza");
        break;
      case 2:
	for(i=0;i<imax;i++) xxx[i]=xx[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"xx");
        break;
      case 3:
	for(i=0;i<imax;i++) xxx[i]=ff[i];
	xxx[imax]=xxx[0];
	strcpy(textx,"ff");
        break;
      case 4:
	for(i=0;i<imax;i++) xxx[i]=vvx[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"vx");
	break;
      case 5:
	for(i=0;i<imax;i++) xxx[i]=vvd[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"vd");
        break;
      case 6:
	for(i=0;i<imax;i++) xxx[i]=vvr[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"vr");
        break;
      case 7:
	for(i=0;i<imax;i++) xxx[i]=vvv[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"v");
        break;
      case 8:
	for(i=0;i<imax;i++) xxx[i]=eex[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"ex");
        break;
      case 9:
	for(i=0;i<imax;i++) xxx[i]=eer[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"er");
        break;
      case 10:
	for(i=0;i<imax;i++) xxx[i]=eee[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"e");
        break;
      case 11:
	for(i=0;i<imax;i++) xxx[i]=evx[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"evx");
        break;
      case 12:
	for(i=0;i<imax;i++) xxx[i]=fto[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"ftot");
        break;
      case 13:
	for(i=0;i<imax;i++) xxx[i]=fel[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"felas");
        break;
      case 14:
	for(i=0;i<imax;i++) xxx[i]=fex[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"fex");
        break;
      case 15:
	for(i=0;i<imax;i++) xxx[i]=fio[i]*rnc;
	xxx[imax]=xxx[0];
	strcpy(textx,"fion");
        break;
      case 16:
	for(i=0;i<imax;i++) xxx[i]=fio[i]/vvd[i];
	xxx[imax]=xxx[0];
	strcpy(textx,"alfa");
        break;
      default:
        cont=0;
    }//end switch
    switch( menu.show() )
    {
      case 1:
	for(i=0;i<=imax;i++) yyy[i]=1.*i/imax;
	strcpy(texty,"faza");
        break;
      case 2:
	for(i=0;i<imax;i++) yyy[i]=xx[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"xx");
        break;
      case 3:
	for(i=0;i<imax;i++) yyy[i]=ff[i];
	yyy[imax]=yyy[0];
	strcpy(texty,"ff");
        break;
      case 4:
	for(i=0;i<imax;i++) yyy[i]=vvx[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"vx");
	break;
      case 5:
	for(i=0;i<imax;i++) yyy[i]=vvd[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"vd");
        break;
      case 6:
	for(i=0;i<imax;i++) yyy[i]=vvr[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"vr");
        break;
      case 7:
	for(i=0;i<imax;i++) yyy[i]=vvv[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"v");
        break;
      case 8:
	for(i=0;i<imax;i++) yyy[i]=eex[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"ex");
        break;
      case 9:
	for(i=0;i<imax;i++) yyy[i]=eer[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"er");
        break;
      case 10:
	for(i=0;i<imax;i++) yyy[i]=eee[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"e");
        break;
      case 11:
	for(i=0;i<imax;i++) yyy[i]=evx[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"evx");
        break;
      case 12:
	for(i=0;i<imax;i++) yyy[i]=fto[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"ftot");
        break;
      case 13:
	for(i=0;i<imax;i++) yyy[i]=fel[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"felas");
        break;
      case 14:
	for(i=0;i<imax;i++) yyy[i]=fex[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"fex");
        break;
      case 15:
	for(i=0;i<imax;i++) yyy[i]=fio[i]*rnc;
	yyy[imax]=yyy[0];
	strcpy(texty,"fion");
        break;
      case 16:
	for(i=0;i<imax;i++) yyy[i]=fio[i]/vvd[i];
	yyy[imax]=yyy[0];
	strcpy(texty,"alfa");
        break;
      default:
        cont=0;
    }//end switch
    if(cont) 
    {
      graph.show(imax,xxx,yyy,textx,texty);
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
