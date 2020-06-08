#pragma hdrstop
#include <cstring.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mylib.h>

// BASE ARRAY
void
TBaseArray::Control()
{
  if(size>0) return;
  else error_message("Error in TBaseArray::Control()");
}

void
TBaseArray::Alloc(int _size)
{
  if(size>0) delete ff;
  size=_size;
//  if(size*sizeof(float)>64000L) error_message("Size is too large in TBaseArray::Alloc");
  ff=new float[size];
  if(ff==0) error_message("Memory allocation error in TBaseArray::Alloc");
  Obnul();
}

float
TBaseArray::Max()
{
  Control();
  float xmax=ff[0];
  for(int n=1;n<size;n++)
  {
	 float x=ff[n];
	 if(xmax<x) xmax=x;
  }
  return xmax;
}

float
TBaseArray::Min()
{
  Control();
  float xmin=ff[0];
  for(int n=1;n<size;n++)
  {
	 float x=ff[n];
	 if(xmin>x) xmin=x;
  }
  return xmin;
}

float
TBaseArray::Sum()
{
  Control();
  float sum=0.;
  for(int n=0;n<size;n++) sum+=ff[n];
  return sum;
}

void
TBaseArray::Normir(float kk)
{
  Control();
  float s=Sum();
  if(s==0.) return;
  float k=kk/s;
  for(int n=0;n<size;n++) ff[n]*=k;
}

void
TBaseArray::Write(int fd)
{
  Control();
  write(fd,ff,size*sizeof(float));
}

void
TBaseArray::Read(int fd)
{
  Control();
  read(fd,ff,size*sizeof(float));
}

void
TBaseArray::Obnul()
{
  Control();
  for(int n=0;n<size;n++) ff[n]=0.;
}

void
TBaseArray::operator += (float x)
{
  Control();
  for(int n=0;n<size;n++) ff[n]+=x;
}

void
TBaseArray::operator += (TBaseArray& bar)
{
  Control();
  if(size!=bar.size) error_message("Error in TBaseArray::operator += (TBaseArray&)");
  for(int n=0;n<size;n++) ff[n] += (bar.ff)[n];
}

void
TBaseArray::operator *= (float x)
{
  Control();
  for(int n=0;n<size;n++) ff[n]*=x;
}

// SINGLE ARRAY
float&
TSingleArray::operator [](int n)
{
  Control();
  if(n<0||n>=size) error_message("Index error in TSingleArray");
  return ff[n];
}

void
TSingleArray::Integral()
{
  Control();
  for(int n=1;n<size;n++) ff[n]+=ff[n-1];
}

// DOUBLE ARRAY
void
TDoubleArray::Init(int _ysize,int _xsize)
{
  Alloc( _ysize*_xsize );
  ysize=_ysize;
  xsize=_xsize;
}

float*
TDoubleArray::operator [](int j)
{
  Control();
  if(j<0||j>=ysize) error_message("Index error in TDoubleArray");
  return ff+j*xsize;
}

// RANDOM
void
TRandom::Control()
{
  if(size==0) error_message("Error in TRandom::Control()");
}

TRandom::TRandom(int _size, string _fname)
{
  size=0;
  Init(_size,_fname);
}

void
TRandom::Init(int _size,string _fname)
{
  if(size>0) delete rr;
  size=_size;
  rr=new double[size];
  if(rr==0) error_message("Alloc error in TRandom");
  fname=_fname;
  int i,flag_new_random;
  int fd=open(fname.c_str(),O_RDONLY|O_BINARY);
  if(fd==-1) flag_new_random=1;
  else
  {
	 int sz;
	 read(fd,&sz,sizeof(int));
	 if(sz==size)
	 {
		for(i=0;i<size;i++) read(fd,rr,size*sizeof(double));
		flag_new_random=0;
	 }
	 else flag_new_random=1;
  }
  if(flag_new_random==1) for(i=0;i<size;i++) rr[i]=987654321.0/double(i+1);
  close(fd);
  path=".\\";
}

void TRandom::RegistrateDirectory(string s)
{
  path=s+"\\"+fname;
}

TRandom::~TRandom()
{
  if(size>0)
  {
	 int fd=handle_write((char*)path.c_str());
	 write(fd,&size,sizeof(int));
	 for (int i=0;i<size;i++ ) write(fd,rr,size*sizeof(double));
	 close(fd);
	 delete rr;
  }
}

double
TRandom::operator [](int i)
{
  Control();
  if(i<0||i>=size) error_message("Argument out range in TRandom");
  double r=fmod(16807.*rr[i],2147483647.);
  rr[i]=r;
  r*=.4656612873077392258e-9 ;
  if(r<=0.||r>=1.) error_message("Random out range (0,1)");
  return r;
}

// NEWLINE
void newline(FILE* fp)
{
  while(1){ int k=fgetc(fp); if(k==10 || k==-1)break; }
}

// MESSAGE
void error_message(char * ss)
{
//  MessageBox(0,ss,"Error",MB_OK);
  FatalAppExit(0,ss);
}
void message(char * ss)
{
  MessageBox(0,ss,"Message",MB_OK);
}

// APROX
float aprox(float x1,float y1,float x2,float y2,float x)
{
  return y1+(y2-y1)*(x-x1)/(x2-x1);
}

// TAB FUNCTION
TTabFunc::TTabFunc(char * file_name)
{
  FILE * fp=handle_scan(file_name);
  float x,y;
  fscanf(fp,"%f",&x);
  size=0;
  while(x>=0.)
  {
	 fscanf(fp,"%f",&y);
	 size++;
	 fscanf(fp,"%f",&x);
  }
  xx=new float[size];
  yy=new float[size];
  fseek(fp,0,0);
  for(int i=0;i<size;i++)
  {
	 fscanf(fp,"%f",xx+i);
	 fscanf(fp,"%f",yy+i);
  }
  float x1=xx[size-2];
  float x2=xx[size-1];
  float y1=yy[size-2];
  float y2=yy[size-1];
  xmin=xx[0];
  xmax=x2;
  aa=(y2*x2-y1*x1)/(x2-x1);
  bb=(y1-y2)*x1*x2/(x2-x1);
}

TTabFunc::~TTabFunc()
{
  delete xx,yy;
}

float
TTabFunc::Ordinata(float x)
{
  if(x<xmin) return 0.;
  if(x<=xmax)
  {
	 int i=0;
	 while(x>xx[i]) i++;
	 return aprox(xx[i-1],yy[i-1],xx[i],yy[i],x);
  }
  else return aa+bb/x;
}

// HANDLE
int handle_read(char* file_name)
{
  int fd=open(file_name,O_BINARY|O_RDONLY);
  if(fd<0) error_message("Binary file read error");
  return fd;
}

int handle_write(char* file_name)
{
  int fd=open(file_name,O_BINARY|O_WRONLY);
  if(fd<0)
  {
	 FILE * fp=fopen(file_name,"w");
	 fclose(fp);
	 fd=open(file_name,O_BINARY|O_WRONLY);
	 if(fd<0) error_message("Error in handle_write()");
  }
  return fd;
}

FILE * handle_scan(char* file_name)
{
  FILE * fp=fopen(file_name,"r");
  if(fp<=0) error_message("Error in handle_scan()");
  return fp;
}

float fmax(float x,float y)
{
  if(x>y) return x;
  else return y;
}