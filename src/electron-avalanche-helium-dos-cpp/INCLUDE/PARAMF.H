// 
//	   
//	       
//	     

//	   :
extern double 		voltage;	//  Æąļ¦„­Ø„.
extern double 		dk; 		// «Ø­  §®­ė Ŗ ā®¤­®£® Æ ¤„­Øļ
extern double 		field;		// «„ŖāąØē„įŖ®„ Æ®«„. 
extern double 		dd; 		// «Ø­  £ §®ą §ąļ¤­®£® Æą®¬„¦ćāŖ 
extern long int 	nstat;		// ®«Øē„įā¢® įā āØįāØē„įŖØå ķ«„Ŗāą®­®¢	
extern char		file_param[];	// ¬ļ ä ©«  Æ ą ¬„āą®¢
extern long int 	ilav;		// ®«Øē„įā¢® ķ«„Ŗāą®­­ėå « ¢Ø­
extern long int 	istat;		// „ŖćéØ© ­®¬„ą įā āØįāØē„įŖ®£® ķ«„Ŗāą®­ 	
extern double 		ftime;		// ą„¬ļ įē„ā 

void 	print_par(); 			// „ē āģ Æ ą ¬„āą®¢ ļē„©ŖØ ­  ¤ØįÆ«„©
void 	fscan_par(char*);		// ā„­Ø„ Æ ą ¬„āą®¢ ļē„©ŖØ Ø§ ä ©« 	

//	       
const int 	imax=20;		// Øį«® ą §”Ø„­Ø© Æą®¬„¦ćāŖ 
const int 	imax1=imax+1;
const int	nmas=16;		// ®«Øē„įā¢® ¬ įįØ¢®¢
const int	fremax=200;		//  ŖcØ¬ «ģ­ ļ ķ­„ą£Øļ ¤«ļ 
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

//	     
void 	read_param(); 		// CēØā āģ ¬ įįØ¢ė Ø§ ä ©«  
void 	write_param(); 		//  ÆØįģ ¬ įįØ¢®¢ ¢ ä ©« 
void 	print_param(); 		// „ē āģ ¬ įįØ¢®¢ ­  ¤ØįÆ«„© 

double	xtoe(int,double);
double	etox(int,double);
double	etof(int,double);