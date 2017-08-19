
#include "NPCZombie.h"
#include "score/sxscore.h"

BEGIN_PROPTABLE(CNPCZombie)
// empty
	
END_PROPTABLE()

REGISTER_ENTITY_NOLISTING(CNPCZombie, npc_zombie);

CNPCZombie::CNPCZombie(EntityManager * pMgr) :
	BaseClass(pMgr)
{
	m_fSpeedWalk = 0.07f;
	m_fSpeedRun = 0.12f;

	m_idSndIdle = SSCore_SndCreate3d("mobs/zombie/zombie_idle_16.ogg", false, 0, 30);
	m_idSndIdle2 = SSCore_SndCreate3d("mobs/zombie/zombie_idle_17.ogg", false, 0, 30);
	m_idSndDeath = SSCore_SndCreate3d("mobs/zombie/zombie_die_1.ogg", false, 0, 45);
}

CNPCZombie::~CNPCZombie()
{

}

void CNPCZombie::OnSync()
{
	BaseClass::OnSync();

	SSCore_SndPosWSet(m_idSndIdle,&GetPos());
	SSCore_SndPosWSet(m_idSndIdle2, &GetPos());
	SSCore_SndPosWSet(m_idSndDeath, &GetPos());

	//���� �������� ������ ����
	if (m_fHealth < 0.0f)
	{
		//�� ������������� �������� ������
		this->PlayAnimation("fake_death0");
		SSCore_SndPlay(m_idSndDeath);
		m_fHealth = 0.f;	//�������� �������� ������ ��� ������ ����������� �������� �� ����
		return;
	}

	if (m_fHealth <= 0.f)
		return;

	//���� ������ � ����, �������� ����
	if (m_statePath == NPC_STATE_PATH_LOST)
	{
		//!!!���� ������ ������� ����� ����
		m_stateMove = NPC_STATE_MOVE_IDLE_START;
		m_idCurrQuaidInPath = -1;
	}
	//����� ���� ��������� ���� == ������� ����� �� ������� (����������)
	else if (m_statePath == NPC_STATE_PATH_BITBEYOND)
	{
		m_stateMove = NPC_STATE_MOVE_RUN;
		pathWalk();
	}

	if (m_idCurrAiQuad < 0)
		return;

	randWalk();
}

void CNPCZombie::randWalk()
{
	if (m_idCurrQuaidInPath == -1)
	{
		float rndradius = randf(20.f,40.f)*0.5f;
		float3 rndpos;
		rndpos.x = m_vPosition.x + randf(-rndradius, rndradius);
		rndpos.y = m_vPosition.y + randf(-rndradius, rndradius);
		rndpos.z = m_vPosition.z + randf(-rndradius, rndradius);

		Core_RFloat3Get(G_RI_FLOAT3_OBSERVER_POSITION, &rndpos);

		if (pathFind(SAIG_QuadGetNear(&rndpos,true)))
		{
			m_idCurrQuaidInPath = 0;
			m_vLastPathPos = GetPos();
		}

		return;
	}

	if (m_stateMove == NPC_STATE_MOVE_IDLE_START && !this->PlayingAnimations("idle0"))
	{
		m_stateMove = NPC_STATE_MOVE_IDLE;
		this->PlayAnimation("idle0");
		SSCore_SndPlay(m_idSndIdle);
	}
	else if (m_stateMove == NPC_STATE_MOVE_IDLE && !this->PlayingAnimations("idle0"))
		m_stateMove = NPC_STATE_MOVE_WALK;
	else if (m_stateMove != NPC_STATE_MOVE_IDLE)
	{
		if (!this->PlayingAnimations("walk0"))
		{
			this->PlayAnimation("walk0");
			SSCore_SndPlay(m_idSndIdle2);
		}

		pathWalk();
	}
}