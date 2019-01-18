
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __UTILS_H
#define __UTILS_H

#include <gdefines.h>
#include <graphix/graphix.h>
#include <common/array.h>
#include <common/SXMath.h>

#include <gcore/sxgcore.h>
#include <gcore/gcore_data.h>

//##########################################################################

extern IGXContext *g_pDXDevice;
extern HMODULE m_hLibGXAPI;
extern Array<DEVMODE> g_aModes;
extern IMesh *g_pScreenTexture;

//##########################################################################

//! ������������� ����������
void InitDevice(SXWINDOW hWnd, int iWidth, int iHeight, bool isWindowed, DWORD dwFlags);

//! ������������� ���������� ����
void InitFPStext();

//! ������������� �������������� ��������
void InitFullScreenQuad();

//! ������������� ������� ������� ��������
void InitArrModes();

//! ������������� ������ �������� ��� 
void InitRT4Gbuffer();

//! �������� ��������
void LoadShaders();

//! ���������� ������� ��� tone mapping
void ToneMappingGetArrDownScale4x4(int iWidth, int iHeight, float2 aDS[]);

//! ������ tone mapping
void ToneMappingCom(DWORD timeDelta, float fFactorAdapted);

#endif