// Time statistic counting
// Abramov A.A., 1997

#ifndef __TSTAT_H
#define __TSTAT_H

#ifndef __MYLIB_H
  #include <mylib.h>
#endif

class TTStat
{
  private:
    int status;
	 TSingleArray current;
	 TSingleArray voltage;
  public:
	 TTStat(){status=0;}
	 void Init();
	 TSingleArray& GetCurrent(){ return current;}
	 TSingleArray& GetVoltage(){ return voltage;}
	 void Step();
	 void Read(int);// from binary file
	 void Write(int);// to binary file
	 float GetTime();
 	 void Clear();
};

extern TTStat tstat;

#endif