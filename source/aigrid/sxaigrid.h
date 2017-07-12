
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

/*!
\file
������������ ���� sxaigrid - ���������� AI ����� (�������������)
*/

/*! \defgroup sxaigrid sxaigrid - ���������� ������������� ����� (AI �����)
AI ����� ������� �� ��������� (����. ����), ����� ����� ������� (����������� ����� �� xz), ��������� ����� ����� ���� ������������\n
 \warning ������� #SAIG_QuadAdd #SAIG_QuadDelete #SAIG_GridGenerate ���� �������� ����������� �����, ���� �������� �������� ����� �������, ������� ����� ���� ������� �������� ���������� ��������� �����������,
 ���� ��������� ����������� �������� ��� ����� ���������� ������� ������� #SAIG_GridTestValidation ����� ���� ��������� ����������� ����� ����� ���������� � ����� ������ ����.
 \warning �������������� ����� (�����) ��������� ������, ����� ������� ��� �������� (���� ����������) ����� ���� ��� ����� ��������� �������� ���������� ������� #SAIG_BBCreateFinish, ��� ������� ���������� ��������� ����������� ������������, ����� ����� ������� ����������� � ������� ����������

@{
*/

#ifndef __sxaigrid
#define __sxaigrid

#include <gdefines.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxgcore_d.lib")
#else
#pragma comment(lib, "sxgcore.lib")
#endif
#include <gcore\\sxgcore.h>

/*! \name ������� ������� ����������
@{*/

SX_LIB_API long SAIG_0GetVersion();				//!< ������ ����������
SX_LIB_API void SAIG_Dbg_Set(report_func rf);	//!< ���������� ������� ��������� ���������

//! ������������ ����������
SX_LIB_API void SAIG_0Create(
	const char* name,			//!< ������������� ���
	bool use_graphics = false,	//!< ������������ �� ����������� ����������� (��� ���������� � �������) ��� ��� (������� �����)
	bool is_unic = true			//!< ������ �� ���������� ���� ���������� �� �����
	);

SX_LIB_API void SAIG_AKill();	//!< ���������� ����������

//!@}

#define AIGRID_QUADS_CENTERS_MAXHEIGHT	0.6f	/*!< ������������ ������ ����� �������� �������� ������ */

#define AIGRID_BBOXSIZE					5.f		/*!< ������� �������������� ������ */

#define LAIGRID_QUADS_CENTERS_MAXHEIGHT	60		/*!< int*100 ������������ ������ ����� �������� �������� ������ */
#define LAIGRID_QUAD_SIZE				70		/*!< int*100 ������� ����� */
#define LAIGRID_QUAD_SIZEDIV2			35		/*!< int*100 ���������� ������ ����� */

//�����������
#define AIGRID_QUAD_DIR_ALL				0		/*!< ���� ����� �������� � ������������� � ������������� ����������� */
#define AIGRID_QUAD_DIR_POSITIVE		1		/*!< ���� ����� ������ ������������� ������� */
#define AIGRID_QUAD_DIR_NEGATIVE		-1		/*!< ���� ����� ������ ������������� ������� */
#define AIGRID_QUAD_DIR_NONE			2		/*!< ���� �� ����� ��������� */

#define AIGRID_QUAD_SIZE				0.7f	/*!< ������� ����� */
#define AIGRID_QUAD_SIZEDIV2			0.35f	/*!< ���������� ������ ����� */
#define AIGRID_QUAD_ADDYPOS				0.01f;	/*!< �� ������� ������ ����� ��������� ���� */

//���� �����������
#define AIGRID_COST_DIRECT				10		/*!< ���� ������� ����������� */
#define AIGRID_COST_DIAGONAL			14		/*!< ���� ����������� �� ��������� */

#define AIGRID_COST_GPATH				500		/*!< ���������� ����������� ��������� (int(dist * 100)) ��� ���������� ���������� ���������� */

#define AIGRID_COSTADD_TEMPBUSY			50		/*!< ��������� ��������� ��� ������� ����� ���� ������� �������� ����� */
#define AIGRID_COSTADD_BUSY				250		/*!< ��������� ��������� ��� ������� ����� ���� ������� ����� */

#define AIGRID_QUADSCOUNT_BUSY			50		/*!< ��������� (���� �� ����������� � ���������, �� �� �� ���������) � �������� ������� ����� ����������� ��������� ����� */

#define AIGRID_ENTITY_MAX_HEIGHT		1.5f								/*!< ������������ ������ ��������, ������� ����� ������������� �� ����� */
#define AIGRID_ENTITY_MAX_HEIGHTDIV2	(AIGRID_ENTITY_MAX_HEIGHT * 0.5f)	/*!< ���������� ������������ ������ �������� */

#define AIGRID_COLOR_GBBOX				D3DCOLOR_ARGB(128, 0, 255, 0)		/*!< ���� �������� ��������������� ������ */
#define AIGRID_COLOR_SEL_MAIN			D3DCOLOR_ARGB(220, 255, 255, 255)	/*!< ���� ����������� ����� */
#define AIGRID_COLOR_SEL_ADD			D3DCOLOR_ARGB(100, 255, 255, 255)	/*!< ���� ������� (������) ����������� ����� */

//! ��������� ��������� �����
enum AIQUAD_STATE
{
	AIQUAD_STATE_FREE = 0,		//!< ��������
	AIQUAD_STATE_TEMPBUSY = 1,	//!< �������� �����
	AIQUAD_STATE_BUSY = 2,		//!< �����
};

/*! ��� ������� ��� ��������� ����� �� ������, 
�� ���� ���� ������� ������� �����, 
���������� false � ������ ����� (������� �� �������) � true � ������ �������(���� ������� ����������� ��� ��� ���������� � ������� ������, ���� �� ������ �� ���������) 
*/
typedef bool(*g_aiquad_phy_navigate) (float3_t * pos);
/*! �������������� g_aiquad_phy_navigate, ������������ �������� ��� ������ � ������ */
SX_LIB_API void SAIG_SetFunc_QuadPhyNavigate(g_aiquad_phy_navigate func);

SX_LIB_API void SAIG_Clear();						//!< ������� ���� ������

//����������/��������
SX_LIB_API void SAIG_GridSave(const char* path);	//!< ���������� �����
SX_LIB_API void SAIG_GridLoad(const char* path);	//!< �������� �����

/*! \name �������������� ����� 
@{*/

SX_LIB_API void SAIG_BBCreate(const float3* center, const float3* param);	//!< ������� �������������� ����� �� ����������
SX_LIB_API bool SAIG_BBIsCreated();											//!< ������ �� �������������� �����

//���������/��������� ���������
SX_LIB_API void SAIG_BBSetDimensions(const float3* dim);	//!< ��������� ��������� ������ ��� ������ ���
SX_LIB_API void SAIG_BBGetDimensions(float3* dim);			//!< ���������� �������� ������

//���������/��������� �������
SX_LIB_API void SAIG_BBSetPos(const float3* pos);			//!< ��������� ������� ������
SX_LIB_API void SAIG_BBGetPos(float3* pos);					//!< ���������� ������� ������

SX_LIB_API void SAIG_BBCreateFinish();						//!< ���������� �������� ��������������� ������, ����� �������� �������� �����-���� ��� ������ ����� ����������
SX_LIB_API bool SAIG_BBIsCreatedFinish();					//!< ��������� �� �������� ������
//!@}

/*! \name ���������� AI ������
@{*/

SX_LIB_API void SAIG_GridClear();							//!< ������� ������ �����
SX_LIB_API ID SAIG_GridTraceBeam(const float3* start, const float3* dir);	//!< ����������� ���� � �������� ��� ����������� � ����� ���� ������ �����, ���������� id ����� ���� ���� �����������
SX_LIB_API void SAIG_GridTestValidation();									//!< ���� ���������������� ����� � ���������� ��������� ��������
SX_LIB_API UINT SAIG_GridGetCountSplits();
SX_LIB_API void SAIG_GridSetMarkSplits(bool mark);			//!< ��������� �������
SX_LIB_API bool SAIG_GridGetMarkSplits();					//!< ���������� ��������� ��������� �������

SX_LIB_API void SAIG_GridGenerate();						//!< ������� ���������, �� ����� �������� ����� ���������� ��� �� �����
SX_LIB_API UINT SAIG_GridGetCountQuads();					//!< ���������� ���������� ������ � �����
SX_LIB_API int SAIG_GridFindPath(ID beginq, ID endq);		//!< ����� ����, (beginq,beginq]
SX_LIB_API UINT SAIG_GridGetSizePath();						//!< ������ ���������� ���� � ���������� ���������
SX_LIB_API bool SAIG_GridGetPath(ID * pmem, UINT count);	//!< ������ ���������� ���� � ��� ���������� ������

SX_LIB_API void SAIG_GridSetColorArr(const ID * pmem, DWORD color, UINT count);	//!< ��������� ����� ������� ������
SX_LIB_API void SAIG_GridSetNullColor();					//!< ��������� ����� � ���� ������

//!@}

/*! \name ���������� ���������� �����
@{*/

SX_LIB_API void SAIG_QuadSetState(ID id, AIQUAD_STATE state);	//!< ������������� ��������� ��� �����
SX_LIB_API AIQUAD_STATE SAIG_QuadGetState(ID id);				//!< ���������� ������� ��������� �����

SX_LIB_API ID SAIG_QuadGet(const float3* pos, bool isnear_or_permissible);		//!< �������� id ����� �� �������, isnear_or_permissible - ����� ������� ���� (true), ��� ����� ������� � �������� ���������� ������� ��������� ����� (false)?

SX_LIB_API void SAIG_QuadSetPosY(ID id, float posy);			//!< ��������� ������� �� ��� Y ��� �����
SX_LIB_API float SAIG_QuadGetPosY(ID id);						//!< ���������� ������� �� ��� Y �����

SX_LIB_API ID SAIG_QuadAdd(const float3* pos);					//!< ���������� ����� � �������
SX_LIB_API bool SAIG_QuadDelete(ID id);							//!< �������� ����� �� ��� id

SX_LIB_API void SAIG_QuadSelect(ID id, bool consider_prev);		//!< ���������� ����� � ������ ���������, id - ������������� �����, ���� -1 �� ������� ������, consider_prev - ��������� �� ���������� ����������, ���� ��� �� ������� ������ � ���������� ����, ���� �� �� ���������� ������
SX_LIB_API void SAIG_QuadSelectedAddPosY(float posy);			//!< ���������� � ������� �� ��� Y ��� ���������� ������
SX_LIB_API void SAIG_QuadSelectedDelete();						//!< �������� ���������� ������

SX_LIB_API bool SAIG_QuadIsFree(ID id, int radius);				//!< �������� �� ���� id � ������� radius (radius - ���������� ������ ������ ���������� � id, 1 - ������ ������ ���������, 2 - ������ ��� �������� � �.�.)
SX_LIB_API ID SAIG_QuadGetNear(const float3* pos, bool isfree = false, int raius = 1);	//!< ���������� id ���������� ����� (���� isfree == true �� ���� ������ ���������) � �������� ����������� radius

#define SAIG_QuadSetColor(id, color) SAIG_GridSetColorArr(&id, color, 1)

//!@}

/*! \name Graph points
 \note Graph points (����������) - ������������� �������� �� AI ����� ����� ������� �������� ������� ���������� �������� ����. ��� �������� �������� �������� ���������� �����, ������ �������� � ������ �����������
 \note ����������� �� ������ ���� �����, ��� ����� ���� ����������� �������, ���� ������������� ������������� (�� ������ ������� ������ �������� �����)
@{*/

SX_LIB_API void SAIG_GraphPointGenerate();					//!< �������������� ��������� ����������� � ������� �������������� ������
SX_LIB_API UINT SAIG_GraphPointGetCount();					//!< ���������� ���������� �����������
SX_LIB_API void SAIG_GraphPointClear();						//!< ������� ������ �����������
SX_LIB_API void SAIG_GraphPointAdd(ID id);					//!< ���������� ���������� (id - ������������� ����� �����)
SX_LIB_API void SAIG_GraphPointDelete(ID id);				//!< �������� ���������� (id - ������������� ����� �����)
SX_LIB_API ID SAIG_GraphPointGetNear(ID beginq, ID endq);	//!< ����� �������� �������� ���������� ����� ��������� � �������� ������� ����������

//!@}

/*! \name ������
@{*/

SX_LIB_API void SAIG_RenderQuads(const ISXFrustum * frustum, const float3 * viewpos, float dist);	//!< ��������� �����
SX_LIB_API void SAIG_RenderGraphPoints(const float3 * viewpos, float dist);							//!< ��������� �����������
SX_LIB_API void SAIG_RenderBB();			//!< ��������� �������������� �������

//!@}

#endif

//!@} sxaigrid