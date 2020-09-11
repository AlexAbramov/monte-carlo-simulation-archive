#include<math.h>
#include<mylib.h>
#include<hesex.h>

// THRESHOLD ARRAYS
const int ii=6;
const int jj=7;
static char*	type_name[ii]={"s1","s3","p1","p3","d1","d3"};
static int	level_min[ii]={2,2,2,2,3,3};
static float	s1_pot[jj]={ 0., 0., 20.62, 22.92, 23.67, 24.01, 24.19 };
static float s3_pot[jj]={ 0., 0., 19.82, 22.72, 23.59, 23.97, 24.17 };
static float p1_pot[jj]={ 0., 0., 21.22, 23.09, 23.74, 24.05, 24.21 };
static float p3_pot[jj]={ 0., 0., 20.96, 23.01, 23.71, 24.03, 24.20 };
static float d1_pot[jj]={ 0., 0., 0.,    23.07, 23.74, 24.04, 24.21 };
static float d3_pot[jj]={ 0., 0., 0.,    23.07, 23.74, 24.04, 24.21 };

// THRESHOLD FUNCTIONS
const int imax=ii-1;
const int jmax=jj-1;
static void controlx(int i)
{
  if(i<0||i>imax) error_message("THeSex: Argument i out of range");
}
static void control(int i,int j)
{
  controlx(i);
  if(j<level_min[i]) error_message("THeSex: Argument j out of range");
}
static float s1pot(int j){ control(0,j); return s1_pot[j]; }
static float s3pot(int j){ control(1,j); return s3_pot[j]; }
static float p1pot(int j){ control(2,j); return p1_pot[j]; }
static float p3pot(int j){ control(3,j); return p3_pot[j]; }
static float d1pot(int j){ control(4,j); return d1_pot[j]; }
static float d3pot(int j){ control(5,j); return d3_pot[j]; }
typedef float tpot(int);
static tpot * pot[ii]={&s1pot,&s3pot,&p1pot,&p3pot,&d1pot,&d3pot};

// SEQUATIONS
const float rb=13.595, rrb=1./rb, pia2=.878;
const float b1s=.36, b3s=2.24, b3p=10.8, b1d=.330, b3d=1.24;
static float x,p;
static float s1se( int n, float e)	// n - main quantum number of level
{			 							// e - energy [eV]
  e*=rrb;
  p=s1pot(n)*rrb;
  if(e>p) return 4.*b1s*sqrt(1.-p/e)/(p*e*n*n*n)*pia2;
  else return 0.;
}
static float s3se( int n, float e)
{
  e*=rrb;
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
  x*=x;
  return 1.+as/e*(1.+bs/e)/(1.+x*x);
}
static float p1se( int n, float e)
{
  const float d=2., cn=.65;
  static float fn[]={0.,0.,.2762,.0734,.0307,.0157,.0091};
  float fnn;
  e*=rrb;
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
  e*=rrb;
  p=p3pot(n)*rrb;
  x=(e+p)*n;
  if(e>p) return 4.*b3p*sqrt(1.-p/e)/(p*x*x*x)*pia2;
  else return 0.;
}
static float d1se( int n, float e)
{
  e*=rrb;
  p=d1pot(n)*rrb;
  if(e>p) return 4.*b1d*sqrt(1.-p/e)/(p*(e+p)*n*n*n)*pia2;
  else return 0.;
}
static float d3se( int n, float e)
{
  e*=rrb;
  p=d3pot(n)*rrb;
  x=e*n;
  if(e>p) return 4.*b3d*sqrt(1.-p/e)/(p*(e+p)*x*x*n)*pia2;
  else return 0.;
}
typedef float tse(int,float);
static tse * se[ii]={&s1se,&s3se,&p1se,&p3se,&d1se,&d3se};


// CLASS MEMBERS
THeSex::THeSex()
{}

float
THeSex::Threshold(int i,int j)
{
  control(i,j);
  return pot[i](j);
}

float
THeSex::Sequation(int i,int j,float e)
{
  control(i,j);
  return se[i](j,e);
}

float
THeSex::Sequation(int j0,float e,int k)
{
  float s=0.;
  for(int j=j0;j<=j0+k;j++)
  for(int i=0;i<ii;i++)
  {
	 s+=Sequation(i,j,e);
  }
  return s;
}


char*
THeSex::TypeName(int i)
{
  controlx(i);
  return type_name[i];
}

int
THeSex::TypeMax()
{
  return imax;
}

int
THeSex::LevelMin(int i)
{
  controlx(i);
  return level_min[i];
}

int
THeSex::LevelMax()
{
  return jmax;
}
