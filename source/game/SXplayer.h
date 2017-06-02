#ifndef _SXplayer_H_
#define _SXplayer_H_

#include "SXbaseAnimating.h"
#include "SXpointCamera.h"


enum
{
	PM_NONE = 0,
	PM_FORWARD = 0x01,   // ������
	PM_BACKWARD = 0x02,  // �����
	PM_LEFT = 0x04,      // �����
	PM_RIGHT = 0x08,     // ������
	PM_CROUCH = 0x10,    // ��������
	PM_JUMP = 0x20,      // ��������
	PM_RUN = 0x40,       // ������
	PM_CRAWL = 0x80,     // ������
	PM_OBSERVER = 0x100, // �����������

	PM_STOP = 0xFFFF,
};

class SXplayer: public SXbaseAnimating
{
	DECLARE_CLASS(SXplayer, SXbaseAnimating);
	DECLARE_PROPTABLE();
public:
	SXplayer(EntityManager * pMgr);
	~SXplayer();
	
	SXpointCamera * GetCamera();

	void Observe()
	{
		m_uMoveDir |= PM_OBSERVER;
	}
	void Spawn();

	void Move(UINT dir, bool start);

	virtual void UpdateInput(float dt);

	void OnSync();

	void SetPos(const float3 & pos);

	void Attack(BOOL state);
	void Attack2(BOOL state);

	float3 GetWeaponOrigin();

protected:

	SXpointCamera * m_pCamera;

	UINT m_uMoveDir;

	ID m_iUpdIval;

	float3_t m_vPitchYawRoll;

	btCollisionShape * m_pCollideShape;
	btRigidBody * m_pRigidBody;
	btPairCachingGhostObject * m_pGhostObject;
	btKinematicCharacterController * m_pCharacter;

	bool m_bCanJump;

	float m_fViewbobStep;
	float m_fViewbobY;
	float3_t m_fViewbobStrafe;
};

#endif
