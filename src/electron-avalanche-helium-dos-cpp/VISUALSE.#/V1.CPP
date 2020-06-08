//	ВИЗУАЛИЗАЦИЯ ВХОДНЫХ ФУНКЦИЙ СЕЧЕНИЙ
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<selas.h>
#include<sex.h>
#include<sion.h>
#include<mygraph.h>
#include<newline.hpp>
#define ipex1 20
#define ipion1 25
#define imax 1000
const int nu=100;
const float rnu=1./nu;
int main()
{
  int imaxg,kit;
  int i,n,t,n0,n1,t0,t1;
  float x,y,e;
  static float pp[33];for(i=0;i<33;i++)pp[i]=-1.;	
  static float xx[imax+1];	
  static float yy[imax+1];
  static float yy1[imax+1];
  static float yy2[imax+1];
  static float yys[imax+1];
  //system("..\\edit ..\\dat\\visual.dat");
  FILE * fp=fopen("..\\dat\\visual.dat","r");
    fscanf(fp,"%i",&imaxg);newline(fp);
    fscanf(fp,"%i",&kit);newline(fp);
    fscanf(fp,"%i",&n0);newline(fp);
    fscanf(fp,"%i",&n1);newline(fp);
    fscanf(fp,"%i",&t0);newline(fp);
    fscanf(fp,"%i",&t1);
  fclose(fp);
  //printf("\n imaxg=%i",imaxg);
  //printf("\n n0=%i",n0);
  //printf("\n n1=%i",n1);
  //printf("\n t0=%i",t0);
  //printf("\n t1=%i",t1);
  if(imaxg>imax)imaxg=imax;
  if(n0<2)n0=2;
  if(n1<n0)n1=n0;
  if(t0<0)t0=0;
  if(t1>=ntl||t1<t0)t1=ntl-1;
  char textx[]="Энергия,[eV]";
  char texty[50];
  //getch();
  
  initgraph();
  TBox box("..\\gdat\\box.dat");  
  TMenu menu("..\\gdat\\menu.dat");
  TGraph graph("..\\gdat\\graph.dat");
  TDialog dialog("..\\gdat\\dialog.dat");
  TDialog dialog1("..\\gdat\\dialog1.dat");
  box.show();
  int cont=1;

  while(cont)
  {
    switch( menu.show() )
    {
      case 1:
        for(i=0;i<=imaxg;i++)
        { 
          e=float(i);
          xx[i]=e;
          yy[i]=selasfn(e);
	}
        graph.show(imaxg,xx,yy,textx,"Упругое сечение");
	break;
      case 2:
        for(i=ipex1;i<=imaxg;i++)
        { 
          e=float(i);
          xx[i]=e;
          y=0.;
          for(n=n0;n<=n1;n++)
          {
            for(t=t0;t<=t1;t++)
            { 
              if(n>=tmin[t])
 	        y=y+tse[t](n,e);
            }
          }
          yy[i]=y;
	}
        graph.show(imaxg-ipex1,xx+ipex1,yy+ipex1,textx,"Сечение возбуждения");
        break;
      case 3:
        for(i=ipion1;i<=imaxg;i++)
        { 
          e=float(i);
          xx[i]=e;
          yy[i]=sionfn(e);
	}
        graph.show(imaxg-ipion1,xx+ipion1,yy+ipion1,textx,"Сечение ионизации");
	break;
      case 4:
        e=atof(dialog.show());
        for(i=0;i<=nu;i++)
        {
          x=pi*i*rnu;
	  xx[i]=x;
          yy[i]=spelasd(e,x);
        }
        graph.show(nu,xx,yy,"Угол рассеяния,[рад]","Плотность вероятности рассеяния");
	getch();
        for(i=0;i<=nu;i++)
        {
          x=pi*float(i)*rnu;
	  xx[i]=x;
          yy[i]=.5*(1.-cos(x));
          yy1[i]=spelaspl(e,x);
          yy2[i]=spelasp(e,x);
        }
        graph.show(nu,xx,yy,"Угол рассеяния,[rad]","Вероятность рассеяния");
        graph.show(yy1,1);
        graph.show(yy2,2);
	getch();
        for(i=0;i<=nu;i++)
        {
          x=float(i)*rnu;
	  xx[i]=x;
          yy[i]=acos(1.-x-x);
          yy1[i]=spelasrl(kit,e,x);
          yy2[i]=spelasr(kit,e,x);
        }
        graph.show(nu,xx,yy,"Вероятность рассеяния","Угол рассеяния,[rad]");
        graph.show(yy1,1);
        graph.show(yy2,2);
	break;
      case 5:
        n=atoi(dialog1.show());
        if(n<2)break;
        for(i=0;i<=imaxg;i++)yys[i]=0.;
        for(t=0;t<ntl;t++)if( n>=tmin[t] )
        {
          for(i=ipex1;i<=imaxg;i++)
          { 
            e=float(i);
            xx[i]=e;
 	    y=tse[t](n,e);
 	    yy[i]=y;
 	    yys[i]=yys[i]+y;
	  }
          sprintf(texty,"Номер уровня - %2i, тип уровня - %2i",n,t);
          graph.show(imaxg-ipex1,xx+ipex1,yy+ipex1,textx,texty);
          getch();
        }
        sprintf(texty,"Номер уровня - %2i",n);
        graph.show(imaxg-ipex1,xx+ipex1,yys+ipex1,textx,texty);
        getch();
        break;
      case 6:
	e=atof(dialog.show());
        for(i=0;i<=nu;i++)
        {
          x=float(i)*rnu;
          xx[i]=x;
          yy[i]=spiond(e,x);
        }
        graph.show(nu,xx,yy,"Доля энергии","Дифференциальное сечение ионизации.");
	getch();
        for(i=0;i<=nu;i++)
        {
          x=float(i)*rnu;
          xx[i]=x;
          yy[i]=spionp(e,x);
        }
        graph.show(nu,xx,yy,"Доля энергии","Вероятность");
	getch();
        for(i=0;i<=nu;i++)
        {
          x=float(i)*rnu;
          xx[i]=x;
          yy[i]=spionr(kit,e,x);
        }
        graph.show(nu,xx,yy,"Вероятность","Доля энергии");
	break;
      case 7:
        e=atof(dialog.show());
        imaxg=int(e);
        if(imaxg<ipion1)imaxg=ipion1;
        if(imaxg>imax)imaxg=imax;
	break;
      case 8:
        TPot Pot("..\\gdat\\pot.dat");
        for(t=0;t<ntl;t++)  
	{
	  i=0;
	  for(n=tmin[t];n<=6;n++)
	  {
	    pp[i]=tpot[t](n);
	    i++;
	  }
	  pp[i]=-1.;
          Pot.show(tmin[t],pp,tname[t]);
        }
	break;
      default:
        cont=0;
    }//end switch
    if(cont) if(getch()==27)break;
  }//end while

  closegraph();
  return 0;
}
