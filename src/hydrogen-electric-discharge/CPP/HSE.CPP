#include <io.h>
#include <fcntl.h>
#include <math.h>
#pragma hdrstop
#include <mylib.h>
#include <hse.h>

float ntoe(int n)
{
  if(n<64) return float(n);
  if(n<96) return float((n<<1)-64);
  if(n<128) return float((n<<2)-256);
  if(n<160) return float((n<<3)-768);
  if(n<192) return float((n<<4)-2048);
  if(n<224) return float((n<<5)-5120);
  if(n<=256) return float((n<<6)-12288);
  error_message("Argument overflow in ntoe()");
  return(0.);
}

int eton(float e)
{
  if(e<0.) error_message("Argument out range in eton()");
  int ie=int(e);
  if(ie<64) return ie;
  if(ie<128) return 32+(ie>>1);
  if(ie<256) return 64+(ie>>2);
  if(ie<512) return 96+(ie>>3);
  if(ie<1024) return 128+(ie>>4);
  if(ie<2048) return 160+(ie>>5);
  if(ie<=4096) return 192+(ie>>6);
  return 4096;
}

float * spelas;
float * energy;
float * vel;

static void check_alloc(float * tt)
{
  if(tt==0) error_message("Error in check_alloc()");
}

void alloc_se()
{
  spelas=new float[NEMAX1*NU];check_alloc(spelas);
  energy=new float[NEMAX1];	check_alloc(energy);
  vel=new float[NEMAX1];	   check_alloc(vel);

  for(int ne=0;ne<=NEMAX;ne++)
  {
	 float e=ntoe(ne);
	 energy[ne]=e;
	 vel[ne]=sqrt(e);
  }
}

void dealloc_se()
{
  delete spelas,energy,vel;
}

void read_se(char* fname)
{
  int fd=handle_read(fname);
  int sf=sizeof(float);
  read(fd,spelas,sf*NEMAX1*NU);
  close(fd);
}

void write_se(char* fname)
{
  int fd=handle_write(fname);
  int sf=sizeof(float);
  write(fd,spelas,sf*NEMAX1*NU);
  close(fd);
}

static int	ne;
static int	nr;
static float	s1;
static float	s2;
static float	s3;
static float	s4;
static float	dx;
static float	dy;
static float*	ps;
static const float 	rio=float(NU-1);

static inline float	aprox(float s1,float s2,float dx)
{
  return s1+dx*(s2-s1);
}

static inline float	aproxim(float s1,float s2,float s3,float s4,float dx,float dy)
{
  return s1+dx*(s2-s1)+dy*(s3-s1)+dx*dy*(s4+s1-s2-s3);
}

static float	saprox(float *ps,float e)
{
  ne=eton(e);
  ps=ps+ne;
  s1=*ps;
  s2=*(ps+1);
  if(ne<64) dx=e-float(ne);
  else dx=(e-energy[ne])/(energy[ne+1]-energy[ne]);
  return aprox(s1,s2,dx);
}

static float	saproxim(float *ps,float e,float r,int ny)
{
  ne=eton(e);
  nr=int(r);
  ps=ps+ne*ny+nr;
  s1=*(ps);
  s2=*(ps+ny);
  s3=*(ps+1);
  s4=*(ps+ny+1);
  if(ne<64) dx=e-float(ne);
  else dx=(e-energy[ne])/(energy[ne+1]-energy[ne]);
  dy=r-nr;
  return aproxim(s1,s2,s3,s4,dx,dy);
}

float velf(float e){ return saprox(vel,e);}
float spelasf(float e,float r){ return saproxim(spelas,e,r*rio,NU  );}

