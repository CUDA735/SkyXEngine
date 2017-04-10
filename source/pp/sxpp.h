
#ifndef __sxpostprocess
#define __sxpostprocess

#include <gdefines.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxgcore_d.lib")
#else
#pragma comment(lib, "sxgcore.lib")
#endif
#include <gcore\\sxgcore.h>

//�������� ������ ��� �������� ������� sepia
#define PP_SEPIA_LIGHT_COLOR float3_t(1.0,0.9,0.5)
#define PP_SEPIA_DARK_COLOR float3_t(0.2,0.05,0.0)
#define PP_SEPIA_WEIGHTS_COLOR float3_t(0.27, 0.67, 0.06)

#define PP_SUN_RADIUS 30 //������ ������ � �������� ��� lens flare
#define PP_MAX_ANGLE_VISIBLE_SUN 1.57 //������������ ���� ����� �������� ����������� � �������� ��������� ����� ��� ������� ��� ����� ������, ������ ����� ������ ��� �� �����

SX_LIB_API long SPP_0GetVersion();				//���������� ������ ����������
SX_LIB_API void SPP_Dbg_Set(report_func rf);	//��������� ������� ��������� ���������

//������������� ����������
SX_LIB_API void SPP_0Create(
	const char* name,			//��� ����������
	IDirect3DDevice9* device,	
	float2_t* winsize,			//������� backbuffer (���� �������)
	bool is_unic				//������ �� ���� ��� ���������� ����������
	);

SX_LIB_API void SPP_0Kill();	//����������� ����������

//��������� �������� render targets
SX_LIB_API void SPP_RTSetInput(ID rt);	//������� ����������� ������� ����� ����������������
SX_LIB_API void SPP_RTSetOutput(ID rt);	//�������������� ����������� ��� ���������� ����
//!!! ��� ������� ������ ���� ��������, �� 0 �� 1, ��� 0 ��� ����� ������, � 1 ��� ������������ ����������� �� ������
//!!! ������ ���������� � ������������ ������
//!!! ������ ����������� � ����� �������: depth = (z + near)/far
//��� near � far ������� � ������� ��������� ��������� �������������� (� ������� 0,25 � 400)
//z - z ���������� ����������� ������� �������������������� wordview projection �������� � ������������������ � ���������� ������
SX_LIB_API void SPP_RTSetDepth0(ID rt);	//������� (�������� 0-1), ��������� ������������ �������
//� ������������ � ���������� �������, ������ ���������� 9���� ����) ����� ����������� ������������
//� � ���� ������ �� ������� ����� 1 (��� �������������)
SX_LIB_API void SPP_RTSetDepth1(ID rt);	//������� (�������� 0-1)
SX_LIB_API void SPP_RTSetNormal(ID rt);	//������� (� ��� ����� � ������������)

//������ � ������������� (�������) � ���������� ������� rt
SX_LIB_API ID SPP_RTGetCurrRender();	//�������� ������� rt ��� ������� � ����
SX_LIB_API ID SPP_RTGetCurrSend();		//�������� ������� rt ��� �������� � ������
SX_LIB_API void SPP_RTIncr();			//����������� ������� ����� �� � ������� ������ � ������� ����������
SX_LIB_API void SPP_RTNull();			//�������� ������� rt, �� ���� ����� ������ rt ������� ������ input, � �������������� output

//���������� ������ ���������������� ����������
//���������� �������� ����� ������� ������� ������������
SX_LIB_API void SPP_Update(
	float3_t* viewpos,	//������� ���� �����������
	float3_t* viewdir,	//����������� �������
	float4x4* view,		//������� ����
	float4x4* proj,		//������� ��������
	float2_t* winsize,	//������� ������� ���� �������
	float2_t* nearfar,	//������� � ������� ��������� ���������
	float projfov		//���� ������ � ��������
	);
SX_LIB_API void SPP_UpdateSun(float3* sunpos);		//����������� ������� ������
SX_LIB_API void SPP_ChangeTexSun(const char* str);	//������� �������� ������ �� str


//�������

//������ ������, ���������� depth0
//������������ �������� ����������� �������� SPP_ChangeTexSun
//sun_color - rgb ���� (0-1), w - �� ������� ���� ���������� � �������� (0-1)
SX_LIB_API void SPP_RenderSun(float4_t* sun_color);

//bloom
//param.x - �� ������� ��� ����������� ���� ������� ��� �������
//param.y - ����������� �������� ����� ��� ����������� ����� bright pass
//param.z - �� ������� ��� ����������� ���� ������� ���� �� ������ ����
//��������� ��������: 1, 0.8, 1
SX_LIB_API void SPP_RenderBloom(float3_t* param);

//lens flare, ������ ���������� ������ ����� �������, ���������� depth0
//param.x - ��������� (�������)
//param.y - ������ ��������
//param.z - ��������� �������������
//use_bloom - ������������ �� � ���������� ������ �� bloom �������, ���� true �� ���� ������ ������ ���� ���� bloom
//��������� ������ ��� 8 (NumSamples) �������: 0.25f, 0.3f, 0.9f, use_bloom - �� ��������
SX_LIB_API void SPP_RenderLensFlare(float3_t* param, bool use_bloom);

//depth of field, ������� ��������, ���������� depth0
//��� ���������� param ����������� � ������
//param.x - ������ ���������� ���������� �������
//param.y - ��� ��� �������������
//param.z - ����������� ������� �� ������� ���������
//param.w - ����������� ������� �� ������� ���������
//sky_blur - �� ������� % ��������� ���� (0-1)
//��� �������: param:0, 200, 0, 50, sky_blur: 0
SX_LIB_API void SPP_RenderDOF(float4_t* param, float sky_blur);

//linear fog, �������� �����, ���������� depth0
//color - ���� ������ (0-1)
//param.x - ������������� ������
//param.y - �� ������� ���� � ������
//param.z - ����������� �������� ������
//param.w - ������������ �������� ������
//��������� ��������: 0.8, 1, 0.1, 0.9
SX_LIB_API void SPP_RenderFog(float3_t* color, float4_t* param);

//space screen ambient occulusion, ���������� ��������� (������ ���������) � ������������ ������, ���������� depth1
//param.x - ������
//param.y - ���������� ���������� ������� � ������� ����� ������� ��� �������� ���������
//param.z - ������������ ������� �� ������� (���� ������� ������ �����������)
//param.w - ���������� ������� ��� ���������
//��������� ��������: 0.3f, 0.1f, 0.8f, 0.3f / GData::NearFar.y
SX_LIB_API void SPP_RenderSSAO(float4_t* param);

//motion blur, �������� � ��������, ���������� depth0
//coef - ���������� ��������, 0 - 1
//timeDelta - ����� ������� �������� ����� � �����
SX_LIB_API void SPP_RenderMotionBlur(float coef, DWORD timeDelta);

//����������� �������
SX_LIB_API void SPP_RenderWhiteBlack(float coef);	//������ ����� �����������, coef - ���������� �������� �� �������� � ������-������ (0-1)
SX_LIB_API void SPP_RenderSepia(float coef);		//������ �����, , coef - ���������� �������� �� �������� � ����� (0-1)
//��������� �����������
//param.x - contrast/��������
//param.y - brightness/�������
//param.z - gamma/�����-���������
//����������� ���������: 1,1,0
SX_LIB_API void SPP_RenderCBG(float3_t* param);


//ANTI ALIASING

//nfaa
//param.x - strength, ��������� �������, ������� ������� �������
//param.y - scale, ������������ �������
//param.z - notmal map, ������� �������������� �������
//������������� ���������: 2, 1, 0
SX_LIB_API void SPP_RenderNFAA(float3_t* param);
SX_LIB_API void SPP_RenderDLAA();	//dlaa

#endif