//	ДЕКЛАРАЦИЯ ПАРАМЕТРОВ ГАЗОРАЗРЯДНОЙ ЯЧЕЙКИ
//	И МАССИВОВ ПАРАМЕТРОВ ДЛЯ УЧЕТА СТАТИСТИКИ ЭЛЕКТРОННЫХ ЛАВИН
//	ДЕКЛАРАЦИЯ ФУНКЦИЙ ДЛЯ РАБОТЫ С МАССИВАМИ

//	ДЕКЛАРАЦИЯ ПАРАМЕТРОВ ГАЗОРАЗРЯДНОЙ ЯЧЕЙКИ:
extern double		conc;		// concentration
extern double 		f0;		// max electric field [v/sm]
extern double 		fr; 		// frequence [MHz]
extern long int 	nc;		// number of circles
extern int		imax;		// size of arrays
extern char		file_param[];	// Имя файла параметров
extern double 		ftime;		// Время счета [min]

void 	print_par(); 			// Печать параметров ячейки на дисплей
void 	fscan_par(char*);		// Чтение параметров ячейки из файла

//	ДЕКЛАРАЦИЯ МАССИВОВ ПАРАМЕТРОВ ДЛЯ УЧЕТА СТАТИСТИКИ ЭЛЕКТРОННЫХ ЛАВИН
const int nmas=14;			// Количество массивов
const int fremax=200;			// max energy for fre

extern double* 	xx;
extern double* 	ff;
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

extern double	x;	// sm
extern double	vx;	
extern double	er;	// eV
extern double	ss;	
extern double	sss;	

const double	kk=59.3; //v[sm/mksec]=v[sqe]*kk

extern double	ww; //2*pi*fr
extern double	dt; //1/fr/imax [mksec]
extern double	df; //2*pi/imax	
extern double	uu; //v_ampl_coleb
extern double	aa; //x_ampl_coleb [sm]

extern double* 	fre;	

//	ДЕКЛАРАЦИЯ ФУНКЦИЙ ДЛЯ РАБОТЫ С МАССИВАМИ

void 	read_param(); 		// Cчитать массивы из файла 
void 	write_param(); 		// Запись массивов в файл 
void 	print_param(); 		// Печать массивов на дисплей