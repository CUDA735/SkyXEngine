
#ifndef __sxgeom
#define __sxgeom

#include <gdefines.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxgcore_d.lib")
#else
#pragma comment(lib, "sxgcore.lib")
#endif
#include <gcore\\sxgcore.h>

SX_LIB_API long SGeom_0GetVersion();			//���������� ������ ���������� ���������
SX_LIB_API void SGeom_Dbg_Set(report_func rf);	//���������� ����� ������� ������ ���������
SX_LIB_API void SGeom_0Create(	//������������� ����������
	const char* name,			//���
	IDirect3DDevice9* device,	//��������� ��
	const char* std_path_mesh,	//���� �� ����� � �������� (����������� ��������� � ��������������, �� ��������)
	bool is_unic = true			//������ �� ���������� ���� ���������� �� �����
	);

SX_LIB_API void SGeom_0CreateKill();	//����������� ����������

SX_LIB_API void SGeom_OnLostDevice();	//��������� ������ ����������
SX_LIB_API void SGeom_OnResetDevice();	//��������� �������������� ����������

//������� ��������, ��������������� ������������� ���������� �������������
//{{
SX_LIB_API void SGeom_0SettModelsSetSortFrontToBackModels(bool val);	//unsupported
SX_LIB_API bool SGeom_0SettModelsGetSortFrontToBackModels();			//unsupported

//���������� � ������� front to back �� ������ �������
SX_LIB_API void SGeom_0SettModelsSetSortFrontToBackSplits(bool val);
SX_LIB_API bool SGeom_0SettModelsGetSortFrontToBackSplits();

//��������������
//{
//�������� ��������� �������� ���� (���� �����) � ������ ������� ����
SX_LIB_API float SGeom_0SettGreenGetDistLods1();
SX_LIB_API void SGeom_0SettGreenSetDistLods1(float val);

//��������� ��������� ������� ���� � ������ ������� ����
SX_LIB_API float SGeom_0SettGreenGetDistLods2();
SX_LIB_API void SGeom_SettGreenSetDistLods2(float val);

//������� ������� (�������) �����, �� 0 �� 100
SX_LIB_API int SGeom_0SettGreenGetFreqGrass();	
SX_LIB_API void SGeom_0SettGreenSetFreqGrass(int val);

//������ ���������� �����,������� �� 0 �� DistLods1
SX_LIB_API float SGeom_0SettGreenGetBeginEndLessening();
SX_LIB_API void SGeom_0SettGreenSetBeginEndLessening(float val);

//���������� front to back �� ������ �������
SX_LIB_API bool SGeom_0SettGreenGetSortFrontToBackSplits();
SX_LIB_API void SGeom_0SettGreenSetSortFrontToBackSplits(bool val);
//}
//}}

/*
� ������ ��������� ��������� ��� ��������� ����� ���� � ��� ��� ����������� �������������� ������� ��������� � ������.
������� ���� ����������� ������� �������������� ������� ��� ������ ��������� ��������� ��� ����������� ��������.
��� �������� ����� ������� � ��������� �����, � ����� ���� ��� ������� ����� ������ ����� �������� �� ��������� ���������� �� ����� �������.
������:
long id_arr_cam = SGeom_ModelsAddArrForCom();
long id_arr_shadow = SGeom_ModelsAddArrForCom();
long id_arr_light = SGeom_ModelsAddArrForCom();
...
SGeom_ModelsComVisible(frustum_cam,pos_cam,id_arr_cam);
SGeom_ModelsComVisible(frustum_shadow,pos_shadow,id_arr_shadow);
SGeom_ModelsComVisible(frustum_light,pos_light,id_arr_light);
...
SGeom_ModelsRender(timeDelta,id_arr_cam);
SGeom_ModelsRender(timeDelta,id_arr_shadow);
SGeom_ModelsRender(timeDelta,id_arr_light);
*/

//������� ����������� ���������, ��������������� ������������� ���������� �����������!!!
//{{
SX_LIB_API void SGeom_ModelsClear();	//�������� ������ ���� �������

//!���� ����������� � ���� ������������� �����, �������� � ���� ����
SX_LIB_API void SGeom_ModelsSave(const char* path);	//��������� ��� ������ � �������� ����
SX_LIB_API void SGeom_ModelsLoad(const char* path);	//��������� �������� ���� � ��������

SX_LIB_API long SGeom_ModelsGetCount();	//���������� ������� � ������� ������

//��������� ��������� ���� ������� ��� �������� 
SX_LIB_API void SGeom_ModelsComVisible(	
	ISXFrustum* frustum,	//������� ��� �������� ������� ��������� �������
	float3* viewpos,		//������� ��������� �������� ����� ���������� ���������
	ID id_arr = 0			//������������� ������� ���������� � ��������� ��� ��������, ��������� ����� SGeom_ModelsAddArrForCom, ���� 0 �� ������� � ���������
	);	

//��������� ���� �������, �� ������ ���������� � ��������� �� ������� ��������� id_arr
SX_LIB_API void SGeom_ModelsRender(
	DWORD timeDelta,			
	int sort_mtl,				//���� ���������, ��� ������������ ��������� �� "������", �� ��������� 0
	ID id_arr = 0,				//������������� ������� � ����������� � ���������
	bool is_sorted = false,		//������������ �� ���������� � ���������� �������� front to back
	ID exclude_model_id = -1,	//������������� ������ ������� ���������� ��������� �� ������� (�� ������ ��������� ���������0
	ID exclude_group_id = -1	//������������� ��������� ������� ���� ��������� �� �������, ���� ������� �������� ������ 0, ����� ��������� ����� ������ � id exclude_model_id	
	);	

//�������� ������
SX_LIB_API ID SGeom_ModelsAddModel(
	const char* path,	//���� �� ������, ������������ ������������ ����
	const char* lod1,	//���� �� ����, ������������ ������������ ����
	const char* name	//��� ������
	);

SX_LIB_API void SGeom_ModelsDelModel(long id);	//������� ������ ��� ������� id

SX_LIB_API void SGeom_ModelsGetMinMax(float3* min, float3* max);	//�������� ����� �������������� ����� ����� ������ �������
SX_LIB_API ID SGeom_ModelsAddArrForCom();				//�������� ������ ���������, ���������� ��� �������������
SX_LIB_API void SGeom_ModelsDelArrForCom(ID id_arr);	//������� ������ ��������� � ������� id_arr

//���������� �������� �� id - ���������� ������� �������
//id ������ �� ���������, ���� ������� ������ �� �������� ������ �� ��� �������� ����� id ������ �� ������� ������
//{
SX_LIB_API char* SGeom_ModelsMGetName(ID id);			//�������� ��� ������
SX_LIB_API const char* SGeom_ModelsMGetPathName(ID id);	//�������� ���� �� ������ ������������ ������������ ����
SX_LIB_API long SGeom_ModelsMGetCountPoly(ID id);		//�������� ���������� ��������� ������

//����� ��������� ������� ��� ��� ����� ������, ��� ���� ����� ��������� �������� � ���� ���� �������� SGeom_ModelsMApplyTransform(long id)
SX_LIB_API float3* SGeom_ModelsMGetPosition(ID id);	//�������� ������� ������
SX_LIB_API float3* SGeom_ModelsMGetRotation(ID id);	//�������� �������� ������
SX_LIB_API float3* SGeom_ModelsMGetScale(ID id);	//�������� ��������������� ������

SX_LIB_API const char* SGeom_ModelsMGetLodPath(ID id);				//�������� ���� �� ���� ������������ ������������ ����
SX_LIB_API void SGeom_ModelsMSetLodPath(ID id, const char* path);	//���������� ���� �� ���� ������������ ������������ ���� � ���������

SX_LIB_API void SGeom_ModelsMApplyTransform(ID id);	//��������� ������������� ��� ������
//}

SX_LIB_API void SGeom_ModelsMSortGroups(float3* viewpos,int sort_mtl);

SX_LIB_API ID SGeom_ModelsMGetCountGroups(ID id);
SX_LIB_API ID SGeom_ModelsMGetGroupIDMat(ID id, ID group);
SX_LIB_API void SGeom_ModelsMGetGroupCenter(ID id, ID group, float3_t* center);
SX_LIB_API void SGeom_ModelsMGetGroupMin(ID id, ID group, float3_t* min);
SX_LIB_API void SGeom_ModelsMGetGroupMax(ID id, ID group, float3_t* max);
SX_LIB_API void SGeom_ModelsMGetGroupPlane(ID id, ID group, D3DXPLANE* plane);

SX_LIB_API void SGeom_ModelsMGetArrBuffsGeom(
	float3_t*** arr_vertex,		//(*arr_vertex)[num_model][num_vertex] - ������� ������
	int32_t** arr_count_vertex, //(*arr_count_vertex)[num_model] - ���������� ������ ��� ������
	uint32_t*** arr_index,		//(*arr_index)[num_model][num_vertex] - ������� ������
	int32_t** arr_count_index,	//(*arr_count_index)[num_model] - ���������� �������� ��� ������
	int32_t* count_models		//(*count_model) - ���������� �������
	);
//}}

//*************************************************************************************************************************

//������� ��������������, ��������������� ������������� ���������� �����������!!!
//{{

//���� ��������������
enum GeomGreenType
{
	ggtr_all = -1,	//������������ ������ ��� �������� ��������� ���� ����� � ������ � �������
	
	ggt_grass = 0,	//�����
	ggt_tree,		//�������
};

//�������� ������� ��������������
SX_LIB_API ID SGeom_GreenAddGreen(
	const char* name,		//���
	const char* path_mask,	//���� �� ����� �� ������� ����� �������������� ��������������
	float count_max,		//���������� �� ������� ����� �������� ��������� �� �����
	const char* path, const char* lod1, const char* lod2,	//���� ������������ ������������ ����, �� ������ � �����,
															//���� lod1 � lod2 ����� 0, ����� ����� �������� ������� �����, ����� ������� ������
															//���� �������� �� ������������ �����������
	const char* navmesh		//������������� ���, ������� ����� ������� � ������� SGeom_GreenGetMNavMeshAndTransform ��� �������� �� �������� ����� ������� �����������
	);

SX_LIB_API void SGeom_GreenDelGreen(ID id);	//������� ������� ��������������

SX_LIB_API ID SGeom_GreenAddArrForCom();			//�������� ������ ���������, ���������� ��� �������������
SX_LIB_API void SGeom_GreenDelArrForCom(ID id_arr);	//������� ������ ���������

//!������, ����, ���� ���������, ����������� � ���� ������������� �����, ����� � �������� ����������� � ���� ����
SX_LIB_API void SGeom_GreenSave(const char* path);	//��������� ���������� � �������������� � �������� ����
SX_LIB_API void SGeom_GreenLoad(const char* path);	//��������� ���������� � �������������� �� ��������� �����

SX_LIB_API void SGeom_GreenClear();	//�������� ������ ��������������

//���������� ��������� ���� �������������� ��� ��������
SX_LIB_API void SGeom_GreenComVisible(
	ISXFrustum* frustum,	//������� ��� �������� ������� ��������� �������
	float3* viewpos,		//������� ��������� �������� ����� ���������� ���������
	ID id_arr = 0			//������������� ������� ���������� � ��������� ��� ��������, ��������� ����� SGeom_ModelsAddArrForCom, ���� 0 �� ������� � ���������
	);

//��������� ���� �������, �� ������ ���������� � ��������� �� ������� ��������� id_arr
//type - ��� �������� �������������� �� ������������ GeomGreenType
//������ GeomGreenType::ggtr_all ����� ���������� ��� ���� ��������������
SX_LIB_API void SGeom_GreenRender(DWORD timeDelta, float3* viewpos, GeomGreenType type, ID id_arr = 0);	

SX_LIB_API long SGeom_GreenGetCount();	//�������� ���������� ������ �������������� (�� ����� ������)

//���������� ��������� ��������������
//{
SX_LIB_API char* SGeom_GreenMGetName(ID id);		//�������� ���
SX_LIB_API long SGeom_GreenMGetCountGen(ID id);		//�������� ���������� ��������������� ���������
SX_LIB_API int SGeom_GreenMGetTypeCountGen(ID id);	//�������� ��� ��������������
SX_LIB_API const char* SGeom_GreenMGetModel(ID id);	//�������� ���� �� ������ ������������ ������������ ����
SX_LIB_API const char* SGeom_GreenMGetLod1(ID id);	//�������� ���� �� ������� ���� ������ ������������ ������������ ����
SX_LIB_API const char* SGeom_GreenMGetLod2(ID id);	//�������� ���� �� ������� ���� ������ ������������ ������������ ����
SX_LIB_API const char* SGeom_GreenMGetMask(ID id);	//�������� ���� �� ����� �� ������� ������������� ��������������, ������������ ������������ ����
SX_LIB_API const char* SGeom_GreenMGetNav(ID id);		//�������� ���� �� ���� ��������� ������������ ������������ ����

SX_LIB_API void SGeom_GreenMSetLod(ID id, int lod, const char* pathname);	//���������� ��� (��� �������) lod �� 0 �� 2 ������������, pathname ���� �� ������ ������������ ������������ ����
SX_LIB_API void SGeom_GreenMSetNav(ID id, const char* pathname);	//���������� ��� ���������, pathname ���� �� ������ ������������ ������������ ����
//}

SX_LIB_API void SGeom_GreenGetMNavMeshAndTransform(
	float3_t*** arr_vertex,			//(*arr_vertex)[num_green_mesh_nav][num_vertex] - ������� ������
	int32_t** arr_count_vertex,		//(*arr_count_vertex)[num_green_mesh_nav] - ���������� ������ ��� ������
	uint32_t*** arr_index,			//(*arr_index)[num_green_mesh_nav][num_vertex] - ������� ������
	int32_t** arr_count_index,		//(*arr_count_index)[num_green_mesh_nav] - ���������� �������� ��� ������
	float4x4*** arr_transform,		//(*arr_transform)[num_type_green][num_elem] - ������� ��� ������������� ������ ���������
	int32_t** arr_count_transform,	//(*arr_count_transform)[num_type_green] - ���������� ������ ��� �������������
	int32_t* arr_count_green		//(*arr_count_green) - ���������� ������ �������������� �� �����
	);

//}}

#endif