
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#ifndef __SXLEVEL_H
#define __SXLEVEL_H

#include <gdefines.h>

#undef SX_LIB_API
#define SX_LIB_API extern "C" __declspec (dllimport)

#if defined(_DEBUG)
#pragma comment(lib, "sxgcore_d.lib")
#else
#pragma comment(lib, "sxgcore.lib")
#endif
#include <gcore/sxgcore.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxscore_d.lib")
#else
#pragma comment(lib, "sxscore.lib")
#endif
#include <score/sxscore.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxgeom_d.lib")
#else
#pragma comment(lib, "sxgeom.lib")
#endif
#include <geom/sxgeom.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxaigrid_d.lib")
#else
#pragma comment(lib, "sxaigrid.lib")
#endif
#include <aigrid/sxaigrid.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxparticles_d.lib")
#else
#pragma comment(lib, "sxparticles.lib")
#endif
#include <particles/sxparticles.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxpp_d.lib")
#else
#pragma comment(lib, "sxpp.lib")
#endif
#include <pp/sxpp.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxphysics_d.lib")
#else
#pragma comment(lib, "sxphysics.lib")
#endif
#include <physics/sxphysics.h>

#if defined(_DEBUG)
#pragma comment(lib, "sxgame_d.lib")
#else
#pragma comment(lib, "sxgame.lib")
#endif
#include <game/sxgame.h>


#ifdef SX_DLL
#undef SX_LIB_API
#define SX_LIB_API extern "C" __declspec (dllexport)
#endif

//#############################################################################

//! ������ ����������
SX_LIB_API long SLevel_0GetVersion();

//! ��������� ������� ������ ���������
SX_LIB_API void SLevel_Dbg_Set(report_func rf);

//! ������������� ����������
SX_LIB_API void SLevel_0Create(
	const char *szName,			//!< ������������� ��� ����������
	bool isUnic = true			//!< ������ �� ���������� ���� ���������� �� ������ �����
	);

//! ����������� ����
SX_LIB_API void SLevel_AKill();

//#############################################################################

//! ������� ������
SX_LIB_API void SLevel_Clear();					

//! �������� ������
SX_LIB_API void SLevel_Load(const char *szName, bool isGame);	

//! ���������� ������
SX_LIB_API void SLevel_Save(const char *szName);

//! ���������� � ���������� ��� ������
SX_LIB_API const char* SLevel_GetName(char *szName=0);


//! �������� ����� � ����� � ��������
SX_LIB_API void SLevel_LoadParticles();			

//! ���������� ����� � ����� � ��������
SX_LIB_API void SLevel_SaveParticles();			

//#############################################################################

/*! defgroup sxgame_ambient_snd ������� ����� ���������
\ingroup sxgame
\note ����� ����������� ����������
\note ���� �� ����� ������������ ���������� �� �������
@{
*/

//! �������� ����
SX_LIB_API void SLevel_AmbientSndAdd(const char* path);

//! ���������� ����� ���������� ����������� ������
SX_LIB_API UINT SLevel_AmbientSndGetCount();

//! � path ���������� ���� �� ����� �� ��� id
SX_LIB_API void SLevel_AmbientSndGet(ID id, char* path);

//! ������� ������ ������
SX_LIB_API void SLevel_AmbientSndClear();

//! ������ ������������ ������
SX_LIB_API void SLevel_AmbientSndPlay();

//! ���������� ������������
SX_LIB_API void SLevel_AmbientSndUpdate();

//! ����� ������������
SX_LIB_API void SLevel_AmbientSndPause();

//! ���������� "������������� �� �����"
SX_LIB_API bool SLevel_AmbientSndGetPlaying();

//!@} sxgame_ambient_snd

//#############################################################################

/*! defgroup sxgame_weather ������� ����� ���������
\ingroup sxgame
\note ����� ������ ���������� �� ��������� �������� �������
\note ��� ����� ������ ��� ��������� ���������� �������� ������������ ������ �� ������� ������ � ������� �� ��������� �������� �������, ������� #SXLevel_WeatherUpdate ���������� �������� � �������� ����� (� �������) ��� ������ �����

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

//! �������� ������� ������
SX_LIB_API void SLevel_WeatherLoad(const char* path);

//! ���������� ������
SX_LIB_API void SLevel_WeatherUpdate();

//! ���������� ������� ��������� �����
SX_LIB_API float SLevel_WeatherGetCurrRainDensity();

//! ������ ��������������� ������ ������
SX_LIB_API void SLevel_WeatherSndPlay();

//! ������������� ��������������� ������ ������
SX_LIB_API void SLevel_WeatherSndPause();

//! ���������� "��������������� �� ����� ������"
SX_LIB_API bool SLevel_WeatherSndIsPlaying();

//!@} sxgame_weather

#endif