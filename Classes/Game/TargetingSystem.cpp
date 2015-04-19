#include "TargetingSystem.h"
#include "Vector2D.h"

#include "MapNodeData.h"
#include "Soldier.h"
#include "AttackSystem.h"
#include "AttackRange.h"

TargetingSystem::TargetingSystem( Soldier* owner ):m_pOwner(owner),m_pCurrentTarget(0)
{

}

TargetingSystem::~TargetingSystem()
{

}

void TargetingSystem::Update()
{
	if (!m_pOwner) return;

	std::vector<Soldier*> Soldiers;
	m_pOwner->FindSoldiersInRange(m_pOwner->CurViewRadius,true,RangeType::CIRCLE,Soldiers);

	Soldier* ClosestSoldier = NULL;
	int ClosestSteps = 999999;

	if (Soldiers.size())
	{
		for (int i = 0 ; i < Soldiers.size(); ++i)
		{
			auto soldier = Soldiers[i];

			if (soldier && soldier->GetCampIndex() != m_pOwner->GetCampIndex())
			{
				int dis = m_pOwner->GetStayGPos().Distance(soldier->GetStayGPos());

				if (ClosestSteps > dis)
				{
					ClosestSteps = dis;
					ClosestSoldier = soldier;
				}
			}
		}
		//
		m_pCurrentTarget = ClosestSoldier;
	}


}

bool TargetingSystem::isTargetWithinAttackRange() const
{
	if(!m_pCurrentTarget) return false;
	bool ret = m_pOwner->GetAttackSystem()->GetAttackRange()->Inspect(m_pCurrentTarget->GetStayGPos());
	return ret;
}

bool TargetingSystem::isTargetShootable() const
{
	return true;
}

double TargetingSystem::GetTimeTargetHasBeenVisible() const
{
	return 0;
}

double TargetingSystem::GetTimeTargetHasBeenOutOfView() const
{
	return 0;

}
