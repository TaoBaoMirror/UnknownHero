#include "Goal_MoveStep.h"
#include "Msg_Type.h"

Goal_MoveStep::Goal_MoveStep( Soldier* pBot, const GridPos& from, const GridPos& to )
	:Goal<Soldier>(pBot, goal_move_step),From(from),To(to)
{

}

void Goal_MoveStep::Activate()
{
	m_iStatus = active;

// 	if(!m_pOwner->MoveTo(To))
// 	{
// 		m_iStatus = failed;
// 	}
// 	else
// 	{
// 		m_iStatus = completed;
// 	}

	if(!m_pOwner->TravalTo(To))
	{
		m_iStatus = failed;
	}
	else
	{
		m_iStatus = completed;
	}
}

int Goal_MoveStep::Process()
{
	ActivateIfInactive();

	return m_iStatus;
}

void Goal_MoveStep::Terminate()
{

}

bool Goal_MoveStep::HandleMessage( const Telegram& msg )
{
	switch(msg.Msg)
	{
	case Msg_MoveStepOver:

		m_iStatus = completed;

		break;

	}

	return true;
	
}
