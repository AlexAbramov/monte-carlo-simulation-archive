#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<mygraph.h>
#include<param.h>
const int narg=2;
char* varg[2];
int main(int narg,char* varg[])
{
  float yymax;
  FILE * fp=fopen("yymax","r");
    fscanf(fp,"%f",&yymax);
  fclose(fp);
  int i;
  strcpy(file_param,varg[1]);
  read_param();
  print_par();
  int i1=imax*3/5;
  int i2=imax*4/5;
  int ii=i2-i1+1;
  double ddx;
  double vdr=0.;
  double esr=0.;
  double fexsr=0.;
  double evxsr=0.;
  double fion=0.;
  double alfa=0.;
  double nn=0.;
  for(i=0;i<=imax;i++)nn+=vvx[i];
  for(i=i1;i<=i2;i++)
  { 
    vdr+=vvd[i]/mm[i]; 
    esr+=eee[i]/mm[i]; 
    fion+=fio[i]/mm[i]; 
    fexsr+=fex[i]/mm[i]; 
    evxsr+=evx[i]/mm[i]; 
    alfa+=fio[i]/vvd[i];
  }
  ddx=(evx[i2]/vvd[i2]-evx[i1]/vvd[i1])*(imax-1)/(dd*ii);
  vdr=vdr/ii;
  esr=esr/ii;
  fion=fion/ii;
  fexsr=fexsr/ii;
  evxsr=evxsr/ii;
  alfa=alfa/ii;
  printf("\n nsum=%.3f",nn); 
  printf("\n vdr=%.3f",vdr); 
  printf("\n esr=%.3f",esr); 
  printf("\n fio=%.3f",fion); 
  printf("\n fex=%.3f",fexsr); 
  printf("\n evx=%.3f",evxsr); 
  printf("\n ddx=%.3f",ddx); 
  printf("\n alfa=%.3f",alfa); 
  if(getch()==27) return 0;
  
  initgraph();
  TBox box("..\\gdat\\box.dat");  
  TMenu menu("..\\gdat\\menuvis.dat");
  TGraph graph("..\\gdat\\graph.dat");
  box.show();

  float * xxx=new float[imax+1];
  float * yy=new float[imax+1];
  for(i=0;i<=imax;i++) xxx[i]=xx[i];
  char textx[10]="x";
  char texty[10];
  texty[49]=0;

  int cont=1;
  while(cont)
  {
/*
    switch( menu.show() )
    {
      case 1:
	for(i=0;i<=imax;i++) xxx[i]=xx[i];
	strcpy(textx,"x");
        break;
      case 2:
	for(i=0;i<=imax;i++) xxx[i]=ff[i];
	strcpy(textx,"E");
        break;
      case 3:
	for(i=0;i<=imax;i++) xxx[i]=de[i];
	strcpy(textx,"de");
        break;
      case 4:
	for(i=0;i<=imax;i++) xxx[i]=mm[i];
	strcpy(textx,"mm");
        break;
      case 5:
	for(i=0;i<=imax;i++) xxx[i]=vvx[i]/mm[i];
	strcpy(textx,"vx");
	break;
      case 6:
	for(i=0;i<=imax;i++) xxx[i]=vvd[i]/mm[i];
	strcpy(textx,"vd");
        break;
      case 7:
	for(i=0;i<=imax;i++) xxx[i]=vvr[i]/mm[i];
	strcpy(textx,"vr");
        break;
      case 8:
	for(i=0;i<=imax;i++) xxx[i]=vvv[i]/mm[i];
	strcpy(textx,"v");
        break;
      case 9:
	for(i=0;i<=imax;i++) xxx[i]=eex[i]/mm[i];
	strcpy(textx,"ex");
        break;
      case 10:
	for(i=0;i<=imax;i++) xxx[i]=eer[i]/mm[i];
	strcpy(textx,"er");
        break;
      case 11:
	for(i=0;i<=imax;i++) xxx[i]=eee[i]/mm[i];
	strcpy(textx,"e");
        break;
      case 12:
	for(i=0;i<=imax;i++) xxx[i]=evx[i]/mm[i];
	strcpy(textx,"<e*vx>");
        break;
      case 13:
	for(i=0;i<=imax;i++) xxx[i]=fto[i]/mm[i];
	strcpy(textx,"ftot");
        break;
      case 14:
	for(i=0;i<=imax;i++) xxx[i]=fel[i]/mm[i];
	strcpy(textx,"felas");
        break;
      case 15:
	for(i=0;i<=imax;i++) xxx[i]=fex[i]/mm[i];
	strcpy(textx,"fex");
        break;
      case 16:
	for(i=0;i<=imax;i++) xxx[i]=fio[i]/mm[i];
	strcpy(textx,"fion");
        break;
      case 17:
	for(i=0;i<=imax;i++) xxx[i]=fio[i]/vvd[i];
	strcpy(textx,"alfa");
        break;
      default:
        cont=0;
    }//end switch
*/
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
	for(i=0;i<=imax;i++) yy[i]=fio[i]*mm[i]/eee[i]/eee[i];
	strcpy(texty,"fion");
        break;
      case 17:
//	for(i=0;i<=imax;i++) yy[i]=fio[i]/vvd[i];
	for(i=0;i<=imax;i++) yy[i]=fio[i]*mm[i]/vvd[i]/eee[i];
	strcpy(texty,"alfa");
        break;
      default:
        cont=0;
    }//end switch
    if(cont) 
    {
      graph.show(imax,xxx,yy,textx,texty);
//	for(i=0;i<imax;i++)if(yy[i]>yymax)yy[i]=yymax;
//      graph.show(imax,xxx,yy,"","");
/*
  	strcpy(file_param,"030.x5");
  	read_param();
	for(i=0;i<=imax;i++) yy[i]=eee[i]/mm[i];
      	graph.show(yy,0);
*/
      	if(getch()==27)break;
    }
    
  }//end while

  closegraph();
  delete yy;
  return 0;
}
