
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
SX_LIB_API void SXGame_AKill();

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

//#############################################################################

/*! defgroup sxgame_ambient_snd ������� ����� ���������
 \ingroup sxgame
 \note ����� ����������� ����������
 \note ���� �� ����� ������������ ���������� �� �������
 @{
*/

//! �������� ����
SX_LIB_API void SGame_AmbientSndAdd(const char* path);

//! ���������� ����� ���������� ����������� ������
SX_LIB_API UINT SGame_AmbientSndGetCount();

//! � path ���������� ���� �� ����� �� ��� id
SX_LIB_API void SGame_AmbientSndGet(ID id, char* path);

//! ������� ������ ������
SX_LIB_API void SGame_AmbientSndClear();

//! ������ ������������ ������
SX_LIB_API void SGame_AmbientSndPlay();

//! ���������� ������������
SX_LIB_API void SGame_AmbientSndUpdate();

//! ����� ������������
SX_LIB_API void SGame_AmbientSndPause();

//! ���������� "������������� �� �����"
SX_LIB_API bool SGame_AmbientSndIsPlaying();

//!@} sxgame_ambient_snd

//#############################################################################

/*! defgroup sxgame_weather ������� ����� ���������
 \ingroup sxgame
 \note ����� ������ ���������� �� ��������� �������� �������
 \note ��� ����� ������ ��� ��������� ���������� �������� ������������ ������ �� ������� ������ � ������� �� ��������� �������� �������, ������� #SGame_WeatherUpdate ���������� �������� � �������� ����� (� �������) ��� ������ �����

����-������ ������� ��:
 - �������� ������ (sections) � ������� ������ ���������� ����� ������ �� �������, � ������� ��� ����� 01:11:12 ��� ������ ��� ���� �������� ��� ������ � ������� ��� 1 ���� ���� 11 ����� � 12 ������
 - ������ � ����������� ������ (��� ������� ���������� �������)
 - ������ � ����������� ��������� ������, ���� ������� ������� \n

������ ������ ������� ��:
 - sky_texture - ��� �������� ��� ���������
 - sky_rotation - ���� �������� ��������� (� ��������)
 - sky_color - ���� ���� float4 [0-1] ��� ������ ��� ���������� ��� ��� ����, � ��������� ���������� �� ������� ����� �������� ����
 - clouds_texture - �������� �������
 - clouds_color - ���� ������� float4 [0-1] ��� ������ ��� ���������� ��� ��� ����, � ��������� ���������� �� ������� ����� �������� ����
 - clouds_rotate - ������� ������� (� ��������)
 - clouds_transparency - ������������ ������� [0-1]
 - clouds_speed - �������� �������� �������
 - sun_texture - �������� ������, ���� ������� 0 �� ������ ����� ���������
 - sun_color - ���� ������ � ��������� �� ������ float3 [0-1]
 - sun_pos - ������� ������ � �������� �� ��� X � Z
 - far - ��������� ���������
 - rain_density ��������� ����� [0-1]
 - rain_color - ���� ����� float4 [0-1] ��� ������ ��� ���������� ��� ��� ����, � ��������� ���������� �� ������� ����� �������� ����
 - thunderbolt - ����� �� ������
 - thunder_period - ������������ ������ ������ ������
 - fog_color - ���� ������ float3 [0-1]
 - fog_density - ��������� ������
 - env_ambient - ��� ������ � ���������� ������� ��� ������ ������ \n

��� ����� � ������ ������ �����������, �� ����������� env_ambient \n
��� ���������� �������� ����������� \n

������ � ���������� ������� ������� ��:
 - period - ���������� (� �����) ����� ���������������� UINT2 (�� � ��), ���������� ��������
 - volume - ��������� (� ���������) ��������������� UINT2 (�� � ��), ���������� ��������
 - sounds - ������ ������ ����� �������

@{
*/

#define WEATHER_RAIN_VOL_SND_UPDATE	1000	/*!< ���������� ����� ������������ ��������� ����� ����� (�����) */
#define WEATHER_RAIN_VOL_SND_DIST	20.f	/*!< ��������� �� �����������, � ������� ������� ����� ������ ������� ����� */
#define WEATHER_RAIN_MIN_Y_OBSERVER	5.f		/*!< �� ������� ���� ����� ����������� ������� ����� ����� ������������ ����������� */
#define WEATHER_RAIN_RECREATE_COUNT	500		/*!< ���������� ������������� ������ ��� ������ ��������� ����� (������ ���� �������������� ��� �������� ��� ��������� ������� ��������� ����������� ����� ����� ���� ������������) */
#define WEATHER_THUNDERBOLT_LIGHT_TIME	500	/*!< ����� �������� ����� ��� ������ (�����)*/
#define WEATHER_THUNDERBOLT_WIDTH	100.f	/*!< ������ ���������� ������������ ��� ������ */
#define WEATHER_THUNDERBOLT_LENGTH	10.f	/*!< ����� ���������� ������������ ��� ������ */
#define WEATHER_THUNDERBOLT_HEIGHT	100.f	/*!< ������ ���������� ������������ ��� ������ */

//! �������� ������� ������
SX_LIB_API void SGame_WeatherLoad(const char* path);

//! ���������� ������
SX_LIB_API void SGame_WeatherUpdate();

//! ���������� ������� ��������� �����
SX_LIB_API float SGame_WeatherGetCurrRainDensity();

//! ������ ��������������� ������ ������
SX_LIB_API void SGame_WeatherSndPlay();

//! ������������� ��������������� ������ ������
SX_LIB_API void SGame_WeatherSndPause();

//! ���������� "��������������� �� ����� ������"
SX_LIB_API bool SGame_WeatherSndIsPlaying();

//!@} sxgame_weather

#endif

/*! @} sxgame*/

