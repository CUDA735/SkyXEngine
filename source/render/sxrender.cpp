
#include "sxrender.h"

//##########################################################################

//! ������������ ���� ��� �������� ������ ����� �������
namespace GData
{
	IDirect3DDevice9* DXDevice = 0;	//!< dx ����������

	//! ������� ���������� ������� ��������� (���� �������)
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//! ������������� ���� �������
	void InitWin(
		const char* name,	//!< ��� ���� (������ ��������)
		const char* caption	//!< �������� ����
		);

	HWND HandlePreview = 0;	//!< ����� ������ ����
	HWND HandleParent3D = 0;//!< ����� ���� �������� ���� �������, �� ������ ����������
	HWND Handle3D = 0;		//!< ����� ���� �������

	float2_t WinSize = float2_t(800, 600);	//!< ������ ���� ������� (������� �������)
	bool IsWindowed = true;					//!<������������ �� ������� ����� �������?


	DS_RT FinalImage = DS_RT::ds_rt_scene_light_com;//!< ��������� �����������
	ISXCamera* ObjCamera = 0;	//!< ������ ��� ������� ����� ������
	ID IDSelectTex = -1;
	int ReSize = 0;				//!< 0 - ������ �� ������, 1 - ������, 2 - ������� ����� ��������� � �����

	float2_t NearFar = float2_t(0.025, 400);	//!< �������� ������� � ������� ���������� ���������
	float ProjFov = SM_PIDIV4;				//!< fov ������

	ID DefaultGeomIDArr = -1;
	ID DefaultGreenIDArr = -1;
	ID DefaultAnimIDArr = -1;

	float3 ConstCurrCamPos;	//!< ������� ������
	float3 ConstCurrCamDir;	//!< ����������� ������� ������

	//! ��������� ����������� ������ �� ���������
	float4_t CamWalkParamEditor = float4_t(
		10.f,	//!< ������� �������� ������
		5.f,	//!< ���������� ���������
		0.7f,	//!< ���������� �� ��������� �������� � ������� 
		0.5f	//!< ���������� �� ��������� �������� �����
		);

	//�������
	void InitAllMatrix();		//!< ������������� ������
	float4x4 MCamView;			//!< ������� ���� ������
	float4x4 MCamProj;			//!< ������� �������� ������
	float4x4 MLightProj;		//!< ������� �������� ���������� ������, ������ �����त ��������� ������
	float4x4 MRefPlaneSkyProj;	//!< ������� �������� �� ������� skybox � sky clouds, �� ������� ���������, ���������� MCamProj
	float4x4 MRefCubeSkyProj;	//!< ������� �������� �� ������� skybox � sky clouds, �� ���������� ���������

	//////

	//! ������������ ���� � ���������������� ��������
	namespace IDsShaders
	{
		//! �������� ���� ����������� ��������
		void InitAllShaders();

		//! ��������� �������
		namespace VS
		{
			ID ScreenOut;
			ID ResPos;
		};

		//! ���������� �������
		namespace PS
		{
			ID ScreenOut;
			ID ComLightingNonShadow;
			ID ComLightingShadow;

			ID BlendAmbientSpecDiffColor;

			ID ToneMapping;

			ID StencilStr;
			ID StencilColumn;
			ID StencilStrColumn;
			ID UnionAlpha;
		};
	};
};

//#########################################################################

#if !defined(DEF_STD_REPORT)
#define DEF_STD_REPORT
report_func g_fnReportf = DefReport;
#endif

//##########################################################################

SX_LIB_API void ComDeviceLost()
{
	if (GData::ReSize != 2)
	{
		//�������� ������� ������ ���� � ������� ��������
		RECT rect_scene;
		GetClientRect(GData::Handle3D, &rect_scene);


		GData::WinSize.x = rect_scene.right;
		GData::WinSize.y = rect_scene.bottom;
	}

	//���������� ��� ��� ���������� ��� �������������� ����������
	SGCore_OnLostDevice();
	SGeom_OnLostDevice();
	SML_OnLostDevice();
	SPE_OnLostDevice();

	bool bf = SGCore_OnDeviceReset(GData::WinSize.x, GData::WinSize.y, GData::IsWindowed);
	if (bf)
	{
		//���� ���-���� ������� ����� ���� ������ ����� ���� �������������
		g_fnReportf(REPORT_MSG_LEVEL_ERROR, "reset device is failed ... \n");
	}
	else
	{
		GData::InitAllMatrix();
		GData::ReSize = 0;
		SGCore_OnResetDevice();
		SML_OnResetDevice();
		SGeom_OnResetDevice();
		SPE_OnResetDevice();


		GData::DXDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}
}