
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

/*!
\file
������������ ���� sxgame - ���������� ������� ��������
*/

/*! \defgroup sxgame sxgame - ���������� ������� ��������
@{
*/


#ifndef _SXGAME_H_
#define _SXGAME_H_

#include <gdefines.h>

#include <gcore/sxgcore.h>


/*! �������������� ����������
*/
SX_LIB_API void SXGame_0Create();

/*! ���������������� ����������
*/
SX_LIB_API void SXGame_0Kill();

/*! ������������� ������� ���������
*/
SX_LIB_API void SXGame_Dbg_Set(report_func rf);

/*! ������������� ���������� ������� ����������
*/
SX_LIB_API void SXGame_UpdateSetThreadNum(int num);

/*! ��������� ����������
@param[in] thread ����� ������, ������������ ����������
*/
SX_LIB_API void SXGame_Update(int thread = 0);

/*! ��������� �������������. ��� �������������� ����������
*/
SX_LIB_API void SXGame_Sync();

/*! ��������� ������ entity �� �����
*/
SX_LIB_API void SXGame_LoadEnts(const char * file);

/*! ��������� ������� � ����
*/
SX_LIB_API void SXGame_SaveEnts(const char * file);

/*! �������� ������ � ���
*/
SX_LIB_API void SXGame_PlayerSpawn();

SX_LIB_API void SXGame_EditorRender();

SX_LIB_API ISXCamera * SXGame_GetActiveCamera();

#endif

/*! @} */

