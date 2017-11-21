
#ifndef __reflection
#define __reflection

#include <gdefines.h>

#define SM_D3D_CONVERSIONS
#include <common/SXMath.h>
#include <common/Array.h>
#include <d3d9.h>

#include "sxmtllight.h"
#include "ml_data.h"

extern report_func g_fnReportf;

class Reflection
{
public:
	Reflection();
	~Reflection();

	void OnLostDevice();
	void OnResetDevice();

	SX_ALIGNED_OP_MEM

	void Init(MTLTYPE_REFLECT howref);
	MTLTYPE_REFLECT GetTypeReflect(){ return TypeRef; };

	void PreRenderRefPlane(D3DXPLANE* plane);
	void PostRenderRefPlane();
	IDirect3DTexture9* GetRefPlaneTex();

	void BeginRenderRefCube(float3_t* center);
	void PreRenderRefCube(int cube, float4x4* world);
	void PostRenderRefCube(int cube);
	void EndRenderRefCube(float3_t* viewpos);
	bool UpdateCountUpdate(float3_t* viewpos);
	bool AllowedRender();
	void NullingCountUpdate();
	IDirect3DCubeTexture9* GetRefCubeTex();

	void SetMinMax(float3_t* min, float3_t* max);

	void SetIDArr(ID id, int cube, ID idarr);
	int GetCountIDArrs();
	ID GetIDArr(ID id, int cube);

	bool IsComNow;	//обрабатывать ли сейчас, на случай еси видно или нет
	float3 PositionReflect;	//позиция откуда идут отражения, обновляется каждый раз
	float3 Position;
	float3 PosMin, PosMax;
	float4x4 MatrixView;
	ISXFrustum* ReflectFrustum[6];
	Array<ID*> IDArr;

	long CountUpdate;

	//protected:
	MTLTYPE_REFLECT TypeRef;
	D3DXPLANE Plane;
	float ZNear;
	float4x4 OldMatProj,OldMatView,OldMatViewProj;
	IDirect3DSurface9* BackBuffer;

	IDirect3DSurface9* SurfaceZBuffer;
	IDirect3DSurface9* LastSurfaceZBuffer;

	IDirect3DTexture9* TextureReflect;
	IDirect3DSurface9* SurfaceReflect;

	IDirect3DSurface9* CubeReflectSurface[6];
	IDirect3DCubeTexture9* TextureCubeReflect;
};

#endif