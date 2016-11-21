
#ifndef SX_POST_PROCESS_H
#define SX_POST_PROCESS_H

		/*#ifndef EXPORT_DATA
				#ifdef SX_EXE
					#define EXPORT_DATA __declspec (dllimport)
				#else
					#define EXPORT_DATA __declspec (dllexport)
				#endif
		#endif*/
#define EXPORT_DATA

//�������� ����������� �������������
//��� ��� ���������� �������� ��������
//�������� ������ ��� ��������

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//��������� ������� ��� ������ ���������
#define SXPP_RT_FORMAT_RGBA8	"RGBA8"		// D3DFMT_A8R8G8B8
#define SXPP_RT_FORMAT_R5G6B5	"R5G6B5"	// D3DFMT_R5G6B5
#define SXPP_RT_FORMAT_R32F		"R32F"		// D3DFMT_R32F
#define SXPP_RT_FORMAT_GR32F	"GR32F"		// D3DFMT_G32R32F
#define SXPP_RT_FORMAT_ABGR32F	"ABGR32F"	// D3DFMT_A32B32G32R32F
#define SXPP_RT_FORMAT_R16F		"R16F"		// D3DFMT_R16F
#define SXPP_RT_FORMAT_GR16F	"GR16F"		// D3DFMT_G16R16F
#define SXPP_RT_FORMAT_ABGR16F	"ABGR16F"	// D3DFMT_A16B16G16R16F

//���� ������� (��������� ��������)
#define SXPP_TEX_TYPE_LOAD_STR		"load"
#define SXPP_TEX_TYPE_ENGINE_STR	"engine"
#define SXPP_TEX_TYPE_PP_STR		"pp"

//���� ������� (�������� ��������)
#define SXPP_TEX_TYPE_LOAD_NUM		0
#define SXPP_TEX_TYPE_ENGINE_NUM	1
#define SXPP_TEX_TYPE_PP_NUM		2

//����������� ���� �������� ������� �������� ��������� ������ ���������
#define SXPP_TEX_ID_SCREEN		"screen"

//��������� ���� ������, ��� ������������� � ������
#define SXPP_SHADER_DATA_TYPE_FLOAT		"float"
#define SXPP_SHADER_DATA_TYPE_FLOAT2	"float2"
#define SXPP_SHADER_DATA_TYPE_FLOAT3	"float3"
#define SXPP_SHADER_DATA_TYPE_FLOAT4	"float4"
#define SXPP_SHADER_DATA_TYPE_INT		"int"
#define SXPP_SHADER_DATA_TYPE_MATRIX	"float4x4"
#define SXPP_SHADER_DATA_TYPE_MACRO		"macro"

//��� ���������� �������
#define SXPP_PASS_TEX_FILTER_NONE		"none"
#define SXPP_PASS_TEX_FILTER_LINEAR		"linear"
#define SXPP_PASS_TEX_FILTER_POINT		"point"
#define SXPP_PASS_TEX_FILTER_ANISOTROPY "anisotropy"

//��� ��������� �������
#define SXPP_PASS_TEX_ADRESS_WRAP		"wrap"
#define SXPP_PASS_TEX_ADRESS_CLAMP		"clamp"
#define SXPP_PASS_TEX_ADRESS_MIRROR		"mirror"

#define SXPP_ERROR_G_MESSAGE "SkyX Engine - PostProcess library"
#define SXPP_ERROR_G "Error"
#define SXPP_ERROR_MESSAGE_NO_VALUE "no value"

//���� ��������
#define SXPP_SHADER_VERTEX 0
#define SXPP_SHADER_PIXEL 1

//���� ������
enum SXPP_ERROR_CODE
{
	SXPP_OK = 0,							//��� ������
	SXPP_ERR_NOT_FILE = -1,					//�� ������ ����
	SXPP_ERR_INVALID_VALUE = -2,			//���������� ��������
	SXPP_ERR_NEW_BEGIN_PP = -3,				//������� ������ ���������� ������������ � ���������� ��������
	SXPP_ERR_NOT_FOUND_NAME = -4,			//�� ������� ���
	SXPP_ERR_NOT_FOUND_ITEM = -5,			//�� ������ ������� ����-��������
	
	SXPP_ERR_NOT_FOUND_PP = -6,				//�� ������ ����-�������
	SXPP_ERR_INVALID_NUMBER_OF_PP = -7,		//���������� ����� ������������

	SXPP_ERR_TEX_RT = -8,					//������������ �������� ���� ������� ������ �������
	SXPP_ERR_NON_UNIC_ITEM = -9,			//�� ���������� ����
	
	SXPP_ERR_INVALID_VER_SHADER = -10,		//���������� ������ �������
	SXPP_ERR_DISCREPANCY_VER_SHADER = -11,	//������������� ������ ��������
	SXPP_ERR_MAX_NUM = -12,					//�������� ����� ��������
	SXPP_ERR_INVALID_RT_SAVE = -13,			//����������� ������������ ������ ����������
	SXPP_ERR_REDIFINITION_GDATA = -14,		//�������������� global_namespace_data_pp
	SXPP_ERR_GDATA_PASS = -15,				//� ���������� ������������ ���� ������ ����
	SXPP_ERR_GDATA_SEQUENCE = -16,			//� ���������� ������������ ���� ������� ������������������
	SXPP_ERR_G_NON_UNIC_ITEM = -17,			//�� ���������� ����, ��������� �� ���� �������������

	SXPP_ERR_MAX_NUM_REC = -18,				//�������� ����� ���������� �������
	SXPP_ERR_NON_END_REC = -19				//����������� ��������, �������� ������� � ��������� ��������� ���� ���������
};

//���������
#define SXPP_DET_ITEM_GDATA	"global_namespace_data_pp"
#define SXPP_DET_ITEM_POSTPROCESS	"postprocess"
#define SXPP_DET_ITEM_RENDER_TARGET	"render_target"
	#define SXPP_DET_ITEM_RENDER_TARGET_WIDTH			"width"
	#define SXPP_DET_ITEM_RENDER_TARGET_HEIGHT			"height"
		#define SXPP_DET_ITEM_RENDER_TARGET_SIZE_FULL	"full"
	#define SXPP_DET_ITEM_RENDER_TARGET_FORMAT			"format"
	#define SXPP_DET_ITEM_RENDER_TARGET_BLEND_SCREEN	"blend_screen"

#define SXPP_DET_ITEM_TEXTURES		"textures"
	#define SXPP_DET_ITEM_TEXTURES_NF_TYPE		"texture type"
	#define SXPP_DET_ITEM_TEXTURES_NF_NAME		"texture name"
	#define SXPP_DET_ITEM_TEXTURES_NF_ID		"texture id"

#define SXPP_DET_ITEM_SHADER_VS		"shader_vs"
#define SXPP_DET_ITEM_SHADER_PS		"shader_ps"
	#define SXPP_DET_ITEM_SHADER_PATH		"path"
	#define SXPP_DET_ITEM_SHADER_VERSION	"version"
	#define SXPP_DET_ITEM_SHADER_MACRO		"macro"
	#define SXPP_DET_ITEM_SHADER_NF_DEF		"macro definition"
	#define SXPP_DET_ITEM_SHADER_INIT_DATA	"init_data"
	#define SXPP_DET_ITEM_SHADER_INIT_DATA_NF_TYPE	"type"
	#define SXPP_DET_ITEM_SHADER_INIT_DATA_NF_VALUE	"value"

#define SXPP_DET_ITEM_PASS			"pass"
	#define SXPP_DET_ITEM_PASS_TEXTURE				"texture"
	#define SXPP_DET_ITEM_PASS_TEXTURE_NF_SLOT		"texture slot"
	#define SXPP_DET_ITEM_PASS_TEXTURE_NF_ADRESS	"texture adress"
	#define SXPP_DET_ITEM_PASS_TEXTURE_NF_FILTER	"texture filter"

#define SXPP_DET_ITEM_SEQUENCE		"sequence"

//���������� �������� �� 1 ����������
#define SXPP_SETTINGS_SB_RENDER_TARGET	16	//���������� ������ ���������
#define SXPP_SETTINGS_SB_TEXTURES		16	//���������� ������� �� ������ ������ ���������
#define SXPP_SETTINGS_SB_PASS			16	//���������� ������
#define SXPP_SETTINGS_SB_PASS_TEX		8	//���������� ������� � �����
#define SXPP_SETTINGS_SB_SEQUENCE		16	//���������� ������ � ������������������
#define SXPP_SETTINGS_SB_SHADER			16	//���������� ��������
#define SXPP_SETTINGS_SB_SHADER_DATA	32	//���������� ���������� ������� ����� ���������������
#define SXPP_SETTINGS_SB_SHADER_MACRO	32	//���������� �������� ������� ���������� � ������

#define SXPP_SETTINGS_SB_PP				64	//���������� ������������

#define SXPP_SETTINGS_SB_MAX_COUNT_REC	64	//���������� ����������� ��� �������� (��� ������������ �������)
#define SXPP_SETTINGS_SB_COUNT_TEX_FOR_USING 64	//���������� ������������

#define SXPP_SETTINGS_SB_ERROR_MSG 1024			//������ ������� ��� ����������� ���������
#define SXPP_SETTINGS_SB_SRC_ERR 512			//������ ������� ��� ��������� ������

//������������ ���� c ������� ��� ������ ������������
namespace SXPostProcessGD
{
	//��������� ��� �������� � ������������� ��������� �������
	struct EXPORT_DATA EngineTexture
	{
		EngineTexture();

		int CountTextures;	//����������
		//���������� ��������� ��������
		int AddTexture(
						const char* name,		//��� �� ������� �������� ����� �������� �� ����� ������������	 
						IDirect3DTexture9* tex);//��������� �� ��������	
		//������� � �������
		char Name[256][SXPP_SETTINGS_SB_COUNT_TEX_FOR_USING];
		IDirect3DTexture9* Texture[SXPP_SETTINGS_SB_COUNT_TEX_FOR_USING];
	};


	struct EXPORT_DATA SXPPGDData
	{
		SXPPGDData();

		float2_t WidthHeightBackBuffer;

		IDirect3DDevice9* Device;

		char* PathForShaders;		//���� �� ����� � ���������
		char* PathForTextures;		//���� �� ����� � ����������
		char* PathForSave;			//���� �� ����� ���� ��������� ������������� ����������
		
		//��� ������ ���������� ��� �������������� ���������� ����������� ����������� �� ������
		//�������� ������ ���� ��������� ���������, ��� ���������� ������ (���� �� �����������)
		IDirect3DTexture9*	FinalScene;		//����� ��������� �����
		IDirect3DTexture9*	FinalScene2;	//����� ��������� �����
		
		char KeySave;	//��� ������, ��� ������� �� ������� ����� ����������� ������ ��������

		float2_t SizeBackBuffer;	//������ ��� ������� (� ����������� ������� ����)
	} EXPORT_DATA Data;

	EXPORT_DATA EngineTexture DataTex;

	EXPORT_DATA bool IsCurrentTex;			//���������� ������������ ���������� � ��������� ������

	EXPORT_DATA void InitData(SXPPGDData *data);	//������������� ������

	//��������� ��������� �� ��������
	EXPORT_DATA IDirect3DTexture9* GetCurrentRenderTexture();		//������� �������� � ������� ����� ����������� ������
	EXPORT_DATA IDirect3DTexture9** GetCurrentRenderTextureLP();
	EXPORT_DATA IDirect3DTexture9* GetCurrentSendTexture();
	
	//��� - ������� �� ������� ������� ������ ������� (�������� ��� ��������� �������)
	EXPORT_DATA ID3DXMesh* ScreenTexture;

	EXPORT_DATA void CreateScreenTexture(); //������� ���-�������
};

//��������� ��� ������������ ������ �� ������
struct EXPORT_DATA SXPostProcessError
{
	SXPostProcessError();

	SXPP_ERROR_CODE Code;		//��� ������
	DWORD GenStrError;			//����� ������ �� ������� ������������ ������
	char GenFileError[256];		//���� � ������ ������������ ������
	DWORD NumStr;				//������ �� ������� ���������� ������, ��� ������ �����
	char Str[256];				//
	char Str2[256];				//
	char Str3[256];				//
	char Str4[256];				//
	char Str5[256];				//
	char Str6[256];				//
};

//��������� ����������� �����������
struct EXPORT_DATA SXPostProcessData
{
	SXPostProcessData();
	~SXPostProcessData();

	struct SXPPRenderTarget
	{
		SXPPRenderTarget();
		~SXPPRenderTarget();

		char Name[256];
		int Width,Height;				//������, �����
		char WidthStr[32],HeightStr[32];//���� ������ ��������
		DWORD Format;					//������
		bool BlendScreen;
		IDirect3DTexture9*	Texture;
	} RenderTarget[SXPP_SETTINGS_SB_RENDER_TARGET];

	struct SXPPShader
	{
		SXPPShader();
		~SXPPShader();

		char Name[256];		//��� �������
		char Path[256];		//���� ��������
		char Version[256];	//������ �������
		DWORD Shader;

		//��������� ��� ������������� ������ � �������
		struct InitData
		{
			char NameVar[256];	//��� ����������
			char Type[256];		//���
			char ValueStr[256];	//�������� ��������
			void* ValueData;	//��������� �� ��������
			DWORD CountBytes;	//���������� ���� ���������� ������ ����������
		} Data[SXPP_SETTINGS_SB_SHADER_DATA];

		int NumData;	//���������� ��������������� ����������

		void SetMacro(const char* name,const char* def);

		void SetEndMacro();

		D3DXMACRO Macro[SXPP_SETTINGS_SB_SHADER_MACRO];
		int CountMacro;
		
	} ShaderVS[SXPP_SETTINGS_SB_SHADER], ShaderPS[SXPP_SETTINGS_SB_SHADER];

	//
	struct SXPPSequence
	{
		char Pass[SXPP_SETTINGS_SB_SEQUENCE][256];
		int PassNum[SXPP_SETTINGS_SB_SEQUENCE];
	} Sequence;

	//��������� ����������� ��������
	struct SXPPTextures
	{
		SXPPTextures();
		~SXPPTextures();

		char Name[256];
		int Type;		//��� ��������
		char ID[256];	//���� Type == engine �� ��� �������� � ������, ����� ��� ���� ��������
		bool IsOtherPP;	//��� �������� �� ������� �������? ���� ���������� ��� pp
		bool IsTex;		//��� �������� ��� ������ �������
		int HowPP;		//���� ������ ��� pp, �� ������ ������� ����� ��������	
		int HowNum;		//���������� �����
		IDirect3DTexture9*	Texture;
	} Textures[SXPP_SETTINGS_SB_TEXTURES];

	struct SXPPPass
	{
		SXPPPass();

		char Name[256];	//��� �������
		char RT[256];	//��� render target
		int RTNum;		//���������� ����� ������ ��������
		bool IsCurrentPPRT;	//�� �������� �� �������� �����, ��� �� ���������� ������
		//��������� ��� ��������� �������
		struct TexParam
		{
			char Name[256];	//��� ��������
			int Slot;		//����
			int Filter[3];	//������
			int Adress;		//���������
		} Texture[SXPP_SETTINGS_SB_PASS_TEX];
		int TextureNum[SXPP_SETTINGS_SB_PASS_TEX];		//���������� ������ ��� �������
		int TextureTypeNum[SXPP_SETTINGS_SB_PASS_TEX];	//���� �������, 0 - ��������, 1 - ������ �������
		bool IsCurrentPPTex[SXPP_SETTINGS_SB_PASS_TEX];	//�� �������� �� �������� �����, ��� �� ���������� ������

		char ShaderVS[256];	//��� ���������� �������
		int ShaderVSNum;	//���������� ����� �������
		bool IsCurrentPPVS;	//� ������� �� ������� ������ ������, ��� � ���������� ������?

		char ShaderPS[256];	//��� ����������� �������
		int ShaderPSNum;	//���������� ����� �������
		bool IsCurrentPPPS;	//� ������� �� ������� ������ ������, ��� � ���������� ������?

		int CountTextures;	//���������� �������
	} Pass[SXPP_SETTINGS_SB_PASS];

	char Name[256];	//��� ������������
	int RTNum;		//���������� ������ ���������
	int SVSNum;		//���������� ��������� ��������
	int SPSNum;		//���������� ���������� ��������
	int SeqNum;		//���������� ������ � ������������������
	int TexNum;		//���������� �������
	int PassNum;	//���������� ������
};

class EXPORT_DATA SXFileText
{
public:
	SXFileText();
	~SXFileText();
	int LoadFile(const char* path);

	bool IsEndFile();
	void GetStr(char* buf,int size);

	void GetText(char* buf,int size); //test
	void DeleteAll(char* str_b,char* str_e,bool size_end_elem,bool paste_new_str);

	void SetPosition(DWORD pos);
	DWORD GetPosition();
	DWORD GetCurrentStr();

private:
	DWORD Position;
	long Size;
	char* FileText;
};

//�������� ������������ ��� �������� �������� ��������
struct SXRecValidate
{
	SXRecValidate();
	void Add(int pp,int num);

	int Validate();

	//� ������ ������� ������������ �� ��� ��� ����������
	int PP[SXPP_SETTINGS_SB_MAX_COUNT_REC];
	int Num[SXPP_SETTINGS_SB_MAX_COUNT_REC];
	int Count;	//���������� ������ ���������� � �������
};

//��������� ��� �������� ������ � ������
struct SXComTransferShaderData
{
	SXComTransferShaderData();
	int CountData;		//���������� ������

	int AddData(const char* name,void* data,long size);

	struct SXShaderData
	{
		char NameVar[256];	//��� ����������
		void* Data;			//��������� �� ����������
		long CountBytes;	//������ � ������
	} ShaderData[64];
};

class EXPORT_DATA SXLoaderPPFile
{
public:
	SXLoaderPPFile();
	~SXLoaderPPFile();
	//�������� ������������
	int Load(const char* path,SXPostProcessError *error);
	
	//���������
	//��������� ������ ��������� ��� ���������� ������� � �������� ����������� ��������, 
	//����� ����� ���� ��������� ���������� �������� �� ���� � �����������
	int Render(								//������� ������� ���������, ������ ����� ��� ���� ���������, ��������� �������
				int how_pp,					//����� ������������
				SXPostProcessError *error,
				int count_rt_save = 0,		//���������� ������ � ������� rt_save_arr
				int* rt_save_arr = 0);		//������ � �������� ������ ��������� ������� �������� ����������
	int Render(
				const char* name_pp,		//��� ������������
				const char* how_rt_save,	//������ � ������� ������ ��������� (����������� \n � � ����� ����) ������� �������� ���������� 
				SXPostProcessError *error);

	//�������� �� ������ � �������
	bool IsDefined(
					const char* pp,		//��� ������������
					int shader_type,	//��� �������, ��������� ��� ����������, -1 - ������ � � ��� � ������
					const char* shader,	//��� �������
					const char* define);//��� ���������	
	//�������� ��������� �������
	//��������� ���������� IsDefined
	const char* GetDefine(const char* pp,int shader_type,const char* shader,const char* define);

	int GetPPNum();	//���������� ���������� ����������� �������������

	//������������� ������ ������������
	int InitData(const char* name_pp,SXPostProcessError *error=0);	//�� �����
	int InitData(int how_pp,SXPostProcessError *error=0);			//�� ����������� ������
	int InitDataAll(SXPostProcessError *error);						//���� �����������

	//����������/���������� ������ ������������ � ������
	//0 - ����������
	//1 - ���������
	//-1 - �������� �����
	//-2 - �� ������� �����

	int AddShaderData(
						const char* pp,				//��� ������������
						int type_shader,			//��� �������, ��������� ��� ����������? ����� ������� -1 ����� ����� ����� ����������� � ����� ��������� � ����� ���������� ��������

						//����� ��� �� �����������: passnum,pass,shader_name,shader_name_pp
						//��� ������ �� ������ ������ ��� ������ ���������
						//������ ���� ������ passnum �� ��� ��������� ������������
						//��������� ��������: passnum = -1, shader_name_pp,shader_name,pass = 0 ��� [0] = 0
						const char* shader_name_pp,	//��� ������� � ����� ������������
						const char* shader_name,	//��� ����� ������� � �����������
						const char* pass,			//��� ������� � ������� ������������� ������
						int passnum,				//����� ������� (pass) �� ������������������ (sequence) ������� � 0

						const char* name_var,		//��� ����������
						void* data,					//��������� �� ��������
						long size);					//���������� ����

	//���������� �������� AddShaderData, ���������� ��� ��� �� ����������
	//����������� ���������� ������ �� AddShaderData
	int AddShaderData(const char* pp,int type_shader,int passnum,const char* name_var,void* data,long size);
	int AddShaderData(const char* pp,int type_shader,const char* pass,const char* name_var,void* data,long size);
	int AddShaderData(const char* pp,int type_shader,const char* shader_name_pp,const char* shader_name,const char* name_var,void* data,long size);


	int GetIndexNumPP(const char* pp);//���������� ���������� ����� ������������ �� �����

	//������������ ��������:
	//-2 - �� ������� ��������
	//-1 - �� ������ ����������� ���� �� ���������
	//0 - ��� ������
	int GetTexInfo(const char* ppname,int ppnum,const char* name,D3DSURFACE_DESC* desc,int type = -1); //�������� ������ ��������/������ ��������

	//�������� ����������� ������
	int CheckValidate(const char* name_pp,SXPostProcessError *error=0);	//�� ����� ������������
	int CheckValidate(int how_pp,SXPostProcessError *error=0);			//�� ����������� ������ ������������
	int CheckValidateAll(SXPostProcessError *error=0);					//�������� ���� �������������, ������ ���� ������� ����� �������� ���� �������������

	//����������� �������, ����������� �������� �� SXPP_SETTINGS_SB_MAX_COUNT_REC
	bool IsValidTexturePP(
							int pp,							//���������� ����� ������������
							int numtex,						//���������� ����� ��������
							SXRecValidate *rec_validate,	//��������� ������� ������������ ����������� ��������
							int *error);					//����� ������ ����������� ��������

	bool IsPPThere(int pp);	//������� �� ����������� � ����� pp

	//���������� ������ ����� �������� ������� ��� � ������ ��������

	//�������� �������� �� ����� � ����(�����������), ��������� GetTexturePP ���� ���� �������������
	//-1 ����� ����� ������� � ������ ���������, 0 - �������� (���� ���� �������� ��������� �� ������ �������, ��� ��������� ��� ��������)
	//1 - ����� ����� ������ ���������
	//������ ������� ������������ ��� ������������� � ��������, ���� �� �������� �� ������������������ ��� �������
	//��� �������������� ��� ���� ����� �������� ���� ������������ ������ ������� ��������� � ��� ������� �����������
	IDirect3DTexture9* GetTexture(const char* name,int type=-1);
	IDirect3DTexture9* GetTexture(
									const char* ppname,	//��� ������������, ����� ���� 0 � ������ ���� ppnum ������� �� -1
									int ppnum,			//���������� ����� ������������, ���� ������� �������� �������� �� -1 �� ppname ������������, ����� ����� ���� �� ppname
									const char* name,	//��� ��������/������ ��������
									int type=-1);		//��� ��������(0)/������ �������(1), -1 - � ����� ������ ����

	IDirect3DTexture9* GetTexturePP(int pp,int numtex);			//�������� �������� ��������� � ������ �����������, ����������� �����

private:
	int PPNum;									//���������� ����������� �������������
	int HowGlobalNSData;						//���������� ����� ����������� ������������ ����
	char PathForGData[256];						//���� �� ����� �� �������� ���� ��������� ���������� ������������
	SXPostProcessData PP[SXPP_SETTINGS_SB_PP];	//������ � ����������� � �������������

	//������ ��� �������� � �������, ��� ������� ������� ��������
	SXComTransferShaderData ComTrShaderDataVS[SXPP_SETTINGS_SB_PP][SXPP_SETTINGS_SB_SEQUENCE];
	SXComTransferShaderData ComTrShaderDataPS[SXPP_SETTINGS_SB_PP][SXPP_SETTINGS_SB_SEQUENCE];
};

class SXWrapLoaderPPFile
{
public:
	SXWrapLoaderPPFile();
	~SXWrapLoaderPPFile();
	void Load(const char* path);

	void Render(int how_pp,int count_rt_save = 0,int* rt_save_arr = 0);
	void Render(const char* name_pp,const char* how_rt_save);
	void Render(const char* name_pp);

	void RenderComError(SXPostProcessError *error);

	bool IsDefined(const char* pp,int shader_type,const char* shader,const char* define);		//�������� �� ������ � �������
	const char* GetDefine(const char* pp,int shader_type,const char* shader,const char* define);//�������� ��������� �������

	int GetPPNum();	//���������� ���������� ����������� �������������

	//���������� �������� AddShaderData, ���������� ��� ��� �� ����������
	//����������� ���������� ������ �� AddShaderData
	void AddShaderData(const char* pp,int type_shader,int passnum,const char* name_var,void* data,long size);
	void AddShaderData(const char* pp,int type_shader,const char* pass,const char* name_var,void* data,long size);
	void AddShaderData(const char* pp,int type_shader,const char* shader_name_pp,const char* shader_name,const char* name_var,void* data,long size);

	int GetIndexNumPP(const char* pp);//���������� ���������� ����� ������������ �� �����

	//������������� ������
	void InitData(const char* name_pp);
	void InitData(int how_pp);
	void InitDataAll();

	void InitDataComError(SXPostProcessError *error);

	//�������� ����������� ������
	void CheckValidate(const char* name_pp);
	void CheckValidate(int how_pp);
	void CheckValidateAll();

	void CheckValidateComError(SXPostProcessError *error);

	bool IsPPThere(int pp);	//������� �� ����������� � ����� pp

	IDirect3DTexture9* GetTexture(const char* name,int type=-1);
	IDirect3DTexture9* GetTexture(const char* ppname,int ppnum,const char* name,int type=-1);

	void GetTexInfo(const char* ppname,int ppnum,const char* name,D3DSURFACE_DESC* desc,int type = -1); //�������� ������ ��������/������ ��������

private:
	SXLoaderPPFile* PP;
};

//-------------------------------------------

SXWrapLoaderPPFile::SXWrapLoaderPPFile()
{
	PP = new SXLoaderPPFile();
}

SXWrapLoaderPPFile::~SXWrapLoaderPPFile()
{
	SX_SAFE_DELETE(this->PP);
}

int SXWrapLoaderPPFile::GetPPNum()
{
	return PP->GetPPNum();
}

void SXWrapLoaderPPFile::Load(const char *path)
{
	SXPostProcessError error = SXPostProcessError();
	int result = PP->Load(path,&error);

		if(error.Code != SXPP_OK)
		{
			char src_gen[SXPP_SETTINGS_SB_SRC_ERR];
			sprintf(src_gen,"%s%s%s%d","�������� ��������� ������: [",error.GenFileError,"] : ",error.GenStrError);
			char mess[SXPP_SETTINGS_SB_ERROR_MSG];
				if(error.Code == SXPP_ERR_NOT_FILE)
					sprintf(mess,"%s%s%s%s","���� ����-�������� [",error.Str,"] �� ������� �������\n\n",src_gen);
				//��������
				else if(error.Code == SXPP_ERR_NEW_BEGIN_PP)
				{
						//if(result == error.Code)	//error
							sprintf(mess,"%s%s%s%d%s%s%s%s","[",path,"] : ",error.NumStr," - � ����-�������� [",error.Str,"] ������� ������ ������� ����-��������\n\n",src_gen);
						//else	//warning
				}
						else if(error.Code == SXPP_ERR_NOT_FOUND_NAME)
					sprintf(mess,"%s%s%s%d%s%s%s%s","[",path,"] : ",error.NumStr," - �� ������� ����������� [",error.Str,"]\n\n",src_gen);
				else if(error.Code == SXPP_ERR_INVALID_VALUE)
					sprintf(mess,"%s%s%s%d%s%s%s%s%s%s%s%s","[",path,"] : ",error.NumStr," - ���������� �������� [",error.Str,"] : [",error.Str2,"] : [",error.Str3,"] \n\n",src_gen);
				else if(error.Code == SXPP_ERR_MAX_NUM)
					sprintf(mess,"%s%s%s%d%s%s%s%s%s%s","[",path,"] : ",error.NumStr," - �������� ����� �������� [",error.Str,"] ��� [",error.Str2,"] \n\n",src_gen);
				else if(error.Code == SXPP_ERR_REDIFINITION_GDATA)
					sprintf(mess,"%s%s%s%d%s%s%s%s%s%s%s%s","[",path,"] : ",error.NumStr," - �������������� �������� [",SXPP_DET_ITEM_GDATA, "] � ����� [",error.Str,"], ������� ���� ������� ��� �������� � [",error.Str2,"] \n\n",src_gen);
				else if(error.Code == SXPP_ERR_GDATA_PASS)
					sprintf(mess,"%s%s%s%d%s%s%s%s%s%s","[",path,"] : ",error.NumStr," - ������������ ����������  [",SXPP_DET_ITEM_PASS, "] ��� ["SXPP_DET_ITEM_GDATA,"] \n\n",src_gen);
				else if(error.Code == SXPP_ERR_GDATA_SEQUENCE)
					sprintf(mess,"%s%s%s%d%s%s%s%s%s%s","[",path,"] : ",error.NumStr," - ������������ ����������  [",SXPP_DET_ITEM_SEQUENCE, "] ��� ["SXPP_DET_ITEM_GDATA,"] \n\n",src_gen);
			MessageBox(0,mess,SXPP_ERROR_G_MESSAGE,MB_OK|MB_ICONSTOP|MB_SYSTEMMODAL);
		}
}

void SXWrapLoaderPPFile::AddShaderData(const char* pp,int type_shader,int passnum,const char* name_var,void* data,long size)
{
	int error = this->PP->AddShaderData(pp,type_shader,passnum,name_var,data,size);
		if(error < 0)
		{
			//ERROR 
		}
}

void SXWrapLoaderPPFile::AddShaderData(const char* pp,int type_shader,const char* pass,const char* name_var,void* data,long size)
{
	int error = this->PP->AddShaderData(pp,type_shader,pass,name_var,data,size);
		if(error < 0)
		{
			//ERROR 
		}
}

void SXWrapLoaderPPFile::AddShaderData(const char* pp,int type_shader,const char* shader_name_pp,const char* shader_name,const char* name_var,void* data,long size)
{
	int error = this->PP->AddShaderData(pp,type_shader,shader_name_pp,shader_name,name_var,data,size);
		if(error < 0)
		{
			//ERROR 
		}
}


bool SXWrapLoaderPPFile::IsPPThere(int pp)
{
	return this->PP->IsPPThere(pp);
}

IDirect3DTexture9* SXWrapLoaderPPFile::GetTexture(const char* name,int type)
{
	return this->PP->GetTexture(name,type);
}

IDirect3DTexture9* SXWrapLoaderPPFile::GetTexture(const char* ppname,int ppnum,const char* name,int type)
{
	return this->PP->GetTexture(ppname,ppnum,name,type);
}

void SXWrapLoaderPPFile::GetTexInfo(const char* ppname,int ppnum,const char* name,D3DSURFACE_DESC* desc,int type)
{
	this->PP->GetTexInfo(ppname,ppnum,name,desc,type);
}


void SXWrapLoaderPPFile::Render(const char *name_pp)
{
	SXPostProcessError error = SXPostProcessError();
	int result = PP->Render(name_pp,0,&error);

	RenderComError(&error);
}

void SXWrapLoaderPPFile::Render(int how_pp,int count_rt_save,int* rt_save_arr)
{
	SXPostProcessError error = SXPostProcessError();
	int result = PP->Render(how_pp,&error,count_rt_save,rt_save_arr);

	RenderComError(&error);
}

void SXWrapLoaderPPFile::Render(const char* name_pp,const char* how_rt_save)
{
	SXPostProcessError error = SXPostProcessError();
	int result = PP->Render(name_pp,how_rt_save,&error);

	RenderComError(&error);
}

void SXWrapLoaderPPFile::RenderComError(SXPostProcessError *error)
{
		if(error->Code != SXPP_OK)
		{
			char src_gen[SXPP_SETTINGS_SB_SRC_ERR];
			sprintf(src_gen,"%s%s%s%d","�������� ��������� ������: [",error->GenFileError,"] : ",error->GenStrError);
			char mess[SXPP_SETTINGS_SB_ERROR_MSG];
				if(error->Code == SXPP_ERR_NOT_FOUND_PP)
					sprintf(mess,"%s%s%s%s","�� ������ ����-������� [",error->Str,"] \n\n",src_gen);
				else if(error->Code == SXPP_ERR_INVALID_RT_SAVE)
					sprintf(mess,"%s%s%s%s","������� ������������ ������ ���������� [",error->Str,"], ���� ������� ������� ����������� render_target \n\n",src_gen);
				else if(error->Code == SXPP_ERR_INVALID_NUMBER_OF_PP)
					sprintf(mess,"%s%s%s%s%s%s","������� ������ ����� ����-�������� [",error->Str,"], ����� ����-���������[",error->Str2,"] \n\n",src_gen);
			MessageBox(0,mess,SXPP_ERROR_G_MESSAGE,MB_OK|MB_ICONSTOP|MB_SYSTEMMODAL);
		}
}

bool SXWrapLoaderPPFile::IsDefined(const char* pp,int shader_type,const char* shader,const char* define)
{
	return PP->IsDefined(pp,shader_type,shader,define);
}

const char* SXWrapLoaderPPFile::GetDefine(const char* pp,int shader_type,const char* shader,const char* define)
{
	return PP->GetDefine(pp,shader_type,shader,define);
}

void SXWrapLoaderPPFile::CheckValidate(const char* name_pp)
{
	SXPostProcessError error = SXPostProcessError();
	int result = PP->CheckValidate(name_pp,&error);

	CheckValidateComError(&error);
}

void SXWrapLoaderPPFile::CheckValidate(int how_pp)
{
	SXPostProcessError error = SXPostProcessError();
	int result = PP->CheckValidate(how_pp,&error);

	CheckValidateComError(&error);
}

void SXWrapLoaderPPFile::CheckValidateComError(SXPostProcessError *error)
{
		if(error->Code != SXPP_OK)
		{
			char src_gen[SXPP_SETTINGS_SB_SRC_ERR];
			sprintf(src_gen,"%s%s%s%d","�������� ��������� ������: [",error->GenFileError,"] : ",error->GenStrError);
			char mess[SXPP_SETTINGS_SB_ERROR_MSG];
				if(error->Code == SXPP_ERR_NOT_FOUND_PP)
					sprintf(mess,"%s%s%s%s","�� ������ ����-������� [",error->Str,"] \n\n",src_gen);
				else if(error->Code == SXPP_ERR_INVALID_NUMBER_OF_PP)
					sprintf(mess,"%s%s%s%s%s%s","������� ������ ����� ����-�������� [",error->Str,"], ����� ����-���������[",error->Str2,"] \n\n",src_gen);
				else if(error->Code == SXPP_ERR_NON_UNIC_ITEM)
					sprintf(mess,"%s%s%s%s%s%s","�� ���������� ������� [",error->Str,"] : [",error->Str2,"] \n\n",src_gen);
				else if(error->Code == SXPP_ERR_TEX_RT)
					sprintf(mess,"%s%s%s%s","������������ �������� [",error->Str,"] �������� ������� render_target \n\n",src_gen);
				else if(error->Code == SXPP_ERR_NOT_FOUND_ITEM)
					sprintf(mess,"%s%s%s%s%s%s%s%s","�� ������ ������� [",error->Str,"] : [",error->Str2,"] ����������� [",error->Str3,"]  \n\n",src_gen);
				else if(error->Code == SXPP_ERR_DISCREPANCY_VER_SHADER)
					sprintf(mess,"%s%s%s%s%s%s%s%s%s%s","������������� ������ �������� [",error->Str,"]:[",error->Str2,"] & [",error->Str3,"]: [",error->Str4,"]  \n\n",src_gen);
				else if(error->Code == SXPP_ERR_G_NON_UNIC_ITEM)
					sprintf(mess,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s","���������� ����� ��������� [",error->Str,"]:[",error->Str2,"] type [",error->Str3,"] & [",error->Str4,"]:[",error->Str5,"] type [",error->Str6,"]  \n\n",src_gen);
			MessageBox(0,mess,SXPP_ERROR_G_MESSAGE,MB_OK|MB_ICONSTOP|MB_SYSTEMMODAL);
		}
}

void SXWrapLoaderPPFile::InitData(const char* name_pp)
{
	SXPostProcessError error = SXPostProcessError();
	int result = PP->InitData(name_pp,&error);

	InitDataComError(&error);
}

void SXWrapLoaderPPFile::InitData(int how_pp)
{
	SXPostProcessError error = SXPostProcessError();
	int result = PP->InitData(how_pp,&error);

	InitDataComError(&error);
}

void SXWrapLoaderPPFile::InitDataComError(SXPostProcessError *error)
{
		if(error->Code != SXPP_OK)
		{
			char src_gen[SXPP_SETTINGS_SB_SRC_ERR];
			sprintf(src_gen,"%s%s%s%d","�������� ��������� ������: [",error->GenFileError,"] : ",error->GenStrError);
			char mess[SXPP_SETTINGS_SB_ERROR_MSG];
				if(error->Code == SXPP_ERR_NOT_FOUND_PP)
					sprintf(mess,"%s%s%s%s","�� ������ ����-������� [",error->Str,"] \n\n",src_gen);
				else if(error->Code == SXPP_ERR_INVALID_NUMBER_OF_PP)
					sprintf(mess,"%s%s%s%s%s%s","������� ������ ����� ����-�������� [",error->Str,"], ����� ����-���������[",error->Str2,"] \n\n",src_gen);
				else if(error->Code == SXPP_ERR_NOT_FOUND_ITEM)
					sprintf(mess,"%s%s%s%s%s%s%s%s","�� ������ ������� [",error->Str,"] : [",error->Str2,"] � ����-�������� [",error->Str3,"] \n\n",src_gen);
				else if(error->Code == SXPP_ERR_NON_END_REC)
					sprintf(mess,"%s%s%s%s%s%s%s%s%s%s","������� [",error->Str,"] : [",error->Str2,"] ��������� �� ������� [",error->Str3,"] : [",error->Str4,"] ������� ��� �� ���� � ��������� (���������� �������) \n\n",src_gen);
				else if(error->Code == SXPP_ERR_MAX_NUM_REC)
					sprintf(mess,"%s%s%s%s%s%s","������� ����� ������������ ������ ����������� ��������� �������� ��� [",error->Str,"] : [",error->Str2,"] \n\n",src_gen);
				MessageBox(0,mess,SXPP_ERROR_G_MESSAGE,MB_OK|MB_ICONSTOP|MB_SYSTEMMODAL);
		}
}

void SXWrapLoaderPPFile::InitDataAll()
{
	SXPostProcessError error = SXPostProcessError();
	int result = PP->InitDataAll(&error);

	InitDataComError(&error);
}

void SXWrapLoaderPPFile::CheckValidateAll()
{
		for(int i=0;i<this->GetPPNum();i++)
			this->CheckValidate(i);
}

#endif