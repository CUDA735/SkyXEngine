
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __UTILS_H
#define __UTILS_H

#include <gdefines.h>
#include <d3d9.h>
#include <common/array.h>
#include <common/SXMath.h>

#include <gcore/sxgcore.h>
#include <gcore/gcore_data.h>

//##########################################################################

extern IDirect3DDevice9 *g_pDXDevice;
extern D3DCAPS9 g_dxCaps;
extern D3DPRESENT_PARAMETERS g_oD3DAPP;
extern IDirect3D9 *g_pD3D9;
extern ID3DXFont *g_pFPStext;
extern Array<DEVMODE> g_aModes;
extern ID3DXMesh *g_pScreenTexture;

//##########################################################################

//! ������������� ����������
void InitDevice(HWND hWnd, int iWidth, int iHeight, bool isWindowed, DWORD dwFlags);

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