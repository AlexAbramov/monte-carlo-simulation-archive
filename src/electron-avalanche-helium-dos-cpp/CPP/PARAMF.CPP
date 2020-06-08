//  ОПРЕДЕЛЕНИЕ ФУНКЦИЙ ДЛЯ РАБОТЫ С МАССИВАМИ
#include<io.h>
#include<fcntl.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<paramf.h>
#define maxchar 30

double		voltage;	// Напряжение
double  	dk;		// dk
double  	field;		// Электрическое поле,после dk
double  	dd; 		// Длина газоразрядного промежутка
long int	nstat;		// Количество статистических электронов
char 		file_param[30];	// Имя файла параметров
long int 	ilav;		// Номер текущего статистического электрона
long int 	istat;		// Номер текущего статистического электрона
double  	ftime;		// Время счета

static double	mas[imax1*nmas];
double * xx=mas;
double * ff=mas+1*imax1;
double * de=mas+2*imax1;
double * mm=mas+3*imax1;	
double * vvx=mas+4*imax1;	
double * vvd=mas+5*imax1;	
double * vvr=mas+6*imax1;	
double * vvv=mas+7*imax1;	
double * eex=mas+8*imax1;		
double * eer=mas+9*imax1;		
double * eee=mas+10*imax1;		
double * evx=mas+11*imax1;		
double * fto=mas+12*imax1;	
double * fel=mas+13*imax1;	
double * fex=mas+14*imax1;	
double * fio=mas+15*imax1;	
static const int index=imax1*fremax1;
static double huge masf[index];
double huge* fre=masf;
static double huge masff[index];
double huge* mdr=masff;

static 	int fd=-1;
static 	void new_line(FILE* fp)// Функция для перехода на новую строку при чтении файла  
{ 
  while(1){ int k=fgetc(fp); if(k==10||k==-1)break;} 
}

void print_par() 	// печать на дисплей
{
  printf("\n voltage=%f",voltage);
  printf("\n dk=%f",dk);
  printf("\n field=%f",field);
  printf("\n dd=%f",dd);
  printf("\n nstat=%li",nstat);
  printf("\n file_param=%s",file_param);
  printf("\n ilav=%li",ilav);
  printf("\n istat=%li",istat);
  printf("\n ftime=%f \n",ftime);
  printf("\n imax=%i",imax);
  printf("\n nmas=%i",nmas);
  printf("\n fremax=%i\n\n",fremax);
}

// Инициализация параметров:
static int fscan=0;
void fscan_par(char * string)	
{
  FILE * fp=fopen(string,"r");
  if(fp==0){ printf("\n\a\a Файл '%s' не найден.",string); exit(-1); }
    fscanf(fp,"%lf",&voltage);new_line(fp);  
    fscanf(fp,"%lf",&dk);new_line(fp);  
    fscanf(fp,"%lf",&field);new_line(fp);  
    fscanf(fp,"%lf",&dd);new_line(fp);  
    fscanf(fp,"%li",&nstat);new_line(fp);  
    fscanf(fp,"%s",file_param);
  fclose(fp);
  ilav=0;
  istat=0;
  ftime=0.;
  fscan=1;
}

void read_param() 
{
  if(fscan==0)
  {
    fd=open(file_param,O_RDONLY|O_BINARY);
    if(fd==-1){printf("\n\a\a Ошибка при попытке чтения из файла параметров '%s'",file_param);exit(-1);}
    read(fd,&voltage,8);
    read(fd,&dk,8);
    read(fd,&field,8);
    read(fd,&dd,8);
    read(fd,&nstat,4);
    read(fd,&ilav,4);
    read(fd,&istat,4);
    read(fd,&ftime,8);
    read(fd,mas,8*imax1*nmas);
    read(fd,masf,8*index);
    read(fd,masff,8*index);
    close(fd);
  }
}

void write_param() // Запись параметров в файл file_param
{
  fd=open(file_param,O_WRONLY|O_BINARY);
  if(fd==-1){printf("\n\a\a Ошибка при попытке записи в файл параметров '%s'",file_param);exit(-1);}
  write(fd,&voltage,8);
  write(fd,&dk,8);
  write(fd,&field,8);
  write(fd,&dd,8);
  write(fd,&nstat,4);
  write(fd,&ilav,4);
  write(fd,&istat,4);
  write(fd,&ftime,8);
  write(fd,mas,8*imax1*nmas);
  write(fd,masf,8*index);
  write(fd,masff,8*index);
  close(fd);
} 

void print_param() // печать на дисплей
{
  for( int i=0; i<=imax; i++)
    printf("\n %8i  %8.3f %8.3f %8.3f %8.3f",i,xx[i],ff[i],de[i],mm[i]);
  printf("\n");
}

double xtoe(int i,double x)
{
  if(i<0||i>=imax){ printf("\n\a\a Error1 in xtoe()"); exit(-1); }
  static double dx,df;
  dx=xx[i+1]-xx[i];
  if(x<0.||x>dx){ printf("\n\a\a Error2 in xtoe()"); exit(-1); }
  df=ff[i+1]-ff[i];
  if(df==0.)return x*ff[i];
  else return x*( ff[i]+df*x/(dx+dx) );
}

double etox(int i,double e)
{
  static double a,b,x,dx;
  if(i<0||i>=imax){ printf("\n\a\a Error1 in etox()"); exit(-1); }
  b=ff[i];
  a=b-ff[i+1];
  dx=xx[i+1]-xx[i];
  if(a==0.)x=e/b;
  else 
  { 
    a=a/dx;
    x=(sqrt(b*b+a*(e+e))-b)/a;
  }  
  if(x<0.||x>dx){ printf("\n\a\a Error2 in etox()"); exit(-1); }
  return x;
}

double etof(int i,double e)
{
  static double a,b,x,dx;
  if(i<0||i>=imax){ printf("\n\a\a Error1 in etof()  %i",i); exit(-1); }
  b=ff[i];
  a=b-ff[i+1];
  if(a==0.)return b;
  dx=xx[i+1]-xx[i];
  a=a/dx;
  return sqrt(b*b+a*(e+e));
}