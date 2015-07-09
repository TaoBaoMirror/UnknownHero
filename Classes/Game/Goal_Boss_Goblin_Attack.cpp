#include "Goal_Boss_Goblin_Attack.h"

Goal_Boss_Goblin_Attack::Goal_Boss_Goblin_Attack( Boss_GoblinKing* pBot )
	:Goal<Boss_GoblinKing>(pBot, boss_goblin_attack)
{

}

void Goal_Boss_Goblin_Attack::Activate()
{
	m_iStatus = active;
	//
	m_pOwner->SkillAttack();
	//
	m_iStatus = completed;
}

int Goal_Boss_Goblin_Attack::Process()
{
	ActivateIfInactive();

	return m_iStatus;
}

void Goal_Boss_Goblin_Attack::Terminate()
{

}

bool Goal_Boss_Goblin_Attack::HandleMessage( const Telegram& msg )
{
	return true;
}