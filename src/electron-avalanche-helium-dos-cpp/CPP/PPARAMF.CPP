//  ОПРЕДЕЛЕНИЕ ФУНКЦИЙ ДЛЯ РАБОТЫ С МАССИВАМИ
#include<io.h>
#include<fcntl.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pparam.h>
static const int nchar=30;
static const int nhr=20;
double 		conc;		// concentration
double 		f0;		// max electric field
double 		fr; 		// frequence
long int 	nc;		// number of circles
int		imax;		
char		file_param[nchar];	// Имя файла параметров
double 		ftime;		// Время счета

double x;
double vx;
double er;
double ss;
double sss;

double ww;
double dt;
double df;
double uu;
double aa;

void 	print_par(); 			// Печать параметров ячейки на дисплей
void 	fscan_par(char*);		// Чтение параметров ячейки из файла	

double * mas;
double * xx;
double * ff;
double * vvx;	
double * vvd;	
double * vvr;	
double * vvv;	
double * eex;		
double * eer;		
double * eee;		
double * evx;		
double * fto;	
double * fel;	
double * fex;	
double * fio;	

static 	int fd=-1;
static 	void new_line(FILE* fp)// Функция для перехода на новую строку при чтении файла  
{ 
  while(1){ int k=fgetc(fp); if(k==10||k==-1)break;} 
}

void alloc_mas()
{
  mas=new double[imax*8*nmas];
  xx=mas;	
  ff=mas+1*imax;	
  vvx=mas+2*imax;	
  vvd=mas+3*imax;	
  vvr=mas+4*imax;	
  vvv=mas+5*imax;	
  eex=mas+6*imax;		
  eer=mas+7*imax;		
  eee=mas+8*imax;		
  evx=mas+9*imax;		
  fto=mas+10*imax;	
  fel=mas+11*imax;	
  fex=mas+12*imax;	
  fio=mas+13*imax;	
}

void dealloc_mas()
{
  delete mas;
}

void print_par() 	// печать на дисплей
{
  printf("\n conc=%f",conc);
  printf("\n f0=%f",f0);
  printf("\n fr=%f",fr);
  printf("\n nc=%li",nc);
  printf("\n imax=%i",imax);
  printf("\n file_param=%s",file_param);
  printf("\n ftime=%f \n",ftime);
  printf("\n ww=%f",ww);
  printf("\n dt=%f",dt);
  printf("\n df=%f",df);
  printf("\n uu=%f",uu);
  printf("\n aa=%f\n",aa);
}

// Инициализация параметров:
static int fscan=0;
void fscan_par(char * string)	
{
  FILE * fp=fopen(string,"r");
  if(fp==0){ printf("\n\a\a Файл '%s' не найден.",string); exit(-1); }
    fscanf(fp,"%lf",&conc);new_line(fp);  
    fscanf(fp,"%lf",&f0);new_line(fp);  
    fscanf(fp,"%lf",&fr);new_line(fp);  
    fscanf(fp,"%i",&imax);new_line(fp);  
    fscanf(fp,"%s",file_param);
  fclose(fp);
  alloc_mas();
  fscan=1;
  for(int i=0;i<imax*nmas;i++) mas[i]=0.;
}

void read_param() 
{
  if(fscan==0)
  {
    fd=open(file_param,O_RDONLY|O_BINARY);
    if(fd==-1){printf("\n\a\a Ошибка при попытке чтения из файла параметров '%s'",file_param);exit(-1);}
    read(fd,&conc,8);
    read(fd,&f0,8);
    read(fd,&fr,8);
    read(fd,&nc,4);
    read(fd,&imax,2);
    read(fd,&ftime,8);
    alloc_mas();
    read(fd,mas,8*imax*nmas);
    read(fd,&x,8);
    read(fd,&vx,8);
    read(fd,&er,8);
    read(fd,&ss,8);
    read(fd,&sss,8);
    read(fd,&ww,8);
    read(fd,&dt,8);
    read(fd,&df,8);
    read(fd,&uu,8);
    read(fd,&aa,8);
    close(fd);
  }
}

void write_param() // Запись параметров в файл file_param
{
  fd=open(file_param,O_WRONLY|O_BINARY);
  if(fd==-1){printf("\n\a\a Ошибка при попытке записи в файл параметров '%s'",file_param);exit(-1);}
  write(fd,&conc,8);
  write(fd,&f0,8);
  write(fd,&fr,8);
  write(fd,&nc,4);
  write(fd,&imax,2);
  write(fd,&ftime,8);
  write(fd,mas,8*imax*nmas);
  write(fd,&x,8);
  write(fd,&vx,8);
  write(fd,&er,8);
  write(fd,&ss,8);
  write(fd,&sss,8);
  write(fd,&ww,8);
  write(fd,&dt,8);
  write(fd,&df,8);
  write(fd,&uu,8);
  write(fd,&aa,8);
  close(fd);
} 

void print_param() // печать на дисплей
{
  for( int i=0; i<imax; i++)
    printf("\n%i\t%f\t%f",i,xx[i],ff[i]);
  printf("\n");
}