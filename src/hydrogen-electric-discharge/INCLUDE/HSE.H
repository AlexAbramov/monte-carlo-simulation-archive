#ifndef __HSE_H
#define __HSE_H

#define FILE_SE "..\\..\\dat\\hse.bin"// default binary data file

#define	EMAX		4096.	// max electron energy [eV]
#define	NEMAX		256	// size_x of arrays
#define	NU			32		// size_y of two dimencional arrays
#define	KK			59.3  // kk*v[sqev]=v [sm/mksec]
#define	NEMAX1	(NEMAX+1)

float ntoe(int);// index to energy
int 	eton(float);// energy to index

extern float * spelas;// elastic differential
extern float * energy;// energy
extern float * vel;// velocity

void alloc_se();// allocate arrays of cross-sections and thresholds
void dealloc_se();// deallocate it
void read_se(char* =FILE_SE);// read arrays from binary file
void write_se(char* =FILE_SE);// write arrays to binary file

float velf(float);// return velocity [sqev]; arg - energy [eV]
float spelasf(float,float);// return angle [rad] of elastic differential collision; args: energy [eV], random[0,1]

#endif