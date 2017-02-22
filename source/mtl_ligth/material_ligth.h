
#ifndef __sxmlight
#define __sxmlight

#include <gdefines.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <sxmath.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "DxErr9.lib")
#pragma comment(lib, "d3dx9.lib")

//���� ���������� �����
#define LIGHTS_TYPE_NONE -1		//�� �������������
#define LIGHTS_TYPE_GLOBAL 0	//����������
#define LIGHTS_TYPE_POINT 1		//��������
#define LIGHTS_TYPE_DIRECTION 2	//������������

#define LIGHTS_TYPE_SHADOWED_STATIC 0		//����������� �������� �����, ���� ����������� ������ ��������� ������ (��� ������������), ����� �� �����������
#define LIGHTS_TYPE_SHADOWED_DYNAMIC 1		//��������� ������������ ����

#define LIGHTS_UPDATE_MAX_COUNT_FOR_STATIC 3	//������������ ���������� ���������� ����������� ���������� �����, � ������ ������ �������

//��������� ��� ������� ����� �������� ��� �������� ���������� ���������
//������ LIGHTS_UPDATE_L0_DIST - ���������� ����� ������ ����
//������ LIGHTS_UPDATE_L2_DIST - ���������� �� �����
#define LIGHTS_UPDATE_L0_DIST 10	//
#define LIGHTS_UPDATE_L1_DIST 30	//
#define LIGHTS_UPDATE_L2_DIST 70	//

//���������� ���������� ������� ����������� �����
//���������: LIGHTS_UPDATE_PSSM_SPLIT*number_split
//������ ������ ����� ����������� ������ ����, ������ ����� ����
#define LIGHTS_UPDATE_PSSM_SPLIT 1		
#define LIGHTS_UPDATE_PSSM_SPLIT_5 2	//����������� ���������� ���������� ������ ��� 5 ������

#define LIGHTS_LOCAL_STD_TOP_RADIUS 0.1	//����������� �������� ��������/���������� ������� ��� ������������� �����
#define LIGHTS_LOCAL_STD_NEAR 0.1		//����������� �������� ������� ��������� ��������� ��� ����� ���������� �����

//******************
//���� ����� ��� ����� ������������ �� ������� ���������
//���� ������ ������, � ��� ����������� �� ���� (LIGHTS_GLOBAL_MAX_POWER), �� ��������� ��������� ����� ����� ������� ��������� �����
//������, ��� ��� ��� real-time ��������, ���� ������� ���������
//���� ����� � ������� ���������� ��� sqrt(power/LIGHTS_GLOBAL_MAX_POWER), ���� ��������� ������ ����� ������������ ��� �����
//����� ������� � ����� ������ � ����� ������� � �� �������� ����� ������� ���� �����
//������ ����� ����� ��������� ���������� ��������� � ����������� (��� ������������ ����) �� ��������� ���������� ���� ������� ������ � ����������� (LIGHTS_LOCAL_MAX_POWER)
//******************
#define LIGHTS_GLOBAL_MAX_POWER 200.f	//������������ ���� ����������� �����
#define LIGHTS_LOCAL_MAX_POWER 100.f	//������������ ���� ���������� �����
#define LIGHTS_GLOBAL_STD_RADIUS 999999	//������ ����������� ���������

#define LIGHTS_POS_G_MAX 1000	//������������ ����������� ����� (����� ��� ������������ �����)

SX_LIB_API long SML_0GetVersion();			//������ ����������
SX_LIB_API void SML_Dbg_Set(report_func rf);//���������� ������� ��������� ���������

//������������ ����������
SX_LIB_API void SML_0Create(
	const char* name,				//������������� ���
	IDirect3DDevice9* device,		//dx ���������� (��� ������������������)
	const char* std_path_material,	//���������� ���� �� ���������� � �����������
	const char* std_path_mesh,		//���������� ���� �� ���������� � ������
	float2_t* winsize,				//������ ���� � ������� ���������� ������
	float projfov,					//fov ��������
	bool is_unic = true				//������ �� ���������� ���� ���������� �� �����
	);

SX_LIB_API void SML_0Kill();

//��������� ������ � �������������� ����������
SX_LIB_API void SML_OnLostDevice();	//�������� ��� ������� ����������
//�������� ��� �������������� ����������, � ��������� ���������� ������� � ������� ������
SX_LIB_API void SML_OnResetDevice(
	int width,		//������ ����
	int heigth,		//������ ����
	float projfov	//fov ����
	);

//��������� �������� ����� ��� �����
//{
//���������
SX_LIB_API void SML_LigthsSettLCoefSizeDepth(float coef);	//��� ���������� �����
SX_LIB_API void SML_LigthsSettGCoefSizeDepth(float coef);	//��� ����������� �����

//�����������
SX_LIB_API float SML_LigthsGettLCoefSizeDepth();	//��������� ����
SX_LIB_API float SML_LigthsGettGCoefSizeDepth();	//���������� ����
//}

//���������� ����������� ��������� �� ��������� ������� ������ � ������� ����
SX_LIB_API void SML_LigthsUpdate(float3* const_cam_pos,float4x4* camview);

SX_LIB_API void SML_LigthsSave(const char* path);	//��������� ������ �����
SX_LIB_API void SML_LigthsLoad(const char* path);	//��������� ������ �����

SX_LIB_API void SML_LigthsClear();		//�������� ������ �����
SX_LIB_API long SML_LigthsGetCount();	//����� ���������� �����
SX_LIB_API long SML_LigthsGetIDOfKey(long key);	//�������� id �� ����� (����������� ������), � ������� � ������ ������� ������ �������

//������� �������� ���� (������ �� ��� �������)
SX_LIB_API ID SML_LigthsCreatePoint(
	float3* center,		//����� ����� (�������)
	float power,		//���� �����
	float dist,			//��������� �� ������� ���������������� ����
	float3* color,		//���� � �������� 0-1
	bool isglobal,		//���������� �� ���� (���� ������)
	bool is_shadowed	//����������� �� ���� ����
	);

//������� ������������ ����
SX_LIB_API ID SML_LigthsCreateDirection(
	float3* pos,		//������� ����� (�������)
	float power,		//���� �����
	float dist,			//��������� �� ������� ���������������� ����
	float3* color,		//���� � �������� 0-1
	float3* dir,		//����������� ������� (����� float3(0,-1,0))
	float top_radius,	//������� (���������) ������
	float angle,		//����
	bool is_shadow		//����������� �� ���� ����
	);

SX_LIB_API int SML_LigthsGetType(ID id);	//���������� ��� �����

SX_LIB_API ID SML_LigthsCreateCopy(ID id);	//������� ����� ������� � ������� �� ��� id
SX_LIB_API void SML_LigthsDeleteLight(ID id);	//�������� �����

//��� �����, name - ���������� ������
SX_LIB_API char* SML_LigthsGetName(ID id);
SX_LIB_API void SML_LigthsSetName(ID id, const char* name);

//������������ �����, ��������� ���������� ��������� ��������
SX_LIB_API ID SML_LigthsReCreatePoint(ID id, float3* center, float power, float dist, float3* color, bool isglobal, bool is_shadowed);
SX_LIB_API ID SML_LigthsReCreateDirection(ID id, float3* pos, float power, float dist, float3* color, float3* dir, float top_radius, float angle, bool is_shadow);

//������ �  ����� ��������� �����
//{
//�������� �������������� ����������� ����������� ������ � ������� �����
//������������� ����� ������������ (���������, � �� ��������� �������) ���������
SX_LIB_API bool SML_LigthsExistsSource(ID id);					//���� �� �������� � �����
SX_LIB_API void SML_LigthsBindToGroupSource(ID id, int group);	//�������� (�������������) ��������� �������� � ������� �����
SX_LIB_API long SML_LigthsGetBindedGroupSource(ID id);			//����� ��������� ������� ��������� � ������� �����
SX_LIB_API long SML_LigthsGetCountGroupSource(ID id);				//����� ���������� �������� � ����
SX_LIB_API const char* SML_LigthsGetPathNameSource(ID id);		//������������� ���� �� ����� � �����
SX_LIB_API const char* SML_LigthsGetNameGroupSource(ID id, int group);//��� ��������� ����, group - ����� ��������� (��������� � ����)
SX_LIB_API void SML_LigthsLoadSource(ID id, const char* path);	//��������� ��� �� �������������� ���� path, � ��������� �� ������� 0 ���������
//}

//������
//{
//��������� ���� ���������� ����� �� ����� �����������, 
//�� ��������� ��������� ��������� ������� ��������� � ����� �����
SX_LIB_API void SML_LigthsRenderAllExceptGroupSource(ID id, DWORD timeDelta);

//��������� ���� ��������� �����, render_bind_group - �������� �� �� ������ ������� ��������� � �����
SX_LIB_API void SML_LigthsRenderSource(ID id, bool render_bind_group, DWORD timeDelta);

//��������� ��������������� ������
SX_LIB_API void SML_LigthsRender(ID id, DWORD timeDelta);
//}

//���� �����
SX_LIB_API void SML_LigthsGetColor(ID id, float3* color);
SX_LIB_API void SML_LigthsSetColor(ID id, float3* vec);

//������� �����
//for_mesh - ������� ���� ���������
//greal �������� �������� ����������, � ������ ���� � ��� ���������� �������� �����
SX_LIB_API void SML_LigthsGetPos(ID id, float3* vec, bool for_mesh, bool greal = false);
SX_LIB_API void SML_LigthsSetPos(ID id, float3* vec, bool greal = false);

//���� �����
SX_LIB_API void SML_LigthsSetPower(ID id, float power);
SX_LIB_API float SML_LigthsGetPower(ID id);
SX_LIB_API float SML_LigthsGetPowerDiv(ID id);	//���������� "������������������� �������� ����" ��� �������� � ������

SX_LIB_API float SML_LigthsGetDist(ID id);	//���������� ��������� �� ������� ���������������� ����
//��������� ����� ���������
//dist - ����� ��������� (������ ��� ��������� � ������ ��� �������������)
//is_create ����� �� ������������ ������?
SX_LIB_API void SML_LigthsSetDist(ID id, float dist, bool is_create = true);

//�������� �����, rot_mesh - �������� ���� ��������� �����
SX_LIB_API void SML_LigthsGetRot(ID id, float3* vec, bool rot_mesh);
SX_LIB_API void SML_LigthsSetRot(ID id, float3* vec, bool rot_mesh);

//����������� �������, rot_mesh - ����������� ���� ��������� �����
SX_LIB_API void SML_LigthsGetDir(ID id, float3* vec, bool rot_mesh);
SX_LIB_API void SML_LigthsSetDir(ID id, float3* vec, bool rot_mesh);

//���������� ����������
//{
//��������� ��������
SX_LIB_API bool SML_LigthsComVisibleForFrustum(ID id, ISXFrustum* frustum);	//����� �� ���� � ������ �������� frustum
SX_LIB_API float SML_LigthsComDistFor(ID id, float3* viewpos);				//��������� �� viewpos �� ������ �����

//��������������� �������� (� ������� � ������ ������)
//������� ��������� � ���������� �� ����������� viewpos �� ������ �����, ��� ������� �����
SX_LIB_API void SML_LigthsComVisibleFrustumDistFor(ISXFrustum* frustum, float3* viewpos);
SX_LIB_API bool SML_LigthsGetVisibleForFrustum(ID id);//����� �� ���� � ������������ ��������
SX_LIB_API float SML_LigthsGetDistFor(ID id);			//������������ ��������� �� ������� ����������� �� ������ �����
//}

//���������/���������� �����
SX_LIB_API int SML_LigthsIsEnable(ID id);
SX_LIB_API void SML_LigthsSetEnable(ID id, bool val);

//���� ��� ������������� ���������
SX_LIB_API float SML_LigthsGetAngle(ID id);
SX_LIB_API void SML_LigthsSetAngle(ID id, float angle);

//������� ������ ��� ������������� ���������
SX_LIB_API float SML_LigthsGetTopRadius(ID id);
SX_LIB_API void SML_LigthsSetTopRadius(ID id, float top_radius);

//���������� ������
//{{
//��� ��������� ����� ������������ ���� render target full screen
//��� ����������� ������������ ��� ���� ����������� render target � ������ render target
//��� ����������� ������ �������� ������ �������, ������� ������ �� �������
//��� ��� ������������ ����� ���� render target ��� ��������� ����� 
//�� ������ � ������� ������ ������� ����� ������������� � �������� ���� ������ ��� ������ �����

SX_LIB_API bool SML_LigthsIsShadow(ID id);	//����������� �� ����
SX_LIB_API void SML_LigthsSetShadow(ID id, bool is_shadow);	//��������� ������� �����

SX_LIB_API bool SML_LigthsGet4Or3SplitsG(ID id);	//
SX_LIB_API void SML_LigthsSet4Or3SplitsG(ID id, bool bf4or3);	//

SX_LIB_API IDirect3DTexture9* SML_LigthsGetShadow();	//���������� �������� � ������ (���� ���������� ������� �����������) �� �������� ����������
SX_LIB_API void SML_LigthsNullingShadow();	//��������� ����� �����

//���������� ������� ������� � ����� ������
//{
//��� ���� ����� �����, ���������� �������� ��� ������� �����
SX_LIB_API void SML_LigthsInRenderBegin(ID id);	//���������������� ���������
SX_LIB_API void SML_LigthsInRenderEnd(ID id);		//����������� ���������

//��� ����������� � ���������� �����, ���������� �������� ��� ������� �����
SX_LIB_API void SML_LigthsInRenderPre(ID id, int cube);	//���������������� �������� ����� �������� ��� ������/�������
SX_LIB_API void SML_LigthsInRenderPost(ID id, int cube);	//����������� �������� ����� �������� ��� ������/�������
//}

SX_LIB_API void SML_LigthsShadowSetShaderOfTypeMat(ID id, int typemat, float4x4* wmat);
SX_LIB_API void SML_LigthsGenShadow(ID id);	//��������� ���� �� ������ ��� ������������ ���������� � ���������

//����������� ������� ����
//randomsam - ������������ �� �������� �� ���������� �����������
//size - ���������� ���������� ������� ������� ��� ��������
//isfirst - ������� �� ���������� �������� ��� ������� ����, ������ �������� ���� ��� �� �������� �� �������������� ���� ��������� false
SX_LIB_API void SML_LigthsSoftShadow(bool randomsam, float size, bool isfirst = false);

//���������� ��������� �� ������� 
//how - ����� ������ ��� �����������, 0 ��� �������������, � ����� ������� ��� ���������
SX_LIB_API ISXFrustum* SML_LigthsGetFrustum(ID id, int how);

//���������� �������� ����������� �����, split - ����� ������, pos - ������� �����������, dir - ����������� ������� �����������
SX_LIB_API void SML_LigthsUpdateFrustumsG(ID id, int split, float3* pos, float3* dir);

//���������� ��������� ��� ��������� �����
SX_LIB_API float SML_LigthsGetBias(ID id);
SX_LIB_API void SML_LigthsSetBias(ID id, float bias);

//���������� ��������� ��� ��������� �����
SX_LIB_API void SML_LigthsSetBlurPixel(ID id, float blur_pixel);
SX_LIB_API float SML_LigthsGetBlurPixel(ID id);

//���������� ������� ���������� ��������� ��� ����� (��������� ����)
SX_LIB_API void SML_LigthsSetShadowLocalNear(ID id, float slnear);
SX_LIB_API float SML_LigthsGetShadowLocalNear(ID id);

//���������� ������� ���������� ��������� ��� ����� (��������� ����)
//!!! ������ ��������� ��������� � ���� �������������� ��� �������� �� ��� ���������� �� ���� �����
SX_LIB_API void SML_LigthsSetShadowLocalFar(ID id, float slfar);
SX_LIB_API float SML_LigthsGetShadowLocalFar(ID id);

//���������� ��������� ��� �������� ������ (����)
SX_LIB_API void SML_LigthsSetEnableCubeEdge(ID id, int edge, bool enable);
SX_LIB_API bool SML_LigthsGetEnableCubeEdge(ID id, int edge);

//���������� ��������� ��������� ������ �� ������� (� ������� �� ���������, �������������� � �������)
//������� ��� ���� ����� �������� �������� ��������� (���� ��� �����) �� �������
//� ������� ����� ���������� ��������� � ����� ������ � �������� � ��������
//inid - ������������� �������/������� ������ ���� ��� ������ ������������� �������
//how - ����� ������ ��� �����������, 0 ��� �������������, � ����� ������� ��� ���������
//id_arr - ����� ������� ��������� �� ������� ������� ���� ����� ������������ �� ���������
SX_LIB_API ID SML_LigthsGetIDArr(ID id, ID inid, int how);
SX_LIB_API void SML_LigthsSetIDArr(ID id, ID inid, int how, ID id_arr);

//���������� �������������� ��������� ����� (LIGHTS_TYPE_SHADOWED_DYNAMIC, LIGHTS_TYPE_SHADOWED_STATIC)
SX_LIB_API void SML_LigthsSetTypeShadowed(ID id, int type);
SX_LIB_API int SML_LigthsGetTypeShadowed(ID id);

//���������� ������������ �����
//{
//���������� ��������� ������ ����� ���������� ��������� �� ��������� ����
//viewpos - ������� ������ ��� ������� ���������, �� ��������� ���������� ����� ���������� ������ ����������
//ghow - ����� ������ ��� �����������, 0 ��� �������������, � ����� ������� ��� ���������
SX_LIB_API bool SML_LigthsUpdateCountUpdate(ID id, float3* viewpos, int ghow = -1);

//��������� �� ��������� ����, ghow ���������� SML_LigthsUpdateCountUpdate
SX_LIB_API bool SML_LigthsAllowedRender(ID id, int ghow = -1);
SX_LIB_API void SML_LigthsSetNullCountUpdate(ID id);	//�������� ������� ���������� � ��������� �� ������� ����
//}
//}}

//��������� hdr, factor_adapted - �� ������� ������ "����" ���������
SX_LIB_API void SML_LigthsComHDR(DWORD timeDelta, float factor_adapted = 10);


SX_LIB_API long SML_LigthsDelGetCount();
SX_LIB_API int SML_LigthsDelGetType(long key);
SX_LIB_API void SML_LigthsDelDel(long key);
SX_LIB_API ID SML_LigthsDelGetIDArr(long key, ID inid, int how);

/////////

//���� render targets
#define DS_RT_COLOR 0	//����	rgba8
#define DS_RT_NORMAL 1	//������� (������� �����������)	rfb10a2
#define DS_RT_PARAM 2	//��������� ���������	r5g6b5
#define DS_RT_DEPTH 3	//�������	r16f

#define DS_RT_COLOR2 8	//����	rgba8
#define DS_RT_NORMAL2 9	//������� (������� �����������)	rfb10a2
#define DS_RT_PARAM2 10	//��������� ���������	r5g6b5
#define DS_RT_DEPTH2 11	//�������	r16f

#define DS_RT_AMBIENT_DIFF 4	//������� ���� (���� �����) � ��������� ��������� rgba16f
#define DS_RT_SPECULAR 5		//�����	r16f

#define DS_RT_AMBIENT_DIFF2 12	//������� ���� (���� �����) � ��������� ��������� rgba16f
#define DS_RT_SPECULAR2 13		//�����	r16f

#define DS_RT_SCENE_LIGHT_COM 6	//���������� �����	rgb10a2
#define DS_RT_SCENE_LIGHT_COM2 14//���������� �����	rgb10a2
#define DS_RT_ADAPTED_LUM_CURR 7//������� rt ��������� ����� � ��������� r16f

SX_LIB_API ID SML_DSGetRT_ID(int type);	//id render target �� ��� ����
SX_LIB_API IDirect3DTexture9* SML_DSGetRT(int type);	//�������� render target �� ��� ����
SX_LIB_API void SML_DSInCopyRT(int type);	//�������� ��������� render target (������ ������� ds)

/////////

#define MTL_MAX_SIZE_DIR 64
#define MTL_MAX_SIZE_NAME 64

//���� ����������
#define MTL_GEOM 0
#define MTL_GRASS 1
#define MTL_TREE 2
#define MTL_ANIM 3
//#define MTL_LIGHT 4

SX_LIB_API ID SML_MtlLoad(const char* name, int mtl_type = MTL_GEOM);
SX_LIB_API long SML_MtlGetCount();
SX_LIB_API int SML_MtlGetType(ID id);
SX_LIB_API int SML_MtlIsRefraction(ID id);
SX_LIB_API int SML_MtlTypeReflection(ID id);
SX_LIB_API void SML_MtlUpdate(DWORD timeDelta);
SX_LIB_API void SML_MtlRender(ID id, float4x4* world);
SX_LIB_API void SML_MtlRenderLight(float4_t* color, float4x4* world);
SX_LIB_API void SML_MtlSetMainTexture(ID slot, ID id);

SX_LIB_API void SML_MtlRefSetPlane(D3DXPLANE* plane);
SX_LIB_API void SML_MtlRefSetCenter(float3_t* center);
SX_LIB_API void SML_MtlRefPreRenderPlane(float4x4* world);
SX_LIB_API ISXFrustum* SML_MtlRefGetfrustum();
SX_LIB_API void SML_MtlRefPostRenderPlane();
SX_LIB_API IDirect3DTexture9* SML_MtlRefGetTexPlane();

#endif