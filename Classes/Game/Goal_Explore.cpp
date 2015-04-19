#include "Goal_Explore.h"
#include "Goal_FollowPath.h"

void Goal_Explore::Activate()
{
	m_iStatus = active;

	RemoveAllSubgoals();

	if (!m_bDestinationIsSet)
	{
		std::list<GridPos>	path;

		do
		{
			GameWorld::Instance()->GetSceneMap().GetRandomNodeLocation(m_CurrentDestination);

		}while(!GameWorld::Instance()->GetSceneMap().GetNode(m_CurrentDestination).Walkable());

		if(GameWorld::Instance()->CheckCanArrived(m_pOwner->GetStayGPos(),m_CurrentDestination,&path))
		{
			RemoveAllSubgoals();

			path.pop_front();	//������һ������Ϊ��һ�����ƶ������ڵ�λ��

			AddSubgoal(new Goal_FollowPath(m_pOwner,path));

			m_bDestinationIsSet = true;
		}

	}
}

int Goal_Explore::Process()
{
	ActivateIfInactive();

	m_iStatus = ProcessSubgoals();

	return m_iStatus;
}

bool Goal_Explore::HandleMessage( const Telegram& msg )
{
	return true;
}
