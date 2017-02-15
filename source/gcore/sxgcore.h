
#ifndef __sxgcore
#define __sxgcore

//���������� ��������
//{
#define SGCORE_RI_INT_COUNT_POLY	0
#define SGCORE_RI_INT_COUNT_DIP		1
//}

#include <gdefines.h>

#include <d3d9.h>
#include <d3dx9.h>
#define SM_D3D_CONVERSIONS
#include <sxmath.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "DxErr9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <gcore\ModelFile.h>

#include <core\sxcore.h>

#define SXGC_STR_SIZE_DBG_MSG 4096

#define SXGC_ERR_NON_DETECTED_D3D -1
#define SXGC_ERR_FAILED_INIT_D3D -2

typedef void(*g_func_dip) (UINT type_primitive, long base_vertexIndex, UINT min_vertex_index, UINT num_vertices, UINT start_index, UINT prim_count);
typedef void(*g_func_set_material) (UINT id, float4x4* world);
typedef long(*g_func_load_material) (const char* name, int mtl_type);

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

//{
SX_LIB_API void SGCore_DIP(UINT type_primitive, long base_vertexIndex, UINT min_vertex_index, UINT num_vertices, UINT start_index, UINT prim_count);
SX_LIB_API void SGCore_SetMtl(UINT id, float4x4* world);
SX_LIB_API long SGCore_LoadMtl(const char* name, int mtl_type);

SX_LIB_API void SGCore_SetFunc_DIP(g_func_dip func);
SX_LIB_API void SGCore_SetFunc_SetMtl(g_func_set_material func);
SX_LIB_API void SGCore_SetFunc_LoadMtl(g_func_load_material func);
//}

//�������
//{{
//�������������  �������� (��������� ����� �������) ���������� �� ������ ��������������� �������������� ����� DWORD
//���� ���� ��� �� ������������� �� ������ ����� �� ��� � ������ ������ ��� �� ������ name ������� ���� �������� SGCore_ShaderLoad
//��� ������� ����������� � ������� 3.0
//���� ��� ������� �� �������� ������ ������ (_) �� ������ ������� ��������� � ����� ����������
//���� ������ �������� ������ ������ (_) �� ������ �� ������� ������� �������� ��� ��� ����� � ������� ��������� ������ � ����� ������
//pp_shader.vs - ����� �� ������������ ����: /pp/pp_shader.vs

//���� �������� (int type_shader)
#define SXGC_SHADER_VERTEX 0
#define SXGC_SHADER_PIXEL 1

//�������� �������
SX_LIB_API DWORD SGCore_ShaderLoad(
	int type_shader,		//��� �������
	const char* path,		//��� ����� ������� � �����������
	const char* name,		//��� ������� ������� ���������� ��� ��������
	int is_check_double,	//��������� �� �� ������������ (�� ��������� ����� ����� � �����������)
	D3DXMACRO* macro = 0	//�������
	);

SX_LIB_API void SGCore_ShaderGetName(int type_shader, DWORD id, char* name);	//���������� ��� ������� � name
SX_LIB_API DWORD SGCore_ShaderIsExist(int type_shader, const char* name);		//���������� �� ������ � ������ name, ���� �� �� ���������� id
SX_LIB_API bool SGCore_ShaderIsValidate(int type_shader, DWORD id);				//�������� �� ������ � ������ id

//���������� �������
SX_LIB_API void	SGCore_ShaderUpdateN(int type_shader, const char* name, D3DXMACRO macro[] = 0);
SX_LIB_API void SGCore_ShaderUpdate(int type_shader, DWORD id, D3DXMACRO macro[] = 0);

SX_LIB_API void SGCore_ShaderSetStdPath(const char* path);	//���������� ���������� ���� ������ ����� �������
SX_LIB_API void SGCore_ShaderGetStdPath(char* path);		//���������� ���������� ���� ������ ������� �������

//������������� ��� �������
//� ������ ��������
SX_LIB_API void SGCore_ShaderReloadAll();	

SX_LIB_API DWORD SGCore_ShaderGetID(int type_shader, const char* shader);	//�������� ������������� ������� �� �����

//���� �������
SX_LIB_API void SGCore_ShaderBindN(int type_shader, const char* shader);
SX_LIB_API void SGCore_ShaderBind(int type_shader, DWORD shader);

SX_LIB_API void SGCore_ShaderUnBind();	//��������� ������ ��������

//�������� ������ � ������
//{
//name_var - ��� ���������� ������� ������������� ��������
//data ��������� ��������

//�������� float ��������
SX_LIB_API void SGCore_ShaderSetVRFN(int type_shader, const char* name_shader, const char* name_var, void* data);
SX_LIB_API void SGCore_ShaderSetVRF(int type_shader, DWORD num_shader, const char* name_var, void* data);

//�������� int ��������
SX_LIB_API void SGCore_ShaderSetVRIN(int type_shader, const char* name_shader, const char* name_var, void* data);
SX_LIB_API void SGCore_ShaderSetVRI(int type_shader, DWORD num_shader, const char* name_var, void* data);
//}
//}}


//��������
//{{
//������������� ������� (��������� ����� �������) ���������� �� ������ ��������������� �������������� ����� DWORD
//���� ���� ���� �� ������������� �� ������ ����� �� ��� � ������ ������ ��� ��� �������� � �����������
//��� �������� ����������� ����� ��������� ������ ������ (_), ������ �� ������� ������� �������� ��� ��� ����� � ������� ��������� ������ � ����� ������
//mtl_tex.dds - ����� �� ������������ ����: /mtl/mtl_tex.dds

SX_LIB_API void SGCore_LoadTexStdPath(const char* path);
SX_LIB_API DWORD SGCore_LoadTexAddName(const char* name);	//��������� ��� ��������, ������ �������� �� ��� ID (��������� � �������)
SX_LIB_API DWORD SGCore_LoadTexGetID(const char* name);		//�������� id �� �����
SX_LIB_API void SGCore_LoadTexGetName(DWORD id, char* name);//�������� ��� �� id

//������� ����� ��� �������� tex � ��������� �� ��� name, ���������� id
//������ ������ ���� �������, ��� ����������� �������� ������ ���� ���������
//��������� ������� ���������� � managed pool (D3DPOOL_MANAGED) ��� ��������� ������ � �������������� ���������� ���� �� ��������
SX_LIB_API DWORD SGCore_LoadTexCreate(const char* name, IDirect3DTexture9* tex);	
SX_LIB_API DWORD SGCore_LoadTexUpdateN(const char* name);	//��������/������������� �������� name, ���� �������� �� ���� � ������ �� ���������
SX_LIB_API void SGCore_LoadTexUpdate(DWORD id);				//��������/������������� ��������

SX_LIB_API IDirect3DTexture9* SGCore_LoadTexGetTex(DWORD id);	//���������� �������� �� id

//�������� ���� ������� ������������ � �������
//����� �������� ������ ���� �������
//������� ������� ��������� ���� �� �� ����������� �������� �� ������ ��������� � ������ ����� ������
SX_LIB_API void SGCore_LoadTexLoadTextures();	
//}


//RENDER TARGETS
//{{

//�������� ����� render target
SX_LIB_API DWORD SGCore_RTAdd(
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
SX_LIB_API void SGCore_RTDelete(DWORD num);			//������� rt �� id

SX_LIB_API DWORD SGCore_RTGetNum(const char* text); //���������� id �� �����

SX_LIB_API IDirect3DTexture9* SGCore_RTGetTextureN(const char* text);	//���������� �������� �� �����
SX_LIB_API IDirect3DTexture9* SGCore_RTGetTexture(DWORD num);			//���������� �������� �� id
//}


//��������� ����������� ������ dse
struct ISXDataStaticModel : public IBaseObject
{
	virtual ~ISXDataStaticModel(){};

	virtual ISXDataStaticModel* GetCopy()=0;	//�������� ���������� ����� ������
	
	IDirect3DVertexBuffer9* VertexBuffer;	//�������� �����
	IDirect3DIndexBuffer9* IndexBuffer;		//��������� �����
	vertex_static* ArrVertBuf;				//������ ������
	DWORD* ArrIndBuf;						//������ ��������

	DWORD SubsetCount;		//���������� ��������
	char** ArrTextures;		//������ ���� ������� ��� ����������
	UINT* StartIndex;		//������ ��������� ������� �������� ��� ������ ���������
	UINT* IndexCount;		//������ ���������� �������� ��� ������ ���������
	UINT* StartVertex;		//������ ��������� ������� ������ ��� ������ ���������
	UINT* VertexCount;		//������ ���������� ������ ��� ������ ���������
	UINT AllIndexCount;		//����� ���������� ��������
	UINT AllVertexCount;	//����� ���������� ������
};

SX_LIB_API ISXDataStaticModel* SGCore_CrDSModel();	//������� ����������� ������
SX_LIB_API void SGCore_LoadStaticModel(const char* file, ISXDataStaticModel** data);	//��������� ����������� ������, data ���������������� ������
SX_LIB_API void SGCore_SaveStaticModel(const char* file, ISXDataStaticModel** data);	//��������� ����������� ������

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

SX_LIB_API void SGCore_SkyCloudsCr();//��������

//���������� ���� �������� �������
SX_LIB_API void SGCore_SkyCloudsSetStdPathTex(const char* path);
SX_LIB_API void SGCore_SkyCloudsGetStdPathTex(char* path);

//��������� �������� � �������
//��� ��� ������� ������� ���������� �� ����� ���� ������ ������� ������� ������, ���������� ������� ��������� ������ � 2 ���� ������ ��� ���� ��������� �������
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