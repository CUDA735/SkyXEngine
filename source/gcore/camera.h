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

	inline void PosLeftRight(float units);	//�����/������
	inline void PosUpDown(float units);	//�����/����
	inline void PosFrontBack(float units);	//������/�����
	
	inline void RotUpDown(float angle);	//�������� �����/����
	inline void RotRightLeft(float angle);	//�������� ������/�����
	inline void Roll(float angle);	//����
	inline void SetOrientation(const SMQuaternion & q);

	inline void GetViewMatrix(float4x4* view_matrix);//�������� ������� ����
	
	inline void GetPosition(float3* pos);
	inline void SetPosition(float3* pos);

	inline void GetDirection(float3* dir);
	inline void SetDirection(float3* dir);
	
	inline void GetRight(float3* right);
	inline void GetUp(float3* up);
	inline void GetLook(float3* look);
	inline void GetRotation(float3* rot);

	inline float GetRotationX();
	inline float GetRotationY();
	inline float GetRotationZ();

	inline void SetFOV(float fov);
	inline float GetFOV();

	inline void UpdateView();
};

#endif
