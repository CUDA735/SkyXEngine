
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __MODELS_H
#define __MODELS_H

#include <new>
#include <common/string.h>
#include <common/string_utils.h>
#include <common/array.h>
#include <gcore/sxgcore.h>
#include "sxgeom.h"

/*! \name ���� �������
@{*/

//! ������ �������
#define GEOM_COUNT_TYPE_SEGMENTATION_QUAD 4

//! �����������
#define GEOM_COUNT_TYPE_SEGMENTATION_OCTO 8

//! ��������� ���������� ��������� ��� ������� ��������� 
#define GEOM_DEFAULT_RESERVE_COM 512	

//!@}

#define GEOM_COPY_POSTFIX "-copy"

extern IDirect3DDevice9 *g_pDXDevice;
extern D3DCAPS9 g_dxCaps;

//##########################################################################

#define STATIC_PRECOND_VISCALCOBJ_ID(idVisCalcObj, retVal) \
if (!(idVisCalcObj >= 0 && m_aVisInfo.size() > idVisCalcObj && m_aVisInfo[idVisCalcObj]))\
{\
	LibReport(REPORT_MSG_LEVEL_ERROR, "%s - static: unresolved id '%d' for array of compute visible", GEN_MSG_LOCATION, idVisCalcObj); \
	return retVal; \
}

#define STATIC_PRECOND_MODEL_ID(idModel, retVal) \
if(!(idModel >= 0 && idModel < (int)m_aModels.size() && m_aModels[idModel]))\
{\
	LibReport(REPORT_MSG_LEVEL_ERROR, "%s - static: unresolved id '%d' for array of models", GEN_MSG_LOCATION, idModel); \
	return retVal; \
}

#define STATIC_PRECOND_TRANSPARENCY_MODEL_ID(idModel, retVal) \
if(!(idModel >= 0 &&idModel < (int)m_aTransparency.size() && m_aTransparency[idModel]))\
{\
	LibReport(REPORT_MSG_LEVEL_ERROR, "%s - static: unresolved id '%d' for array of transparency models", GEN_MSG_LOCATION, idModel); \
	return retVal; \
}

#define STATIC_ERROR_MODEL_GROUP_ID(idModel, idGroup, retVal) \
	LibReport(REPORT_MSG_LEVEL_ERROR, "%s - static: unresolved id '%d' for group models %d", GEN_MSG_LOCATION, idGroup, idModel); \
	return retVal;

//##########################################################################

/*
�������������� ������� �� ����������, ��� �������� ����� �� �������, ��� ������� ������ �������� ���� id, ��� ������ ��� ���� id ��������, ������� ��������� ��������� ������� �� ���� ���� � ��������� ������
������� �������� ��������� �� ������� id �������� �� �����, ������� ������� ����������� �������� ������ - ��������� �� ������, ����� ��������� �������� � �������� ������� + ���������� �� � ������ �������, � ����� ���� �� ������� ����������� id ��������
*/

//! ����� ������� ����������� ���������
class CModels
{
public:
	CModels();
	~CModels();

	//! ����� ���������� ������, ������ ������ �����������
	struct CPhysMesh
	{
		CPhysMesh();
		~CPhysMesh();

		//! ������ ������
		Array<float3_t> m_aVertex;

		//! ������ ��������
		Array<uint32_t> m_aIndex;

		//! ������ id ���������� ��� ������� �������
		Array<ID> m_aMtrl;

		//! ������ ���� ������� ��� ������� �������
		Array<ID> m_aNumMtrl;

		//! ������ ���� ���������� ��� ������ ���������
		Array<String> m_aStringMtrl;

		//! ���� �� ����������� ������
		String m_sPath;
	};

	/*! ��� - ������������������ ������, ������� �������� ������ ������������ ������ ����� ����������� �� ����������� �������� �� ������
	*/
	struct CLod
	{
		CLod();
		~CLod();

		//! ���� �� ������ ���� � ����� ����������� ���������
		String m_sPath;

		//! ��������� �� ������ ISXDataStaticModel
		ISXDataStaticModel *m_pModel;

		//! ������ ��������������� �������, ��� �������� ������ ���� ������ �����
		Array<ID> m_aIDsTextures;
	};

	//! �������, ����� ������
	struct CSegment
	{
		CSegment();
		~CSegment();

		//! ������ �� 4/8 ������ ������� �������
		CSegment *m_aSplits[GEOM_COUNT_TYPE_SEGMENTATION_OCTO];

		//! ��������� �� ������������ �����
		CSegment *m_pParent;

		//! ��������� ������ �� ���������� ��������, ��������� ������ - ��� �������� ��� ������ ���������
		uint32_t **m_ppArrPoly;

		//! ������ � ����������� ��������� �� ������ ���������
		uint32_t *m_pCountPoly;

		//! ������ � �������� ��������
		uint32_t *m_pNumberGroup;

		//! ���������� ��������
		uint32_t m_uiCountSubSet;

		//! ����� ���������� ���������
		uint32_t m_uiCountAllPoly;


		//! ����������� �������������� ����� ��� ������������ �������
		ISXBound *m_pBoundVolumeSys;

		//! ���������� �������������� �����
		ISXBound *m_pBoundVolumeP;

		//! ������� ���������� �� ������ (��� ����������� ����� �������� ���)
		float m_fDistForCamera;

		//! ������������� �����
		ID m_ID;

		//! ���������� ����� ����� �� ������� ���������� ������
		ID m_SID;

		//! ������� ����������� �������� �����
		ID m_idDepth;

		//! ����� �� ����� ����� ������ ����?
		bool m_isFinite;

		//ID3DXMesh *m_pBoundBox;	
	};

	//! ���������� � ���������
	struct CGroupInfo
	{
		CGroupInfo();
		~CGroupInfo();

		SX_ALIGNED_OP_MEM2();

		//! �������
		float3 m_vMin;

		//! ��������
		float3 m_vMax;

		//! �����
		float3 m_vCenter;

		//! ���������
		D3DXPLANE m_oPlane;
	};

	//! �������������� ������
	struct CTransparencyModel
	{
		CTransparencyModel();
		~CTransparencyModel();

		SX_ALIGNED_OP_MEM2();

		//! id ������ � ������� ����������� ������ ���
		ID m_idModel;

		//! ����� �� ������
		bool m_isVisible4Observer;

		//! ��������� �� �����������
		float m_fDist4Observer;

		//! ���������� � ��������� :)
		CGroupInfo m_oGroupInfo;

		//! ��� ��������
		String m_sTex;

		//! id ��������
		ID m_idTex;

		//! ���������� ������
		int32_t m_iCountVertex;

		//! ���������� ��������
		int32_t m_iCountIndex;

		//! ��������� �����
		IDirect3DVertexBuffer9 *m_pVertexBuffer;

		//! ��������� �����
		IDirect3DIndexBuffer9 *m_pIndexBuffer;

		//! �������������� �����
		ISXBound *m_pBoundVolume;
	};

	//! ��������� ������
	struct CModel
	{
		CModel();
		~CModel();

		SX_ALIGNED_OP_MEM

		//! ��� ������
		String m_sName;

		//! ���� �� ������ � ����� ����������� ���������
		String m_sPath;

		//! ��������� �� ������ ISXDataStaticModel
		ISXDataStaticModel *m_pModel;

		//! ��������� �� ���
		CLod *m_pLod;

		//! ���������� ������
		CPhysMesh *m_pPhysics;

		//! ������ ��������������� �������
		Array<ID> m_aIDsTextures;

		//! ������ � ����������� � ����������
		Array<CGroupInfo*> m_aGroupInfo;

		//! �������������� ����� ������������ ������
		ISXBound *m_pBoundVolume;

		//! �������� �� ���?
		bool m_isRenderLod;

		//! ��������� �� �����������
		float m_fDist4Observer;

		//! ������ �������������� ������� ������������� ������ ������
		Array<ID> m_aTransparency;

		//! ������ � ����������
		CSegment *m_pArrSplits;

		//! ����� ���������� ���������/�������
		ID m_idCountSplits;

		//! ���������� ���������� ���������
		ID m_idCountSplitsRender;

		//! ���������� ��������� ������� ���� ���������� ��� ������ ���������
		UINT *m_pCountDrawPoly;

		//! ������ �������� �������� ��� ������ ���������, ������� ���� ����������
		UINT **m_pVisibleIndeces;

		//! ����� ��������, ����������� � real-time
		IDirect3DIndexBuffer9 *m_pVisibleIndexBuffer;
	};

	//######################################################################

	//! ��������� ���������� ����������� ����������� ���������� � �������� ������ ��� �������
	struct CVisInfoModel
	{
		CVisInfoModel();
		~CVisInfoModel();

		//! ����� �� ������
		bool m_isVisible;

		//! ������ �������� � ���� ��������� �� ��������
		CSegment **m_ppSegments;

		//! ������ m_ppSegments 
		int m_iCount;

		//! ������� ��������� �������� � m_ppSegments
		int m_iCountCom;
	};

	//! ������ �������� ���������
	struct CVisInfo
	{
		CVisInfo();
		~CVisInfo();

		//! ���������� � ��������� �������� ������
		Array<CVisInfoModel*> m_aVisible4Model;

		//! ���������� � ��������� �� �������
		Array<bool> m_aVisible4Transparency;
	};

	//######################################################################

	//! ���������� ������ � ���� ������� � �������� ����
	void save(const char *szPath);

	//! �������� ��������� ����� � ������� �������
	void load(const char *szPath);

	//**********************************************************************

	//! �������� ������
	ID addModel(const char *szPath, const char *szName, const char *szLod, const char *szPhys, bool needSegmentation);

	//! ������� ������ (�� �������� �������� ��������� ���� ��������)
	void deleteModel(ID idModel);

	//! ������� ������ ������� (������� ��� ������)
	void clear();

	//! ������ ����������� ������ �� �� id, ���������� id ����� (�����) ������
	ID copy(ID idModel);

	//! ���������� ���������� �������
	int getCountModel();

	//! ���������� ������� � �������� ���� �������
	void getMinMax(float3 *pMin, float3 *pMax);

	//**********************************************************************

	//! �������� ����� ������ �������� ���������, ���������� id
	ID addVisCaclObj();

	//! ���������� �� ������ �������� ��������� � id
	bool existsVisCaclObj(ID idVisCaclObj);

	//! ������� ������ �������� ��������� �� ��� id
	void deleteVisCaclObj(ID idVisCaclObj);

	//**********************************************************************

	//! ���������� �� ������� ��� �����������
	void sortTransparency(const float3 *pViewPos);

	//! ���� �� �� ������ ��� ������ � idVisCalcObj ������� ��������� ���������
	bool existsTransparency4Render(ID idVisCalcObj);

	//**********************************************************************

	//! ��������� ��������� ������
	void modelSetPosition(ID idModel, const float3 *pPos);

	//! ���������� (� ���������� � �������� ���� �� NULL) ������� ������
	const float3* modelGetPosition(ID idModel, float3 *pPos=0);

	//! ��������� ��������� ������ (� ��������)
	void modelSetRotation(ID idModel, const float3 *pRot);

	//! ���������� (� ���������� � �������� ���� �� NULL) �������� ������
	const float3* modelGetRotation(ID idModel, float3 *pRot=0);

	//! ��������� ��������������� ������
	void modelSetScale(ID idModel, const float3 *pScale);

	//! ���������� (� ���������� � �������� ���� �� NULL) ������� ������
	const float3* modelGetScale(ID idModel, float3 *pScale=0);

	//! ������ �������������� �������, ��� ��������� ������� ������� �������, ������ ����� ������������������ �� ������ ���������, ��� ������� ������ ��������� ��������
	void modelComBound(ID idModel);

	//**********************************************************************

	//! ��������� ���� ������
	void modelSetLod(ID idModel, const char *szPath);

	//! ��������� ���������� �������� ������
	void modelSetPhysics(ID idModel, const char *szPath);

	//! ��������� ���������� �������� ������
	void modelSetPhysics2(CModel *pModel, const char *szPath);

	//! ���������� ���� �� ����� ������
	const char* modelGetPath4Model(ID idModel);

	//! ���������� ���� �� ����� ����
	const char* modelGetPath4Lod(ID idModel);

	//! ���������� ���� �� ����� ���������� ������
	const char* modelGetPath4Physics(ID idModel);
	
	//! ���������� ������� � �������� ������
	void modelGetMinMax(ID idModel, float3 *pMin, float3 *pMax);

	//! ���������� ��� ������ � ���������� �� � szName ���� ���� �������� �� NULL
	const char* modelGetName(ID idModel, char *szName=0);

	//! ��������� ����� ��� ������
	void modelSetName(ID idModel, const char *szName);

	//! ���������� ���������� ��������� ������
	int modelGetCountPoly(ID idModel);
	
	//! ���������� ���������� �������� ������
	int modelGetCountGroups(ID idModel);

	//! ���������� id ��������� ��������� ������
	ID modelGetGroupMtrlID(ID idModel, ID idGroup);
	
	//! ���������� �������/�������� ��������� ������
	void modelGetGroupMinMax(ID idModel, ID idGroup, float3_t *pMin, float3_t *pMax);

	//! ���������� ��������� ��������� ������
	void modelGetGroupPlane(ID idModel, ID idGroup, D3DXPLANE *pPlane);

	//! ���������� ����� ������ ��������� ������
	void modelGetGroupCenter(ID idModel, ID idGroup, float3_t *pCenter);

	//! �������������� �� ������
	bool modelGerSegmentation(ID idModel);

	//**********************************************************************

	//! ������ ���������
	void comVisible(const IFrustum *pFrustum, const float3 *pViewPos, ID idVisCalcObj = SX_GEOM_DEFAULT_VISCALCOBJ);

	//**********************************************************************

	//! ������ ����� ������
	void renderSingly(DWORD timeDelta, ID idModel, ID idMtrl = -1, const float3 *pPos = 0);

	//! ������ �������
	void render(DWORD timeDelta, GEOM_RENDER_TYPE type, ID idVisCalcObj = SX_GEOM_DEFAULT_VISCALCOBJ);

	//**********************************************************************

	//! ��������� ���������� ������ ���� �������
	void getArrBuffsGeom(
		float3_t ***pppArrVertex,	//!< (*arr_vertex)[num_model][num_vertex] - ������� ������
		int32_t	**ppArrCountVertex, //!< (*arr_count_vertex)[num_model] - ���������� ������ ��� ������
		uint32_t ***pppArrIndex,	//!< (*arr_index)[num_model][num_vertex] - ������� ������
		ID ***pppArrMtl,			//!< (*arr_mtl)[num_model][num_vertex] - �������� ��� �������
		int32_t **ppArrCountIndex,	//!< (*arr_count_index)[num_model] - ���������� �������� ��� ������
		int32_t *pCountModels		//!< (*count_model); ���������� �������
		);

	//����������� ����
	bool traceBeam(const float3 *pStart, const float3 *pDir, float3 *pResult, ID * idModel, ID * idMtrl);

protected:

	//! ������ �������, ������� ���������� ���, ��� ���������
	Array<CModel*> m_aModels;

	//! ������ �������� �������� ���������
	Array<CVisInfo*> m_aVisInfo;

	//**********************************************************************

	//! �������� �� ������
	ID createTransparencyModel(ID idTex, const char *szTex, const vertex_static_ex *pArrVertex, int iCountVertex, const UINT *pArrIndex, int iCountIndex);

	//! ������ �� �������
	Array<CTransparencyModel*> m_aTransparency;

	//! ������ �� �������, ������������� �� ��������� �� �� ������ �� �����������
	Array<CTransparencyModel*> m_aSortTransparency;

	//**********************************************************************

	/*! ������ ������� ����������� ������
	@{*/

	//! ������ ������ ������� ������
	float3 *m_pCurrArrMeshVertex;

	//! ������ �������� ������� ������
	UINT *m_pCurrArrMeshIndex;

	//!@}

	//**********************************************************************

	//! ������ ��������� ��� ���� ���������, ��� #traceBeam
	void getPartBeam(ID idModel, ID idVisCalcObj, const float3 *pStart, const float3 *pDir);

	//**********************************************************************

	//! �������� ������ � ������� �������� ���������
	void addModelInVisCalcObj(ID idModel);

	//! ������� ������ �� �������� �������� ���������
	void deleteModelOutVisCalcObj(ID idModel);

	//**********************************************************************

	//! ����������� ������
	void segmentation(CModel *pModel);

	//! ����������� �������� ������
	void segmentation2(CSegment *pSplit, CModel *pMesh, int iCountSplitsSys, int iCountPolyInSegment, Array<CSegment*> *pQueue);

	//! ����������� ����� �����������
	void segmentationCycle(CSegment *pSplit, CModel *pMesh, int iCountSplitsSys, int iCountPolyInSegment);

	//! ������������� m_pBoundVolumeP ������ ��� ����� �� ��������� ������� �����
	void editVolume(CModel *pMesh, CSegment *pSplit);

	//! ��������� ������� ����� ��������������, �������� ������ ������, ��������� ������� ����� ��������
	void setSplitID(CSegment *pSplit, ID *pSplitsIDs, ID *pSplitsIDsRender);

	//! �������� ������� ������ ��� �������� ��������� ��������� ������
	void createExternalData4SegmentModel(CModel *pModel);

	//**********************************************************************

	//! �������� ��������������� �� ������� ��� ������������ ������� (�� ������ �������������� �������, ����� ��������� ���� �� �������� �������)
	void reCalcIdTransparency();

	//! ������������� id �������� ��� �� �������
	void reSetIdModel4Transparency(ID idModel);

	//**********************************************************************

	//! ��������� ���������� � ���������� ������
	void modelGenGroupInfo(CModel *pModel);

	//! ��������� ���������� ��������� �� ������
	void modelGenGroupInfo4Transparency(CTransparencyModel *pModel);

	//**********************************************************************

	//! ������ ������� ��� �� ������� �� id �������� ������, ����� �������� ������ ��� ���� ����� �����������, ��� ��� �� �������� �������
	void modelComBoundArrTransparency(ID idModel);

	//! ������ ������� ���������
	void modelComBound4Segments(ID idModel);

	//**********************************************************************

	//! ������ ��������� �� �������
	void comVisibleTransparency(const IFrustum *pFrustum, const float3 *pViewPos, ID idVisCalcObj = 0);

	//! ����������� ��������� ��������
	void comVisibleSegment(ID idVisCalcObj, const IFrustum *pFrustum, CSegment **ppSplits, int *iCount, CSegment *pSegment, const float3 *pViewPos, Array<CSegment*, GEOM_DEFAULT_RESERVE_COM> *pQueue, int iCountSplitsRender);

	//**********************************************************************

	//! ������ ���� ������
	void renderLod(DWORD timeDelta, ID idModel, ID idTex = -1, const float3 *pPos = 0);

	//! ������ ������
	void renderObject(DWORD timeDelta, ID idModel, ID idTex = -1, const float3 *pPos = 0);

	//! ������ ��������� ������
	void renderSegmets(DWORD timeDelta, ID idModel, ID idTex = -1, ID idVisCalcObj = SX_GEOM_DEFAULT_VISCALCOBJ);

	//! ������ �� ������
	void renderTransparency(DWORD timeDelta, CTransparencyModel *pTransparencyModel);
};

#endif