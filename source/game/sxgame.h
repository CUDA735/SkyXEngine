
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

#ifndef SXGAME_EXPORT
#define SXGAME_EXPORT _declspec(dllimport)
#endif

#include <gdefines.h>

#include <gcore/sxgcore.h>

#include "SXbaseEntity.h"


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

SX_LIB_API void SXGame_EditorRender(ID id, ID id_sel_tex);

SX_LIB_API ISXCamera * SXGame_GetActiveCamera();

/*! �������� ���������� ������������������ ������� entity
*/
SX_LIB_API int SXGame_EntGetClassListCount();

/*! �������� ������ ������������������ ������� entity.
	������ ��� ������ const char * ������ ���� �������� �������
*/
SX_LIB_API void SXGame_EntGetClassList(const char ** pszClassList, int count);

/*! ������� entity ��������� ������
*/
SX_LIB_API SXbaseEntity * SXGame_CreateEntity(const char * classname);

/*! ���������� entity
*/
SX_LIB_API void SXGame_RemoveEntity(SXbaseEntity * pEnt);

/*! �������� ������� ������� ��� ��������� ������
*/
SX_LIB_API proptable_t * SXGame_EntGetProptable(const char * classname);

/*! �������� �������� �������� �� ��������� ��� ��������� ������
*/
SX_LIB_API const char * SXGame_EntGetDefault(const char * classname, const char * key);

/*! ���������� ���� entity
*/
SX_LIB_API int SXGame_EntGetCount();

/*! ���������� ���� entity
*/
SX_LIB_API SXbaseEntity * SXGame_EntGet(ID id);

#endif

/*! @} */

