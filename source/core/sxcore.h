
#ifndef __sxcore
#define __sxcore

#include <fstream>
#include <gdefines.h>

//��� ������� ��� ��������� � ��������� �����
typedef void(*THREAD_UPDATE_FUNCTION)();

enum CoreTaskFlag
{
	CoreTF_NONE = 0x0,

	CoreTF_REPEATING = 0x1 << 0, //< ������ ����� �����������, ���� �� ������� - ���������� ������ ���� ���
	CoreTF_THREADSAFE = 0x1 << 1, //< ������ ����� ���� ��������� � ����� ������
	CoreTF_FRAME_SYNC = 0x1 << 2, //< ������ ���������� ������������� �� ������� �����
	CoreTF_ON_SYNC = 0x1 << 3, //< ��� ����������� � ������ �������������(��������� ����������� �������� ��� ������ ������� �� ����� �������������)

	CoreTF_SINGLETHREADED = CoreTF_NONE, //< ������ ����������� � ������� ������, ���� ���
	CoreTF_SINGLETHREADED_REPEATING = CoreTF_REPEATING, //< ������ ����������� � ������� ������, �����������
	CoreTF_BACKGROUND = CoreTF_THREADSAFE,  //< ������ ����������� � ����(�� ������� �������������) ���� ���
	CoreTF_BACKGROUND_REPEATING = CoreTF_THREADSAFE | CoreTF_REPEATING, //< ������ ����������� � ����(�� ������� �������������), �� ���������� �����������
	CoreTF_BACKGROUND_SYNC = CoreTF_THREADSAFE | CoreTF_FRAME_SYNC, //< ������ ����� ����������� � ����� ������, ������� �������������, ����������� ���� ���
	CoreTF_BACKGROUND_SYNC_REPEATING = CoreTF_THREADSAFE | CoreTF_REPEATING | CoreTF_FRAME_SYNC, //< ������ ����� ����������� � ����� ������, ������� �������������, ����������� �����������

	CoreTF_ALL = ~0x0
};

//������� ������� ����
//������ ������� Core_0 ���� ���������� ��� ������������������� ����

SX_LIB_API long Core_0GetVersion();	//���������� ������ ����
SX_LIB_API void Core_0Create(const char* name, bool is_unic = true); //�������� ������ ����, name - ���, is_unic - ������ �� ��� ���� ���� ����������
SX_LIB_API void Core_Dbg_Set(report_func rf); //��������� ������ ����������� ������ ���������� ����������
SX_LIB_API int Core_0FileExists(const char* path); //���������� �� ����
SX_LIB_API char** Core_0CommandLineToArgvA(char* CmdLine,int* _argc); //���������� ������ ����� � ����������� � ������ CmdLine, � _argc ���������� ���������� ��������� ���������, �� ���� ���������� ������ ���������� �������
SX_LIB_API int Core_0ClipBoardCopy(const char *str); //�������� ������ � ����� ������

//�������� �����
//������� ������ �� ���������� ����
SX_LIB_API void Core_MTaskAdd(	//�������� ������
								THREAD_UPDATE_FUNCTION func, //������� ���������
								DWORD flag = CoreTF_SINGLETHREADED_REPEATING); //���� �� CoreTaskFlag
SX_LIB_API void Core_MTaskStart();	//���������� ������������ ��� ������
SX_LIB_API void Core_MTaskStop();	//���������� ��� ������

SX_LIB_API void Core_AKill(); //���������� ����
SX_LIB_API void Core_AGetName(char* name); //�������� ��� ����

///////
//��������� ��� ������/������ ������

//����� ��������
#define SXFILE_BIN 0	//��������
#define SXFILE_TEXT 1	//���������
//�������� type - ����� ������� �����
struct ISXFile : public IBaseObject
{
	virtual ~ISXFile(){};
	virtual int Open(const char* path, int type = SXFILE_TEXT) = 0;	//������� ����
	virtual int Create(const char* path, int type = SXFILE_TEXT) = 0;//������� ����
	virtual int Add(const char* path, int type = SXFILE_TEXT) = 0;	//�������� � ����� �����
	virtual size_t ReadB(void* dest, size_t size)=0;	//������� � dest ���������� ���� size
	virtual size_t WriteB(void* src, size_t size)=0;	//�������� src � ��������� size ����
	virtual size_t ReadT(const char* format, ...) = 0;	//������ �� �����, ... - ������ ���������
	virtual size_t WriteT(const char* format, ...) = 0;	//������ � ����
	virtual size_t GetSize()=0;	//�������� ������ ����� � ������
	virtual char ReadChar()=0;	//������� ������
	virtual size_t GetPos() = 0;//������ �����
	virtual void SetPos(size_t pos) = 0; //���������� �������
	virtual void Close()=0;		//������� ����
	virtual BOOL IsEOF()=0;		//������� ������� �������� ������ �����?
};

SX_LIB_API ISXFile* Core_CrFile(); //������� ��������� ������ ISXFile
SX_LIB_API ISXFile* Core_OpFile(const char* path, int type); //������� ����

////////
//��������� ��� ������ � ������� ������������ (ini)
//�������� acceptIncludes - ������������ �� ��������� ������ ������ ��������
//!!!������ � ����� �������� � ���� ������, � ��� �������� ��� ����� ���� ������ �� ����������� ������
//!!! ����� �������� ����� ���������� ������/������, ������ �������
struct ISXLConfig : public IBaseObject
{
	virtual ~ISXLConfig(){};
	virtual int Open(const char* path)=0;	//������� ����
	virtual const char* GetKey(const char* section, const char* key) = 0; //�������� �������� ����� key ������� � ������ section
	virtual const char* GetKeyName(const char* section, int key) = 0; //�������� ��� ����� �� ������
	virtual const char* GetSectionName(int num) = 0; //�������� ��� ����� �� ������
	virtual void Set(const char* section, const char* key, const char* val)=0; //���������� �������� val ����� key ����� � ������ section
	virtual int Save()=0;	//��������� ����
	virtual int GetSectionCount(bool acceptIncludes = false)=0;	//���������� ������ � �����
	virtual int GetKeyCount(bool acceptIncludes = false)=0; //����� ���������� ������
	virtual int GetKeyCount(const char* section, bool acceptIncludes = false) = 0; //����� ���������� ������ � ������
	virtual bool SectionExists(const char* section, bool acceptIncludes = false)=0; //���������� �� ������ section
	virtual bool KeyExists(const char* section, const char* key, bool acceptIncludes = false)=0; //���������� �� ���� key � ������ section
};

SX_LIB_API ISXLConfig* Core_CrLConfig(); //������� ���� ��������� ������ ISXLConfig
SX_LIB_API ISXLConfig* Core_OpLConfig(const char* path); //������� ���� ��������

#endif