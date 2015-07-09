#include "Goal_AttackTarget.h"
#include "AttackSystem.h"
#include "TargetingSystem.h"
#include "Goal_Attack.h"
#include "Goal_HuntTarget.h"
#include "Actor/Monster.h"

void Goal_AttackTarget::Activate()
{
	m_iStatus = active;

	//如果这个意图是重新激活的，而且他有其他子意图，则必须清除掉那些
	RemoveAllSubgoals();

	//这个确保角色都有一个目标~~ 
	if (!m_pOwner->GetTargetingSystem()->isTargetPresent())
	{
		m_iStatus = completed;

		return;
	}

	//判断是否可以打的到~
	if (m_pOwner->GetTargetingSystem()->isTargetWithinAttackRange())
	{		
		AddSubgoal(new Goal_Attack(m_pOwner, m_pOwner->GetTargetingSystem()->GetTarget()));		
	}
	//如果目标不在攻击范围内,就去追击
	else
	{
		//m_iStatus = completed;

		AddSubgoal(new Goal_HuntTarget(m_pOwner));
	}
}

//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_AttackTarget::Process()
{
	ActivateIfInactive();

	m_iStatus = ProcessSubgoals();

	ReactivateIfFailed();

	return m_iStatus;
}

Goal_AttackTarget::Goal_AttackTarget( Monster* pOwner ) :Goal_Composite<Monster>(pOwner, goal_attack_target)
{

}
