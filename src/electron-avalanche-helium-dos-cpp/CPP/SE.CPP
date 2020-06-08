// ОПРЕДЕЛЕНИЕ ФУНКЦИЙ СЕЧЕНИЙ И ФУНКЦИЙ ДЛЯ РАБОТЫ С МАССИВАМИ
#include<io.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<se.h>

char	file_se[30]="..\\dat\\sehe";		// Имя файла массивов сечений

static const float	pexim[nexp]=	// Массив потенциалов возбуждения
{ pex, 20.62, 20.96, 21.22, 23.00, 23.70, 24.2 };
  
float	pexi(int n)	// Функция возвращающая потенциалы возбуждения
{ 
  if(n<0||n>=nexp){printf("Недопустимый аргумент в pexi(int).");exit(-1);}
  return pexim[n];
}

//  ДЕКЛАРАЦИЯ МАССИВОВ:
float*	stot;			//суммарное сечение
float*	ftot;			//ftot
float*	selas;			//сечение упругих процессов
float*	sex;			//сечение возбуждения
float*	sion;			//сечение ионизации
float*	spelas;			//дифференциальное сечение упругих процессов
float*	spex;			//дифференциальное сечение возбуждения
float*	spion;			//дифференциальное сечение ионизации
float*	energy;

//  Определение констант для работы с массивами:
static const int	nemax1=nemax+1;
static const int	nemax2=nemax1-ipex;
static const int	nemax3=nemax1-ipion;

//  ОПРЕДЕЛЕНИЕ ФУНКЦИЙ ДЛЯ РАБОТЫ С МАССИВАМИ:
float ntoe(int n)
{
  if(n<64) return float(n);
  if(n<96) return float((n<<1)-64);
  if(n<128) return float((n<<2)-256);
  if(n<160) return float((n<<3)-768);
  if(n<192) return float((n<<4)-2048);
  if(n<224) return float((n<<5)-5120);
  if(n<=256) return float((n<<6)-12288);
  printf("\n\a\a Energy overflow.");
  exit(-1);
} 

int eton(float e)
{
  if(e<0.){printf("\n\a\a e<0 в функции eton(float e)");exit(-1);} 
  int ie=int(e);
  if(ie<64) return ie;
  if(ie<128) return 32+(ie>>1);
  if(ie<256) return 64+(ie>>2);
  if(ie<512) return 96+(ie>>3);
  if(ie<1024) return 128+(ie>>4);
  if(ie<2048) return 160+(ie>>5);
  if(ie<=4096) return 192+(ie>>6);
  return 4096;// vstavka
  printf("\n\a\a Energy overflow.");
  exit(-1);
} 

static void alloc_error()
{ printf("\n\a\a Ошибка при аллокатировании массивов сечений.");exit(-1); }

void alloc_se()
{
  if(nemax1*nu>16383)
  {printf("\n\a\a Слишком большой массив дифференциальных сечений.");exit(-1);}
  stot=new float[nemax1];	if(stot==0)alloc_error();
  ftot=new float[nemax1];	if(ftot==0)alloc_error();
  selas=new float[nemax1];	if(selas==0)alloc_error();
  sex=new float[nemax2];	if(sex==0)alloc_error();
  sion=new float[nemax3];	if(sion==0)alloc_error();
  spelas=new float[nemax1*nu];	if(spelas==0)alloc_error();
  spex=new float[nemax2*nexp];	if(spex==0)alloc_error();
  spion=new float[nemax3*nu];	if(spion==0)alloc_error();
  energy=new float[nemax1];	if(energy==0)alloc_error();
  for(int ne=0;ne<=nemax;ne++)energy[ne]=ntoe(ne);
  sex=sex-ipex;
  sion=sion-ipion;
  spex=spex-ipex*nexp;
  spion=spion-ipion*nu;
}
 
void dealloc_se()
{
  sex=sex+ipex;
  spex=spex+ipex*nexp;
  sion=sion+ipion;
  spion=spion+ipion*nu;
  delete stot;
  delete ftot;
  delete selas;
  delete sex;
  delete sion;
  delete spelas;
  delete spex;
  delete spion;
  delete energy;
} 

void read_se()
{
  int fd=open(file_se,O_RDONLY|O_BINARY);
  if(fd<0){ printf("\n\a\a Ошибка при попытке чтения из файла %s.",file_se); exit(-1); }
  read(fd,stot,4*nemax1);
  read(fd,ftot,4*nemax1);
  read(fd,selas,4*nemax1);
  read(fd,sex+ipex,4*nemax2);
  read(fd,sion+ipion,4*nemax3);
  read(fd,spelas,4*nemax1*nu);
  read(fd,spex+ipex*nexp,4*nemax2*nexp);
  read(fd,spion+ipion*nu,4*nemax3*nu);
  close(fd);
} 

void write_se()
{
  FILE * fp=fopen(file_se,"w"); fclose(fp);
  int fd=open(file_se,O_WRONLY|O_BINARY);
  if(fd==-1)
  { printf("\n\a\a Ошибка при попытке записи в файл %s",file_se); exit(-1); }
  write(fd,stot,4*nemax1);
  write(fd,ftot,4*nemax1);
  write(fd,selas,4*nemax1);
  write(fd,sex+ipex,4*nemax2);
  write(fd,sion+ipion,4*nemax3);
  write(fd,spelas,4*nemax1*nu);
  write(fd,spex+ipex*nexp,4*nemax2*nexp);
  write(fd,spion+ipion*nu,4*nemax3*nu);
  close(fd);
} 

// Вспомогательные переменные и функции:
static int	ne;
static int	nr;
static float	s1;
static float	s2;
static float	s3;
static float	s4;
static float	dx;
static float	dy;
static float*	ps;
static const float 	rio=float(nu-1);
static const float 	rex=float(nexp-1);

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

// ОПРЕДЕЛЕНИЕ ФУНКЦИЙ СЕЧЕНИЙ:
float	stotf( float e)		{ return saprox(stot, e);} 

float	ftotf( float e)		{ return saprox(ftot, e);} 

float	selasf(float e)		{ return saprox(selas,e);} 

float	sexf(  float e)		
{ 
  if(e<pex){printf("\n\a\a e<pex в функции sexf(float e)");exit(-1);}
  return saprox(sex,  e);
} 

float	sionf( float e)		
{ 
  if(e<pion){printf("\n\a\a e<pion в функции sionf(float e)");exit(-1);}
  return saprox(sion, e);
} 

float	spelasf(float e,float r){ return saproxim(spelas,e,r*rio,nu  );} 

int	spexf(  float e,float r)
{ 
  if(e<pex){printf("\n\a\a e<pex в функции spexf(float e,float r)");exit(-1);}
  if(r<0.||r>1.){printf("\n\a\a r<0 или r>1 в функции spexf(float e,float r)");exit(-1);} 

  ne=eton(e);
  if(ne<64) dx=e-float(ne);
  else dx=(e-energy[ne])/(energy[ne+1]-energy[ne]);
  ps=spex+nexp*ne;
  for(int n=0;n<nexp-1;n++)
  {
    r=r-aprox(*ps,*(ps+nexp),dx);
    if(r<0.||e<*(pexim+n+1))break;
    ps++;
  }
  return n;
} 

float	spionf( float e,float r)
{ 
  if(e<pion){printf("\n\a\a e<pion в функции spionf(float e,float r)");exit(-1);}
  if(r<0.||r>1.){printf("\n\a\a r<0 или r>1 в функции spionf(float e,float r)");exit(-1);}
  return saproxim(spion, e,r*rio,nu  );
} 
