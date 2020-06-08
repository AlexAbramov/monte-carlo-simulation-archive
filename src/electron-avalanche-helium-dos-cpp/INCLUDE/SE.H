//	���������� �������� ������� � ������� ��� ������ � ����
//		( �����୮��� ���ࣨ� [eV] )               

extern char	file_se[];	// ��� 䠩�� ���ᨢ�� �祭��.

//  ����������� ��������
const float	emax=4096.;	// ���ᨬ��쭮 ��������� ���ࣨ� �����஭��.
const int 	nemax=256;	// �����୮��� ���ᨢ��.
const int 	nu=32;		// ������⢮ �祥� ��� ����७樠���� �祭��.
const int 	nexp=7;		// ������⢮ ���뢠���� �஢��� ����㦤����.
     
//  �������� ����������� ����������� � ��������� 
const float	pex=19.82;	// ������ ��⥭樠� ����㦤����
extern float 	pexi(int);	// �����頥� ��⥭樠�� ����㦤����
const float 	pion=24.58;	// ��⥭樠� ������樨
const float	kk=59.3;	// kk*v[sqev]=v[10^6] sm/sec
  
//  ���������� ������� �������
extern float 	stotf(float);		//�㬬�୮� �祭��
extern float 	ftotf(float);		//ftot
extern float 	selasf(float);		//�祭�� ��㣨� ����ᮢ
extern float 	sexf(float);		//�祭�� ����㦤����
extern float 	sionf(float);		//�祭�� ������樨
extern float 	spelasf(float,float);	//����७樠�쭮� �祭�� ��㣨� ����ᮢ
extern int 	spexf(float,float);	//����७樠�쭮� �祭�� ����㦤����
extern float 	spionf(float,float);	//����७樠�쭮� �祭�� ������樨
extern float 	ftotf(float);		//�㬬�ୠ� fi 
//----------------------------------------------------------------------------

// ���������� �������� �������
extern float* 	stot;		//�㬬�୮� �祭��
extern float* 	ftot;		//ftot
extern float* 	selas;		//�祭�� ��㣨� ����ᮢ
extern float* 	sex;		//�祭�� ����㦤����
extern float* 	sion;		//�祭�� ������樨
extern float* 	spelas;		//����७樠�쭮� �祭�� ��㣨� ����ᮢ
extern float* 	spex;		//����७樠�쭮� �祭�� ����㦤����
extern float* 	spion;		//����७樠�쭮� �祭�� ������樨
extern float* 	energy;		//���ᨢ ���ࣨ�

// ���������� ������� ��� ������ � ���������
int eton(float);
float ntoe(int);
void alloc_se();
void dealloc_se();
void read_se();
void write_se();

// ��������� ��� ������ � ���������
const int ipex=int(pex);
const int ipion=int(pion);
const int ipex1=ipex+1;
const int ipion1=ipion+1;
