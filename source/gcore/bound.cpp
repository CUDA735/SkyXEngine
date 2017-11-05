
#include "Bound.h"

void CreateCone(float fTopRadius, float fBottomRadius, float fHeight, ID3DXMesh ** ppMesh, IDirect3DDevice9 * pDevice,UINT iSideCount)
{
	UINT iVC = iSideCount * 2;
	UINT iIC = (iSideCount - 2) * 6 + iSideCount * 6;
	float3_t * pVertices = new float3_t[iVC];
	UINT * pIndices = new UINT[iIC];

	//top
	UINT iCurV = 0;
	for(UINT i = 0; i < iSideCount; i++)
	{
		float A = (float)i / (float)iSideCount * SM_2PI;
		pVertices[iCurV] = float3_t(fTopRadius * cosf(A),0.0f, -fTopRadius * sinf(A));
		iCurV++;
	}

	//bottom
	for(UINT i = 0; i < iSideCount; i++)
	{
		float A = (float)i / (float)iSideCount * SM_2PI;
		pVertices[iCurV] = float3_t(fBottomRadius * cosf(A), -fHeight, fBottomRadius * sinf(A));
		iCurV++;
	}

	//top
	UINT iCurI = 0;
	for(UINT i = 0; i < iSideCount - 2; i++)
	{
		pIndices[iCurI] = 0;
		iCurI++;
		pIndices[iCurI] = 1 + i;
		iCurI++;
		pIndices[iCurI] = 2 + i;
		iCurI++;
	}

	//bottom
	for(UINT i = 0; i < iSideCount - 2; i++)
	{
		pIndices[iCurI] = iSideCount;
		iCurI++;
		pIndices[iCurI] = iSideCount + 1 + i;
		iCurI++;
		pIndices[iCurI] = iSideCount + 2 + i;
		iCurI++;
	}

	//side
	for(UINT i = 0; i < iSideCount; i++)
	{
		pIndices[iCurI] = (i + 1) % iSideCount;
		iCurI++;
		pIndices[iCurI] = i;
		iCurI++;
		pIndices[iCurI] = (iSideCount - i) % iSideCount + iSideCount;
		iCurI++;

		pIndices[iCurI] = (iSideCount - i) % iSideCount + iSideCount;
		iCurI++;
		pIndices[iCurI] = (2 * iSideCount - i - 1) % iSideCount + iSideCount;
		iCurI++;
		pIndices[iCurI] = (i + 1) % iSideCount;
		iCurI++;
	}

	D3DXCreateMeshFVF(iIC / 3, iVC, D3DXMESH_32BIT | D3DXMESH_MANAGED, D3DFVF_XYZ, pDevice, ppMesh);
	VOID * pData;
	(*ppMesh)->LockVertexBuffer(D3DLOCK_DISCARD, &pData);
	memcpy(pData, pVertices, sizeof(float3_t) * iVC);
	(*ppMesh)->UnlockVertexBuffer();

	(*ppMesh)->LockIndexBuffer(D3DLOCK_DISCARD, &pData);
	memcpy(pData, pIndices, sizeof(UINT) * iIC);
	(*ppMesh)->UnlockIndexBuffer();
	
	mem_delete(pIndices);
	mem_delete(pVertices);
}

void ComputeBoundingBox(IDirect3DVertexBuffer9* vertex_buffer,ISXBound** bound,DWORD count_vert,DWORD bytepervert)
{
	float3_t *V = 0;
	HRESULT hr = 0;
	float3_t Max;
	float3_t Min;
	
		if(SUCCEEDED(vertex_buffer->Lock(0,0, (void **)&V,0)))
		{
			float3_t tmppos = *(float3_t*)((char*)(V) + bytepervert * 0);
			Max = tmppos;
			Min = tmppos;

				for(DWORD i=0;i<count_vert;i++)
				{
					float3_t pos = *(float3*)((char*)(V) + bytepervert * i);

						if(pos.x > Max.x)
							Max.x = pos.x;

						if(pos.y > Max.y)
							Max.y = pos.y;

						if(pos.z > Max.z)
							Max.z = pos.z;


						if(pos.x < Min.x)
							Min.x = pos.x;

						if(pos.y < Min.y)
							Min.y = pos.y;

						if(pos.z < Min.z)
							Min.z = pos.z;
				}
			vertex_buffer->Unlock();
		}

	(*bound)->SetMinMax(&float3(Min),&float3(Max));
}

void ComputeBoundingBox2(IDirect3DVertexBuffer9* vertex_buffer,ISXBound* bound,DWORD count_vert,DWORD bytepervert)
{
	float3_t *V = 0;
	HRESULT hr = 0;
	float3_t Max;
	float3_t Min;
	
		if(SUCCEEDED(vertex_buffer->Lock(0,0, (void **)&V,0)))
		{
			float3_t tmppos = *(float3*)((char*)(V) + bytepervert * 0);
			Max = tmppos;
			Min = tmppos;

				for(DWORD i=0;i<count_vert;i++)
				{
					float3_t pos = *(float3*)((char*)(V) + bytepervert * i);

						if(pos.x > Max.x)
							Max.x = pos.x;

						if(pos.y > Max.y)
							Max.y = pos.y;

						if(pos.z > Max.z)
							Max.z = pos.z;


						if(pos.x < Min.x)
							Min.x = pos.x;

						if(pos.y < Min.y)
							Min.y = pos.y;

						if(pos.z < Min.z)
							Min.z = pos.z;
				}
			vertex_buffer->Unlock();
		}

	Min.x /= 100.f;
	Min.y /= 100.f;
	Min.z /= 100.f;

	Max.x /= 100.f;
	Max.y /= 100.f;
	Max.z /= 100.f;

	bound->SetMinMax(&float3(Min),&float3(Max));
}


//////////////////////////////////

bool InPosition2D(float3* min,float3* max,float3* pos)
{
		if((max->x >= pos->x && min->x <= pos->x) && (max->z >= pos->z && min->z <= pos->z))
			return true;
		else if(
				(long(max->x * 1000) >= long(pos->x * 1000) && long(min->x * 1000) <= long(pos->x * 1000))
				&& 
				(long(max->z * 1000) >= long(pos->z * 1000) && long(min->z * 1000) <= long(pos->z * 1000))
				)
			return true;
		else 
			return false;
}

bool InPositionAbs2D(float3* min,float3* max,float3* pos)
{
		if((max->x > pos->x && min->x < pos->x) && (max->z > pos->z && min->z < pos->z))
			return true;
		else
			return false;
}


int CountPositionPoints2D(float3* min,float3* max,float3* p1,float3* p2,float3* p3)
{
	int Count = 0;

		if(InPosition2D(min,max,p1))
			Count++;
		if(InPosition2D(min,max,p2))
			Count++;
		if(InPosition2D(min,max,p3))
			Count++;

	return Count;
}

int CountPositionPointsAbs2D(float3* min,float3* max,float3* p1,float3* p2,float3* p3)
{
	int Count = 0;

		if(InPositionAbs2D(min,max,p1))
			Count++;
		if(InPositionAbs2D(min,max,p2))
			Count++;
		if(InPositionAbs2D(min,max,p3))
			Count++;

	return Count;
}


bool InPositionPoints2D(float3* min,float3* max,float3* p1,float3* p2,float3* p3)
{
		if(CountPositionPointsAbs2D(min,max,p1,p2,p3) >= 1)	
			return true;
		else if(CountPositionPoints2D(min,max,p1,p2,p3) >= 2)	
			return true;
		else
			return false;
}

///////////////////////////////////

bool InPosition3D(float3* min,float3* max,float3* pos)
{
		if((max->x >= pos->x && min->x <= pos->x) && (max->y >= pos->y && min->y <= pos->y) && (max->z >= pos->z && min->z <= pos->z))
			return true;
		else if(
				(long(max->x * 1000) >= long(pos->x * 1000) && long(min->x * 1000) <= long(pos->x * 1000))
				&& 
				(long(max->y * 1000) >= long(pos->y * 1000) && long(min->y * 1000) <= long(pos->y * 1000))
				&&
				(long(max->z * 1000) >= long(pos->z * 1000) && long(min->z * 1000) <= long(pos->z * 1000))
				)
			return true;
		else 
			return false;
}

bool InPositionAbs3D(float3* min,float3* max,float3* pos)
{
		if((max->x > pos->x && min->x < pos->x) && (max->y > pos->y && min->y < pos->y) && (max->z > pos->z && min->z < pos->z))
			return true;
		else
			return false;
}


int CountPositionPoints3D(float3* min,float3* max,float3* p1,float3* p2,float3* p3)
{
	int Count = 0;

		if(InPosition3D(min,max,p1))
			Count++;
		if(InPosition3D(min,max,p2))
			Count++;
		if(InPosition3D(min,max,p3))
			Count++;

	return Count;
}

int CountPositionPointsAbs3D(float3* min,float3* max,float3* p1,float3* p2,float3* p3)
{
	int Count = 0;

		if(InPositionAbs3D(min,max,p1))
			Count++;
		if(InPositionAbs3D(min,max,p2))
			Count++;
		if(InPositionAbs3D(min,max,p3))
			Count++;

	return Count;
}


bool InPositionPoints3D(float3* min,float3* max,float3* p1,float3* p2,float3* p3)
{
		if(CountPositionPointsAbs3D(min,max,p1,p2,p3) >= 1)	
			return true;
		else if(CountPositionPoints3D(min,max,p1,p2,p3) >= 2)	
			return true;
		else
			return false;
}

////////////////////

void ComputeBoundingBoxArr8(ISXBound* bound,ISXBound** bound_arr)
{
	float3 tmpMin2,tmpMax2;
	float3 tmpMin,tmpMax;
	bound->GetMinMax(&tmpMin2,&tmpMax2);
	bound->GetMinMax(&tmpMin,&tmpMax);

	float x = (tmpMax.x + tmpMin.x) * 0.5;
	float y = (tmpMax.y + tmpMin.y) * 0.5;
	float z = (tmpMax.z + tmpMin.z) * 0.5;

	float dist_x = (tmpMax.x - tmpMin.x) * 0.25;
	float dist_y = (tmpMax.y - tmpMin.y) * 0.25;
	float dist_z = (tmpMax.z - tmpMin.z) * 0.25;


	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(dist_x,dist_y,dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(dist_x,dist_y,dist_z);

	(bound_arr[0])->SetMinMax(&tmpMin2,&tmpMax2);


	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(-dist_x,dist_y,dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(-dist_x,dist_y,dist_z);

	(bound_arr[1])->SetMinMax(&tmpMin2, &tmpMax2);


	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;
	//bound->GetMinMax(&tmpMin2,&tmpMax2);

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(dist_x,dist_y,-dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(dist_x,dist_y,-dist_z);

	(bound_arr[2])->SetMinMax(&tmpMin2, &tmpMax2);


	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;
	//bound->GetMinMax(&tmpMin2,&tmpMax2);

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(-dist_x,dist_y,-dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(-dist_x,dist_y,-dist_z);

	(bound_arr[3])->SetMinMax(&tmpMin2, &tmpMax2);


	
	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(dist_x,-dist_y,dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(dist_x,-dist_y,dist_z);

	(bound_arr[4])->SetMinMax(&tmpMin2, &tmpMax2);


	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(-dist_x,-dist_y,dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(-dist_x,-dist_y,dist_z);

	(bound_arr[5])->SetMinMax(&tmpMin2, &tmpMax2);


	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;
	//bound->GetMinMax(&tmpMin2,&tmpMax2);

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(dist_x,-dist_y,-dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(dist_x,-dist_y,-dist_z);

	(bound_arr[6])->SetMinMax(&tmpMin2, &tmpMax2);


	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;
	//bound->GetMinMax(&tmpMin2,&tmpMax2);

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(-dist_x,-dist_y,-dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(-dist_x,-dist_y,-dist_z);

	(bound_arr[7])->SetMinMax(&tmpMin2, &tmpMax2);
}

void ComputeBoundingBoxArr4(ISXBound* bound,ISXBound** bound_arr)
{
	float3 tmpMin2,tmpMax2;
	float3 tmpMin,tmpMax;
	bound->GetMinMax(&tmpMin2,&tmpMax2);
	bound->GetMinMax(&tmpMin,&tmpMax);

	float x = (tmpMax.x + tmpMin.x) * 0.5;
	float y = (tmpMax.y + tmpMin.y) * 0.5;
	float z = (tmpMax.z + tmpMin.z) * 0.5;

	float dist_x = (tmpMax.x - tmpMin.x) * 0.25;
	float dist_y = (tmpMax.y - tmpMin.y) * 0.5;
	float dist_z = (tmpMax.z - tmpMin.z) * 0.25;


	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(dist_x,0,dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(dist_x,0,dist_z);

	(bound_arr[0])->SetMinMax(&tmpMin2,&tmpMax2);


	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(-dist_x,0,dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(-dist_x,0,dist_z);

	(bound_arr[1])->SetMinMax(&tmpMin2, &tmpMax2);


	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;
	//bound->GetMinMax(&tmpMin2,&tmpMax2);

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(dist_x,0,-dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(dist_x,0,-dist_z);

	(bound_arr[2])->SetMinMax(&tmpMin2, &tmpMax2);


	tmpMin2.x = -dist_x;
	tmpMin2.y = -dist_y;
	tmpMin2.z = -dist_z;

	tmpMax2.x = dist_x;
	tmpMax2.y = dist_y;
	tmpMax2.z = dist_z;
	//bound->GetMinMax(&tmpMin2,&tmpMax2);

	tmpMin2 += float3(x,y,z);
	tmpMin2 += float3(-dist_x,0,-dist_z);

	tmpMax2 += float3(x,y,z);
	tmpMax2 += float3(-dist_x,0,-dist_z);

	(bound_arr[3])->SetMinMax(&tmpMin2, &tmpMax2);
}

////////////////////


void CreateBoundingBoxMesh(float3* min, float3* max, ID3DXMesh** bbmesh, IDirect3DDevice9* device)
{
	float dist_x = abs(max->x - min->x);
	float dist_y = abs(max->y - min->y);
	float dist_z = abs(max->z - min->z);

	//ID3DXMesh* BoundMesh = 0;
	HRESULT hr = 0;

	hr = D3DXCreateBox(
						device,
						dist_x,
						dist_y,
						dist_z,
						bbmesh,
						0);

	void* Vetx = 0;
	int VertexBytes =  (*bbmesh)->GetNumBytesPerVertex();
	D3DXVECTOR3 dv = D3DXVECTOR3((max->x + min->x)*0.5f,(max->y + min->y)*0.5f,(max->z + min->z)*0.5f);

	(*bbmesh)->LockVertexBuffer(0,&Vetx);
		for(int i=0; i<(*bbmesh)->GetNumVertices(); i++)
		{
			D3DXVECTOR3* v = (D3DXVECTOR3*)((char*)(Vetx) + VertexBytes * i);
			*v += dv;
		}
	(*bbmesh)->UnlockVertexBuffer();
}




float4x4* SXTransObject::CalcWorld()
{
	World = SMMatrixScaling(Scale) * /*Rotation.GetMatrix()*/SMMatrixRotationX(Rotation.x) * SMMatrixRotationY(Rotation.y) * SMMatrixRotationZ(Rotation.z) * SMMatrixTranslation(Position);
	return &World;
}

////

void SXBound::CalcBound(IDirect3DVertexBuffer9* vertex_buffer, DWORD count_vert, DWORD bytepervert)
{
	BYTE *V = 0;
	HRESULT hr = 0;
	
		if (vertex_buffer && SUCCEEDED(vertex_buffer->Lock(0, 0, (void **)&V, 0)))
		{
			float3_t tmppos = *(float3_t*)((char*)(V) + bytepervert * 0);
			Max = tmppos;
			Min = tmppos;

				for(DWORD i=0;i<count_vert;i++)
				{
					float3_t pos = *(float3_t*)((char*)(V) + bytepervert * i);

						if(pos.x > Max.x)
							Max.x = pos.x;

						if(pos.y > Max.y)
							Max.y = pos.y;

						if(pos.z > Max.z)
							Max.z = pos.z;


						if(pos.x < Min.x)
							Min.x = pos.x;

						if(pos.y < Min.y)
							Min.y = pos.y;

						if(pos.z < Min.z)
							Min.z = pos.z;
				}
			vertex_buffer->Unlock();
		}

	Center = (Min + Max) * 0.5f;
	Radius = SMVector3Length(Center-Max);
}

float4x4* SXBound::CalcWorldAndTrans()
{
	CalcWorld();

	Max = SMVector3Transform(Max, World);
	Min = SMVector3Transform(Min, World);

	Center = (Min + Max) * 0.5f;

	Radius = SMVector3Length(Center - Max);
	return &World;
}

void SXBound::GetPosBBScreen(SXPosBBScreen *res, float3* campos, float3* sizemapdepth, float4x4* mat)
{
	float3 max,min;
	max = Max;
	min = Min;

	float2 mins,maxs,minmaxdepth;

	float4 point0 = float4(max.x,max.y,max.z,1.0f);
	float4 point1 = float4(max.x,max.y,min.z,1.0f);
	float4 point2 = float4(max.x,min.y,max.z,1.0f);
	float4 point3 = float4(min.x,max.y,max.z,1.0f);
	float4 point4 = float4(max.x,min.y,min.z,1.0f);
	float4 point5 = float4(min.x,min.y,max.z,1.0f);
	float4 point6 = float4(min.x,max.y,min.z,1.0f);
	float4 point7 = float4(min.x,min.y,min.z,1.0f);

	point0 = SMVector4Transform(point0,*mat);
	TRANSFORM_COORD_SCREEN2(point0,sizemapdepth);

	point1 = SMVector4Transform(point1,*mat);
	TRANSFORM_COORD_SCREEN2(point1,sizemapdepth);

	point2 = SMVector4Transform(point2,*mat);
	TRANSFORM_COORD_SCREEN2(point2,sizemapdepth);

	point3 = SMVector4Transform(point3,*mat);
	TRANSFORM_COORD_SCREEN2(point3,sizemapdepth);

	point4 = SMVector4Transform(point4,*mat);
	TRANSFORM_COORD_SCREEN2(point4,sizemapdepth);

	point5 = SMVector4Transform(point5,*mat);
	TRANSFORM_COORD_SCREEN2(point5,sizemapdepth);

	point6 = SMVector4Transform(point6,*mat);
	TRANSFORM_COORD_SCREEN2(point6,sizemapdepth);

	point7 = SMVector4Transform(point7,*mat);
	TRANSFORM_COORD_SCREEN2(point7,sizemapdepth);

	maxs.x = point0.x;
	maxs.y = point0.y;

	mins.x = point0.x;
	mins.y = point0.y;

	minmaxdepth.x = point0.z;
	minmaxdepth.y = point0.z;

		if(point1.x > maxs.x)
			maxs.x = point1.x;
		if(point2.x > maxs.x)
			maxs.x = point2.x;
		if(point3.x > maxs.x)
			maxs.x = point3.x;
		if(point4.x > maxs.x)
			maxs.x = point4.x;
		if(point5.x > maxs.x)
			maxs.x = point5.x;
		if(point6.x > maxs.x)
			maxs.x = point6.x;
		if(point7.x > maxs.x)
			maxs.x = point7.x;

		if(point1.y > maxs.y)
			maxs.y = point1.y;
		if(point2.y > maxs.y)
			maxs.y = point2.y;
		if(point3.y > maxs.y)
			maxs.y = point3.y;
		if(point4.y > maxs.y)
			maxs.y = point4.y;
		if(point5.y > maxs.y)
			maxs.y = point5.y;
		if(point6.y > maxs.y)
			maxs.y = point6.y;
		if(point7.y > maxs.y)
			maxs.y = point7.y;




		if(point1.x < mins.x)
			mins.x = point1.x;
		if(point2.x < mins.x)
			mins.x = point2.x;
		if(point3.x < mins.x)
			mins.x = point3.x;
		if(point4.x < mins.x)
			mins.x = point4.x;
		if(point5.x < mins.x)
			mins.x = point5.x;
		if(point6.x < mins.x)
			mins.x = point6.x;
		if(point7.x < mins.x)
			mins.x = point7.x;

		if(point1.y < mins.y)
			mins.y = point1.y;
		if(point2.y < mins.y)
			mins.y = point2.y;
		if(point3.y < mins.y)
			mins.y = point3.y;
		if(point4.y < mins.y)
			mins.y = point4.y;
		if(point5.y < mins.y)
			mins.y = point5.y;
		if(point6.y < mins.y)
			mins.y = point6.y;
		if(point7.y < mins.y)
			mins.y = point7.y;


		if(point1.z > minmaxdepth.y)
			minmaxdepth.y = point1.z;
		if(point2.z > minmaxdepth.y)
			minmaxdepth.y = point2.z;
		if(point3.z > minmaxdepth.y)
			minmaxdepth.y = point3.z;
		if(point4.z > minmaxdepth.y)
			minmaxdepth.y = point4.z;
		if(point5.z > minmaxdepth.y)
			minmaxdepth.y = point5.z;
		if(point6.z > minmaxdepth.y)
			minmaxdepth.y = point6.z;
		if(point7.z > minmaxdepth.y)
			minmaxdepth.y = point7.z;

		if(point1.z < minmaxdepth.x)
			minmaxdepth.x = point1.z;
		if(point2.z < minmaxdepth.x)
			minmaxdepth.x = point2.z;
		if(point3.z < minmaxdepth.x)
			minmaxdepth.x = point3.z;
		if(point4.z < minmaxdepth.x)
			minmaxdepth.x = point4.z;
		if(point5.z < minmaxdepth.x)
			minmaxdepth.x = point5.z;
		if(point6.z < minmaxdepth.x)
			minmaxdepth.x = point6.z;
		if(point7.z < minmaxdepth.x)
			minmaxdepth.x = point7.z;

	mins.x = (mins.x);
	mins.y = (mins.y);

	maxs.x = (maxs.x);
	maxs.y = (maxs.y);

		if(mins.x < 0.f)
			mins.x = 0.f;

		if(mins.y < 0.f)
			mins.y = 0.f;

		if(maxs.x > sizemapdepth->x)
			maxs.x = sizemapdepth->x;

		if(maxs.y > sizemapdepth->y)
			maxs.y = sizemapdepth->y;

	res->x = (mins.x);
	res->y = (mins.y);

	res->width = (maxs.x-mins.x);
	res->height = (maxs.y-mins.y);


	res->mindepth = minmaxdepth.x;
	res->maxdepth = minmaxdepth.y;

		if(res->mindepth < 0.f)
			res->mindepth = 0.f;

	res->IsVisible = true;

		/*if(campos->x > Min.x && campos->y > Min.y && campos->z > Min.z   &&   campos->x < Max.x && campos->y < Max.y && campos->z < Max.z)
			res->IsIn = true;*/
}

void SXBound::SetMinMax(float3* min, float3* max)
{
	Min = *min;
	Max = *max;

	/*float3 vec = (Max - Min) * 0.5f;
	Radius = sqrt(vec.x * vec.x + vec.y * vec.y + vec.x * vec.z);*/

	Center = (Min + Max) * 0.5f;
	Radius = SMVector3Length(Center - Max);
};

void SXBound::GetMinMax(float3* min, float3* max) const
{
	*min = Min; *max = Max;
};

void SXBound::SetSphere(float3* center, float* radius)
{
	Center = *center;
	Radius = *radius;

	Min = Center - float3(Radius, Radius, Radius);
	Max = Center + float3(Radius, Radius, Radius);
};

void SXBound::GetSphere(float3* center, float* radius) const
{
	*center = Center;
	*radius = Radius;
};

bool SXBound::IsPointInSphere(float3* point) const
{
	float distsqr = SMVector3Dot(Center - *point);
	if (distsqr <= Radius*Radius)
		return true;
	else
		return false;
}

bool SXBound::IsPointInBox(float3* point) const
{
	if (point->x >= Min.x && point->y >= Min.y && point->z >= Min.z && point->x <= Max.x && point->y <= Max.y && point->z <= Max.z)
		return true;
	else
		return false;
}