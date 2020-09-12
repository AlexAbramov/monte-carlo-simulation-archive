#include <math.h>
#pragma hdrstop
#include <hydrogen.h>
#include <hse.h>

THydrogen hydrogen;

THydrogen::THydrogen()
{
  pselas=new TTabFunc(HYDROGEN_SELAS_FILE);
  psex=new TTabFunc(HYDROGEN_SEX_FILE);
  psion=new TTabFunc(HYDROGEN_SION_FILE);
  FILE * fp=handle_scan(HYDROGEN_CONC_FILE);
	 fscanf(fp,"%f",&conc); newline(fp);
	 fscanf(fp,"%f",&pex); newline(fp);
	 fscanf(fp,"%f",&pion); newline(fp);
	 fscanf(fp,"%f",&dio);
  fclose(fp);
  alloc_se();
  read_se();
}

THydrogen::~THydrogen()
{
  delete pselas,psion,psex;
  dealloc_se();
}

float
THydrogen::Pion()
{
  return pion;
}

float
THydrogen::Pex()
{
  return pex;
}

float
THydrogen::Spion()
{
  return dio;
}

float
THydrogen::Selas(float e)
{
  return conc*pselas->Ordinata(e);
}

float
THydrogen::Sex(float e)
{
  if(e<Pex()) return 0.;
  return conc*psex->Ordinata(e);
}

float
THydrogen::Sion(float e)
{
  if(e<Pion()) return 0.;
  return conc*psion->Ordinata(e);
}

float
THydrogen::Stot(float e)
{
  return Selas(e)+Sex(e)+Sion(e);
}

float
THydrogen::Felas(float e)
{
  return Selas(e)*velf(e);
}

float
THydrogen::Fex(float e)
{
  return Sex(e)*velf(e);
}

float
THydrogen::Fion(float e)
{
  return Sion(e)*velf(e);
}

float
THydrogen::Ftot(float e)
{
  return Stot(e)*velf(e);
}

float
THydrogen::Fex1(float e)
{
  return KK*Fex(e);
}

float
THydrogen::Fion1(float e)
{
  return KK*Fion(e);
}

float
THydrogen::Ftot1(float e)
{
  return KK*Ftot(e);
}

float
THydrogen::Kper()
{
  return KK;
}

float
THydrogen::Conc()
{
  return conc;
}

float
THydrogen::Spelas(float e,float r)
{
  return spelasf(e,r);
}

