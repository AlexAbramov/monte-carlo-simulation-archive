// 		‘‡„€ˆ… ”€‰‹‚ Œ€‘‘ˆ‚‚ ‘…—…ˆ‰
#include<process.h>
#include<conio.h>
#include<se.h>
#include<selas.h>
#include<sex.h>
#include<sion.h>
#include<mygraph.h>
#include<math.h>
#include<newline.hpp>
static float deaprox(float,float*,float=0.);
static float deaprox(float pot,float *ps,float r)
{
  float de=pot-int(pot);
  return r+(r-*ps)*de/(1.-de);  
}
int main()
{
  const float rnu=1./float(nu-1);
  float r;
  float e;  
  float pp[10];
  float * ps;
  int i,j,t,m,n;
  
  system("..\\edit.com ..\\dat\\create.dat");

  initgraph();
  TGraph 	graph("..\\gdat\\graph.dat");
  TMessage 	message("..\\gdat\\message.dat");
  TMessage 	message1("..\\gdat\\message1.dat");
  TMessage 	message2("..\\gdat\\message2.dat");
  TMessage 	message3("..\\gdat\\message3.dat");

  alloc_se();

// ‘—ˆ’›‚€ˆ… „€›•
  FILE* fp=fopen("..\\dat\\create.dat","r");
  if(fp==0){ printf("\n\a\a ” ©« 'create.dat' ­¥ ­ ©¤¥­."); exit(-1); }
    int delay;		
    fscanf(fp,"%i",&delay);newline(fp);
    float emaxg;
    fscanf(fp,"%f",&emaxg);newline(fp);
    int kit;
    fscanf(fp,"%i",&kit);newline(fp);
    int nlmax;
    fscanf(fp,"%i",&nlmax);newline(fp);
    int* mm=new int[nexp];
    int* mmm=new int[nexp*ntl];
    for(j=0;j<nexp;j++)
    { 
      fscanf(fp,"%i",mm+j);
      for(t=0;t<ntl;t++)fscanf(fp,"%i",mmm+j*ntl+t);
    }
  fclose(fp);
  if(emaxg>emax)emaxg=emax;
  int imaxg=eton(emaxg);

// ‘…—…ˆ… ““ƒƒ ‘“„€…ˆŸ
  for(i=0;i<=nemax;i++)
  { 
    selas[i]=selasfn(energy[i]);
  }
  char textx[]="Energy, [eV]";
  graph.show(imaxg,energy,selas,textx,"Elastic sequation.");

// „ˆ””……–ˆ€‹œ… ‘…—…ˆ… ““ƒƒ ‘“„€…ˆŸ
  for(i=0;i<=nemax;i++)
  {
    e=energy[i];
    //printf("\n i=%i  e=%f",i,e);
    ps=spelas+i*nu;
    *ps=0.;
    for(j=1;j<nu-1;j++)
    { 
      r=float(j)*rnu;
      *(ps+j)=spelasr(kit,e,r);
    }
    *(ps+nu-1)=pi;
  }
  if(delay==1)message.show();

// ‚ˆ‡“€‹ˆ‡€–ˆŸ ’…–ˆ€‹‚ ‚‡“†„…ˆŸ
  TPot pot("..\\gdat\\pot.dat");
  for(t=0;t<ntl;t++)  
  {
    i=0;
    for(n=tmin[t];n<=6;n++)
    {
      pp[i]=tpot[t](n);
      i++;
    }
    pp[i]=-1.;
    pot.show(tmin[t],pp,tname[t]);
  }
// „ˆ””……–ˆ€‹œ›… ‘…—…ˆŸ ‘“„€…ˆŸ ‚‡“†„…ˆŸ
  for(i=ipex1;i<=nemax;i++)
  {  
    e=energy[i];
    for(j=0;j<nexp;j++)
    {
      ps=spex+nexp*i+j;
      *ps=0.;
      for(t=0;t<ntl;t++)if(mmm[ntl*j+t])
        *ps=*ps+tse[t](mm[j],e);
    }
  }
  for(i=ipex1;i<=nemax;i++) 
  {
    e=energy[i];
    ps=spex+nexp*i+nexp-1;
    for(j=mm[nexp-1]+1;j<=nlmax;j++)
    {
      for(t=0;t<ntl;t++)if(mmm[ntl*(nexp-1)+t])
        *(ps+t)=*(ps+t)+tse[t](j,e);
    }  
  }
  for(j=0;j<nexp;j++)//show spex
  {
    for(i=ipex1;i<=nemax;i++)sex[i]=spex[nexp*i+j];
    char texty[20];
    sprintf(texty,"Exitation - %i",j);
    if(delay==1)message.show();
    graph.show( imaxg-ipex1,energy+ipex1,sex+ipex1,textx,texty);
  };
  if(delay==1)message.show();

// ‘…—…ˆ… ‘“„€…ˆŸ ‚‡“†„…ˆŸ
  for(i=ipex1;i<=nemax;i++)
  {
    sex[i]=0.;
    for(j=0;j<nexp;j++)sex[i]=sex[i]+spex[nexp*i+j];
  }
  graph.show(imaxg-ipex1,energy+ipex1,sex+ipex1,textx,"Exitation.");//show sex
    
// ‘…—…ˆ… ‘“„€…ˆŸ ˆˆ‡€–ˆˆ
  for(i=ipion1;i<=nemax;i++)
  { 
    sion[i]=sionfn(energy[i]);
  }
  if(delay==1)message.show();
  graph.show(imaxg-ipion1,energy+ipion1,sion+ipion1,textx,"Ionization.");

// „ˆ””……–ˆ€‹œ… ‘…—…ˆ… ‘“„€…ˆŸ ˆˆ‡€–ˆˆ
  for(i=ipion1;i<=nemax;i++)
  {
    e=energy[i];
    ps=spion+i*nu;
    *ps=0.;
    for(j=1;j<nu-1;j++)
    { 
      r=float(j)*rnu*.5;
      *(ps+j)=spionr(kit,e,r);
    }
    *(ps+nu-1)=.5;
  }
  
// ‘“ŒŒ€… ‘…—…ˆ… ‚‘…• –…‘‘‚
  for(i=0;i<=ipex;i++)stot[i]=selas[i];
  for(i=ipex1;i<=ipion;i++)stot[i]=selas[i]+sex[i];
  for(i=ipion1;i<=nemax;i++)stot[i]=selas[i]+sex[i]+sion[i];
  if(delay==1)message.show();
  graph.show(imaxg,energy,stot,textx,"Total sequation,[A*A].");


// ……Œˆ‚Š€ Œ€‘‘ˆ‚‚
  for(i=0;i<=nemax;i++)selas[i]=selas[i]/stot[i];
  for(i=ipex1;i<=nemax;i++)for(j=0;j<nexp;j++)
    spex[i*nexp+j]=spex[i*nexp+j]/sex[i];
  for(i=ipex1;i<=nemax;i++)sex[i]=sex[i]/stot[i];
  for(i=ipion1;i<=nemax;i++)sion[i]=sion[i]/stot[i];


// “—…’ Š€…‚›• ””…Š’‚
  ps=sion+ipion;
  *ps=deaprox(pion,ps+1);//i=ipion
  ps=spion+ipion*nu;
  for(j=0;j<nu;j++)//i=ipion
  { 
    *(ps+j)=*(ps+j+nu);
    //r=float(j)*rnu;
    //*(ps+j)=deaprox(pion,ps+j+nu,r);
  }
  ps=sex+ipex;
  *ps=deaprox(pex,ps+1);
  ps=spex+ipex*nexp;
  for(j=0;j<nexp;j++) *(ps+j)=0.;
  *ps=deaprox(pexi(1),ps+nexp,1.);

  if(message1.show()==121)
    for(i=0;i<=nemax;i++)stot[i]=3.3*stot[i];

// FTOT
  for(i=0;i<=nemax;i++)ftot[i]=stot[i]*sqrt(energy[i]);
  graph.show(imaxg,energy,ftot,textx,"ftot");
  if(delay==1)message.show();

  if(message2.show()==121)
  {
// ‡€ˆ‘œ Œ€‘‘ˆ‚‚ ‘…—…ˆ‰ ‚ ’…Š‘’‚Œ ‚ˆ„…
  fp=fopen("se.txt","w");
    fprintf(fp,"\n  ‡­ ç¥­¨ï á¥ç¥­¨© ®á­®¢­ëå ¯à®æ¥áá®¢.");
    fprintf(fp,"\n  n, energy[eV], stot[A*A], selas[%], sex[%], sio[%]");
    for(i=0;i<ipex;i++)
      fprintf(fp,"\n %3i %9.1f %9.5f",
      		     i,energy[i],stot[i]);
    for(i=ipex;i<ipion;i++)
      fprintf(fp,"\n %3i %9.1f %9.5f %9.5f %9.5f",
       		     i,energy[i],stot[i],selas[i],sex[i]);
    for(i=ipion;i<=nemax;i++)
      fprintf(fp,"\n %3i %9.1f %9.5f %9.5f %9.5f %9.5f",
                     i,energy[i],stot[i],selas[i],sex[i],sion[i]);
  fclose(fp);    
  fp=fopen("spex.txt","w");
    fprintf(fp,"\n  ‚ª« ¤ ®¡®¡é¥­­ëå ãà®¢­¥© ¢ ¯®«­®¥ á¥ç¥­¨¥ ¢®§¡ã¦¤¥­¨ï.");
    fprintf(fp,"\n  n, energy[eV], level1, level2, ...");
    for(i=ipex;i<=nemax;i++)for(j=0;j<nexp;j++)
    {
      fprintf(fp,"\n %3i  %4.0f   ",
       		     i,energy[i]);
      for(j=0;j<nexp;j++)fprintf(fp,"%0.5f  ",spex[i*nexp+j]);
    }
  fclose(fp);    
  fp=fopen("spelas.txt","w");
    fprintf(fp,"\n  ‡­ ç¥­¨ï ã£«®¢ à §¡à®á  ¤«ï ã¯àã£®£® á®ã¤ à¥­¨ï ¯à¨ á«ãç ©­®© ¢ë¡®àª¥.");
    fprintf(fp,"\n  n, energy[eV], alfa1, alfa2, ...");
    for(i=0;i<=nemax;i++)
    {
      fprintf(fp,"\n %3i  %4.0f   ",
       		     i,energy[i]);
      for(j=0;j<nu;j++)fprintf(fp,"%6.4f  ",spelas[i*nu+j]);
    }
  fclose(fp);    
  fp=fopen("spion.txt","w");
    fprintf(fp,"\n  ‡­ ç¥­¨ï ¤®«¨ â¥àï¥¬®© í­¥à£¨¨ ¢ ¯à®æ¥áá¥ ¨®­¨§ æ¨¨ ¯à¨ á«ãç ©­®© ¢ë¡®àª¥.");
    fprintf(fp,"\n  n, energy[eV], de1, de2, ...");
    for(i=ipion;i<=nemax;i=i+1)
    {
      fprintf(fp,"\n %3i  %4.0f   ",
       		     i,energy[i]);
      for(j=0;j<nu;j++)fprintf(fp,"%6.4f  ",spion[i*nu+j]);
    }
  fclose(fp);    
  }

  if(message3.show()==121)
  {
// ‡€ˆ‘œ Œ€‘‘ˆ‚‚ ‘…—…ˆ‰ ‚ ˆ€Œ ‚ˆ„…
    write_se();
  }

  dealloc_se();
  delete mm,mmm;
  closegraph();
  return 0;
}
