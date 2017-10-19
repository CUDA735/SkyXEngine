
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

/*!
\file
������������ ���� render_def - ������� �������, ��� �������� ������������ ���� ��� ������ �����������
*/

#ifndef __REDEFINED_FUNC_H
#define __REDEFINED_FUNC_H

#include <GRegisterIndex.h>

#define SM_D3D_CONVERSIONS
#include <common/SXMath.h>

#include <render/render_def.h>

#include <core/sxcore.h>
#include <mtllight/sxmtllight.h>

#include <aigrid/sxaigrid.h>
#include <physics/sxphysics.h>

/*! \defgroup managed_render_redefined_func redefined_func - ������� �������, ��� �������� ������������ ���� ��� ������ �����������
\ingroup managed_render
@{*/

//! ������� ���������, � ������ ������ �� �����������
void RFuncDIP(UINT type_primitive, long base_vertexIndex, UINT min_vertex_index, UINT num_vertices, UINT start_index, UINT prim_count);

//! ������� ��������� ��������� �� id, world - ������� �������
void RFuncMtlSet(ID id, float4x4* world);

//! ������� �������� ���������
ID RFuncMtlLoad(const char* name, int mtl_type);

//! ������� ������ ��� ����� �� �����
bool RFuncAIQuadPhyNavigate(float3_t * pos);

//! ������� ������������ ������� � �����
bool RFuncParticlesPhyCollision(const float3 * lastpos, const float3* nextpos, float3* coll_pos, float3* coll_nrm);

//!@} managed_render_redefined_func

#endif