
#ifndef __sxgcore
#define __sxgcore

//���������� ��������
//{
#define G_RI_INT_COUNT_POLY	0
#define G_RI_INT_COUNT_DIP		1
//}

#include <gdefines.h>

#include <d3d9.h>
#include <d3dx9.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxcore_d.lib")
#else
#pragma comment(lib, "sxcore.lib")
#endif
#include <core\\sxcore.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "DxErr9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <gcore\ModelFile.h>



//���� ����������
#define MTL_TYPE_GEOM 0
#define MTL_TYPE_GRASS 1
#define MTL_TYPE_TREE 2
#define MTL_TYPE_SKIN 3
//#define MTL_LIGHT 4

//������ ����������� ���������, ���������� � ���� �������
#define SXGC_STR_SIZE_DBG_MSG 4096

//
#define SXGC_ERR_NON_DETECTED_D3D -1
#define SXGC_ERR_FAILED_INIT_D3D -2

//���������� mipmap ������� � ����������� ���������
#define SXGC_LOADTEX_COUNT_MIPMAP 5	

//������ � ������� ����� ������������� ����������� ��������
//���� ���������� ������ �� ������� �� ���������� ��������� ���� �������� ���������� ������� ��� ������� �������
#define SXGC_LOADTEX_FORMAT_TEX D3DFMT_FROM_FILE	

SX_LIB_API long SGCore_0GetVersion();			//������ ����������
SX_LIB_API void SGCore_Dbg_Set(report_func rf);	//��������� ������� ������ ���������

//������������� ����������
SX_LIB_API void SGCore_0Create(
	const char* name,			//������������� ��� ����������
	HWND hwnd,					//���������� ���� � ������� ����� �������������� ������
	int width,					//������ ������� �������
	int heigth,					//������ ������� �������
	bool windowed,				//������� ����� ������������ ��? ����� �������������
	DWORD create_device_flags,	//����� �������� ���������� (����������� dx)
	bool is_unic = true			//������ �� ���������� ���� ���������� �� ������ �����
	);

SX_LIB_API void SGCore_0Kill();	//����������� ����

SX_LIB_API IDirect3DDevice9* SGCore_GetDXDevice();	//���������� dx ����������

//����� ����������� ��������� � ���� �������
SX_LIB_API void SGCore_DbgMsg(const char* format, ...);

//��������� ������ � �������������� ����������
//{
SX_LIB_API void SGCore_OnLostDevice();	//�������� ��� ������ ����������
SX_LIB_API int SGCore_OnDeviceReset(int width,int heigth,bool windewed);	//�������� ��� ������� ������ ����������
SX_LIB_API void SGCore_OnResetDevice();	//�������� ��� ������ ���������
//}

//������� ������� ��������� �������� ������� �� �������
//{{
//��������� ����������
SX_LIB_API void SGCore_SetSamplerFilter(DWORD id, DWORD value);	//��� ����������� �����
SX_LIB_API void SGCore_SetSamplerFilter2(DWORD begin_id, DWORD end_id, DWORD value);	//��� ������ ������ �� begin_id �� end_id

//��������� ���������
SX_LIB_API void SGCore_SetSamplerAddress(DWORD id, DWORD value);	//��� ����������� �����
SX_LIB_API void SGCore_SetSamplerAddress2(DWORD begin_id, DWORD end_id, DWORD value);	//��� ������ ������ �� begin_id �� end_id
//}}

//��������� full screen quad (��� ���������� ��� ���� ����� �� ���� ��������)
SX_LIB_API void SGCore_ScreenQuadDraw();


//��������� ���������������� �������
//{
//draw indexed primitive, ������� ���������
typedef void(*g_func_dip) (UINT type_primitive, long base_vertexIndex, UINT min_vertex_index, UINT num_vertices, UINT start_index, UINT prim_count);
//��������� ��������� id, world - ������� �������
typedef void(*g_func_mtl_set) (ID id, float4x4* world);
//�������� ���������, name - ��� �������� � �����������, mtl_type - ��� ��������� �� ������ ������� ��������, MTL_TYPE_
//� ������� ������� �������� ��� ������������ ��������� ����� ��������� �� ��������� mtl_type
typedef ID(*g_func_mtl_load) (const char* name, int mtl_type);
//�������� ���� ���������, �� ������� 0
typedef int(*g_func_mtl_get_sort) (ID id);
//�������� �� ��������� ������� ������� ��������� ���������?
typedef bool(*g_func_mtl_group_render_is_singly) (ID id);
//}

//���������������� ������� (������ �������������� �� ��������� ����������)
//{
SX_LIB_API void SGCore_DIP(UINT type_primitive, long base_vertexIndex, UINT min_vertex_index, UINT num_vertices, UINT start_index, UINT prim_count);
SX_LIB_API void SGCore_MtlSet(ID id, float4x4* world);
SX_LIB_API ID SGCore_MtlLoad(const char* name, int mtl_type);
SX_LIB_API int SGCore_MtlGetSort(ID id);
SX_LIB_API bool SGCore_MtlGroupRenderIsSingly(ID id);
//}

//��������������� �������
//{
SX_LIB_API void SGCore_SetFunc_DIP(g_func_dip func);
SX_LIB_API void SGCore_SetFunc_MtlSet(g_func_mtl_set func);
SX_LIB_API void SGCore_SetFunc_MtlLoad(g_func_mtl_load func);
SX_LIB_API void SGCore_SetFunc_MtlGetSort(g_func_mtl_get_sort func);
SX_LIB_API void SGCore_SetFunc_MtlGroupRenderIsSingly(g_func_mtl_group_render_is_singly func);
//}

//�������
//{{
//�������������  �������� (��������� ����� �������) ���������� �� ������ ��������������� �������������� ����� DWORD
//���� ���� ��� �� ������������� �� ������ ����� �� ��� � ������ ������ ��� �� ������ name ������� ���� �������� SGCore_ShaderLoad
//��� ������� ����������� � ������� 3.0
//���� ��� ������� �� �������� ������ ������ (_) �� ������ ������� ��������� � ����� ����������
//���� ������ �������� ������ ������ (_) �� ������ �� ������� ������� �������� ��� ��� ����� � ������� ��������� ������ � ����� ������
//pp_shader.vs - ����� �� ������������ ����: /pp/pp_shader.vs

//������������ ������ ����� ���������� (�� _)
#define SXGC_SHADER_MAX_SIZE_DIR 64
//������������ ������ ����� � ����������� (����� _)
#define SXGC_SHADER_MAX_SIZE_NAME 64
//����� ������������  ������ ����� �������� � �����������
#define SXGC_SHADER_MAX_SIZE_DIRNAME SXGC_SHADER_MAX_SIZE_DIR + SXGC_SHADER_MAX_SIZE_NAME
//������������ ������ ���� �� ����� ������� (��� ����� �����)
#define SXGC_SHADER_MAX_SIZE_STDPATH 256
//������������ ������ ������� ���� �� ������� (������� ��� �������)
#define SXGC_SHADER_MAX_SIZE_FULLPATH SXGC_SHADER_MAX_SIZE_STDPATH + SXGC_SHADER_MAX_SIZE_DIRNAME

//������������ ����� ����� ���������� � �������
#define SXGC_SHADER_VAR_MAX_SIZE 64
//������������ ���������� ���������� � �������
#define SXGC_SHADER_VAR_MAX_COUNT 64

//���������� �������� � ������� ��������
#define SXGC_SHADER_COUNT_MACRO 12

//���� �������� (int type_shader)
enum ShaderType
{
	st_vertex,	//���������
	st_pixel	//����������
};

//���� �������� ���������� ��������
enum ShaderCheckDouble
{
	scd_none,	//��� ��������
	scd_path,	//�������� �� ���� (����� ������� � �����������)
	scd_name	//�������� �� ����������������� �����
};

//�������� �������
SX_LIB_API ID SGCore_ShaderLoad(
	ShaderType type_shader,	//��� �������
	const char* path,		//��� ����� ������� � �����������
	const char* name,		//��� ������� ������� ���������� ��� ��������
	ShaderCheckDouble is_check_double,	//��������� �� �� ������������ (�� ��������� ����� ����� � �����������)
	D3DXMACRO* macro = 0	//�������
	);

SX_LIB_API void SGCore_ShaderGetName(ShaderType type_shader, ID id, char* name);	//���������� ���������������� ��� ������� � name
SX_LIB_API void SGCore_ShaderGetPath(ShaderType type_shader, ID id, char* path);	//���������� ��� ������ � ����������� � path
SX_LIB_API ID SGCore_ShaderIsExistName(ShaderType type_shader, const char* name);	//���������� �� ������ � ���������������� ������ name, ���� �� �� ���������� id
SX_LIB_API ID SGCore_ShaderIsExistPath(ShaderType type_shader, const char* path);	//���������� �� ������ � ������ ����� � ����������� name, ���� �� �� ���������� id
SX_LIB_API bool SGCore_ShaderIsValidate(ShaderType type_shader, ID id);				//�������� �� ������ � ������ id

//���������� �������
SX_LIB_API void	SGCore_ShaderUpdateN(ShaderType type_shader, const char* name, D3DXMACRO macro[] = 0);
SX_LIB_API void SGCore_ShaderUpdate(ShaderType type_shader, ID id, D3DXMACRO macro[] = 0);

SX_LIB_API void SGCore_ShaderSetStdPath(const char* path);	//���������� ���������� ���� ������ ����� �������
SX_LIB_API void SGCore_ShaderGetStdPath(char* path);		//���������� ���������� ���� ������ ������� �������

//������������� ��� �������
//� ������ ��������
SX_LIB_API void SGCore_ShaderReloadAll();	

SX_LIB_API ID SGCore_ShaderGetID(ShaderType type_shader, const char* shader);	//�������� ������������� ������� �� �����

//���� �������
SX_LIB_API void SGCore_ShaderBindN(ShaderType type_shader, const char* shader);
SX_LIB_API void SGCore_ShaderBind(ShaderType type_shader, ID id);

SX_LIB_API void SGCore_ShaderUnBind();	//��������� ������ ��������

//�������� ������ � ������
//{
//name_var - ��� ���������� ������� ������������� ��������
//data ��������� ��������

//�������� float ��������
SX_LIB_API void SGCore_ShaderSetVRFN(ShaderType type_shader, const char* name_shader, const char* name_var, void* data, int count_float4 = 0);
SX_LIB_API void SGCore_ShaderSetVRF(ShaderType type_shader, ID id, const char* name_var, void* data, int count_float4 = 0);

//�������� int ��������
SX_LIB_API void SGCore_ShaderSetVRIN(ShaderType type_shader, const char* name_shader, const char* name_var, void* data, int count_int4 = 0);
SX_LIB_API void SGCore_ShaderSetVRI(ShaderType type_shader, ID id, const char* name_var, void* data, int count_int4 = 0);
//}
//}}


//��������
//{{
//������������� ������� (��������� ����� �������) ���������� �� ������ ��������������� �������������� ����� DWORD
//���� ���� ���� �� ������������� �� ������ ����� �� ��� � ������ ������ ��� ��� �������� � �����������
//��� �������� ����������� ����� ��������� ������ ������ (_), ������ �� ������� ������� �������� ��� ��� ����� � ������� ��������� ������ � ����� ������
//mtl_tex.dds - ����� �� ������������ ����: /mtl/mtl_tex.dds

//������������ ������ ����� ���������� (�� _)
#define SXGC_LOADTEX_MAX_SIZE_DIR 64
//������������ ������ ����� � ����������� (����� _)
#define SXGC_LOADTEX_MAX_SIZE_NAME 64
//����� ������������  ������ ����� �������� � �����������
#define SXGC_LOADTEX_MAX_SIZE_DIRNAME SXGC_LOADTEX_MAX_SIZE_DIR + SXGC_LOADTEX_MAX_SIZE_NAME
//������������ ������ ���� �� ����� �������� (��� ����� �����)
#define SXGC_LOADTEX_MAX_SIZE_STDPATH 256
//������������ ������ ������� ���� �� �������� (������� ��� ��������)
#define SXGC_LOADTEX_MAX_SIZE_FULLPATH SXGC_LOADTEX_MAX_SIZE_STDPATH + SXGC_LOADTEX_MAX_SIZE_DIRNAME

//���� �������
enum LoadTexType
{
	ltt_load,	//�����������
	ltt_const,	//����������� �����������
	ltt_custom,	//��������� �������������

	//��������������� ����, �� ��� ������ ����� �� ��������� �������� ������� ����� ����
	//���� ���������� ���� ���, � ������ � �������� �� ����� ���� ��� ���� (������ ����� ��� ��������)
	//�� ����� ��������� ltt_load
	ltt_self,	
};

SX_LIB_API void SGCore_LoadTexStdPath(const char* path);	//���������� ����������� ���� ������ ����� ��������
SX_LIB_API void SGCore_LoadTexClearLoaded();				//�������� ������ ����������� �������
SX_LIB_API void SGCore_LoadTexDelete(ID id);				//������� ������� �� id (���������� �� ����)
SX_LIB_API ID SGCore_LoadTexAddName(const char* name, LoadTexType type);//��������� ��� ��������, ������ �������� �� ��� ID (��������� � �������)
SX_LIB_API ID SGCore_LoadTexGetID(const char* name);	//�������� id �� �����
SX_LIB_API void SGCore_LoadTexGetName(ID id, char* name);//�������� ��� �� id

//������� ����� ��� �������� tex � ��������� �� ��� name, ���������� id
//������ ������ ���� �������, ��� ����������� �������� ������ ���� ���������
//��������� ������� ���������� � managed pool (D3DPOOL_MANAGED) ��� ��������� ������ � �������������� ���������� ���� �� ��������
SX_LIB_API ID SGCore_LoadTexCreate(const char* name, IDirect3DTexture9* tex);

//��������/������������� �������� name, ���� �������� �� ���� � ������ �� ���������
//���� �������� ���� ��������, �� ��� � ��� ������� �� ��������, �� ��� ����� ��� ��������� 
//�� ����� ������������ ��� ��������������� ltt_self, ����� ��� �������� �� ���������
SX_LIB_API ID SGCore_LoadTexUpdateN(const char* name, LoadTexType type);
SX_LIB_API void SGCore_LoadTexUpdate(ID id);//��������/������������� ��������

SX_LIB_API IDirect3DTexture9* SGCore_LoadTexGetTex(ID id);	//���������� �������� �� id

//�������� ���� ������� ������������ � �������
//����� �������� ������ ���� �������
//������� ������� ��������� ���� �� �� ����������� �������� �� ������ ��������� � ������ ����� ������
SX_LIB_API void SGCore_LoadTexLoadTextures();	
//}


//RENDER TARGETS
//{{
//����� � �������������� ���������� ���� ��������

//�������� ����� render target
SX_LIB_API ID SGCore_RTAdd(
	UINT width,				//������
	UINT height,			//������
	UINT levels,			//���������� mip-map �������
	DWORD usage,			//
	D3DFORMAT format,		//������ �� D3DFORMAT
	D3DPOOL pool,			//��� ����� ��������� ��������, �� D3DPOOL
	const char* name,		//��� rt
	//���������� �������� rt ������������ ������� �������
	//(���� rt � ������ ������� ��������� �� 1, ���� rt ������ �� 0.5 �� 0.5)
	//���� ������� ������������� �������� �� ������� 0, ��� ����� ��� ����������� �������� ��� �������������� ����������
	float coeffullscreen
	);

SX_LIB_API void SGCore_RTDeleteN(const char* text);	//������� rt �� �����
SX_LIB_API void SGCore_RTDelete(ID num);			//������� rt �� id

SX_LIB_API ID SGCore_RTGetNum(const char* text); //���������� id �� �����

SX_LIB_API IDirect3DTexture9* SGCore_RTGetTextureN(const char* text);	//���������� �������� �� �����
SX_LIB_API IDirect3DTexture9* SGCore_RTGetTexture(ID num);				//���������� �������� �� id
//}


//��������� ����������� ������ dse
struct ISXDataStaticModel : public IBaseObject
{
	virtual ~ISXDataStaticModel(){};

	virtual ISXDataStaticModel* GetCopy()=0;	//�������� ���������� ����� ������
	
	IDirect3DVertexBuffer9* VertexBuffer;	//�������� �����
	IDirect3DIndexBuffer9* IndexBuffer;		//��������� �����
	vertex_static* ArrVertBuf;				//������ ������
	UINT* ArrIndBuf;						//������ ��������

	UINT SubsetCount;		//���������� ��������
	char** ArrTextures;		//������ ���� ������� ��� ����������
	UINT* StartIndex;		//������ ��������� ������� �������� ��� ������ ���������
	UINT* IndexCount;		//������ ���������� �������� ��� ������ ���������
	UINT* StartVertex;		//������ ��������� ������� ������ ��� ������ ���������
	UINT* VertexCount;		//������ ���������� ������ ��� ������ ���������
	UINT AllIndexCount;		//����� ���������� ��������
	UINT AllVertexCount;	//����� ���������� ������
};

SX_LIB_API ISXDataStaticModel* SGCore_StaticModelCr();	//������� ����������� ������
SX_LIB_API void SGCore_StaticModelLoad(const char* file, ISXDataStaticModel** data);	//��������� ����������� ������, data ���������������� ������
SX_LIB_API void SGCore_StaticModelSave(const char* file, ISXDataStaticModel** data);	//��������� ����������� ������
SX_LIB_API IDirect3DVertexDeclaration9* SGCore_StaticModelGetDecl();	//���������� ���������� ������ ����������� ������
///////////

//������� ������ � ����������� ���������
//��� ����������� ������������� ���������� ������� ���������� �������/�������/������� ����� ���� CalculateWorld
struct ISXTransObject : public IBaseObject
{
	virtual ~ISXTransObject(){};

	SX_ALIGNED_OP_MEM

	virtual inline float4x4* CalcWorld() = 0;

	float3 Position;
	float3 Rotation;
	float3 Scale;
	float4x4 World;
};

SX_LIB_API ISXTransObject* SGCore_CrTransObject();	//������� ISXTransObject

//��������� ����������� �������������� ������� � ������������ ������
struct SXPosBBScreen
{
	float x;		//������� �� ��� x � ������������ ������
	float y;		//������� �� ��� y � ������������ ������
	float width;	//������ � ��������
	float height;	//������ � ��������
	float maxdepth;	//����� ������� ������� 0-1
	float mindepth;	//������ ������ ������� 0-1
	bool IsVisible;	//??
	bool IsIn;		//??
};


//����� ��������������� ������
//��� �������� �������� � ��������� ���������� ������� CalculateBound
//SetMinMax, GetMinMax �� ������ CalculateWorldAndTrans ���������� �������������������� ������
//�������� ������ ���������� Bound � Object �������� CalculateWorldAndTrans
class ISXBound : public virtual ISXTransObject
{
public:
	virtual ~ISXBound(){};

	SX_ALIGNED_OP_MEM

	virtual void CalcBound(IDirect3DVertexBuffer9* vertex_buffer, DWORD count_vert, DWORD bytepervert) = 0;

	//������� �������� ������� ������� � ������������� �������� � ���������
	virtual float4x4* CalcWorldAndTrans() = 0;

	virtual void GetPosBBScreen(SXPosBBScreen *res, float3* campos, float3* sizemapdepth, float4x4* mat) = 0;

	virtual void SetMinMax(float3* min, float3* max) = 0;
	virtual void GetMinMax(float3* min, float3* max) = 0;

	virtual void SetSphere(float3* center, float* radius) = 0;
	virtual void GetSphere(float3* center, float* radius) = 0;

	virtual bool IsPointInSphere(float3* point) = 0;
	virtual bool IsPointInBox(float3* point) = 0;

protected:
	float3 Min;
	float3 Max;

	float3 Center;
	float Radius;
};

SX_LIB_API ISXBound* SGCore_CrBound(); //������� ISXBound

/////////////

//�������� ���� (ID3DXMesh) ������ 
SX_LIB_API void SGCore_FCreateCone(
	float fTopRadius,		//������� ������
	float fBottomRadius,	//������ ������
	float fHeight,			//�����
	ID3DXMesh ** ppMesh,	//�������� ���
	UINT iSideCount			//���������� ������??
	);

//������� ��������������� ������ �� ���������� �����
SX_LIB_API void SGCore_FCompBoundBox(IDirect3DVertexBuffer9* vertex_buffer, ISXBound** bound, DWORD count_vert, DWORD bytepervert); //??
SX_LIB_API void SGCore_FCompBoundBox2(IDirect3DVertexBuffer9* vertex_buffer, ISXBound* bound, DWORD count_vert, DWORD bytepervert);	//??

//�������� ���� (ID3DXMesh) ��������������� ������
SX_LIB_API void SGCore_FCreateBoundingBoxMesh(float3* min, float3* max, ID3DXMesh** bbmesh);

//����������� ������� ���������
//{
//����������� ��������� �������
SX_LIB_API void SGCore_OptimizeIndecesInSubsetUint16(uint16_t* ib, uint16_t numFaces, uint16_t numVerts);
SX_LIB_API void SGCore_OptimizeIndecesInSubsetUint32(uint32_t* ib, uint32_t numFaces, uint32_t numVerts);
//}


//������� �������� ��������� ����� � ������ � ������� �������
//{
//�������� ��������� �����/����� � ����� 
//2d - �� ��������� x � z ��������� 
//3d - �� ��������� ���� ���� ���������
//Abs - ���������� ���������� ������
SX_LIB_API bool SGCore_0InPos2D(float3* min, float3* max, float3* pos);	
SX_LIB_API bool SGCore_0InPosAbs2D(float3* min, float3* max, float3* pos);
SX_LIB_API int SGCore_0CountPosPoints2D(float3* min, float3* max, float3* p1, float3* p2, float3* p3);
SX_LIB_API int SGCore_0CountPosPointsAbs2D(float3* min, float3* max, float3* p1, float3* p2, float3* p3);
SX_LIB_API bool SGCore_0InPosPoints2D(float3* min, float3* max, float3* p1, float3* p2, float3* p3);
SX_LIB_API bool SGCore_0InPos3D(float3* min, float3* max, float3* pos);
SX_LIB_API bool SGCore_0InPosAbs3D(float3* min, float3* max, float3* pos);
SX_LIB_API int SGCore_0CountPosPoints3D(float3* min, float3* max, float3* p1, float3* p2, float3* p3);
SX_LIB_API int SGCore_0CountPosPointsAbs3D(float3* min, float3* max, float3* p1, float3* p2, float3* p3);
SX_LIB_API bool SGCore_0InPosPoints3D(float3* min, float3* max, float3* p1, float3* p2, float3* p3);

//������� � ������� ������ ���� ������� ����������������
//���������� (octo) ������� ������ (�� ���� ���� ����)
SX_LIB_API void SGCore_0ComBoundBoxArr8(ISXBound* bound, ISXBound** bound_arr);
//������������ (quad) ������� ������ (�� ���� ���� x � z)
SX_LIB_API void SGCore_0ComBoundBoxArr4(ISXBound* bound, ISXBound** bound_arr);
//}

///////////////
//��������� �������� ���������
struct SXFrustumPlane
{
	float3 Normal;
	float Distance;

	SX_ALIGNED_OP_MEM

	void Normalize()
	{
			float denom = sqrt((Normal.x*Normal.x) + (Normal.y*Normal.y) + (Normal.z*Normal.z));
			Normal.x = Normal.x / denom;
			Normal.y = Normal.y / denom;
			Normal.z = Normal.z / denom;
			Distance = Distance / denom;
	}
};

//����� ����������� �������
class ISXFrustum : public IBaseObject
{
public:
	virtual ~ISXFrustum(){};

	SX_ALIGNED_OP_MEM

	virtual void Update(const float4x4* view, const float4x4* proj) = 0;

	virtual bool PointInFrustum(const float3 *point) = 0;
	virtual bool PolyInFrustum(const float3* p1, const float3* p2, const float3* p3) = 0;
	virtual bool PolyInFrustumAbs(const float3* p1, const float3* p2, const float3* p3) = 0;

	virtual bool SphereInFrustum(const float3 *point, float radius) = 0;

	virtual bool SphereInFrustumAbs(const float3 *point, float radius) = 0;
	virtual bool BoxInFrustum(float3* min, float3* max) = 0;

//protected:
	SXFrustumPlane ArrFrustumPlane[6];

	float3	Point[8];
	float3	Center;
};

SX_LIB_API ISXFrustum* SGCore_CrFrustum(); //������� ISXFrustum


//����� ������
class ISXCamera : public IBaseObject
{
public:
	virtual ~ISXCamera(){};

	SX_ALIGNED_OP_MEM

	//��������
	virtual inline void PosLeftRight(float units) = 0;	//�����/������
	virtual inline void PosUpDown(float units) = 0;		//�����/����
	virtual inline void PosFrontBack(float units) = 0;	//������/�����

	//��������
	virtual inline void RotUpDown(float angle) = 0;		//�������� �����/����
	virtual inline void RotRightLeft(float angle) = 0;	//�������� ������/�����
	virtual inline void Roll(float angle) = 0;			//����

	virtual inline void GetViewMatrix(float4x4* view_matrix) = 0;//�������� ������� ���� � view_matrix

	//�������
	virtual inline void GetPosition(float3* pos) = 0;
	virtual inline void SetPosition(float3* pos) = 0;

	//����������� �������
	virtual inline void GetDirection(float3* dir) = 0;
	virtual inline void SetDirection(float3* dir) = 0;

	//����������� �������
	virtual inline void GetRight(float3* right) = 0;
	virtual inline void GetUp(float3* up) = 0;
	virtual inline void GetLook(float3* look) = 0;
	virtual inline void GetRotation(float3* rot) = 0;

	//������� �� ����
	virtual inline float GetRotationX() = 0;
	virtual inline float GetRotationY() = 0;
	virtual inline float GetRotationZ() = 0;

	ISXFrustum* ObjFrustum;	//������� ���� ������

	float3 LastVal; //??
	bool IsAccel;	//??

protected:
	float3 Right;
	float3 Up;
	float3 Look;

	float3 Position;

	float AngleUpDown, AngleRightLeft, AngleRoll;
};

SX_LIB_API ISXCamera* SGCore_CrCamera();	//������� ISXCamera


//SKY BOX
//{
SX_LIB_API void SGCore_SkyBoxCr();	//��������
SX_LIB_API bool SGCore_SkyBoxIsCr();//��������������� �� skybox
//���������� ���� �������� �������
SX_LIB_API void SGCore_SkyBoxSetStdPathTex(const char* path);
SX_LIB_API void SGCore_SkyBoxGetStdPathTex(char* path);

//!���������� ��������
SX_LIB_API void SGCore_SkyBoxLoadTex(const char *texture);	//�������� ��������, texture - ��� �������� � �����������
SX_LIB_API void SGCore_SkyBoxChangeTex(const char *texture);//����� ��������, texture - ��� �������� � �����������

//���� �� ������� �������� �������� �� ��� y
SX_LIB_API void SGCore_SkyBoxSetRot(float angle);	
SX_LIB_API float SGCore_SkyBoxGetRot();

//���� � ������� ����� ������� �������� 0-1, ����� ���������� - �� ������� ����� �������
SX_LIB_API void SGCore_SkyBoxSetColor(float4_t* color);
SX_LIB_API void SGCore_SkyBoxGetColor(float4_t* color);

//������ ���������, timeDelta - ����� ������� �����, pos - ������� ����������� (y ���������� ���������� �������)
SX_LIB_API void SGCore_SkyBoxRender(float timeDelta, float3* pos);
//}

//SKY CLOUDS
//{
//������� ��������� ������������ xz �� ������� ��������� (�2) ������������ ��������, � ���������� ��������
//��������� ���������

SX_LIB_API void SGCore_SkyCloudsCr();	//��������
SX_LIB_API bool SGCore_SkyCloudsIsCr();	//��������������� �� sky clouds
//���������� ���� �������� �������
SX_LIB_API void SGCore_SkyCloudsSetStdPathTex(const char* path);
SX_LIB_API void SGCore_SkyCloudsGetStdPathTex(char* path);

//��������� �������� � �������
//��� ��� ������� ������� ���������� �� ����� ���� ������ ������� �������� ������, ���������� ������� ��������� ������ � 2 ���� ������ ��� ���� ��������� �������
SX_LIB_API void SGCore_SkyCloudsSetWidthHeightPos(float width, float height, float3* pos);

//!������� 2� ��������
SX_LIB_API void SGCore_SkyCloudsLoadTex(const char *texture);	//�������� ��������, texture - ��� �������� � �����������
SX_LIB_API void SGCore_SkyCloudsChangeTex(const char *texture);	//�������� ��������, texture - ��� �������� � �����������

//���� �������� �� ��� y
SX_LIB_API void SGCore_SkyCloudsSetRot(float angle);
SX_LIB_API float SGCore_SkyCloudsGetRot();

//���������� ������������
SX_LIB_API void SGCore_SkyCloudsSetAlpha(float alpha);
SX_LIB_API float SGCore_SkyCloudsGetAlpha();

//���� � ������� ����� �������� ������ 0-1, ����� ���������� - �� ������� ����� �������
SX_LIB_API void SGCore_SkyCloudsSetColor(float4_t* color);
SX_LIB_API void SGCore_SkyCloudsGetColor(float4_t* color);

//������ �������, timeDelta - ����� ������� �����, pos - ������� ����������� (y ���������� ���������� �������), is_shadow - ��� ����� �� ��������?
SX_LIB_API void SGCore_SkyCloudsRender(DWORD timeDetlta, float3* pos, bool is_shadow);
//}

#endif