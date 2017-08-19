
#ifndef __NPCBASE_H_
#define __NPCBASE_H_

#include "SXbaseAnimating.h"
#include <aigrid/sxaigrid.h>

//! ������� ����������� ��� ���
#define NPC_BASE_DIR float3(0,0,-1)

//����� � ����� ��� ������� ���������� �� ���������� ����
#define NPC_TIME_ORIENT_IN_PATH 250

#define NPC_STEP_HEIGHT_EPSILON	0.05f

#define NPC_QUAD_DIST_NOTBEYOND	AIGRID_QUAD_SIZE
#define NPC_QUAD_DIST_BEYOND	AIGRID_QUAD_SIZE*2.f

//! �������� ��������
enum NPC_STATE_MOVE
{
	NPC_STATE_MOVE_IDLE_START = 0,	//!< �����������
	NPC_STATE_MOVE_IDLE = 1,		//!< �����
	NPC_STATE_MOVE_WALK = 2,		//!< ����
	NPC_STATE_MOVE_RUN = 4,			//!< �����
};

//! ��������� ���������
enum NPC_STATE_DANGER
{
	NPC_STATE_DANGER_CALM		= 0,	//!< �������
	NPC_STATE_DANGER_UNVISIBLE	= 1,	//!< ���������, �� �� ����� ��� ���������
	NPC_STATE_DANGER_VISIBLE	= 2,	//!< ��������� � ����� ��� ���������
};

//! ��������� ����
enum NPC_STATE_PATH
{
	NPC_STATE_PATH_NOTFOUND		= 0,	//!< �� ������ ����
	NPC_STATE_PATH_BITBEYOND	= 1,	//!< �� ��������� (����������� ���������)
	NPC_STATE_PATH_BEYOND		= 2,	//!< �� ��������� (����������� �� ���������)
	NPC_STATE_PATH_LOST			= 3,	//!< ������ � ����
	NPC_STATE_PATH_FOUND		= 4,	//!< ������
};

class CNPCBase : public SXbaseAnimating
{
	DECLARE_CLASS(CNPCBase, SXbaseAnimating);
	DECLARE_PROPTABLE();

public:

	SX_ALIGNED_OP_MEM

	CNPCBase(EntityManager * pMgr);
	~CNPCBase();

	ID getAIQuad();	//id ����� �� ����� �� ������� ����� ���

	//��������� ������� �������������� ����������� �� �� �����
	void SetPos(const float3 &pos);
	bool SetKV(const char *name, const char *value);
	void OnSync();

protected:

	virtual void InitPhysics();

	btPairCachingGhostObject * m_pGhostObject;
	btKinematicCharacterController * m_pCharacter;

	bool pathFind(ID endq);	//!< ����� ���� �� �������� (�� ������� ����� ���) �� endq
	void pathWalk();		//!< �������� �� ����
	void gridCheckBeyond();	//!< �������� �� ����� �� ������� �����, � ���� ��� �� ��������� ��������������� ���������

	//! ��������� ��� �� ����� pos, ttime ����� � ����� �� ������� ��� ����� �������� �/�� �����
	void orientAtPoint(const float3 *pos, DWORD ttime);	
	void updateOrientLerp();//!< ������� ������������ ���������

	float m_fHealth;	//�������� [0,1]

	float m_fSpeedWalk;	//�������� �������� ��� ������
	float m_fSpeedRun;	//�������� �������� ��� ����

	ID m_idCurrAiQuad;			//������� id ����� �� ������� ��������� ���

	Array<ID> m_aPathQuads;		//������ � ���������������� ������ ���� �� �� �����
	ID m_idCurrQuaidInPath;		//����� �������� ����� �� m_arr_path
	
	float3 m_vLastPathPos;		//��������� ������� ��� �� ����

	float3 m_vPosQuadInPathLast;	//������� ���������� ����� �� ������� ��� ���
	float3 m_vPosQuadInPathNext;	//��������� ������ ����� �� ������� ��������� ���
	
	float m_fAngleYLast;		//���������� ���� ��������
	float m_fAngleYNext;		//��������� ���� ��������
	DWORD m_ulTimeAllRot;		//����� ����� ������� ����������
	DWORD m_ulTimeRot;			//����� �� ������� ������ ���� ������������ 

	float m_fStepHeight;		//������ ����
	bool m_canJump;				//������� �� ������
	NPC_STATE_MOVE m_stateMove;	//��������� ��������
	NPC_STATE_PATH m_statePath;	//��������� ����
	DWORD m_ulColor;				//��������� (������ ����� ����������) ���� ��� ��� ����� ������ �����
	DWORD m_ulTimeReturnInGrid;		//�� ������� ����� ��� ������ ��������� �� �� �����
	DWORD m_ulTimeAllReturnInGrid;	//����� ����� ����������� ��� �� �� �����
};

#endif