//	’€‰Œ…
#include<dos.h>
#include<timer.h>
static time time0,time1;
static date date0,date1;
void start_timer()
{
  gettime(&time0); 
  getdate(&date0);
}
float stop_timer()
{
  gettime(&time1); 
  getdate(&date1);
  static float ftime;
  ftime=(time1.ti_hund-time0.ti_hund)/6000. +
        (time1.ti_sec-time0.ti_sec)/60. +
        (time1.ti_min-time0.ti_min)+
        (time1.ti_hour-time0.ti_hour)*60.;
  if(date1.da_day!=date0.da_day) ftime=ftime+1440.;
  return ftime;
}