#include "Goal_Boss_Goblin_Rest.h"


Goal_Boss_Goblin_Rest::Goal_Boss_Goblin_Rest( Boss_GoblinKing* pBot )
	:Goal<Boss_GoblinKing>(pBot, boss_goblin_rest)
{

}

void Goal_Boss_Goblin_Rest::Activate()
{
	m_iStatus = active;
	//
	m_pOwner->FinishRound();
	//
	m_iStatus = completed;
}

int Goal_Boss_Goblin_Rest::Process()
{
	ActivateIfInactive();

	return m_iStatus;
}

void Goal_Boss_Goblin_Rest::Terminate()
{

}

bool Goal_Boss_Goblin_Rest::HandleMessage( const Telegram& msg )
{
	return true;
}
