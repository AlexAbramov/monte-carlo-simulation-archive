//	ВИЗУАЛИЗАЦИЯ МАССИВОВ СЕЧЕНИЙ
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<se.h>
#include<mygraph.h>
#include<newline.hpp>
#define imax 1000
inline const int nnu=100;
inline const float rnu=1./nnu;
#define pi 3.1415
int main()
{
  alloc_se();
  read_se();
  int imaxg,kit;
  int i,n;
  float x,y,e,r;
  static float xx[imax+1];	
  static float yy[imax+1];
  static float yys[imax+1];
  //system("..\\edit ..\\dat\\visual.dat");
  FILE * fp=fopen("..\\dat\\visual.dat","r");
    fscanf(fp,"%i",&imaxg);newline(fp);
    fscanf(fp,"%i",&kit);newline(fp);
  fclose(fp);
  //printf("\n imaxg=%i",imaxg);
  if(imaxg>imax)imaxg=imax;
  char textx[]="Энергия,[eV]";
  char texty[50];
  //getch();
  
  initgraph();
  TBox box("..\\gdat\\box.dat");  
  TMenu menu("..\\gdat\\menu.dat");
  TGraph graph("..\\gdat\\graph.dat");
  TDialog dialog("..\\gdat\\dialog.dat");
  //TDialog dialog1("..\\gdat\\dialog1.dat");
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
          yy[i]=stotf(e);
	}
        graph.show(imaxg,xx,yy,textx,"Полное сечение");
	getch();
        for(i=ipex;i<=imaxg;i++)
        { 
          e=float(i);
          xx[i]=e;
          yy[i]=selasf(e)*stotf(e);
	}
        graph.show(imaxg,xx,yy,textx,"Упругое сечение");
	break;
      case 2:
        for(i=ipex1;i<=imaxg;i++)
        { 
          e=float(i);
          xx[i]=e;
          yy[i]=sexf(e)*stotf(e);
	}
        graph.show(imaxg-ipex1,xx+ipex1,yy+ipex1,textx,"Сечение возбуждения");
        break;
      case 3:
        for(i=ipion1;i<=imaxg;i++)
        { 
          e=float(i);
          xx[i]=e;
          yy[i]=sionf(e)*stotf(e);
	}
        graph.show(imaxg-ipion1,xx+ipion1,yy+ipion1,textx,"Сечение ионизации");
	break;
      case 4:
        e=atof(dialog.show());
        for(i=0;i<=nnu;i++)
        {
          x=i*rnu;
	  xx[i]=x;
          yy[i]=spelasf(e,x);
        }
        graph.show(nnu,xx,yy,"Вероятность","Угол рассеяния,[рад]");
	break;
      case 5:
        e=atof(dialog.show());
        for(i=0;i<=nnu;i++)
        { 
          x=i*rnu;
          xx[i]=x;
          yy[i]=(float)spexf(e,x);
	}
	if(yy[nnu]<.5) i=0;
	else i=1;
        if(i==1) graph.show(nnu,xx,yy,"Вероятность","Номер уровня");
        break;
      case 6:
	e=atof(dialog.show());
        for(i=0;i<=nnu;i++)
        {
          x=i*rnu;
	  xx[i]=x;
          yy[i]=spionf(e,x);
        }
        graph.show(nnu,xx,yy,"Вероятность","Доля энергии");
	break;
      case 7:
        e=atof(dialog.show());
        imaxg=int(e);
        if(imaxg<ipion1)imaxg=ipion1;
        if(imaxg>imax)imaxg=imax;
	break;
      case 8:
	break;
      default:
        cont=0;
    }//end switch
    if(cont) if(getch()==27)break;
  }//end while

  closegraph();
  return 0;
}
