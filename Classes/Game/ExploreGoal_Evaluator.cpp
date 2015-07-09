#include "ExploreGoal_Evaluator.h"
#include "Actor/Monster.h"
#include "Goal_SoldierThink.h"

double ExploreGoal_Evaluator::CalculateDesirability( Monster* pBot )
{
	double Desirability = 0.05;

	Desirability *= m_dCharacterBias;

	return Desirability;
}

void ExploreGoal_Evaluator::SetGoal( Monster* pBot )
{
	pBot->GetBrain()->AddGoal_Explore();
}
