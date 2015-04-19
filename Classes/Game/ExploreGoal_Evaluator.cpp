#include "ExploreGoal_Evaluator.h"
#include "Soldier.h"
#include "Goal_SoldierThink.h"

double ExploreGoal_Evaluator::CalculateDesirability( Soldier* pBot )
{
	double Desirability = 0.05;

	Desirability *= m_dCharacterBias;

	return Desirability;
}

void ExploreGoal_Evaluator::SetGoal( Soldier* pBot )
{
	pBot->GetBrain()->AddGoal_Explore();
}
