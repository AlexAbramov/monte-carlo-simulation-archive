#include<io.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<rnd.h>
#define max1 (maxr+1)

const int		maxr=15;
static int 		i;
static char		file_rnd[]="random";
static double		rr[max1];
static int 		fd;

void read_rnd()
{
  fd=open(file_rnd,O_RDONLY|O_BINARY);
  if(fd==-1)
  {
    for(i=0;i<=maxr;i++) rr[i]=987654321.0/double(i+1);
    FILE * fp=fopen(file_rnd,"w");
    fclose(fp);
    write_rnd();
  }
  else for(i=0;i<=maxr;i++) read(fd,rr,8*max1); 
  close(fd);
}

void write_rnd()
{
  fd=open(file_rnd,O_WRONLY|O_BINARY);
  if(fd==-1){printf("\n\a\a Ошибка при попытке записи в файл '%s'",file_rnd);exit(-1);}
  for (int i=0;i<=maxr;i++ ) write(fd,rr,8*max1);
  close(fd);
}

double rnd(int i)
{ 
//  if( i<0 || i>maxr ){ printf("\n\a\a Неправильный аргумент для ГСЧ.");exit(-1);}
  static double r;
  r=fmod(16807.*rr[i],2147483647.);
  rr[i]=r;
  r*=.4656612873077392258e-9 ;
  if(r<=0.||r>=1.){ printf("\n\a\a Error: r=%.12lf",r);exit(-1);}
  return r;
}

int max_rnd() { return maxr;}

