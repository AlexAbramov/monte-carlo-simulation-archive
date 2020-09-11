// classes for one- and two- dimensional arrays
// class for random numbers generator
// class for tabulated functions
// some usefull functions
// Abramov A.A., 1996.

#ifndef __MYLIB_H
#define __MYLIB_H

#ifndef __STDIO_H
  #include<stdio.h>
#endif
#ifndef __IO_H
  #include<io.h>
#endif
#ifndef __CSTRING_H
  #include<cstring.h>
#endif

// FUNCTIONS
void error_message(char*);
void message(char*);
void newline(FILE*);
FILE * handle_scan(char*);
int handle_read(char*);
int handle_write(char*);
float aprox(float,float,float,float,float);//x1,y1,x2,y2,x
float fmax(float,float);

// BASE ARRAY
class TBaseArray
{
  protected:
	 int size;
	 float * ff;         
	 void Alloc(int);
	 void Control();
  public:
	 TBaseArray(){ size=0; ff=0;}
	 ~TBaseArray(){ delete ff;}
	 int Size(){ return size;}
	 float Max();
	 float Min();
	 float Sum();
	 void Normir(float=1.);
	 void Write(int);
	 void Read(int);
	 void Obnul();
	 void operator += (float);
	 void operator += (TBaseArray&);
	 void operator *= (float);
};

// SINGLE ARRAY
class TSingleArray : public TBaseArray
{
  public:
	 TSingleArray(): TBaseArray(){}
	 TSingleArray(int _size){ Alloc(_size);}
	 void Init(int _size){ Alloc(_size);}
	 void Integral();
	 float & operator [](int);// element=array[i]
};

// DOUBLE ARRAY
class TDoubleArray : public TBaseArray
{
  protected:
	 int ysize,xsize;
  public:
	 TDoubleArray(): TBaseArray(){ ysize=0; xsize=0; }
	 TDoubleArray(int _ysize,int _xsize){ Init(_ysize,_xsize);}
	 void Init(int,int);// ysize,xsize
	 int YSize(){ return ysize;}
	 int XSize(){ return xsize;}
	 float * operator [] (int);// element=array[j][i]
};

// RANDOM
class TRandom
{
  protected:
	 int size;
	 double * rr;
	 string * str;
	 char* GetName(){ return (char*) str->c_str(); }
	 void Control();
  public:
	 int Size(){ return size;}
	 TRandom(){ size=0; rr=0; str=0;}
	 TRandom(int _size,char* name){ size=0; Init(_size,name);}
	 void Init(int,char*);
	 ~TRandom();
	 double operator [] (int);
};

// TABULATED FUNCTION
class TTabFunc
{
  private:
	 int size;
	 float * xx;
	 float * yy;
	 float xmax,xmin;
	 float aa,bb;
  public:
	 TTabFunc(char*);
	 ~TTabFunc();
	 float Ordinata(float);
};

#endif