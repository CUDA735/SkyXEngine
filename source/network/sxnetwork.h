
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

/*!
\file
������������ ���� sxnetwork, ���������� �������� ��������������
*/

#ifndef __SXNETWORK_H
#define __SXNETWORK_H

#define FORCE_NO_SMATH_D3D

#include <gdefines.h>

#undef SX_LIB_API
#define SX_LIB_API extern "C" __declspec (dllimport)

#if defined(_DEBUG)
#pragma comment(lib, "sxcore_d.lib")
#else
#pragma comment(lib, "sxcore.lib")
#endif

#include <core/sxcore.h>

#ifdef SX_DLL
#undef SX_LIB_API
#define SX_LIB_API extern "C" __declspec (dllexport)
#endif

#include "protocol.h"

//#############################################################################

/*! \defgroup sxnetwork sxnetwork - ���������� �������� ��������������
@{*/

#define SXNET_MAX_CLIENTS 256

//! ��������� ������� ������ ���������
SX_LIB_API void SNetwork_Dbg_Set(report_func fnFunc);

//! ������������� ����������
SX_LIB_API void SNetwork_0Create();

//! ����������� ����
SX_LIB_API void SNetwork_AKill();

SX_LIB_API INETbuff *SNetwork_CreateBuffer();
SX_LIB_API void SNetwork_FreeBuffer(INETbuff *pBuf);

//#############################################################################

//! ���������� ����
SX_LIB_API void SNetwork_Update();

//! 
SX_LIB_API void SNetwork_InitServer(unsigned short usPort = 7527, const char *szIp = NULL);
SX_LIB_API void SNetwork_FinishServer();
//! 
SX_LIB_API void SNetwork_Connect(const char *szIp, unsigned short usPort = 7527);
SX_LIB_API void SNetwork_Disconnect();
SX_LIB_API bool SNetwork_IsConnected();

SX_LIB_API void SNetwork_OnClientConnected(PFNCLIENTHANDLER fnHandler);
SX_LIB_API void SNetwork_OnClientDisconnected(PFNCLIENTHANDLER fnHandler);

//#############################################################################

SX_LIB_API void SNetwork_BroadcastMessage(byte *pData, int iLength, bool isReliable = false);
SX_LIB_API void SNetwork_BroadcastMessageBuf(INETbuff *pNetBuff, bool isReliable = false);

//!@} sxnetwork

#endif
