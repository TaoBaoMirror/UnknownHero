#include "Goal_Attack.h"
#include "Msg_Type.h"

Goal_Attack::Goal_Attack( Soldier* pBot,Soldier* pTargetBot )
	:Goal<Soldier>(pBot, goal_attack),m_pTargetBot(pTargetBot)
{

}

void Goal_Attack::Activate()
{
	m_iStatus = active;
	//
	m_pOwner->Attack(m_pTargetBot);
}

int Goal_Attack::Process()
{
	ActivateIfInactive();

	return m_iStatus;
}

void Goal_Attack::Terminate()
{

}

bool Goal_Attack::HandleMessage( const Telegram& msg )
{
	return true;
}
