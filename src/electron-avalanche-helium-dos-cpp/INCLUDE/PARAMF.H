// 
//	ДЕКЛАРАЦИЯ ПАРАМЕТРОВ ГАЗОРАЗРЯДНОЙ ЯЧЕЙКИ
//	И МАССИВОВ ПАРАМЕТРОВ ДЛЯ УЧЕТА СТАТИСТИКИ ЭЛЕКТРОННЫХ ЛАВИН
//	ДЕКЛАРАЦИЯ ФУНКЦИЙ ДЛЯ РАБОТЫ С МАССИВАМИ

//	ДЕКЛАРАЦИЯ ПАРАМЕТРОВ ГАЗОРАЗРЯДНОЙ ЯЧЕЙКИ:
extern double 		voltage;	// Напряжение.
extern double 		dk; 		// Длина зоны катодного падения
extern double 		field;		// Электрическое поле. 
extern double 		dd; 		// Длина газоразрядного промежутка
extern long int 	nstat;		// Количество статистических электронов	
extern char		file_param[];	// Имя файла параметров
extern long int 	ilav;		// Количество электронных лавин
extern long int 	istat;		// Текущий номер статистического электрона	
extern double 		ftime;		// Время счета

void 	print_par(); 			// Печать параметров ячейки на дисплей
void 	fscan_par(char*);		// Чтение параметров ячейки из файла	

//	ДЕКЛАРАЦИЯ МАССИВОВ ПАРАМЕТРОВ ДЛЯ УЧЕТА СТАТИСТИКИ ЭЛЕКТРОННЫХ ЛАВИН
const int 	imax=20;		// Число разбиений промежутка
const int 	imax1=imax+1;
const int	nmas=16;		// Количество массивов
const int	fremax=200;		// Макcимальная энергия для ФРЭЭ
const int 	fremax1=fremax+1;

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
extern double huge*  fre;
extern double huge*  mdr;

//	ДЕКЛАРАЦИЯ ФУНКЦИЙ ДЛЯ РАБОТЫ С МАССИВАМИ
void 	read_param(); 		// Cчитать массивы из файла 
void 	write_param(); 		// Запись массивов в файл 
void 	print_param(); 		// Печать массивов на дисплей 

double	xtoe(int,double);
double	etox(int,double);
double	etof(int,double);