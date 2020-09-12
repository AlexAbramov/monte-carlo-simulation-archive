// Two- and three- dimensional graphs
// Abramov A.A., 1997

#ifndef __MYGRAPH_H
#define __MYGRAPH_H

#if !defined(OWL_DC_H)
  #include <owl\dc.h>
#endif
#ifndef __MYLIB_H
  #include <mylib.h>
#endif

// TWO-DIMENCIONAL GRAPH
class TGraph
{
  protected:
	 // data keeping in file:
	 int nx,ny;
	 float x0,x1;
	 float y0,y1;
	 char formatx[10];
	 char formaty[10];
	 int size1,size2;
	 // derived data initializing by Update method:
	 int i0,j0;
	 int lx,ly;
	 int ii,jj;
	 int Update(TDC&);
	 void Common(TDC&,float,float,char*,char*);
	 int textStatus;
	 float rx,ry;
  public:
	 TGraph(char* ="..\\..\\dat\\graph.dat");
	 void Show(TDC&, TSingleArray&,float=100., char* ="X",char* ="Y");
	 void Show(TDC&, int,float*,float=100.,    char* ="X",char* ="Y");
	 void Show(TDC&, int,float*,float*,      char* ="X",char* ="Y");
	 void Clear(TDC&);
	 void Show1(TDC&, TSingleArray&);
};

// THREE-DIMENCIONAL GRAPH
class TGraphic
{
  protected:
	 // data keeping in file
	 int nx,ny,nz;
	 int angle;
	 float x0,y0;
	 float sx,sy,sz;
	 char formatx[10];
	 char formaty[10];
	 char formatz[10];
	 int size1,size2;
	 // derived data, init by Update method:
	 int i0,j0;
	 int lx,lz;
	 int ii,jj;
	 float xx0,yy0;
	 int xx,yy;
	 int Update(TDC&);
	 void Common(TDC&,float,float,float,char*,char*,char*);
	 int textStatus;
  public:
	 TGraphic(char* ="..\\..\\dat\\graphic.dat");
	 void Show(TDC&,TDoubleArray&,float=100.,float=100.,char* ="X",char* ="Y",char* ="Z");
	 void Clear(TDC&);
};

#endif
