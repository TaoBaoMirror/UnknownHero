#include "Goal_SoldierThink.h"
#include "Goal_Type.h"
#include "Goal_Evaluator.h"
#include "Goal_Explore.h"
#include "Goal_AttackTarget.h"
#include "Goal_Rest.h"
//
#include "ExploreGoal_Evaluator.h"
#include "AttackTargetGoal_Evaluator.h"
#include "Goal_MoveToPosition.h"

#include "Actor/Monster.h"

Goal_SoldierThink::Goal_SoldierThink(Monster* pSoldier)
:Goal_Composite<Monster>(pSoldier, goal_think)
{
	//const double LowRangeOfBias = 0.5;
	//const double HighRangeOfBias = 1.5;

	double ExploreBias = RandInRange(pSoldier->Explore_LowRangeOfBias, pSoldier->Explore_HighRangeOfBias);
	double AttackBias = RandInRange(pSoldier->AttackTarget_LowRangeOfBias, pSoldier->AttackTarget_HighRangeOfBias);

	m_Evaluators.push_back(new ExploreGoal_Evaluator(ExploreBias));
	m_Evaluators.push_back(new AttackTargetGoal_Evaluator(AttackBias));
}

Goal_SoldierThink::~Goal_SoldierThink()
{
	GoalEvaluators::iterator curDes = m_Evaluators.begin();
	for (curDes; curDes != m_Evaluators.end(); ++curDes)
	{
		delete *curDes;
	}
}

void Goal_SoldierThink::Arbitrate()
{
	double best = 0;
	Goal_Evaluator<Monster>* MostDesirable = 0;

	GoalEvaluators::iterator curDes = m_Evaluators.begin();
	for (curDes; curDes != m_Evaluators.end(); ++curDes)
	{
		double desirabilty = (*curDes)->CalculateDesirability(m_pOwner);

		if (desirabilty >= best && desirabilty != 0)
		{
			best = desirabilty;
			MostDesirable = *curDes;
		}
	}

	if (MostDesirable)
	{
		MostDesirable->SetGoal(m_pOwner);
	}
	else
	{
		//如果没有任何一个可以执行的行为意图,则应该跳过它的回合
		AddGoal_Rest();
	}

}

bool Goal_SoldierThink::notPresent( unsigned int GoalType ) const
{
	if (!m_SubGoals.empty())
	{
		return m_SubGoals.front()->GetType() != GoalType;
	}

	return true;
}

int Goal_SoldierThink::Process()
{
	ActivateIfInactive();

	int SubgoalStatus = ProcessSubgoals();

	if (SubgoalStatus == completed || SubgoalStatus == failed)
	{
		if (!m_pOwner->IsPossessed())
		{
			m_iStatus = inactive;
		}
	}

	return m_iStatus;
}

void Goal_SoldierThink::Activate()
{
	Arbitrate();

	m_iStatus = active;

}

void Goal_SoldierThink::AddGoal_MoveToPosition( const GridPos& gpos )
{
	AddSubgoal( new Goal_MoveToPosition(m_pOwner, gpos));

}

void Goal_SoldierThink::AddGoal_GetItem( unsigned int ItemType )
{

}

void Goal_SoldierThink::AddGoal_Explore()
{
	if (notPresent(goal_explore))
	{
		RemoveAllSubgoals();
		AddSubgoal( new Goal_Explore(m_pOwner));
	}
}

void Goal_SoldierThink::AddGoal_AttackTarget()
{
	if (notPresent(goal_attack_target))
	{
		RemoveAllSubgoals();
		AddSubgoal( new Goal_AttackTarget(m_pOwner));
	}
}
void Goal_SoldierThink::AddGoal_Rest()
{
	if (notPresent(goal_rest))
	{
		RemoveAllSubgoals();
		AddSubgoal( new Goal_Rest(m_pOwner));
	}
}
