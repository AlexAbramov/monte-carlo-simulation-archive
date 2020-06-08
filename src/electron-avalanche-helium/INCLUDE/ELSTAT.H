// Statistic counting for electrons
// Abramov A.A., 1997

#ifndef __ELSTAT_H
#define __ELSTAT_H

#ifndef __MYLIB_H
  #include <mylib.h>
#endif

#define __MAXPARAM

class TElStat
{
  private:
	 int xsize,esize;
	 TSingleArray stat;	// statistic weight
	 TSingleArray energy;// mean energy
	 TSingleArray vdr;	// drift velocity
	 TSingleArray vel;	// velocity
	 TSingleArray evx;	// <e*vx>
	 TSingleArray er;		// <er>
	 TSingleArray ee;		// <ee>
	 TSingleArray fel;	// frequency of elastic collisions
	 TSingleArray fex;	// frequency of excited collisions
	 TSingleArray fio;	// frequency of ionized collisions
	 TDoubleArray fre;	// energy distribution function
	 TSingleArray buf;
#ifdef __MAXPARAM
	 TSingleArray test0;
	 TSingleArray test1;
	 TSingleArray test2;
	 TSingleArray test3;
	 TSingleArray test4;
	 TSingleArray test5;
	 TSingleArray test6;
	 TSingleArray test7;
	 TSingleArray test8;
	 TSingleArray test9;
	 TSingleArray test10;
	 TSingleArray test11;
	 TSingleArray test12;
	 TSingleArray test13;
	 TSingleArray test14;
	 TSingleArray test15;
	 TSingleArray test16;
	 TSingleArray test17;
	 TSingleArray test18;
	 TSingleArray test19;
	 int msize;
	 TDoubleArray frem;	// energy and angular distribution function
	 TDoubleArray buffer1;
	 float rdt,rdl;
	 int tsize;
	 TSingleArray TotalTime;
	 TSingleArray TotalS;
	 TSingleArray TotalSx;
	 TSingleArray TotalX;
	 TSingleArray buf2;
	 TSingleArray& InitBuf2(TSingleArray&);
#endif
	 TDoubleArray buffer;
	 TSingleArray bfr;
	 TSingleArray& InitBuf(TSingleArray&);
	 TSingleArray& InitBuf1(TSingleArray&);
  public:
	 TElStat();
	 void Init();
	 TSingleArray& GetDensity();
	 TSingleArray& GetEnergy(){ return InitBuf(energy);}
	 TSingleArray& GetVdr(){ return InitBuf(vdr);}
	 TSingleArray& GetVel(){ return InitBuf(vel);}
	 TSingleArray& GetEvx(){ return InitBuf(evx);}
	 TSingleArray& GetEr(){ return InitBuf(er);}
	 TSingleArray& GetEe(){ return InitBuf(ee);}
	 TSingleArray& GetFel(){ return InitBuf(fel);}
	 TSingleArray& GetFex(){ return InitBuf(fex);}
	 TSingleArray& GetFio(){ return InitBuf(fio);}
	 TSingleArray& GetVel1(){ return InitBuf1(vel);}
	 TSingleArray& GetVdr1(){ return InitBuf1(vdr);}
	 TSingleArray& GetEvx1(){ return InitBuf1(evx);}
	 TSingleArray& GetFel1(){ return InitBuf1(fel);}
	 TSingleArray& GetFex1(){ return InitBuf1(fex);}
	 TSingleArray& GetFio1(){ return InitBuf1(fio);}
#ifdef __MAXPARAM
	 TSingleArray& GetTest0(){ return InitBuf(test0);}
	 TSingleArray& GetTest1(){ return InitBuf(test1);}
	 TSingleArray& GetTest2(){ return InitBuf(test2);}
	 TSingleArray& GetTest3(){ return InitBuf(test3);}
	 TSingleArray& GetTest4(){ return InitBuf(test4);}
	 TSingleArray& GetTest5(){ return InitBuf(test5);}
	 TSingleArray& GetTest6(){ return InitBuf(test6);}
	 TSingleArray& GetTest7(){ return InitBuf(test7);}
	 TSingleArray& GetTest8(){ return InitBuf(test8);}
	 TSingleArray& GetTest9(){ return InitBuf(test9);}
	 TSingleArray& GetTest10(){ return InitBuf(test10);}
	 TSingleArray& GetTest11(){ return InitBuf(test11);}
	 TSingleArray& GetTest12(){ return InitBuf(test12);}
	 TSingleArray& GetTest13(){ return InitBuf(test13);}
	 TSingleArray& GetTest14(){ return InitBuf(test14);}
	 TSingleArray& GetTest15(){ return InitBuf(test15);}
	 TSingleArray& GetTest16(){ return InitBuf(test16);}
	 TSingleArray& GetTest17(){ return InitBuf(test17);}
	 TSingleArray& GetTest18(){ return InitBuf(test18);}
	 TSingleArray& GetTest19(){ return InitBuf(test19);}
	 TSingleArray& GetTotalTime(){ return InitBuf2(TotalTime);}
	 TSingleArray& GetTotalS(){ return InitBuf2(TotalS);}
	 TSingleArray& GetTotalSx(){ return InitBuf2(TotalSx);}
	 TSingleArray& GetTotalX(){ return InitBuf2(TotalX);}
	 TDoubleArray& GetFrem();
	 float total_nion;
	 float total_time;
	 float total_s;
	 float total_sx;
	 float total_x;
	 void Add(float,float,float,float);// args: time,s,sx,x
#endif
	 TDoubleArray& GetFre();
	 TSingleArray& GetFre1(int);// arg: i
	 void Count(int,float,float);// args: i,vx,e
	 void Read(int);// from binary file
	 void Write(int);// to binary file
};

extern TElStat elstat;

#endif