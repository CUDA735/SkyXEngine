
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

/*!
\file
������� ����� ���������
*/

/*! \ingroup cbaseanimating
@{
*/

#ifndef _CBaseCharacter_H_
#define _CBaseCharacter_H_

#include "BaseAnimating.h"
#include "LightDirectional.h"

class CBaseTool;

//! ���� �������� ������
enum PLAYER_MOVE
{
	PM_NONE = 0,
	PM_FORWARD = 0x01,   //!< ������
	PM_BACKWARD = 0x02,  //!< �����
	PM_LEFT = 0x04,      //!< �����
	PM_RIGHT = 0x08,     //!< ������
	PM_CROUCH = 0x10,    //!< ��������
	PM_JUMP = 0x20,      //!< ��������
	PM_RUN = 0x40,       //!< ������
	PM_CRAWL = 0x80,     //!< ������
	PM_OBSERVER = 0x100, //!< �����������

	PM_STOP = 0xFFFF
};

//! ����� ������  \ingroup cbaseanimating
class CBaseCharacter: public CBaseAnimating
{
	DECLARE_CLASS(CBaseCharacter, CBaseAnimating);
	DECLARE_PROPTABLE();
public:
	CBaseCharacter(CEntityManager * pMgr);
	~CBaseCharacter();

	//! ���������/������������� ��������� �����
	void attack(BOOL state);
	//! ���������/������������� ��������� �����
	void attack2(BOOL state);
	//! ��������� ����������� ��������� ������
	void reload();
	//! ��������/��������� ������
	void toggleFlashlight();
	//! ����������� ����� �������� ��������� ������
	void nextFireMode();

	//! ��������� �� ����� �� �����
	bool onGround();

	//! ������������� ���� ����� � ������ ��������� �� ������� ����� �����
	void playFootstepsSound();


	//! �������� ������������ ��� �������� ������ ����������� �������� (� ������ �������� ��������)
	float getCurrentSpread();

protected:
	//! �������
	CLightDirectional* m_flashlight;

	//! ������� ��������
	UINT m_uMoveDir;

	//! ������� ���������� � �����
	CBaseTool * m_pActiveTool;

	//! ��� ������ @{
	btCollisionShape * m_pCollideShape;
	btRigidBody * m_pRigidBody;
	btPairCachingGhostObject * m_pGhostObject;
	btKinematicCharacterController * m_pCharacter;
	//! @}

	//! ���� �������� ������
	float3_t m_vPitchYawRoll;

	//! ���������� �������� ������������ ��������
	float getMomentSpread();

	//! ������ ���������� ��������
	ID m_idTaskSpread;

	//! ��������� �������� ��������
	virtual void updateSpread(float dt);

	//! ����������� �������� ��������
	float m_fCurrentSpread;
};

#endif

//! @}
