// Count
// Abramov A.A., 1997

#ifndef __COUNT_H
#define __COUNT_H

class TCount
{
  protected:
	 float df,fmax;
	 int status;
  public:
	 int nlavmax;
	 int Status(){return status;}
	 TCount();
    void Update();
};

extern TCount count;

#endif