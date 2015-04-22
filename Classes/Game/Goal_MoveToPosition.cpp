#include "Goal_MoveToPosition.h"
#include "Goal_FollowPath.h"
//
#include "MapManager.h"

void Goal_MoveToPosition::Activate()
{
	m_iStatus = active;

	RemoveAllSubgoals();

	
	std::list<GridPos>	path;

	if(!MapManager::GetInstance()->GetCurChunkMap()->CheckCanArrived(m_pOwner->GetStayGPos(),m_Destination,&path))
	{
		m_iStatus = failed;
	}
	else
	{

		RemoveAllSubgoals();

		path.pop_front();	//弹出第一个，因为第一个是移动体现在的位置

		AddSubgoal(new Goal_FollowPath(m_pOwner,path));
	}

}

int Goal_MoveToPosition::Process()
{
	ActivateIfInactive();

	//执行子意图
	m_iStatus = ProcessSubgoals();

	ReactivateIfFailed();

	return m_iStatus;
}

void Goal_MoveToPosition::Terminate()
{

}
