//	        
//		(  §¬¥à­®áâì í­¥à£¨¨ [eV] )               

extern char	file_se[];	// ¬ï ä ©«  ¬ áá¨¢®¢ á¥ç¥­¨©.

//   
const float	emax=4096.;	//  ªá¨¬ «ì­® ¢®§¬®¦­ ï í­¥à£¨ï í«¥ªâà®­®¢.
const int 	nemax=256;	//  §¬¥à­®áâì ¬ áá¨¢®¢.
const int 	nu=32;		// ®«¨ç¥áâ¢® ïç¥¥ª ¤«ï ¤¨ää¥à¥­æ¨ «ì­ëå á¥ç¥­¨©.
const int 	nexp=7;		// ®«¨ç¥áâ¢® ãç¨âë¢ ¥¬ëå ãà®¢­¥© ¢®§¡ã¦¤¥­¨ï.
     
//       
const float	pex=19.82;	// ­¨¦­¨© ¯®â¥­æ¨ « ¢®§¡ã¦¤¥­¨ï
extern float 	pexi(int);	// ¢®§¢à é ¥â ¯®â¥­æ¨ «ë ¢®§¡ã¦¤¥­¨ï
const float 	pion=24.58;	// ¯®â¥­æ¨ « ¨®­¨§ æ¨¨
const float	kk=59.3;	// kk*v[sqev]=v[10^6] sm/sec
  
//    
extern float 	stotf(float);		//áã¬¬ à­®¥ á¥ç¥­¨¥
extern float 	ftotf(float);		//ftot
extern float 	selasf(float);		//á¥ç¥­¨¥ ã¯àã£¨å ¯à®æ¥áá®¢
extern float 	sexf(float);		//á¥ç¥­¨¥ ¢®§¡ã¦¤¥­¨ï
extern float 	sionf(float);		//á¥ç¥­¨¥ ¨®­¨§ æ¨¨
extern float 	spelasf(float,float);	//¤¨ää¥à¥­æ¨ «ì­®¥ á¥ç¥­¨¥ ã¯àã£¨å ¯à®æ¥áá®¢
extern int 	spexf(float,float);	//¤¨ää¥à¥­æ¨ «ì­®¥ á¥ç¥­¨¥ ¢®§¡ã¦¤¥­¨ï
extern float 	spionf(float,float);	//¤¨ää¥à¥­æ¨ «ì­®¥ á¥ç¥­¨¥ ¨®­¨§ æ¨¨
extern float 	ftotf(float);		//áã¬¬ à­ ï fi 
//----------------------------------------------------------------------------

//   
extern float* 	stot;		//áã¬¬ à­®¥ á¥ç¥­¨¥
extern float* 	ftot;		//ftot
extern float* 	selas;		//á¥ç¥­¨¥ ã¯àã£¨å ¯à®æ¥áá®¢
extern float* 	sex;		//á¥ç¥­¨¥ ¢®§¡ã¦¤¥­¨ï
extern float* 	sion;		//á¥ç¥­¨¥ ¨®­¨§ æ¨¨
extern float* 	spelas;		//¤¨ää¥à¥­æ¨ «ì­®¥ á¥ç¥­¨¥ ã¯àã£¨å ¯à®æ¥áá®¢
extern float* 	spex;		//¤¨ää¥à¥­æ¨ «ì­®¥ á¥ç¥­¨¥ ¢®§¡ã¦¤¥­¨ï
extern float* 	spion;		//¤¨ää¥à¥­æ¨ «ì­®¥ á¥ç¥­¨¥ ¨®­¨§ æ¨¨
extern float* 	energy;		//¬ áá¨¢ í­¥à£¨©

//      
int eton(float);
float ntoe(int);
void alloc_se();
void dealloc_se();
void read_se();
void write_se();

//     
const int ipex=int(pex);
const int ipion=int(pion);
const int ipex1=ipex+1;
const int ipion1=ipion+1;

