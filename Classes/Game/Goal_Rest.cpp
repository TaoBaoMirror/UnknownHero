#include "Goal_Rest.h"
#include "Actor/Monster.h"

Goal_Rest::Goal_Rest( Monster* pBot )
	:Goal<Monster>(pBot, goal_rest)
{

}

void Goal_Rest::Activate()
{
	m_iStatus = active;
	//
	m_pOwner->FinishRound();
	//
	m_iStatus = completed;
}

int Goal_Rest::Process()
{
	ActivateIfInactive();

	return m_iStatus;
}

void Goal_Rest::Terminate()
{

}

bool Goal_Rest::HandleMessage( const Telegram& msg )
{
	return true;
}
