#include <cstring.h>
#include <stdio.h>
#include <conio.h>
#pragma hdrstop
#include <mylib.h>
#include <param.h>
#include <elstat.h>
#include "discharg.h"

void print(FILE* fp,TSingleArray& sar)
{
  int size=sar.Size();
  fprintf(fp,"\nsize=%i\n",size);
  for(int i=0;i<size;i++) fprintf(fp,"%9.3f ",sar[i]);
}

void print(FILE* fp,TDoubleArray& dar)
{
  int xsize=dar.XSize();
  int ysize=dar.YSize();
  fprintf(fp,"\nxsize=%i",xsize);
  fprintf(fp,"\nysize=%i",ysize);
  for(int j=0;j<ysize;j++)
  {
	 fprintf(fp,"\n");
	 for(int i=0;i<xsize;i++) fprintf(fp,"%9.3f ",dar[j][i]);
  }
}

void convert(string s)
{
  discharge.Read((char*)s.c_str());
  s[s.length()-1]='t';
  if(param.nlav<=0)
  {
	 printf("\n No statistical information");
	 return;
  }
  FILE * fp=fopen((char*)s.c_str(),"w");
  if(fp==0) error_message("Can't open file");
  fprintf(fp,"\n DISCHARGE CONFIGURATION:\n");
  param.Print(fp);
  if(elstat.total_nion>1.)
  {
	 fprintf(fp,"\n\n\n IONIZATIONS:");
	 float rnion=1./elstat.total_nion;
	 fprintf(fp,"\n nion=%.0f",elstat.total_nion);
	 float nlav=param.nlav;
	 fprintf(fp,"\n nlav=%.0f",nlav);
	 fprintf(fp,"\n nion/nlav=%.3f",elstat.total_nion/nlav);
	 fprintf(fp,"\n <time>[mksec]=%.3f",elstat.total_time*rnion);
	 fprintf(fp,"\n <s>[sm]=%.3f",elstat.total_s*rnion);
	 fprintf(fp,"\n <sx>[sm]=%.3f",elstat.total_sx*rnion);
	 fprintf(fp,"\n <x>[sm]=%.3f",elstat.total_x*rnion);
	 fprintf(fp,"\n\nTotalTime");print(fp,elstat.GetTotalTime());
	 fprintf(fp,"\n\nTotalS");print(fp,elstat.GetTotalS());
	 fprintf(fp,"\n\nTotalSx");print(fp,elstat.GetTotalSx());
	 fprintf(fp,"\n\nTotalX");print(fp,elstat.GetTotalX());

  }
  TSingleArray xcoord(param.xsize);
  for(int i=0;i<xcoord.Size();i++) xcoord[i]=i*param.dx;
  fprintf(fp,"\n\n\n STATISTICAL INFORMATION:");
  fprintf(fp,"\n\nCoordinate");print(fp,xcoord);
  fprintf(fp,"\n\nDensity");print(fp,elstat.GetDensity());
  fprintf(fp,"\n\n<v>");print(fp,elstat.GetVel());
  fprintf(fp,"\n\nvdr");print(fp,elstat.GetVdr());
  fprintf(fp,"\n\n<e>");print(fp,elstat.GetEnergy());
  fprintf(fp,"\n\n<er>");print(fp,elstat.GetEr());
  fprintf(fp,"\n\n<e*vx>");print(fp,elstat.GetEvx());
  fprintf(fp,"\n\n<e*e>");print(fp,elstat.GetEe());
  fprintf(fp,"\n\nfel");print(fp,elstat.GetFel());
  fprintf(fp,"\n\nfex");print(fp,elstat.GetFex());
  fprintf(fp,"\n\nfio");print(fp,elstat.GetFio());
  fprintf(fp,"\n\ntest0");print(fp,elstat.GetTest0());
  fprintf(fp,"\n\ntest1");print(fp,elstat.GetTest1());
  fprintf(fp,"\n\ntest2");print(fp,elstat.GetTest2());
  fprintf(fp,"\n\ntest3");print(fp,elstat.GetTest3());
  fprintf(fp,"\n\ntest4");print(fp,elstat.GetTest4());
  fprintf(fp,"\n\ntest5");print(fp,elstat.GetTest5());
  fprintf(fp,"\n\ntest6");print(fp,elstat.GetTest6());
  fprintf(fp,"\n\ntest7");print(fp,elstat.GetTest7());
  fprintf(fp,"\n\ntest8");print(fp,elstat.GetTest8());
  fprintf(fp,"\n\ntest9");print(fp,elstat.GetTest9());
  fprintf(fp,"\n\ntest10");print(fp,elstat.GetTest10());
  fprintf(fp,"\n\ntest11");print(fp,elstat.GetTest11());
  fprintf(fp,"\n\ntest12");print(fp,elstat.GetTest12());
  fprintf(fp,"\n\ntest13");print(fp,elstat.GetTest13());
  fprintf(fp,"\n\ntest14");print(fp,elstat.GetTest14());
  fprintf(fp,"\n\ntest15");print(fp,elstat.GetTest15());
  fprintf(fp,"\n\ntest16");print(fp,elstat.GetTest16());
  fprintf(fp,"\n\ntest17");print(fp,elstat.GetTest17());
  fprintf(fp,"\n\ntest18");print(fp,elstat.GetTest18());
  fprintf(fp,"\n\ntest19");print(fp,elstat.GetTest19());
  fprintf(fp,"\n\n\n EEDF");print(fp,elstat.GetFre());
  fprintf(fp,"\n\n\n EEADF");print(fp,elstat.GetFrem());
  fclose(fp);
  printf("\n Text file created.");
}

const int narg=2;
char * varg[narg];
int main(int narg,char* varg[])
{
  string s(varg[1]);
  if(s.is_null()!=1&&s.contains(".ele")==1) convert(s);
  else printf("\n First argument must be a file with .ele extention");
  printf("\n Press any key to exit.");
  getch();
  return 0;
}
