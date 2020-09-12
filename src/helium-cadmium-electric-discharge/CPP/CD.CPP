#include<math.h>
#pragma hdrstop
#include<cd.h>

static const float pion=9.0;
static const float pex=4.0;
static const float kper=59.3;

static float velf(float e){if(e>0.)return sqrt(e);else return 0.;}

TCd cd;

TCd::TCd()
{
  FILE * fp=handle_scan("..\\..\\dat\\conc.dat");
	 float dummy;
	 fscanf(fp,"%f",&dummy);newline(fp);
	 fscanf(fp,"%f",&conc);
    conc*=3.3;
  fclose(fp);
  selas=new TTabFunc("..\\..\\dat\\cdselas.dat");
  sex=new TTabFunc("..\\..\\dat\\cdsex.dat");
  sion=new TTabFunc("..\\..\\dat\\cdsion.dat");
}

TCd::~TCd()
{
  delete selas,sex,sion;
}

float
TCd::Pion()
{
  return pion;
}

float
TCd::Pex()
{
  return pex;
}

float
TCd::Selas(float e)
{
  return conc*selas->Ordinata(e);
}

float
TCd::Sex(float e)
{
  if(e<Pex()) return 0.;
  else return conc*sex->Ordinata(e);
}

float
TCd::Sion(float e)
{
  if(e<Pion()) return 0.;
  return conc*sion->Ordinata(e);
}

float
TCd::Stot(float e)
{
  return Selas(e)+Sex(e)+Sion(e);
}

float
TCd::Fex(float e)
{
  return Sex(e)*velf(e);
}

float
TCd::Fion(float e)
{
  return Sion(e)*velf(e);
}

float
TCd::Ftot(float e)
{
  return Stot(e)*velf(e);
}

float
TCd::Fex1(float e)
{
  return Kper()*Fex(e);
}

float
TCd::Fion1(float e)
{
  return Kper()*Fion(e);
}

float
TCd::Ftot1(float e)
{
  return Kper()*Ftot(e);
}

float
TCd::Kper()
{
  return kper;
}

float
TCd::Conc()
{
  return conc;
}