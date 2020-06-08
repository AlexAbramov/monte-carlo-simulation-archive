//	Abramov A.A., 1994 
//	Graphics interface for programs

#include<graphics.h>
#include<stdio.h>

void initgraph();

class TBox
{
  public:
  int x1,y1,x2,y2;
  int c0,c1;
  int fill,border;
  TBox(char*);
  TBox(FILE*);
  void show();
};
typedef TBox * PTBox;

class TGraph
{
  PTBox pbox1;
  PTBox pbox2;
  int nx,ny;
  int ct,cg;
  char formatx[10];
  char formaty[10];

  int i1,j1,j2,j3;
  int lx,ly;

  int nn;
  int flag_plus;
  float * xx;
  float rx,ry;

  public:
  TGraph(char*);
  void show(int,float*,float*,char*,char*);
  void show(float*,int);
};

class TPot // for thresholds hierarchy visualization
{
  PTBox pbox1;
  PTBox pbox2;
  int nx,ny;
  float ymin,ymax;
  char formaty[10];
  char textx[30];
  char texty[30];
  int dx;
  int ct;

  int nn;
  int i1,j1,j2,j3;
  float rx,ry;

  public:
  TPot(char*);
  void show(int,float*,char*);
};

class TMessage
{
  PTBox pbox;
  int frequence,time;
  int nx,ny;
  char * text;

  public:
  TMessage(char*);
  int show();
};

class TDialog
{
  PTBox pbox1;
  PTBox pbox2;
  int dx;
  int nx1,ny1;
  char * text1;

  public:
  TDialog(char*);
  char * string;
  char * show(int=0);
};

class TMenu
{
  PTBox pbox1;
  PTBox pbox2;
  int dx,c0;
  int nx1,ny1;
  char * text1;
  int nx2;
  char * text2;
  void select(int,int,int);

  public:
  int ny2,nomer;
  TMenu(char*);
  int show();
};