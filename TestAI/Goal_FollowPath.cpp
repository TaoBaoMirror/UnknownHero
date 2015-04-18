#include "Goal_FollowPath.h"
#include "Goal_MoveStep.h"


Goal_FollowPath::Goal_FollowPath( Soldier* pBot, std::list<GridPos> path )
	:Goal_Composite<Soldier>(pBot, goal_follow_path),
	m_Path(path)
{

}

void Goal_FollowPath::Activate()
{
	m_iStatus = active;

	if (m_Path.size())
	{
		GridPos GPos = m_Path.front();

		m_Path.pop_front(); 
		//
		AddSubgoal(new Goal_MoveStep(m_pOwner, m_pOwner->GetStayGPos(), GPos));
	}
	else
	{
		m_iStatus = completed;
	}

}

int Goal_FollowPath::Process()
{
	ActivateIfInactive();

	m_iStatus = ProcessSubgoals();

	//���û������ͼ��������·������Ȼ�нڵ㣬��ô�ͼ�������һ��.
	if (m_iStatus == completed && !m_Path.empty())
	{
		Activate(); 
	}

	return m_iStatus;
}

