// Discharge evolution
// Abramov A.A., 1997

#ifndef __DISCHARG_H
#define __DISCHARG_H

class TDischarge
{
  protected:
	 int status;
	 void Control();
  public:
	 int Status(){return status;}
	 TDischarge();
  // initialization
	 void Scan();//from text file
	 void Read(char*);//from binary file
  // methods
	 void Write(char*);//to binary file
	 void Step();
};

extern TDischarge discharge;// use Scan() and Read() for initialization

#endif