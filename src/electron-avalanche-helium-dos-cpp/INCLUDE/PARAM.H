//	Abramov A.A., 1994
//
//	Parameters of gase discharge 
//	Arrays for electron statistic counting 
//	Functions for working with arrays

extern double 		voltage;	// Voltage
extern double 		dk; 		// Length of cathode falling
extern double 		field;		// Electric field 
extern double 		dd; 		// Length of gase discharge box
extern long int 	nstat;		// Number of statistical electrons
extern char		file_param[];	// File name 
extern long int 	ilav;		// текущий номер лавины
extern long int 	istat;		// текущ кол-во стат эл-в 
extern double 		ftime;		// Time of counting

void 	print_par(); 			// Печать параметров ячейки на дисплей
void 	fscan_par(char*);		// Чтение параметров ячейки из файла	

const int imax=100;			// Число разбиений промежутка
const int nmas=16;			// Количество массивов

extern double* 	xx;
extern double* 	ff;
extern double*	de;
extern double* 	mm;
extern double* 	vvx;		
extern double* 	vvd;		
extern double* 	vvr;
extern double* 	vvv;		
extern double* 	eex;		
extern double* 	eer;		
extern double* 	eee;
extern double* 	evx;	
extern double* 	fto;
extern double* 	fel;
extern double* 	fex;	
extern double* 	fio;	


//	ДЕКЛАРАЦИЯ ФУНКЦИЙ ДЛЯ РАБОТЫ С МАССИВАМИ
void 	read_param(); 		// Cчитать массивы из файла 
void 	write_param(); 		// Запись массивов в файл 
void 	print_param(); 		// Печать массивов на дисплей 

double	xtoe(int,double);
double	etox(int,double);
double	etof(int,double);