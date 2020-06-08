// Two-dimensional electric field ( x-component )
// Stationary case
// Abramov A.A., 1997

#ifndef __FIELD_H
#define __FIELD_H

#ifndef __MYLIB_H
  #include <mylib.h>
#endif

class TField
{
  protected:
	 TSingleArray buf;
	 TSingleArray buf1;
	 TDoubleArray ff;
	 TDoubleArray cio;
	 int status;
	 void Control();
	 void FieldStep1(float*,float*);
	 void FieldStep();
	 float CioStep1(float*,float*);
	 void CioStep();
	 float g0,f1;// for gamma function
	 float rz,kup,kdown;
	 float Current(float); //return current; arg: voltage
	 float Current1(float,float*); //return ion current density; arg: voltage, cio1
  public:
	 float Gamma(float);// return gamma; arg: field[V/sm]
	 float Gamma(int);// return gamma; arg: j
	 int Status(){ return status;}
	 TField();
	 ~TField(){}
	 void Init();// from param
	 float Get(int,int);// return ff[j][i]; args: j,i
	 float Get(float,int);// return ff[y][i]; args: y,i
	 TSingleArray & GetBuf(){ return buf;}
	 TSingleArray & GetBuf1(){ return buf1;}
	 TDoubleArray & GetField(){ return ff;}
	 TDoubleArray & GetCio(){ return cio;}
	 void CioAdd(int,float,float);// add ion statistic (i,y,dcio)
	 float GetBuf(int j){return buf[j];}
	 void Read(int);
	 void Write(int);
	 float CioOut();
	 float KoefUp(){return kup;}
	 float KoefDown(){return kdown;}
	 void Step();
};

extern TField field;// use Init() for object initialisation

#endif
