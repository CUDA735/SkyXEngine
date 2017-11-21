#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "sxgcore.h"

//����� ����������� �������
class Frustum : public virtual ISXFrustum
{
public:
	Frustum();
	~Frustum();
	void Release(){ mem_del(this); }
	SX_ALIGNED_OP_MEM

	void Update(const float4x4* view,const float4x4* proj);

	bool PointInFrustum(const float3 *point);
	bool PolyInFrustum(const float3* p1,const float3* p2,const float3* p3);
	bool PolyInFrustumAbs(const float3* p1,const float3* p2,const float3* p3);
	
	bool SphereInFrustum(const float3 *point, float radius) const;

	bool SphereInFrustumAbs(const float3 *point, float radius);
	bool BoxInFrustum(float3* min,float3* max);

};

/////////////////////
class Camera : public virtual ISXCamera
{
public:
	Camera	();
	~Camera	();
	void Release(){ mem_del(this); }
	SX_ALIGNED_OP_MEM

	void PosLeftRight(float units);	//�����/������
	void PosUpDown(float units);	//�����/����
	void PosFrontBack(float units);	//������/�����
	
	void RotUpDown(float angle);	//�������� �����/����
	void RotRightLeft(float angle);	//�������� ������/�����
	void Roll(float angle);	//����
	void SetOrientation(const SMQuaternion & q);

	void GetViewMatrix(float4x4* view_matrix);//�������� ������� ����
	
	void GetPosition(float3* pos);
	void SetPosition(float3* pos);

	void GetDirection(float3* dir);
	void SetDirection(float3* dir);
	
	void GetRight(float3* right);
	void GetUp(float3* up);
	void GetLook(float3* look);
	void GetRotation(float3* rot);

	float GetRotationX();
	float GetRotationY();
	float GetRotationZ();

	void SetFOV(float fov);
	float GetFOV();

	void UpdateView();
};

#endif
