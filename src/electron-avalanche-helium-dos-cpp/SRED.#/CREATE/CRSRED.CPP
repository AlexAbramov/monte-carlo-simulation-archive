#include<string.h>
#include<stdio.h>
#include<param.h>
const int narg=10;
char* varg[narg];
int main(int narg,char* varg[])
{
  const int npar=13;
  double pp[13];
  FILE * fp=fopen("sred","w");
//  FILE * fpp=fopen("sr2","w");
  fprintf(fp,"field\tvx\tvd\tvr\tv\tex\ter\te");
  fprintf(fp,"\tevx\tfto\tfel\tfex\tfio\talfa");
//  fprintf(fpp,"field\tevx\tfto\tfel\tfex\tfio\talfa");
  for(int nn=1;nn<narg;nn++)
  {
    strcpy(file_param,varg[nn]);
    read_param();
    int i1=imax*2/5;
    int i2=imax*4/5;
    double rii=1./double(i2-i1+1);
    for(int p=0;p<npar;p++)pp[p]=0.;
    for(int i=i1;i<=i2;i++)
    { 
      double rmm=1./mm[i];  
      pp[0]+=vvx[i]*rmm;
      pp[1]+=vvd[i]*rmm;
      pp[2]+=vvr[i]*rmm;
      pp[3]+=vvv[i]*rmm;
      pp[4]+=eex[i]*rmm;
      pp[5]+=eer[i]*rmm;
      pp[6]+=eee[i]*rmm;
      pp[7]+=evx[i]*rmm;
      pp[8]+=fto[i]*rmm;
      pp[9]+=fel[i]*rmm;
      pp[10]+=fex[i]*rmm;
      pp[11]+=fio[i]*rmm;
      pp[12]+=fio[i]/vvd[i];
    }
    for(p=0;p<npar;p++)pp[p]*=rii;
    fprintf(fp,"\n%.0f",field);
    for(p=0;p<13;p++)fprintf(fp,"\t%.3f",pp[p]);
//    fprintf(fpp,"\n%.0f",field);
//    for(p=7;p<13;p++)fprintf(fpp,"\t%.3f",pp[p]);
  }
  return 0;
}
