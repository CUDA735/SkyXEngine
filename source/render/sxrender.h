
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
#pragma comment(lib, "sxinput_d.lib")
#else
#pragma comment(lib, "sxinput.lib")
#endif

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

#if defined(_DEBUG)
#pragma comment(lib, "sxdecals_d.lib")
#else
#pragma comment(lib, "sxdecals.lib")
#endif

#undef SX_LIB_API
#define SX_LIB_API extern "C" __declspec (dllimport)
#include <gcore/sxgcore.h>
#include <geom/sxgeom.h>
#include <mtllight/sxmtllight.h>
#include <anim/sxanim.h>
#include <pp/sxpp.h>
#include <particles/sxparticles.h>


#ifdef SX_DLL
#undef SX_LIB_API
#define SX_LIB_API extern "C" __declspec (dllexport)
#endif

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

//##########################################################################

/*! \defgroup managed_render_render_def render_def - �������/��������� �������
\ingroup managed_render
@{*/

/*! \name ��������� �������
@{*/

#define RENDER_STATE_MATERIAL	0	/*!< ��������� ���������� */
#define RENDER_STATE_SHADOW		1	/*!< ��������� ����� */
#define RENDER_STATE_FREE		2	/*!< ������� ��������� (�� ������������) */

//!@}

/*! \name �������������� ��� ����������� ���� ��������� ���������
@{*/

#define RENDER_IDARRCOM_GEOM	0	/*!< ��������� */
#define RENDER_IDARRCOM_GREEN	1	/*!< �������������� */
#define RENDER_IDARRCOM_ANIM	2	/*!< �������� */

//!@}

#define RENDER_PARTICLES_ALPHATEST_VALUE 16	/*!< ����������� �������� ��� ����� ����� */

/*! \name �������������� ��� ����������� ���� ��������� ���������
@{*/

#define RENDER_LAYER_NULL			0	/*!< ������� (������ ����, ����� ����� � ������� ��������, ������ � �.�.) */
#define RENDER_LAYER_UNTRANSPARENT	1	/*!< ������������ ���� */
#define RENDER_LAYER_TRANSPARENT	2	/*!< ������ ���������� ����, ��������� ���� ����� ���� ����������� */

//!@}

/*! ������ �� ������ */
#define RENDER_RESIZE_NONE		0

/*! ������ */
#define RENDER_RESIZE_RESIZE	1

/*! ������� ����� ��������� � ����� */
#define RENDER_RESIZE_CHANGE	2

//! ���� ������� ��������� ������ ����� �� ���������
#define RENDER_DEFAUL_BACKGROUND_COLOR D3DCOLOR_ARGB(0,128,128,128)

#define G_DATA_LIGHT_FAR 100000 /*!< ������� ��������� ��������� ����������� ��� ����� */

//**************************************************************************

/*! \name ������� ������ ��� ������� ��������/����������
@{
*/

/*! ��������*/
#define FILE_FILTER_TEXTURE	"All files\0*.*\0png file(.png)\0*.png\0dds file(.dds)\0*.dds\0\0"

/*! ������ ���� ������*/
#define FILE_FILTER_LEVEL	"SkyX level file(.lvl)\0*.lvl\0All files\0*.*\0\0"

/*! dse ������*/
#define FILE_FILTER_MODEL	"dse file(.dse)\0*.dse\0All files\0*.*\0\0"

/*! ��������� ������*/
#define FILE_FILTER_VS		"vertex shader file(.vs)\0*.vs\0All files\0*.*\0\0"

/*! ���������� ������*/
#define FILE_FILTER_PS		"pixel shader file(.ps)\0*.ps\0All files\0*.*\0\0"

//!@}

/*! \name ���� ��������� ���������� ��������
@{
*/

#define EDITORS_LEVEL_GROUPTYPE_GEOM	1	/*!< ����������� ��������� */
#define EDITORS_LEVEL_GROUPTYPE_GREEN	2	/*!< �������������� */
#define EDITORS_LEVEL_GROUPTYPE_GAME	3	/*!< ������� ������� */
#define EDITORS_LEVEL_GROUPTYPE_AIGRID	4	/*!< ai ����� */

//!@}

#define EDITORS_LEVEL_CAPTION "SXLevelEditor"
#define EDITORS_LEVEL_STATUSBAR_LEVEL_POLY "Level poly: "
#define EDITORS_LEVEL_STATUSBAR_GEOM_POLY "Geom poly: "
#define EDITORS_LEVEL_STATUSBAR_GREEN_POLY "Green poly: "
#define EDITORS_LEVEL_STATUSBAR_GAME_COUNT "Count game object: "

//##########################################################################

SX_LIB_API long SRender_0GetVersion();

//! ���������� ������� ��������� ���������
SX_LIB_API void SRender_Dbg_Set(report_func rf);

//! ������������ ����������
SX_LIB_API void SRender_0Create(
	const char *szName,			//!< ������������� ���
	HWND hWnd3D,
	HWND hWndParent3D,
	bool isUnic = true			//!< ������ �� ���������� ���� ���������� �� �����
	);

//! ���������� ����������
SX_LIB_API void SRender_AKill();

//##########################################################################

SX_LIB_API HWND SRender_GetHandleWin3D();
SX_LIB_API HWND SRender_GetParentHandleWin3D();

SX_LIB_API void SRender_SetHandleWin3D(HWND hWnd);
SX_LIB_API void SRender_SetParentHandleWin3D(HWND hWnd);

SX_LIB_API void SRender_SetCamera(ISXCamera *pCamera);
SX_LIB_API ISXCamera* SRender_GetCamera();

SX_LIB_API void SRender_EditorCameraSetMove(bool canMove);
SX_LIB_API bool SRender_EditorCameraGetMove();

//**************************************************************************

//SX_LIB_API void SRender_SimModelSetPosition(const float3 *pPos);
SX_LIB_API void SRender_SimModelAdd(const char *szName);
SX_LIB_API ID SRender_SimModelGetIDMtl();

SX_LIB_API MTLTYPE_MODEL SRender_SimModelGetType();
SX_LIB_API void SRender_SimModelSetType(MTLTYPE_MODEL type);

SX_LIB_API void SRender_SimModelSetNumCurrModel(int iCurrNumModel);
SX_LIB_API int SRender_SimModelGetNumCurrModel();

SX_LIB_API void SRender_SimModelSetRotationY(float Rotation);
SX_LIB_API float SRender_SimModelGetRotationY();

//**************************************************************************

SX_LIB_API void SRender_EditorSetRenderGrid(bool canRender);
SX_LIB_API bool SRender_EditorGetRenderGrid();

SX_LIB_API void SRender_EditorSetRenderAxesStatic(bool canRender);
SX_LIB_API bool SRender_EditorGetRenderAxesStatic();

//**************************************************************************

SX_LIB_API ID SRender_EditorGetSelectTex();

//**************************************************************************

//##########################################################################

//! ��������� ����� ���������� � ����������
SX_LIB_API void SRender_UpdateInputKeyBoard(DWORD timeDelta);

//! ��������� �������� ���� ������ � �����
SX_LIB_API void SRender_UpdateInputMouseRotate(DWORD timeDelta);

//! ��������� �������� ���� ����� ����
SX_LIB_API void SRender_UpdateInputMouseUpDown(DWORD timeDelta);

//! ������������� ������� ����
SX_LIB_API void SRender_CentererCursor();

//! ���������� ��������� ����� "��������"
SX_LIB_API void SRender_UpdateEditorial(DWORD timeDelta);

//##########################################################################

//! ��������� ������ � �������������� ����������
SX_LIB_API void SRender_ComDeviceLost();

//! ��������� ��������� ��� ���������� �����
SX_LIB_API void SRender_ComVisibleForLight();

//! ��������� ��������� ��� ������
SX_LIB_API void SRender_ComVisibleForCamera();

//! ��������� ��������� ��� ���������
SX_LIB_API void SRender_ComVisibleReflection();


//! ��������� � ��������� �������� ������, ��������� ���������� ���������
SX_LIB_API void SRender_UpdateView();

//! ����� ���������� ��������� ���������� � ���� �������
SX_LIB_API void SRender_OutputDebugInfo(DWORD timeDelta, bool needGameTime);


//! ���������� G ������, �� ���� ������ ���� �����
SX_LIB_API void SRender_BuildMRT(DWORD timeDelta, bool isRenderSimulation);

//! ���������� ���������� � ����� (������ ����� ���� ��� ����������� ���� � ������ ������ ���������� �����)
SX_LIB_API void SRender_UpdateShadow(DWORD timeDelta);

//! ���������/���������� ���������
SX_LIB_API void SRender_UpdateReflection(DWORD timeDelta, bool isRenderSimulation);

SX_LIB_API void SRender_UpdateReflectionScene(DWORD timeDelta);

SX_LIB_API void SRender_UpdateReflectionSimModel(DWORD timeDelta);

//! ��������� ��������� � �������
SX_LIB_API void SRender_RenderSky(DWORD timeDelta);

//! ��������� ���������
SX_LIB_API void SRender_ComLighting(DWORD timeDelta);

//! ����������� ����� ������������
SX_LIB_API void SRender_UnionLayers();

//! ���������� ����������� � ��
SX_LIB_API void SRender_ApplyToneMapping();

//! ������� �����������
SX_LIB_API void SRender_ComToneMapping(DWORD timeDelta);


//! ��������� ��������� (��������)
SX_LIB_API void SRender_RenderParticles(DWORD timeDelta);

//! ��������� ������������
SX_LIB_API void SRender_RenderPostProcess(DWORD timeDelta);

SX_LIB_API void SRender_ShaderRegisterData();

SX_LIB_API void SRender_RenderEditorMain();

//##########################################################################

//! ��������� ��������
SX_LIB_API void SRender_SaveScreenShot();

//! ��������� ������� �������� (�-����� � ��� � ���� �����������)
SX_LIB_API void SRender_SaveWorkTex();

//! �������� ����� ������� (�������/�������������)
SX_LIB_API void SRender_ChangeModeWindow();

#endif