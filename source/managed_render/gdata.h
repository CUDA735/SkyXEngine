
#ifndef __gdata_h
#define __gdata_h

#include <managed_render/model_sim.h>

namespace GData
{
	IDirect3DDevice9* DXDevice = 0;

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitWin(const char* name);
	HWND Handle3D = 0;
	float2_t WinSize = float2_t(800, 600);
	ISXCamera* ObjCamera = 0;
	ModelSim* SimModel = 0;
	int ReSize = 0;	//0 - ������ �� ������, 1 - ������, 2 - ������������ �������� � �����
	float2_t NearFar = float2_t(0.25,400);
	bool IsWindowed = true;
	float ProjFov = SM_PI * 0.25f;

	ID DefaultGeomIDArr = -1;
	ID DefaultGreenIDArr = -1;
	ID DefaultAnimIDArr = -1;
	
	float3 ConstCurrCamPos;	//������� ������
	float3 ConstCurrCamDir;	//����������� ������� ������

	float4_t CamWalkParamEditor = float4_t(
		10.f,	//������� �������� ������
		5.f,	//���������� ���������
		0.7f,	//���������� �� ��������� �������� � ������� 
		0.5f	//���������� �� ��������� �������� �����
		);

	//������� ��������� ���������, ���������� ��� ����������� ��������� �� �������� ������ � ���������
	D3DXPLANE PlaneZCulling;
	D3DXPLANE PlaneZCullingShader;

	//�������
	void InitAllMatrix();
	float4x4 MCamView;			//������� ���� ������
	float4x4 MCamProj;			//������� �������� ������
	float4x4 MLightProj;		//������� �������� ����������� ������, ������ �������� ��������� ������
	float4x4 MRefPlaneSkyProj;	//������� �������� ��� ������� skybox � sky clouds, ��� ������� ���������, ���������� MCamProj
	float4x4 MRefCubeSkyProj;	//������� �������� ��� ������� skybox � sky clouds, ��� ���������� ���������

	//////

	//������������ ���� � ������
	namespace Pathes
	{
		void InitAllPathes();

		char ForExe[1024];
		char WorkingTex[1024];
		char GameSource[1024];
		char Screenshots[1024];
		char Configs[1024];
		char Levels[1024];
		char Meshes[1024];
		char Models[1024];
		char Scripts[1024];
		char Materials[1024];
		char GUIresources[1024];
		char Sounds[1024];
		char Shaders[1024];
		char Textures[1024];
			char TexturesDetail[1024];
			char TexturesSkyBoxes[1024];
	};

	//������������ ���� � ���������������� ��������
	namespace IDsShaders
	{
		void InitAllShaders();
		//��������� �������
		namespace VS
		{
			ID ScreenOut;
			ID ResPos;
		};

		//���������� �������
		namespace PS
		{
			ID ScreenOut;
			ID ComLightingNonShadow;
			ID ComLightingShadow;

			ID BlendAmbientSpecDiffColor;

			ID StencilStr;
			ID StencilColumn;
			ID StencilStrColumn;
			ID UnionAlpha;
			ID SmoothingAlpha;
		};
	};

	namespace IDSRenderTargets
	{

	};
};

#include <managed_render/model_sim.cpp>

#endif