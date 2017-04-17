
#ifndef __render_func
#define __render_func

#include <GRegisterIndex.h>

//��������� �������
#define RENDER_STATE_MATERIAL 0	//��������� ����������
#define RENDER_STATE_SHADOW 1	//��������� �����
#define RENDER_STATE_FREE 2		//������� ��������� (�� ������������)

//�������������� ��� ����������� ���� ��������� ���������
#define RENDER_IDARRCOM_GEOM 0	//���������
#define RENDER_IDARRCOM_GREEN 1	//��������������

namespace SXRenderFunc
{
	//������� ���������� ���������� � ���������
	//{
	//������������� ��� ��������
	inline void SetSamplerFilter(DWORD id, DWORD value);
	inline void SetSamplerAddress(DWORD id, DWORD value);
	
	//��� ���������� ���������� ����� ���������
	inline void SetSamplerFilter(DWORD begin_id, DWORD end_id, DWORD value);
	inline void SetSamplerAddress(DWORD begin_id, DWORD end_id, DWORD value);
	//}

	//��������� �����-���� �� ������� ���������
	//� ������ ������ ���������� ������� ������� � ���������
	void UpdateMsg(DWORD timeDelta);

	//��������� ������ � �������������� ����������
	void ComDeviceLost();

	void UpdateView();	//��������� � ��������� �������� ������, ��������� ���������� ���������
	void OutputDebugInfo(DWORD timeDelta);	//����� ���������� ��������� ���������� � ���� �������

	void ComVisibleForLight();	//��������� ��������� ��� ���������� �����
	void ComVisibleForCamera();	//��������� ��������� ��� ������
	void ComVisibleReflection();
	void ComReflection(DWORD timeDelta);	//���������/���������� ���������

	void RenderInMRT(DWORD timeDelta);	//���������� G ������, �� ���� ������ ���� �����
	void UpdateShadow(DWORD timeDelta);	//���������� ���������� � ����� (������ ����� ���� ��� ����������� ���� � ������ ������ ���������� �����)
	
	void RenderSky(DWORD timeDelta);	//��������� ��������� � �������
	void ComLighting(DWORD timeDelta, bool render_sky);	//��������� ���������, render_sky - �������� �� ����
	
	//���� ��������
	void GameRender(DWORD timeDelta);
	void MainRender(DWORD timeDelta);
	void MaterialEditorRender(DWORD timeDelta);

	void PostProcess(DWORD timeDelta);	//��������� ������������

	//������� �������, ��� �������� ������������ ���� ��� ������ �����������
	//{
	//������� ���������, � ������ ������ �� �����������
	void RFuncDIP(UINT type_primitive, long base_vertexIndex, UINT min_vertex_index, UINT num_vertices, UINT start_index, UINT prim_count);
	//������� ��������� ��������� �� id, world - ������� �������
	void RFuncMtlSet(ID id, float4x4* world);
	//������� �������� ���������
	ID RFuncMtlLoad(const char* name, int mtl_type);
	//}

	//����� ��������/�������� ���������� ��������� ������� �������
	namespace Delay
	{
		DWORD UpdateVisibleForCamera = 0;
		DWORD UpdateVisibleForLight = 0;
		DWORD UpdateVisibleForReflection = 0;

		DWORD UpdateShadow = 0;
		DWORD RenderMRT = 0;
		DWORD ComLighting = 0;
		DWORD PostProcess = 0;
		DWORD ComReflection = 0;
		DWORD GeomSortGroup = 0;

		DWORD Present = 0;
	};
};

#endif