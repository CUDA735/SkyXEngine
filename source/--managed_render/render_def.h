
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

/*!
\file
������������ ���� render_def - �������/��������� �������
*/

#ifndef __RENDER_DEF_H
#define __RENDER_DEF_H

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

//!@} managed_render_render_def

#endif