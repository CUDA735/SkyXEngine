
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __OC_H
#define __OC_H

#include <gdefines.h>
#include <d3d9.h>
#include <common/SXMath.h>

#include <gcore/sxgcore.h>

extern IDirect3DDevice9 *g_pDXDevice;
extern D3DPRESENT_PARAMETERS g_oD3DAPP;

//! ����������� ������� ������ ������� occlusion culling
#define OC_SIZE_COEF 0.25f

//! ��������� (� ������) ��� ������� ���� occlusion culling ������ ����� ������ true
#define OC_DIST_NEAR_NOT_CULL 4.f

//! ����������� ������ ������ ��� ����� occlusion culling
//static float g_fOCbiasDepth = 0.0001f;

//! ���������� �������� ���������� ������������� ��� 
const float g_fOCextTriangle = 2.f;

//! ��������� ���������� ����� ��� ����� occlusion culling
const float3 g_cvOCext(0.05f, 0.05f, 0.05f);

//##########################################################################

/*inline bool OC_RasterizeQuad(const float3 &vA, const float3 &vB, const float3 &vC, const float3 &vD, const float2 &vNearFar)
{
	float3 vNormal = TriGetNormal(vA, vB, vC);
	return (OC_TriangleRasterize(vA, vB, vC, false, vNormal, vNearFar) || OC_TriangleRasterize(vB, vC, vD, false, vNormal, vNearFar));
}*/

void SwapFloat3(float3 &vA, float3 &vB);
void TriGetSphere(const float3 &vA, const float3 &vB, const float3 &vC, float &fRadius, float2 &vCenter);
void QuadGetSphere(const float2 &vMin, const float2 &vMax, float &fRadius, float2 &vCenter);

//##########################################################################

class COcclusionCulling
{
public:

	SX_ALIGNED_OP_MEM

	COcclusionCulling();
	~COcclusionCulling();

	//! ������������� �� ��������� �������� �������
	void init(int iWidth, int iHeight);

	//! ��������� ������ ����������
	void onLostDevice();

	//! �������� ������ ����������
	void onResetDevice(int iWidth, int iHeight);

	//! ��������� �������/�������� ����
	void setEnable(bool isEnable);

	//! ���������� ������� ��������� ����������� �����
	bool getEnable();

	/*! ���������� ������ �����
	 \param idDepthMap - ������������� rt �������
	 \param pFrustum - ������� ������
	*/
	void update(ID idDepthMap, const IFrustum *pFrustum);

	//! ���������� ������� ������ ������� �� ��������� ����� ������
	void reprojection();

	//! ������� ��������� �����
	bool comVisible(const float3 *pMax, const float3 *pMin);

protected:

	bool triFrustumCulling(const float3 &vA, const float3 &vB, const float3 &vC);
	bool triRasterize(const float4 &vA, const float4 &vB, const float4 &vC, bool isRasterize, const float3 &vNormal2, const float2_t &vNearFar);

	//! ������ surfaces ��� ���������
	IDirect3DSurface9 *m_pSurfDepthBuffer[3];

	//! ������ �������
	float *m_pArrDepthBuffer = 0;

	//! ������ ������� ���������
	float4 *m_pArrWorldPos = 0;

	//! ������ �������������� �������
	float *m_pArrDepthBufferReProjection = 0;

	//! ������ ������������ (debug)
	float *m_pArrDepthBufferRasterize = 0;

	//! ������� �� ����
	bool m_isEnable;

	//! ������� ������� �������
	float4x4 m_mOldView;

	//! ������� ������������ �������
	float4x4 m_mOldProj;

	//! ����� ���������� �������� � ������ ��� �����
	int m_iCountPixels;

	//! ������ ������ �����
	int m_iWidth;

	//! ������ ������ �����
	int m_iHeight;

	//! ������ �� ������
	ID m_aRTdepth[2];

	//! ������� ���� ������� #m_aRTdepth
	int m_iCurrRTdepth;


	ID m_idVS_ScreenOut;
	ID m_idPS_ScreenOut;
	ID m_idPS_FindMax9;

	//! ������� ������� ������
	const IFrustum *m_pFrustum;

	int m_iCountFC;
	int m_iCountFCfail;

	float m_fBiasDepth;
};

#endif