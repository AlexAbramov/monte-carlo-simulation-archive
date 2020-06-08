//	GRAPHICS INTERFACE
#include<conio.h>
#include<dos.h>
#include<math.h>
#include<stdlib.h>
#include<mygraph.h>
#include<newline.hpp>

void initgraph()
{
  int gdriver=9;
  int gmode=2;
  initgraph(&gdriver,&gmode,"..\\gdat");
}

static void chek_fopen_error(FILE * fp, char * string)    
{ 
  if(fp==0){ printf("\n\a\a Оpen file error: '%s'",string); exit(-1); }
}


TBox::TBox( FILE * fp)
{
  fscanf( fp,"%i%i%i%i%i%i%i%i",&x1,&y1,&x2,&y2,&c0,&c1,&fill,&border);
}

TBox::TBox( char * string)
{
  FILE * fp=fopen(string,"r");
    chek_fopen_error(fp,string);
    fscanf( fp,"%i%i%i%i%i%i%i%i",&x1,&y1,&x2,&y2,&c0,&c1,&fill,&border);
  fclose(fp);
}

void TBox::show()
{
  setfillstyle( fill, c0);
  bar(x1,y1,x2,y2);
  setlinestyle(0,0,border);
  setcolor(c1);
  rectangle(x1,y1,x2,y2);
}

TGraph::TGraph(char * string)
{
  FILE * fp=fopen(string,"r");
    chek_fopen_error(fp,string);
    pbox1=new TBox(fp);newline(fp);
    pbox2=new TBox(fp);newline(fp);
    fscanf(fp,"%i%i",&nx,&ny);newline(fp);
    fscanf(fp,"%i%i",&ct,&cg);newline(fp);
    fscanf(fp,"%s%s",formatx,formaty);
  fclose(fp);
  i1=pbox1->x1+(pbox2->x1-pbox1->x1)/2;
  j1=pbox1->y1+(pbox2->y1-pbox1->y1)/2;
  j2=pbox2->y2+(pbox1->y2-pbox2->y2)/3;
  j3=pbox2->y2+(pbox1->y2-pbox2->y2)*2/3;
}

void TGraph::show( int _nn, float * _xx, float * yy,
                   char * textx, char * texty)
{
  nn=_nn;
  xx=_xx;
  int i,j;
  float xmin=*xx,ymin=*yy;
  float x,xmax=*xx;//=xx[nn];
  float y, ymax=*yy;
  for(int n=1; n<=nn; n++)
  {
    x=*(xx+n);
    y=*(yy+n);
    if(xmax<x)xmax=x;
    if(ymax<y)ymax=y;
    if(xmin>x)xmin=x;
    if(ymin>y)ymin=y;
  }
  if(xmax<-xmin) xmax=-xmin;
  if(ymax<-ymin) ymax=-ymin;
  if(ymin>=0.&&xmin>=0) flag_plus=1;
  else flag_plus=0;
  if(xmax!=360.)
  {
    x=log10(xmax*.99);
    if(x>0.) j=x;
    else j=x-1;
    float xp=pow(10.,j);
    j=xmax/xp+.99;
    xmax=j*xp;
  }
  if(ymax!=360.)
  {
    y=log10(ymax*.99);
    if(y>0.) j=y;
    else j=y-1;
    float yp=pow(10.,j);
    j=ymax/yp+.99;
    ymax=j*yp;
  }
  int x1=pbox2->x1;
  int y1=pbox2->y1;
  int x2=pbox2->x2;
  int y2=pbox2->y2;
  lx=x2-x1;
  ly=y2-y1;

  pbox1->show();
  pbox2->show();
  setlinestyle(0,0,1);
  if(flag_plus)// lines
  {
    for(n=0; n<=nx+nx; n++)
    {
      i=x1+lx*n/(nx+nx);
      line(i,y1,i,y2);
    }
    for(n=0; n<=ny+ny; n++)
    {
      j=y1+ly*n/(ny+ny);
      line(x1,j,x2,j);
    }
  }
  else
  {
    for(n=0; n<=nx+nx; n++)
    {
      i=x1+lx*n/(nx+nx);
      if(n==nx)
      {
        setlinestyle(0,0,3);
        line(i,y1,i,y2);
        setlinestyle(0,0,1);
      }	
      else line(i,y1,i,y2);
    }
    for(n=0; n<=ny+ny; n++)
    {
      j=y1+ly*n/(ny+ny);
      if(n==ny)
      {
        setlinestyle(0,0,3);
        line(x1,j,x2,j);
        setlinestyle(0,0,1);
      }	
      else line(x1,j,x2,j);
    }
  }
//  settextstyle(10,0,5);
  setcolor(ct);
  char buf[20];
  settextjustify(1,1);
  if(flag_plus)
  {
    for(n=0; n<=nx; n++)
    {
      i=x1+lx*n/nx;
      sprintf(buf,formatx,n*xmax/nx);
      outtextxy(i,j2,buf);
    }
    for(n=0; n<=ny; n++)
    {
      j=y1+ly*(ny-n)/ny;
      sprintf(buf,formaty,n*ymax/ny);
      outtextxy(i1,j,buf);
    }
  }
  else
  {
    for(n=0; n<=nx+nx; n++)
    {
      i=x1+lx*n/(nx+nx);
      sprintf(buf,formatx,(n-nx)*xmax/nx);
      outtextxy(i,j2,buf);
    }
    for(n=0; n<=ny+ny; n++)
    {
      j=y1+ly*(ny+ny-n)/(ny+ny);
      sprintf(buf,formaty,(n-ny)*ymax/ny);
      outtextxy(i1,j,buf);
    }
  }
  settextjustify(2,1);
  outtextxy(x2,j3,textx);
  settextjustify(0,1);
  outtextxy(i1,j1,texty);
  rx=lx/xmax;
  ry=ly/ymax;
  show(yy,cg);
}

void TGraph::show( float * yy, int _cg)
{
  setcolor(_cg);
  int i,j,ii,jj;
  if(flag_plus)
  {
    i=pbox2->x1;
    j=pbox2->y2;
    ii=i+(*xx)*rx;
    jj=j-(*yy)*ry;
    moveto(ii,jj);
    for(int n=1; n<=nn; n++)
    {
      ii=i+*(xx+n)*rx;
      jj=j-*(yy+n)*ry;
      lineto(ii,jj);
    }
  }
  else
  {    
    i=pbox2->x1+lx*.5;
    j=pbox2->y2-ly*.5;
    ii=i+(*xx)*rx*.5;
    jj=j-(*yy)*ry*.5;
    moveto(ii,jj);
    for(int n=1; n<=nn; n++)
    {
      ii=i+*(xx+n)*rx*.5;
      jj=j-*(yy+n)*ry*.5;
      lineto(ii,jj);
    }
  }
}

TPot::TPot(char * string)
{
  FILE * fp=fopen(string,"r");
    chek_fopen_error(fp,string);
    pbox1=new TBox(fp);newline(fp);
    pbox2=new TBox(fp);newline(fp);
    fscanf(fp,"%i%i",&nx,&ny);newline(fp);
    fscanf(fp,"%f%f",&ymin,&ymax);newline(fp);
    fscanf(fp,"%s",formaty);newline(fp);
    fscanf(fp,"%s",textx);newline(fp);
    fscanf(fp,"%s",texty);newline(fp);
    fscanf(fp,"%i",&dx);newline(fp);
    fscanf(fp,"%i",&ct);
  fclose(fp);
  nn=0;

  i1=pbox1->x1+(pbox2->x1-pbox1->x1)/2;
  j1=pbox1->y1+(pbox2->y1-pbox1->y1)/2;
  j2=pbox2->y2+(pbox1->y2-pbox2->y2)/3;
  j3=pbox2->y2+(pbox1->y2-pbox2->y2)*2/3;

  int x1=pbox2->x1;
  int y1=pbox2->y1;
  int x2=pbox2->x2;
  int y2=pbox2->y2;
  int lx=x2-x1;
  int ly=y2-y1;

  pbox1->show();
  pbox2->show();

  setlinestyle(0,0,1);

  int i,j,n;
  for(n=0; n<=nx; n++)
  {
    i=x1+lx*n/nx;
    line(i,y1,i,y2);
  }
  for(n=0; n<=ny; n++)
  {
    j=y1+ly*n/ny;
    line(x1,j,x2,j);
  }

  setcolor(ct);
  char buf[20];
  settextjustify(1,1);
  for(n=0; n<=ny; n++)
  {
    j=y1+ly*(ny-n)/ny;
    sprintf(buf,formaty,ymin+n*(ymax-ymin)/ny);
    outtextxy(i1,j,buf);
  }
  settextjustify(2,1);
  outtextxy(x2,j3,textx);
  settextjustify(0,1);
  outtextxy(i1,j1,texty);
  rx=lx/nx;
  ry=ly/(ymax-ymin);
}

void TPot::show(int n0,float * yy,char * textx)
{
  nn++;
  int i=pbox2->x1+nn*rx;
  setcolor(ct);
  settextjustify(1,1);
  outtextxy(i,j2,textx);

  char buf[20];
  setlinestyle(0,0,3);
  int n=0;
  int j;
  while(*(yy+n)>0.)
  {
    j=pbox2->y2-(*(yy+n)-ymin)*ry;
    sprintf(buf,"%i",n0+n);
    settextjustify(2,1);
    outtextxy(i-dx,j,buf);
    line(i-dx,j,i+dx,j);
    sprintf(buf,formaty,*(yy+n));
    settextjustify(0,1);
    outtextxy(i+dx,j,buf);
    n++;
  }
}

TMessage::TMessage(char * string)
{
  FILE * fp=fopen(string,"r");
    chek_fopen_error(fp,string);
    pbox=new TBox(fp);newline(fp);
    fscanf(fp,"%i%i",&frequence,&time);newline(fp);
    fscanf(fp,"%i%i",&nx,&ny);newline(fp);
    text=new char[nx*ny+ny];
    for(int j=0;j<ny;j++)
    {
      char *pch=text+j*nx;
      while(1)
      { *pch=fgetc(fp); if(*pch==10){ *pch=0; break;}; pch++; }
    }
  fclose(fp);
}

int TMessage::show()
{
  pbox->show();
  setcolor(0);
  settextjustify(1,1);
  for(int j=0;j<ny;j++)
  {
    outtextxy( (pbox->x1+pbox->x2)/2,
               pbox->y1+(j+1)*(pbox->y2-pbox->y1)/(ny+1),
               text+j*nx);
  }
  sound(frequence);
  delay(time);
  nosound();
  return getch();
}

#define string_max_size 33

TDialog::TDialog(char * string)
{
  FILE * fp=fopen(string,"r");
    chek_fopen_error(fp,string);
    pbox1=new TBox(fp);newline(fp);
    pbox2=new TBox(fp);newline(fp);
    fscanf(fp,"%i",&dx);newline(fp);
    fscanf(fp,"%i%i",&nx1,&ny1);newline(fp);
    text1=new char[nx1*ny1+ny1];
    for(int j=0;j<ny1;j++)
    {
      char *pch=text1+j*nx1;
      while(1){ *pch=fgetc(fp); if(*pch==10||*pch==-1){ *pch=0; break;}; pch++; }
    }
  fclose(fp);
  string=new char[string_max_size];
  string[string_max_size-1]=0;
}

char * TDialog::show(int parole)
{
  pbox1->show();
  pbox2->show();
  setcolor(pbox1->c1);
  int yy=pbox2->y1-pbox1->y1;
  setcolor(1);
  settextjustify(1,1);
  for(int n=0;n<ny1;n++)
  {
    outtextxy( (pbox1->x1+pbox1->x2)/2,
               pbox1->y1+yy*(n+n+1)/(ny1+ny1),
               text1+n*nx1);
  }
  setcolor(0);
  settextjustify(0,1);
  yy=pbox2->y1+(pbox2->y2-pbox2->y1)/2;
  char ss[2];
  ss[1]=0;
  n=0;
  char k;
  char true_char;
  while(1)
  {
    k=getch();
    if(k==0)if(getch()==75)k=8;
    if( k==8 && n>0)
    {
      n--;
      if(parole==0) bar( pbox2->x1+dx+dx*n,pbox2->y1+1,
           	 	 pbox2->x1+dx+dx*n+dx,pbox2->y2-1 );
    }
    else
    {
      if(k==13)
      {
        string[n]=0; 
        if(parole==1)
        {
	  if( n==3 && string[0]==65  && string[1]==66 && string[2]==67 )
          {
            outtextxy(pbox2->x1+dx,yy,"Пароль введен правильно.");
	    *string=1;
            return string;
	  }
	  else
	  {
	    *string=0;
            outtextxy(pbox2->x1+dx,yy,"Пароль введен неправильно.");	
          }
        }
	return string;
      }
      if(k==27){ *string=27; return string; }
      true_char=0;
      if( k==32 ) true_char=1;
      if(parole==0)
      {
	if( k==46 ) true_char=1;
        if( k>=48 && k<=57 ) true_char=1;
        if( k>=128 && k<=159 ) true_char=1;
        if( k>=160 && k<=175 ){ true_char=1; k=k-32; }
        if( k>=224 && k<=239 ){ true_char=1; k=k-80; }
      }
      else
      {
        if( k>=65 && k<=90 ) true_char=1;
        if( k>=97 && k<=122 ){ true_char=1; k=k-32; }
      }
      if(true_char)
      {
        *ss=k;
        string[n]=k;
        if(parole==0)outtextxy(pbox2->x1+dx+dx*n,yy,ss);
        if(n<string_max_size-1) n=n+1;
      }
    }
  }
}  

TMenu::TMenu(char * string)
{
  FILE * fp=fopen(string,"r");
    chek_fopen_error(fp,string);
    pbox1=new TBox(fp);newline(fp);
    pbox2=new TBox(fp);newline(fp);
    fscanf(fp,"%i%i",&dx,&c0);newline(fp);
    fscanf(fp,"%i%i",&nx1,&ny1);newline(fp);
    text1=new char[nx1*ny1+ny1];
    for(int j=0;j<ny1;j++)
    {
      char *pch=text1+j*nx1;
      while(1){ *pch=fgetc(fp); if(*pch==10||*pch==-1){ *pch=0; break;}; pch++; }
    }
    fscanf(fp,"%i%i",&nx2,&ny2);newline(fp);
    text2=new char[nx2*ny2+ny2];
    for(j=0;j<ny2;j++)
    {
      char *pch=text2+j*nx2;
      while(1){ *pch=fgetc(fp); if(*pch==10||*pch==-1){ *pch=0; break;}; pch++; }
    }
  fclose(fp);
  nomer=0;
}

void TMenu::select(int n, int color0, int color1)
{
  int yy=pbox2->y2-pbox2->y1;
  setfillstyle(1,color0);
  bar( pbox2->x1+1,pbox2->y1+yy*n/ny2+1,
       pbox2->x2-1,pbox2->y1+yy*(n+1)/ny2-1);
  setcolor(color1);
  outtextxy( dx+(pbox2->x1),
             pbox2->y1+yy*(n+n+1)/(ny2+ny2),
             text2+n*nx2);
}

int TMenu::show()
{
  pbox1->show();
  pbox2->show();
  setcolor(pbox1->c1);
  int yy=pbox2->y1-pbox1->y1;
  setcolor(1);
  settextjustify(1,1);
  for(int n=0;n<ny1;n++)
  {
    outtextxy( (pbox1->x1+pbox1->x2)/2,
               pbox1->y1+yy*(n+n+1)/(ny1+ny1),
               text1+n*nx1);
  }
  setcolor(pbox2->c1);
  yy=pbox2->y2-pbox2->y1;
  for(n=1;n<ny2;n++)
  {
    int j=pbox2->y1+yy*n/ny2;
    line(pbox2->x1,j,pbox2->x2,j);
  }
  setcolor(0);
  settextjustify(0,1);
  for(n=0;n<ny2;n++)select(n,pbox2->c0,0);
  select(nomer,c0,1);
  while(1)
  {
    int k=getch();
    if(k==0)
    {
      k=getch();
      if(k==72||k==80)
      {
        select(nomer,pbox2->c0,0);
        if(k==72){ nomer--; if(nomer==-1)nomer=ny2-1; }
        if(k==80){ nomer++; if(nomer==ny2)nomer=0; }
        select(nomer,c0,1);
      }
    }
    else
    {
      if(k==27)return 0;
      if(k==13)return nomer+1;
    }
  }
}