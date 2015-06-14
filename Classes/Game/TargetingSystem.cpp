#include "TargetingSystem.h"
#include "Vector2D.h"

#include "MapNodeData.h"
#include "Soldier.h"
#include "AttackSystem.h"
#include "Weapon/GameSkill.h"
#include "AttackRange.h"

TargetingSystem::TargetingSystem( Soldier* owner ):m_pOwner(owner),m_pCurrentTarget(0)
{

}

TargetingSystem::~TargetingSystem()
{

}

void TargetingSystem::Update(float dt)
{
	if (!m_pOwner) return;

	std::vector<Soldier*> Soldiers;
	m_pOwner->FindSoldiersInRange(m_pOwner->CurViewRadius,true,RangeType::CIRCLE,Soldiers);

	Soldier* OptimalSoldier = nullptr;
	Soldier* ClosestSoldier = nullptr;
	int ClosestSteps = 999999;
	//得到最近的一个士兵
	int tagetInView = 0;	//-1 没有情况  0 不再视野里 1 在视野里面

	if (Soldiers.size())
	{
		for (int i = 0 ; i < Soldiers.size(); ++i)
		{
			auto soldier = Soldiers[i];

			if (m_pCurrentTarget != nullptr)
			{
				if (soldier == m_pCurrentTarget)
				{
					m_TargetHasBeenVisible+= dt;
					tagetInView = 1;
				}
			}

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
		
	}

	//
	OptimalSoldier = ClosestSoldier;
	//
	if (m_pCurrentTarget != nullptr)
	{
		if (tagetInView == 0)
		{
			m_TargetHasBeenOutOfView += dt;
		}
	}
	else
	{
		//给定一个目标
		m_pCurrentTarget = OptimalSoldier;
		//
		m_TargetHasBeenVisible = 0;
		m_TargetHasBeenOutOfView = 0;

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
	return m_TargetHasBeenVisible;
}

double TargetingSystem::GetTimeTargetHasBeenOutOfView() const
{
	return m_TargetHasBeenOutOfView;

}
