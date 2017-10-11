
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

/*!
\file
������������ ���� sxrender - ���������� ������� �������
*/

#ifndef __SXRENDER_H
#define __SXRENDER_H

#include <gdefines.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxgcore_d.lib")
#else
#pragma comment(lib, "sxgcore.lib")
#endif

#if defined(_DEBUG)
#pragma comment(lib, "sxgeom_d.lib")
#else
#pragma comment(lib, "sxgeom.lib")
#endif

#if defined(_DEBUG)
#pragma comment(lib, "sxmtllight_d.lib")
#else
#pragma comment(lib, "sxmtllight.lib")
#endif

#if defined(_DEBUG)
#pragma comment(lib, "sxparticles_d.lib")
#else
#pragma comment(lib, "sxparticles.lib")
#endif

#if defined(_DEBUG)
#pragma comment(lib, "sxpp_d.lib")
#else
#pragma comment(lib, "sxpp.lib")
#endif

#if defined(_DEBUG)
#pragma comment(lib, "sxanim_d.lib")
#else
#pragma comment(lib, "sxanim.lib")
#endif


#define SX_LIB_API extern "C" __declspec (dllimport)
#include <gcore/sxgcore.h>
#include <geom/sxgeom.h>
#include <mtllight/sxmtllight.h>
#include <anim/sxanim.h>
#include <pp/sxpp.h>
#include <particles/sxparticles.h>

/*#ifdef SX_DLL
#define SX_LIB_API extern "C" __declspec (dllexport)
#endif*/

#define SX_LIB_API
/*
//������� ���������� ���������� � ���������
//{
//������������� ��� ��������
inline void SetSamplerFilter(DWORD id, DWORD value);
inline void SetSamplerAddress(DWORD id, DWORD value);

//��� ���������� ���������� ����� ���������
inline void SetSamplerFilter(DWORD begin_id, DWORD end_id, DWORD value);
inline void SetSamplerAddress(DWORD begin_id, DWORD end_id, DWORD value);

void SetRenderSceneFilter();
void SetRenderSceneFilterUn();
//}
*/

//! ��������� ������ � �������������� ����������
SX_LIB_API void ComDeviceLost();

//! ��������� ��������� ��� ���������� �����
SX_LIB_API void ComVisibleForLight();				

//! ��������� ��������� ��� ������
SX_LIB_API void ComVisibleForCamera();				

//! ��������� ��������� ��� ���������
SX_LIB_API void ComVisibleReflection();			


SX_LIB_API void UpdateDataCVar();

SX_LIB_API void UpdateView();						//!< ��������� � ��������� �������� ������, ��������� ���������� ���������
SX_LIB_API void OutputDebugInfo(DWORD timeDelta);	//!< ����� ���������� ��������� ���������� � ���� �������



SX_LIB_API void BuildMRT(DWORD timeDelta);		//!< ���������� G ������, �� ���� ������ ���� �����
SX_LIB_API void UpdateShadow(DWORD timeDelta);		//!< ���������� ���������� � ����� (������ ����� ���� ��� ����������� ���� � ������ ������ ���������� �����)
SX_LIB_API void UpdateReflection(DWORD timeDelta);	//!< ���������/���������� ���������

void RenderSky(DWORD timeDelta);					//!< ��������� ��������� � �������
void ComLighting(DWORD timeDelta, bool render_sky);	//!< ��������� ���������, render_sky - �������� �� ����
void RenderParticles(DWORD timeDelta);				//!< ��������� ��������� (��������)
void RenderPostProcess(DWORD timeDelta);			//!< ��������� ������������
void ShaderRegisterData();
/*
void SaveScreenShot();		//!< ��������� ��������
void SaveWorkTex();			//!< ��������� ������� �������� (�-����� � ��� � ���� �����������)
void ChangeModeWindow();	//!< �������� ����� ������� (�������/�������������)
*/
#endif