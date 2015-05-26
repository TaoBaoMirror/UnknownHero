#include "Goal_Explore.h"
#include "Goal_FollowPath.h"
#include "Game/Soldier.h"
#include "Goal_SoldierThink.h"
#include "Game/TargetingSystem.h"
//
#include "MapManager.h"
#include "CommonFunc.h"

void Goal_Explore::Activate()
{
	m_iStatus = active;

	RemoveAllSubgoals();

	if (!m_bDestinationIsSet)
	{
		std::list<GridPos>	path;

		do
		{
			G_GetSceneMap().GetRandomNodeLocation(m_CurrentDestination);

		}while( m_pOwner->CanSetTo(m_CurrentDestination) == false);

		if(MapManager::GetInstance()->GetCurChunkMap()->CheckCanArrived(m_pOwner->GetStayGPos(),m_CurrentDestination,&path))
		{
			RemoveAllSubgoals();

			path.pop_front();	//弹出第一个，因为第一个是移动体现在的位置

			AddSubgoal(new Goal_FollowPath(m_pOwner,path));

			m_bDestinationIsSet = true;
		}

	}
}

int Goal_Explore::Process()
{
	ActivateIfInactive();

	m_iStatus = ProcessSubgoals();

	if (m_pOwner->GetTargetingSystem()->isTargetPresent()) 
	{
		RemoveAllSubgoals();

		m_iStatus = completed;
	}

	return m_iStatus;
}

#include "Game/Msg_Type.h"

bool Goal_Explore::HandleMessage( const Telegram& msg )
{
	if (msg.Msg == Msg_FoundTarget)
	{
		m_iStatus = completed;

		m_pOwner->GetBrain()->AddGoal_AttackTarget();
	}

	return true;
}
