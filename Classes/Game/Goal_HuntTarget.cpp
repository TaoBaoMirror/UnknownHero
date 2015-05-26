#include "Goal_HuntTarget.h"
#include "AttackSystem.h"
#include "TargetingSystem.h"
#include "Goal_Attack.h"
#include "Goal_MoveStep.h"

void Goal_HuntTarget::Activate()
{
	m_iStatus = active;
	//
	auto other = m_pOwner->GetTargetingSystem()->GetTarget();

	if (other != nullptr)
	{
		GridPos GPos;
		m_pOwner->MoveCloseToGPos(other->GetStayGPos(),GPos);

		if (!other->GetStayGPos().Equals(GPos))
		{
			AddSubgoal(new Goal_MoveStep(m_pOwner, m_pOwner->GetStayGPos(), GPos));
		}
		else
		{
			m_iStatus = failed;

		}
	}
	else
	{
		m_iStatus = failed;
	}

}

int Goal_HuntTarget::Process()
{
	ActivateIfInactive();

	m_iStatus = ProcessSubgoals();

	if (m_iStatus == failed)
	{
		//TODO
	}

	return m_iStatus;
}
