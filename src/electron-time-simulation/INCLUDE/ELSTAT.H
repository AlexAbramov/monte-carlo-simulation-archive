// Electron statistic counting
// Abramov A.A., 1997

#ifndef __ELSTAT_H
#define __ELSTAT_H

#ifndef __MYLIB_H
  #include <mylib.h>
#endif

class TElStat
{
  private:
	 int tsize,esize;
	 TSingleArray stat;// statistical weight
	 TSingleArray energy;// mean energy
	 TSingleArray vdr;// drift velosity
	 TSingleArray evx;// <e*vx>
	 TSingleArray fex;// frequance of excited collisions
	 TSingleArray fio;// frequance of ionising collisions
	 TDoubleArray fre;// energy distribution function
	 TSingleArray buf;
	 TDoubleArray buffer;
	 TSingleArray bfr;
	 TSingleArray& InitBuf(TSingleArray&);
	 TSingleArray& InitBuf1(TSingleArray&);
  public:
	 TElStat(){tsize=0;esize=0;}
	 void Init();
	 TSingleArray& GetEnergy(){ return InitBuf(energy);}
	 TSingleArray& GetVdr(){ return InitBuf(vdr);}
	 TSingleArray& GetEvx(){ return InitBuf(evx);}
	 TSingleArray& GetFex(){ return InitBuf(fex);}
	 TSingleArray& GetFio(){ return InitBuf(fio);}
	 TSingleArray& GetVdr1(){ return InitBuf1(vdr);}
	 TSingleArray& GetEvx1(){ return InitBuf1(evx);}
	 TSingleArray& GetFex1(){ return InitBuf1(fex);}
	 TSingleArray& GetFio1(){ return InitBuf1(fio);}
	 TDoubleArray& GetFre();
	 TSingleArray& GetFre1(int);
	 void Count(int,float,float);// args: i,vx,e
	 void Read(int);// from binary file
	 void Write(int);// to binary file
};

extern TElStat elstat;

#endif