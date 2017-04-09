
#ifndef __sxmlight
#define __sxmlight

#include <gdefines.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxgcore_d.lib")
#else
#pragma comment(lib, "sxgcore.lib")
#endif
#include <gcore\\sxgcore.h>


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

SX_LIB_API void SML_Update(
	DWORD timeDelta,	//
	float2_t* winsize,	//
	float2_t* nearfar,	//
	float3* poscam,		//
	float4x4* mview,		//
	float projfov		//fov ����
	);

//���� ���������� �����
enum LightsTypeLight
{
	ltl_none = -1,	//�� �������������
	ltl_global,		//����������
	ltl_point,		//��������
	ltl_direction	//������������
};

//���� ����� ���������� �����
enum LightsTypeShadow
{
	lts_none = -1,	//��� �����
	lts_static,		//��������� ����, ���� ����������� ������ ��������� ������ (��� ������������), ����� �� �����������
	lts_dynamic,	//��������� ������������ ����
};

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
//SX_LIB_API void SML_LigthsUpdate(float3* const_cam_pos,float4x4* camview);

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

SX_LIB_API LightsTypeLight SML_LigthsGetType(ID id);	//���������� ��� �����

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
SX_LIB_API void SML_LigthsSetTypeShadowed(ID id, LightsTypeShadow type);
SX_LIB_API LightsTypeShadow SML_LigthsGetTypeShadowed(ID id);

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

/////////////////////////////////////////////////////////////

//���� render targets
enum DS_RT
{
	ds_rt_color = 0,		//����	rgba8
	ds_rt_normal,			//������� (������� �����������)	rfb10a2
	ds_rt_param,			//��������� ���������	rgba8
	ds_rt_depth,			//�������	r16f
	ds_rt_depth0,			//�������	r16f
	ds_rt_depth1,			//�������	r16f

	ds_rt_ambient_diff,		//������� ���� (���� �����) � ��������� ��������� rgba16f
	ds_rt_specular,			//�����	r16f
	ds_rt_scene_light_com,	//���������� �����	rgba16
	ds_rt_scene_light_com2,	//���������� �����	rgba16

	ds_rt_adapted_lum_curr	//������� rt ��������� ����� � ��������� r16f
};

SX_LIB_API ID SML_DSGetRT_ID(DS_RT type);	//id render target �� ��� ����
SX_LIB_API IDirect3DTexture9* SML_DSGetRT(DS_RT type);	//�������� render target �� ��� ����

////////////////////////////////////////////////////////////////

#define MTL_MAX_SIZE_DIR SXGC_LOADTEX_MAX_SIZE_DIR
#define MTL_MAX_SIZE_NAME SXGC_LOADTEX_MAX_SIZE_NAME

#define MTL_REF_UPDATE_MAX_COUNT_FOR_STATIC 3	//������������ ���������� ���������� ����������� ���������, � ������ ������ �������

//��������� ��� ������� ����� �������� ��� �������� ���������� ���������
//������ MTL_REF_UPDATE_L0_DIST - ���������� ����� ������ ����
//������ MTL_REF_UPDATE_L2_DIST - ���������� �� �����
#define MTL_REF_UPDATE_L0_DIST 10	//
#define MTL_REF_UPDATE_L1_DIST 30	//
#define MTL_REF_UPDATE_L2_DIST 70	//

//������� ����� ����� D3DCMP_GREATEREQUAL
#define MTL_ALPHATEST_FREE_VALUE 64		//�������� ���������� ����� ����� (������������ ����������)
#define MTL_ALPHATEST_FORCEBLY_VALUE 8	//�������� ��������������� ����� �����

//������ �������� �� ��������� ����� ��������� � ����������� ������� �� ������� ���������, ���� � ����������� ����������
//�������� ������������� �� ���������
#define MTL_LIGHTING_DEFAULT_ROUGHNESS 250.f/255.f
//�������� f0 (������������� ����������� �����������) �� ���������
#define MTL_LIGHTING_DEFAULT_F0 2.f/255.f

//������ ������� � �����������
#define MTL_REF_TEX_SIZE 512	
//������� ��������� ���������
#define MTl_REF_PROJ_NEAR 0.25
//������� ��������� ���������, ��� ��������� �� ������� ����� ������ ����� � �������� ���������
#define MTl_REF_PROJ_FAR 100

//����������� ����������
//��� ����������� ���������� ������ ���� ��������� �������� (������� ��� �������� ���������)
//� ��� ��������� ������������ ������������ �������� ���������� � ����� ������ ��� ������� ���� ����������
//� �������� ���������� �� ������ ���������� � ������ ��������

//��� ����������� ���������� �� ��������� ��� "������" ������� � ����������� ���������
#define MTL_VIRTUAL_DIR_HAND_MTL '0'

//��� ����������� ���������� �� ��������� ��� ����������� (����������) ����������
#define MTL_VIRTUAL_DIR_STD_MTL "mtrldef"

//���� ���������
enum MtlTypeReflect
{
	mtr_none,			//��� ���������
	mtr_plane,			//�������
	mtr_cube_dynamic,	//�������� ������������
	mtr_cube_static		//�������� �����������, ��������� ���� ������ ��������� ������, ����� �� �����������
};

//���� ������������
enum MtlTypeTransparency
{
	mtt_none,			//��� ������������
	mtt_alpha_lighting,	//����������� ������������
};

//��� ������ ���������
enum MtlTypeModel
{
	tms_static = 0,	//����������� ���������
	tms_grass,		//�������������� �����
	tms_tree,		//�������������� ������
	tms_skin,		//������������ ������

	//�������� �� ���������
	tms_default = tms_static
};

//���������� ��� ���������
enum MtlPhysicType
{
	mpt_concrete = 0,	//�����
	mpt_metal,			//������
	mpt_glass,			//������
	mpt_plastic,		//�������
	mpt_tree,			//������
	mpt_flesh,			//�����
	mpt_ground_sand,	//�����/�����

	//�������� �� ���������
	mpt_default = mpt_concrete,
};

//������ ������������ � �������
enum MtlTransShaderStd
{
	mtss_mat_w = 0,	//������� ������� (������������� ������), world
	mtss_mat_v,		//������� ����, view
	mtss_mat_p,		//������� ��������, projection
	mtss_mat_wv,	//world * view
	mtss_mat_wvp,	//world * view * projection
	mtss_campos,	//������� ������/�����������
	mtss_timedelta,	//������ � ������� float2(CountTimeRender,TimeDelta)
	mtss_winsize,	//������� ���� �������

	mtss_ud			//���������������� ������ (float4)
};

//�������� ���������, ���������� ���������� �������������� ���������, 
//��� ��������� ������������� � ����������� ��������� ������� ��� ������� ���������� ���������� ���
//name - ���_���������.����������
//mtl_type - ��� ������ ��������� �� ������ ���� �������� �� ����� ��������/������
SX_LIB_API ID SML_MtlLoad(const char* name, MtlTypeModel mtl_type = MtlTypeModel::tms_static);

//������������ ���������
//name - �� ������ ������ ������������� ��������� ������
SX_LIB_API void SML_MtlReloadMaterial(ID id, const char* name = 0);

//�������, ������� ��� ����������� ��������� (�� ����� � ������� ��� ��� ��������), ��� ����������� ��������
//�������� �� ��������� � ���������� � ������� ��������, ��� ��� ����� ��������� � ���� ��������������, ������� ���������� ��������
//clear_ref_del - ������� �� ������� �������� ���������, �� ��� ������ ���� �������������� � ���������� ������ �� �������������
SX_LIB_API void SML_MtlClear(bool clear_ref_del);	
SX_LIB_API void SML_MtlSave(ID id);	//��������� �������� �� id
SX_LIB_API long SML_MtlGetCount();	//���������� ���������� ����� ����������
SX_LIB_API MtlTypeModel SML_MtlGetTypeModel(ID id);	//���������� ��� ������ ��������� �� id

//��������� ���� ������ ��������� �� id, 
//�������� ������ ���������� ���� (�����������)!!! ��� ��������� ��� ������� ���� ���� ��������� �������
//������� ��� ������� ������������ ���������� ����������
SX_LIB_API void SML_MtlSetTypeModel(ID id, MtlTypeModel type_model);
//SX_LIB_API void SML_MtlUpdate(DWORD timeDelta);	//���������� ���������� ����������, timeDelta - ����� � ����� �������� ������� �����

//��������� ���������� ��������� �� id, ���������� ����� DIP
//world - ��������� �� ������� ������� ������, ���� 0 - ����� ����� ������� ��������� �������
SX_LIB_API void SML_MtlRender(ID id, float4x4* world);

//��������� ���������� ��������� ��� ������� ��������� �����
//color - rgb - ����, w ��������������, world ���������� SML_MtlRender
SX_LIB_API void SML_MtlRenderLight(float4_t* color, float4x4* world);
SX_LIB_API void SML_MtlSetMainTexture(ID slot, ID id);	//���������� �������� �� ��������� id � ���������� ���� slot

//���������� ��� ���������
SX_LIB_API void SML_MtlSetPhysicMaterial(ID id, MtlPhysicType type);
SX_LIB_API MtlPhysicType SML_MtlGetPhysicMaterial(ID id);

//���������� id ������������ ��������� ��� ������������ ������ ���������� ��������� � MtlTypeModel 
SX_LIB_API ID SML_MtlGetStdMtl(MtlTypeModel type_model);

//���������� ����������� �������������� ������������
//{{
//������ ��������� ������� ���������� ������� ����������� � ������� �� ���������
//0 - ������������ ���������
//��� ��� ������ 0 ������ �������������� ���������

//��������� ���������� �������������� ������������
//� ������� ��� ������������� (����������) �������� ��� ���������� ���� ����� �����������
//��� ���������� �� �������������� � ����������� ����������� ����� ������ (���� ������ ���) ��������� ������� ��� ����
SX_LIB_API void SML_MtlSetIsIncrCountSurf(bool bf);
SX_LIB_API bool SML_MtlGetIsIncrCountSurf();	//���������� �� ��������� ������������
SX_LIB_API void SML_MtlNullingCurrCountSurf();	//��������� �������������� ������������ ������������ (� ������� ��� ����� �����)
SX_LIB_API int SML_MtlGetCurrCountSurf();		//������� ���������� ������������ �������������� ������������
SX_LIB_API void SML_MtlSetCurrCountSurf(int count);	//���������� ������� ���������� ������������ �������������� ������������

//�������������� ��������� ����� ����� ��� �������� ���������� ���������
//� ������� ��� ������� �������������� ������������, ����� ������ (�������) ��������� ���������� �������
SX_LIB_API void SML_MtlSetForceblyAlphaTest(bool isat);	//��������� ��������������� ����� �����, isat - true - ��������, false - ���������
SX_LIB_API bool SML_MtlGetForceblyAlphaTest();			//������� �� �������������� ����� ����
//}

//���������/REFLECTION
//{{

SX_LIB_API void SML_MtlRefSetIDArr(ID id, ID inid, int cube, ID idarr);
SX_LIB_API ID SML_MtlRefGetIDArr(ID id, ID inid, int cube);

SX_LIB_API int SML_MtlDelRefGetCount();
SX_LIB_API ID SML_MtlDelRefGetIDArr(ID key, ID inid, int cube);
SX_LIB_API void SML_MtlDelRefClear();

//��������� ���������� ������� ��� �������� �������� � ����������, viewpos - ������� �����������, viewpos == 0 ������ false
SX_LIB_API bool SML_MtlRefUpdateCountUpdate(ID id, float3_t* viewpos);

//��������� ����������� ������� ��� ������� ��������� � ����������
//������� � ������� �����-���� ���������, ����� ��� ��������� ���� ����� � � ���������� (��������� ��� ����������� ���������)
SX_LIB_API void SML_MtlRefNullingCountUpdate(ID id);

SX_LIB_API void SML_MtlRefSetCenter(ID id, float3_t* center);			//��������� ������ ���������
SX_LIB_API void SML_MtlRefSetMinMax(ID id, float3_t* min, float3_t* max);//���������� ���������
//���������� ������� ���������, cube - ������� ����
//���� ��������� ������� �� ���������� ������� � cube �������� 0, ����� ������ NULL
SX_LIB_API ISXFrustum* SML_MtlRefGetfrustum(ID id, int cube);
SX_LIB_API bool SML_MtlRefIsAllowedRender(ID id);	//�������� �� ������ ��������� ��� ������� ��������� � ������� ������

//������� ���������
//{
SX_LIB_API void SML_MtlRefSetPlane(ID id, D3DXPLANE* plane);		//��������� ��������� ��� ���������
SX_LIB_API void SML_MtlRefPreRenderPlane(ID id, float4x4* world);	//�������������� ��������� ������ ��� ��������� ���������, world - ������� ������� ������
//����� ����� ��������� ���������� �������� ��� ������� ����� ���� ��� ���������� ��������� � �������� ���������
SX_LIB_API void SML_MtlRefPostRenderPlane(ID id);					//����������� ��������
SX_LIB_API IDirect3DTexture9* SML_MtlRefGetTexPlane(ID id);			//���������� �������� � ������� ���������� (���� ��� ����, ����� 0)
//}

//�������� (����������) ���������
//{
SX_LIB_API void SML_MtlRefCubeBeginRender(ID id);	//��������� ����� ��������
SX_LIB_API void SML_MtlRefCubePreRender(ID id, int cube, float4x4* world);//��������� ������� �������� ��� ������� ���� (cube), world - ������� ������� ������ 
//����� ���� ������� ������� (Begin-pre ... post-End) ���������� �������� ��� ������� ����� ���� ��� ���������� ��������� � �������� ���������
SX_LIB_API void SML_MtlRefCubePostRender(ID id, int cube);	//����������� ������� ������� ��� ������� ����
//����������� ����� �������
//viewpos - ������� �����������, ���������� ��� ��������� ���������� �� ��������� ������
//���� viewpos == 0 ���������� ����������� ������� ��� �������� ��������� � ���������� �� ����������
//� ���� ����������� ������������ � ����������� � ������������ ��������� ���������� �� ���������� ������� ��������� ������� SML_MtlRefUpdateCountUpdate
SX_LIB_API void SML_MtlRefCubeEndRender(ID id, float3_t* viewpos);	

SX_LIB_API IDirect3DCubeTexture9* SML_MtlRefCubeGetTex(ID id);	//���������� �������� � ������ ���������� (���� ��� ����, ����� 0)
//}
//}}

//�������� �������� ������� ������������� �� ������/���������
SX_LIB_API void SML_MtlSetTexture(ID id,const char* path_tex);
SX_LIB_API void SML_MtlGetTexture(ID id, char* name);

//!!!� ������� ������ ��� ������� ����������� � ������ 3.0 � ������� � �������� ������ ��������� ������� main
//������� ��� ������� ���������
//!!!������������� ������������� � ��������� � ���������� �������
//��� ��� �� ���� ������ ���� �� ��������� ��������� ������� ����� �������� ���� ���������� �����
//path_vs/path_ps ����������� ������ ��� ������� � �����������, ������ ������������ ���� �����
SX_LIB_API void SML_MtlSetVS(ID id, const char* path_vs);
SX_LIB_API void SML_MtlGetVS(ID id, char* name);
SX_LIB_API void SML_MtlSetPS(ID id, const char* path_ps);
SX_LIB_API void SML_MtlGetPS(ID id, char* name);


//�������� �����������
//{{

//������������� ����� ����� ��� ���������
SX_LIB_API bool SML_MtlGetUsingAlphaTest(ID id);
SX_LIB_API void SML_MtlSetUsingAlphaTest(ID id, bool is_using);

//��������� ��������� id
//���� �������� �� ���������� �� ����� ������� � ����� ������������� ����������
SX_LIB_API void SML_MtlSetLighting(ID id, bool is_lighting);	
SX_LIB_API bool SML_MtlGetLighting(ID id);

//�������� � ����������� ���������, ���� �������� ��� �� ����� ������������ �������� �� ���������
//{
//���� ������������� �������� � ����������� ���������
SX_LIB_API void SML_MtlSetIsTextureLighting(ID id, bool is_tex_lighting);
SX_LIB_API bool SML_MtlGetIsTextureLighting(ID id);

SX_LIB_API void SML_MtlSetTextureLighting(ID id, const char* path_tex);	//�������� �������� � ����������� ��������� path_tex
SX_LIB_API void SML_MtlGetTextureLighting(ID id, char* path_tex);		//� path_tex ���������� ��� �������� � ����������� ���������
//}

//������������� (0-1)
SX_LIB_API void SML_MtlSetRoughness(ID id, float roughness);
SX_LIB_API float SML_MtlGetRoughness(ID id);

//f0 - ������������� ����������� ����������� (0-1)
SX_LIB_API void SML_MtlSetF0(ID id, float f0);
SX_LIB_API float SML_MtlGetF0(ID id);

//����������������, ���� �� MtlTypeTransparency
SX_LIB_API void SML_MtlSetTypeTransparency(ID id, MtlTypeTransparency type);
SX_LIB_API MtlTypeTransparency SML_MtlGetTypeTransparency(ID id);

//��������� ���������, ���� �� MtlTypeReflect
SX_LIB_API void SML_MtlSetTypeReflection(ID id, MtlTypeReflect type);
SX_LIB_API MtlTypeReflect SML_MtlGetTypeReflection(ID id);

//����������� � �����������
//{

//����������� ����� ��������� �� 4 ��������� ������� � �� 4 ������� � �������������
//������ ��� ����������� ��������� ������� (��������� � ��������������) ����������� � �����
//�� ������ ����� �������� ����� �� ����� ��������� � �������������� ��������
//�� ���� ����� ����� ��������� ��������� ����� ����� � ��������� � �������������� ��������

//����� ���������
SX_LIB_API void SML_MtlSetMaskTex(ID id, const char* path_tex);
SX_LIB_API void SML_MtlGetMaskTex(ID id, char* path_tex);

//�������� ������������, �� ������ �����
SX_LIB_API void SML_MtlSetMRTex(ID id, int channel, const char* path_tex);
SX_LIB_API void SML_MtlGetMRTex(ID id, int channel, char* path_tex);

//��������� ��������, �� ������ �����
SX_LIB_API void SML_MtlSetDTex(ID id, int channel, const char* path_tex);
SX_LIB_API void SML_MtlGetDTex(ID id, int channel, char* path_tex);
//}

//����������� ��������� ��� �������� � ������ (� ��������� � ���������� ���������), ������ �� MtlTransShaderStd
//{
//��� ���������� �������
SX_LIB_API void SML_MtlSetSTDVS(ID id, MtlTransShaderStd type, bool is_send);
SX_LIB_API bool SML_MtlGetSTDVS(ID id, MtlTransShaderStd type);

//��� ����������� �������
SX_LIB_API void SML_MtlSetSTDPS(ID id, MtlTransShaderStd type, bool is_send);
SX_LIB_API bool SML_MtlGetSTDPS(ID id, MtlTransShaderStd type);
//}

//�������������� ���������������� ������ � ���� float4 (0-1 ��� ���������, ���� ��� ���������, �� ���������)
//{
//������ ��� ���������� � ����������� ������� ���������
//������ ������ � �� ����������� ����� ���� ����������� � ��������� � ��������
//� ����� � ������� ����� ���� 2 float4 ���������������� ������� � �������
//�� ���� ������ ��������� ��� ����������� �� �� ���-����� ����� ��������� � ���������� ������, ���� ���� � ��������������� ��� ����������

//float4 ��� ���������� �������
SX_LIB_API void SML_MtlSetUDVS(ID id, int component, float val);
SX_LIB_API float SML_MtlGetUDVS(ID id, int component);

//�������� float4 �������, ���������������� ��� ���������� �������, � ���������� ������
SX_LIB_API void SML_MtlSetUDVS_InPS(ID id, bool is_send_ps);
SX_LIB_API bool SML_MtlGetUDVS_InPS(ID id);

//float4 ��� ����������� �������
SX_LIB_API void SML_MtlSetUDPS(ID id, int component, float val);
SX_LIB_API float SML_MtlGetUDPS(ID id, int component);

//�������� float4 �������, ���������������� ��� ����������� �������, � ��������� ������
SX_LIB_API void SML_MtlSetUDPS_InVS(ID id, bool is_send_vs);
SX_LIB_API bool SML_MtlGetUDPS_InVS(ID id);
//}
//}}

#endif