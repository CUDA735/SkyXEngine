
#ifndef _NPCBase_H_
#define _NPCBase_H_

#include "SXbaseAnimating.h"
#include <aigrid/sxaigrid.h>

//! ������� ����������� ��� ���
#define NPC_BASE_DIR float3(0,0,-1)

//����� � ����� ��� ������� ���������� �� ���������� ����
#define NPC_TIME_ORIENT_IN_PATH 250

//! �������� ��������
enum NPC_MOVE_STATE
{
	NPC_MOVE_STATE_IDLE_START = 0x0,	//!< �����������
	NPC_MOVE_STATE_IDLE = 0x1,	//!< �����
	NPC_MOVE_STATE_WALK = 0x2,	//!< ����
	NPC_MOVE_STATE_RUN = 0x4,	//!< �����
};

//! ��������� ���������
enum NPC_DANGER_STATE
{
	NPC_DANGER_STATE_CALM = 0,		//!< �������
	NPC_DANGER_STATE_UNVISIBLE = 1,	//!< ���������, �� �� ����� ��� ���������
	NPC_DANGER_STATE_VISIBLE = 2,	//!< ��������� � ����� ��� ���������
};

class NPCBase : public SXbaseAnimating
{
	DECLARE_CLASS(NPCBase, SXbaseAnimating);
	DECLARE_PROPTABLE();

public:

	SX_ALIGNED_OP_MEM

	NPCBase(EntityManager * pMgr);
	~NPCBase();

	ID GetAIQuad();	//id ����� �� ����� �� ������� ����� ���

	//��������� ������� �������������� ����������� �� �� �����
	void SetPos(const float3 & pos);
	bool SetKV(const char * name, const char * value);
	void OnSync();

protected:

	virtual void InitPhysics();

	btPairCachingGhostObject * m_pGhostObject;
	btKinematicCharacterController * m_pCharacter;

	bool PathFind(ID endq);	//!< ����� ���� �� �������� (�� ������� ����� ���) �� endq
	void PathWalk();		//!< �������� �� ����

	//! ��������� ��� �� ����� pos, ttime ����� � ����� �� ������� ��� ����� �������� � �� �����
	void OrientAtPoint(const float3 * pos, DWORD ttime);	
	void UpdateOrientLerp();//!< ������� ������������ ���������

	float m_health;	//�������� [0,1]

	float m_speed_walk;	//�������� �������� ��� ������
	float m_speed_run;	//�������� �������� ��� ����

	float m_immunity_weapon;	//���������� ���������� � ���� �� ������

	ID m_curr_aiquad;			//������� id ����� �� ������� ��������� ���

	Array<ID> m_arr_path;		//������ � ���������������� ������ ���� �� �� �����
	ID m_curr_quaid_in_path;	//����� �������� ����� �� m_arr_path
	
	float3 m_last_path_pos;		//������� ���������� ����� �� ������� ��� ���
	float3 m_next_path_pos;		//��������� ������ ����� �� ������� ��������� ���
	
	float m_angle_y_last;		//���������� ���� ��������
	float m_angle_y_next;		//��������� ���� ��������
	DWORD m_alltime_rot;		//����� ����� ������� ����������
	DWORD m_time_rot;			//����� �� ������� ������ ���� ������������ 

	NPC_MOVE_STATE m_move_state;
};

#endif