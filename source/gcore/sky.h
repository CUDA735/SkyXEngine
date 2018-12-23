
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __SKY_H
#define __SKY_H

#include <gdefines.h>
#include <d3d9.h>
#include <common/array.h>
#include <common/String.h>
#include "sxgcore.h"

extern IDirect3DDevice9 *g_pDXDevice;
extern D3DPRESENT_PARAMETERS g_oD3DAPP;

//##########################################################################

//! ��������� ������ ��� ���������
struct CSkyBoxVertex
{
	CSkyBoxVertex(float fX,float fY,float fZ,float fU,float fV,float fW)
	{
		x = fX;  y = fY;  z = fZ; u = fU; v = fV; w = fW;
	}
	float x, y, z;
	float u, v, w;
};

//**************************************************************************

//! ��������, ���, �� ������� ������������� ���������� �������� � ������������ ����
class CSkyBox
{
public:
	CSkyBox();
	~CSkyBox();

	SX_ALIGNED_OP_MEM

	//! �������� ��������
	void loadTexture(const char *szTexture);

	//! ��������� �� ��������
	bool isLoadTex();

	//! ������������ ��?
	bool getUse();

	//! ���������� �������������
	void setUse(bool isUse);

	//! ������ ��������
	void changeTexture(const char *szTexture);

	//! � szTexture ������� ��� ������� �������� ��������
	void getActiveTexture(char *szTexture);

	//! � szTexture ������� ��� ��������� ��������
	void getSecondTexture(char *szTexture);

	//! ���������� ���� ��������
	void setRotation(float fAngle);

	//! ���������� ���� ��������
	float getRotation();

	//! ���������� ����, w ���������� ��� ����������� ����� [0,1]
	void setColor(const float4_t *pColor);

	//! � pColor ���������� ����
	void getColor(float4_t *pColor);

	//! ������
	void render(float timeDelta, const float3 *pPos,bool isShadow);

protected:

	//! ���������� ������
	IDirect3DVertexDeclaration9* m_pVertexDeclarationSkyBox;
	
	//! ���� ��������
	float m_fRotaionY;

	//! ������� ��������
	float4x4 m_mMatRotation;

	//! ����
	float4_t m_vColor;

	//! ���������� ���������� �������
	float m_fFactorBlend;

	//! ���������� �� ����� �������
	bool m_isChange;

	//! ������������ ��?
	bool m_isUse;

	
	//bool m_isChangeMainTex;

	//! ������ (�������� ��������)
	ID m_idTex1;

	//! ������ (�������� ������ ��� #changeTexture)
	ID m_idTex2;

	//! ��������� �����
	IDirect3DVertexBuffer9 *m_pVertices;

	//! ��������� �����
	IDirect3DIndexBuffer9  *m_pIndeces;

	//! ��������� ������
	ID m_idVS;

	//! ���������� ������
	ID m_idPS;
};

//##########################################################################

//! ��������� ������ �������
struct CSkyCloudsVertex
{
	CSkyCloudsVertex(float fX,float fY,float fZ,float fU,float fV)
	{
		x = fX;  y = fY;  z = fZ; u = fU; v = fV;
	}
	float x, y, z;
	float u, v;
};

//**************************************************************************

//! ������
class CSkyClouds
{
public:
	CSkyClouds();
	~CSkyClouds();

	SX_ALIGNED_OP_MEM

	//! ���������� ��������� �������
	void setWidthHeightPos(float iWidth,float iHeight, const float3 *pPos);

	//! �������� ��������
	void loadTexture(const char *szTexture);

	//! ��������� �� ��������
	bool isLoadTex();

	//! ������������ ��?
	bool getUse();

	//! ���������� �������������
	void setUse(bool isUse);

	//! �������� ��������
	void changeTexture(const char *szTexture);

	//���������� �������
	void setRotation(float fAngle);

	//! ���������� �������
	float getRotation();

	//! ������������� ������������
	void setAlpha(float fAngle);

	//! ���������� ������������
	float getAlpha();

	//! ����������� ����, w ���������� ��� ����������� ����� [0,1]
	void setColor(const float4_t *pColor);

	//! � pColor ���������� ����
	void getColor(float4_t *pColor);

	//! ���������� �������� ��������
	void setSpeed(float fSpeed);

	//! ���������� �������� ��������
	float getSpeed();

	//! ������
	void render(DWORD timeDetlta, const float3 *pPos, bool isShadow);

private:

	//! ���������� ������
	IDirect3DVertexDeclaration9 *m_pVertexDeclarationClouds;

	//! ���������� ������������
	float m_fAlpha;

	//! ������� �� ��� Y
	float m_fRotaionY;

	//! ������� ��������
	float4x4 m_mMatRotation;

	//! ������������ ��?
	bool m_isUse;

	//! ���� �������
	float4_t m_vColor;

	//! ���������� ���������� ���������� �������� � �����
	float m_fFactorBlend;

	//! ������� ����� �������
	float2_t m_vWidthHeight;

	//! ���������� �� ������ ����� �������
	bool m_isChange;

	//bool m_isChangeMainTex;

	//! �������� �������� �������
	float m_fSpeed;

	//! ������� �������� � ���������� �����������
	float m_fBias;

	//! ��������� �����
	IDirect3DVertexBuffer9 *m_pVertices;

	//! ��������� �����
	IDirect3DIndexBuffer9 *m_pIndeces;

	//! ������ (�������� ��������)
	ID m_idTex1;

	//! ������ (�������� ������ ��� #changeTexture)
	ID m_idTex2;

	//! ��������� ������
	ID m_idVS;

	//! ���������� ������ (��������� ��� ������)
	ID m_idPS;

	//! ���������� ������ (��������� ��� �����)
	ID m_idPS_Shadow;
};

#endif
