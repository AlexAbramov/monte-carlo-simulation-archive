//	”“– ‘…—…‰  ’…–€‹› ‚‡“†„… ƒ…‹
//      ( δ®ΰ¬γ«λ ¤«ο α¥η¥­¨© Ά§οβλ ¨§ ΰ ΅®βλ €«ε §®Ά  "δδ¥ªβ¨Ά­λ¥ α¥η¥­¨ο...",†’”,β15,N1,97-107)
//	( §­ η¥­¨ο ―®β¥­ζ¨ «®Ά Ά§οβλ ¨§ α―ΰ Ά®η­¨ª  "”¨§¨η¥αª¨¥ Ά¥«¨η¨­λ",­¥ΰ£® β®¬¨§¤ β,1991)
#include<math.h>
#include<sex.h>

char*	tname[]={"s1","s3","p1","p3","d1","d3"};
// ‡€—… ’…–€‹‚ ‚‡“†„… ‘…’€ €’€ ƒ…‹ 
static float 	nmax=6;
int		tmin[]={2,2,2,2,3,3};
static float	s1_pot[]={ 0., 0., 20.62, 22.92, 23.67, 24.01, 24.19 };
static float 	s3_pot[]={ 0., 0., 19.82, 22.72, 23.59, 23.97, 24.17 };
static float 	p1_pot[]={ 0., 0., 21.22, 23.09, 23.74, 24.05, 24.21 };
static float 	p3_pot[]={ 0., 0., 20.96, 23.01, 23.71, 24.03, 24.20 };
static float 	d1_pot[]={ 0., 0., 0.,    23.07, 23.74, 24.04, 24.21 };
static float 	d3_pot[]={ 0., 0., 0.,    23.07, 23.74, 24.04, 24.21 };
static float 	s1pot(int n){ if(n>nmax) n=nmax; return s1_pot[n]; }
static float 	s3pot(int n){ if(n>nmax) n=nmax; return s3_pot[n]; }
static float 	p1pot(int n){ if(n>nmax) n=nmax; return p1_pot[n]; }
static float 	p3pot(int n){ if(n>nmax) n=nmax; return p3_pot[n]; }
static float 	d1pot(int n){ if(n>nmax) n=nmax; return d1_pot[n]; }
static float 	d3pot(int n){ if(n>nmax) n=nmax; return d3_pot[n]; }
pot*		tpot[]={&s1pot,&s3pot,&p1pot,&p3pot,&d1pot,&d3pot};

// ”“– ‘…—…‰ ‚‡“†„… ƒ…‹
const float rb=13.595, rrb=1./rb, pia2=.878;
const float b1s=.36, b3s=2.24, b3p=10.8, b1d=.330, b3d=1.24;
static float x,p;

static float s1se( int n, float e)	// n - £« Ά­®¥ ªΆ ­β®Ά®¥ η¨α«® γΰ®Ά­ο
{			 		// e - ν­¥ΰ£¨ο [eV]
  e=e*rrb;
  p=s1pot(n)*rrb;
  if(e>p) return 4.*b1s*sqrt(1.-p/e)/(p*e*n*n*n)*pia2;
  else return 0.;
}

static float s3se( int n, float e)
{
  e=e*rrb;
  p=s3pot(n)*rrb;
  if(e>p) 
  { 
    x=e*n;
    return 4.*b3s*sqrt(1.-p/e)/(p*x*x*x)*pia2;
  }
  else return 0.;
}

static float gg( float e)// e[Rb]
{
  const float as=.96, bs=13., ds=.05;
  x=ds*e;
  x=x*x;
  return 1.+as/e*(1.+bs/e)/(1.+x*x);
}

static float p1se( int n, float e)
{
  const float d=2., cn=.65;
  static float fn[]={0.,0.,.2762,.0734,.0307,.0157,.0091};
  static float fnn;
  e=e*rrb;
  p=p1pot(n)*rrb;
  if(e<p) return 0.;
  if(n>6)
  {
    x=n;
    fnn=1.96/(x*x*x);
  }
  else fnn=fn[n];
  x=p/e;
  return 4.*(1.-x*x)*fnn*log(d+cn*(e-p))/(e*p*gg(e))*pia2;
}

static float p3se( int n, float e)
{
  e=e*rrb;
  p=p3pot(n)*rrb;
  x=(e+p)*n;
  if(e>p) return 4.*b3p*sqrt(1.-p/e)/(p*x*x*x)*pia2;
  else return 0.;
}

static float d1se( int n, float e)
{
  e=e*rrb;
  p=d1pot(n)*rrb;
  if(e>p) return 4.*b1d*sqrt(1.-p/e)/(p*(e+p)*n*n*n)*pia2;
  else return 0.;
}

static float d3se( int n, float e)
{
  e=e*rrb;
  p=d3pot(n)*rrb;
  x=e*n;
  if(e>p) return 4.*b3d*sqrt(1.-p/e)/(p*(e+p)*x*x*n)*pia2;
  else return 0.;
}

se*	tse[ntl]={&s1se,&s3se,&p1se,&p3se,&d1se,&d3se};