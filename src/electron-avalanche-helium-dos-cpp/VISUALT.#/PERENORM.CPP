#include<conio.h>
#include<stdio.h>
const int narg=2;
char* varg[2];
int main(int narg,char* varg[])
{
  FILE * fp=fopen(varg[1],"r");
    int i,imax,jmax;
    fscanf(fp,"%i%i",&imax,&jmax);  
    //printf("\n %i %i",imax,jmax);
    const int ichar=10;
    char * name=new char[imax*ichar];
    float * ff=new float[imax*jmax];
    for( i=0; i<imax; i++)
    { 
      fscanf(fp,"%s",name+i*ichar); 
      //printf("\n %s",name+i*ichar); 
    }
    for( int j=0; j<jmax; j++)for( i=0; i<imax; i++) 
    { 
      fscanf(fp,"%f",ff+j*imax+i); 
      //printf(" %f",*(ff+j*imax+i)); 
    }  
  fclose(fp);
  float * nkf=new float[imax];
  nkf[0]=1.;
  for(i=1; i<imax; i++)nkf[i]=1./ff[imax*jmax-imax+i];
  fp=fopen("outfile","w");
   fprintf(fp,"%i\n%i\n",imax,jmax);
   for( i=0; i<imax; i++)
    { 
      fprintf(fp,"%s\t",name+i*ichar); 
      //printf("\n %s",name+i*ichar); 
    }
    for( j=0; j<jmax; j++)
    {
      fprintf(fp,"\n");	    
      for( i=0; i<imax; i++) 
      { 
        fprintf(fp,"%.3f\t",*(ff+j*imax+i)*nkf[i]); 
        //printf(" %f",*(ff+j*imax+i)); 
      }  
    }
  fclose(fp);
  return 0;
}