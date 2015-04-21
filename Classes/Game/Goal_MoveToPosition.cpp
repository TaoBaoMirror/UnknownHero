#include "Goal_MoveToPosition.h"
#include "Goal_FollowPath.h"
//
#include "MapManager.h"

Goal_MoveToPosition::Goal_MoveToPosition( Soldier* pBot, GridPos gpos ) :
	Goal_Composite<Soldier>(pBot,
	goal_move_to_position),
	m_Destination(gpos)
{

}


void Goal_MoveToPosition::Activate()
{
	m_iStatus = active;

	RemoveAllSubgoals();

	
	std::list<GridPos>	path;

	if(!MapManager::GetInstance()->GetCurChunkMap().CheckCanArrived(m_pOwner->GetStayGPos(),m_Destination,&path))
	{
		m_iStatus = failed;
	}
	else
	{

		RemoveAllSubgoals();

		path.pop_front();	//������һ������Ϊ��һ�����ƶ������ڵ�λ��

		AddSubgoal(new Goal_FollowPath(m_pOwner,path));
	}

}

int Goal_MoveToPosition::Process()
{
	ActivateIfInactive();

	//ִ������ͼ
	m_iStatus = ProcessSubgoals();

	ReactivateIfFailed();

	return m_iStatus;
}

void Goal_MoveToPosition::Terminate()
{

}
