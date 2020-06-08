//	ДЕКЛАРАЦИЯ МАССИВОВ СЕЧЕНИЙ И ФУНКЦИЙ ДЛЯ РАБОТЫ С НИМИ
//		( Размерность энергии [eV] )               

extern char	file_se[];	// Имя файла массивов сечений.

//  ОПРЕДЕЛЕНИЕ КОНСТАНТ
const float	emax=4096.;	// Максимально возможная энергия электронов.
const int 	nemax=256;	// Размерность массивов.
const int 	nu=32;		// Количество ячеек для дифференциальных сечений.
const int 	nexp=7;		// Количество учитываемых уровней возбуждения.
     
//  ЗНАЧЕНИЯ ПОТЕНЦИАЛОВ ВОЗБУЖДЕНИЯ И ИОНИЗАЦИИ 
const float	pex=19.82;	// нижний потенциал возбуждения
extern float 	pexi(int);	// возвращает потенциалы возбуждения
const float 	pion=24.58;	// потенциал ионизации
const float	kk=59.3;	// kk*v[sqev]=v[10^6] sm/sec
  
//  ДЕКЛАРАЦИЯ ФУНКЦИЙ СЕЧЕНИЙ
extern float 	stotf(float);		//суммарное сечение
extern float 	ftotf(float);		//ftot
extern float 	selasf(float);		//сечение упругих процессов
extern float 	sexf(float);		//сечение возбуждения
extern float 	sionf(float);		//сечение ионизации
extern float 	spelasf(float,float);	//дифференциальное сечение упругих процессов
extern int 	spexf(float,float);	//дифференциальное сечение возбуждения
extern float 	spionf(float,float);	//дифференциальное сечение ионизации
extern float 	ftotf(float);		//суммарная fi 
//----------------------------------------------------------------------------

// ДЕКЛАРАЦИЯ МАССИВОВ СЕЧЕНИЙ
extern float* 	stot;		//суммарное сечение
extern float* 	ftot;		//ftot
extern float* 	selas;		//сечение упругих процессов
extern float* 	sex;		//сечение возбуждения
extern float* 	sion;		//сечение ионизации
extern float* 	spelas;		//дифференциальное сечение упругих процессов
extern float* 	spex;		//дифференциальное сечение возбуждения
extern float* 	spion;		//дифференциальное сечение ионизации
extern float* 	energy;		//массив энергий

// ДЕКЛАРАЦИЯ ФУНКЦИЙ ДЛЯ РАБОТЫ С МАССИВАМИ
int eton(float);
float ntoe(int);
void alloc_se();
void dealloc_se();
void read_se();
void write_se();

// КОНСТАНТЫ ДЛЯ РАБОТЫ С МАССИВАМИ
const int ipex=int(pex);
const int ipion=int(pion);
const int ipex1=ipex+1;
const int ipion1=ipion+1;

