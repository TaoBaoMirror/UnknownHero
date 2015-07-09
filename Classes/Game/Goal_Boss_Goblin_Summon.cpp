#include "Goal_Boss_Goblin_Summon.h"



Goal_Boss_Goblin_Summon::Goal_Boss_Goblin_Summon( Boss_GoblinKing* pBot )
	:Goal<Boss_GoblinKing>(pBot, boss_goblin_summon)
{

}

void Goal_Boss_Goblin_Summon::Activate()
{
	m_iStatus = active;
	//
	m_pOwner->SkillSummon(1);
	//
	m_iStatus = completed;
}

int Goal_Boss_Goblin_Summon::Process()
{
	ActivateIfInactive();

	return m_iStatus;
}

void Goal_Boss_Goblin_Summon::Terminate()
{

}

bool Goal_Boss_Goblin_Summon::HandleMessage( const Telegram& msg )
{
	return true;
}