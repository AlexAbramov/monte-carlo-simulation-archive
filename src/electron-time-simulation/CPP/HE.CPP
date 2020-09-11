#include<math.h>
#pragma hdrstop
#include<hese.h>
#include<he.h>

THe he;

THe::THe(char * fn)
{
  alloc_se();
  if(fn==0) read_se();
  else read_se(fn);
  FILE * fp=handle_scan("..\\..\\dat\\conc.dat");
	 fscanf(fp,"%f",&conc);
  fclose(fp);
}

THe::~THe()
{
  dealloc_se();
}

int
THe::LevelMax()
{
  return NEXP-1;
}

float
THe::Pion()
{
  return PION;
}

float
THe::Pex()
{
  return PEX;
}

float
THe::Pex(int i)
{
  return pexi(i);
}

float
THe::Spelas(float e,float r)
{
  return spelasf(e,r);
}

int
THe::Spex(float e,float r)
{
  return spexf(e,r);
}

float
THe::Spion(float e,float r)
{
  return spionf(e,r);
}

float
THe::Selas(float e)
{
  return conc*selasf(e);
}

float
THe::Sex(float e)
{
  return conc*sexf(e);
}

float
THe::Sion(float e)
{
  return conc*sionf(e);
}

float
THe::Stot(float e)
{
  return conc*(selasf(e)+sexf(e)+sionf(e));
}

float
THe::Fex(float e)
{
  return Sex(e)*velf(e);
}

float
THe::Fion(float e)
{
  return Sion(e)*velf(e);
}

float
THe::Ftot(float e)
{
  return Stot(e)*velf(e);
}

float
THe::Fex1(float e)
{
  return KK*Fex(e);
}

float
THe::Fion1(float e)
{
  return KK*Fion(e);
}

float
THe::Ftot1(float e)
{
  return KK*Ftot(e);
}

float
THe::Kper()
{
  return KK;
}

float
THe::Conc()
{
  return conc;
}
