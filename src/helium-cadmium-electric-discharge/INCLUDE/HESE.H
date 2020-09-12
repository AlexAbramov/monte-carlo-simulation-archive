// Functions for working with He sequations and threasholds
// Abramov A.A., 1997

#ifndef __HESE_H
#define __HESE_H

#define FILE_SE "..\\..\\dat\\hese.bin"// default binary data file

#define	EMAX		4096.	// max electron energy [eV]
#define	NEMAX		256	// size_x of arrays
#define	NU			32		// size_y of two dimencional arrays
#define	NEXP		7		// number of excitation levels

#define	PEX		19.82	// lowest excitation threhold
#define 	PION		24.58	// ionization threshold
#define	KK			59.3  // kk*v[sqev]=v [sm/mksec]

#define 	IPEX 		19		// int(pex)
#define 	IPION 	24    // int(pion)
#define 	IPEX1 	(IPEX+1)
#define 	IPION1 	(IPION+1)
#define	NEMAX1	(NEMAX+1)
#define	NEMAX2	(NEMAX1-IPEX)
#define	NEMAX3	(NEMAX1-IPION)

float	pexi(int);// return excitation thresholds; arg -
float ntoe(int);// index to energy
int 	eton(float);// energy to index

extern float * selas;// elastic sequation
extern float * sex;// excited
extern float * sion;// ionising
extern float * spelas;// elastic differential
extern float * spex;// excited differential
extern float * spion;// ionising differential
extern float * energy;
extern float * vel;

void alloc_se();// allocate arrays of sequations and thresholds
void dealloc_se();// deallocate it
void read_se(char* =FILE_SE);// read arrays from binary file
void write_se(char* =FILE_SE);// write arrays to binary file


float velf(float);// return velocity [sqev]; arg - energy [eV]
float selasf(float);// return elastic sequation [A*A]; arg - energy [eV]
float sexf(float);// return excited sequation [A*A]; arg - energy [eV]
float sionf(float);// return ionising sequation [A*A]; arg - energy [eV]
float spelasf(float,float);// return angle [rad] of elastic differential collision; args: energy [eV], random[0,1]
int 	spexf(float,float);// return number of level in excited collision; args: energy [eV], random[0,1]
float spionf(float,float);// return d[0,1] in ionising differential collision; args: energy [eV], random[0,1]
float spexf1(float,int);// return excited sequation for effective level [A*A]; arg - energy [eV]

#endif