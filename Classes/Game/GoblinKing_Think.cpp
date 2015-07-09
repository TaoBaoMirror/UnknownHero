#include "GoblinKing_Think.h"
#include "Goal_Type.h"
#include "Goal_Rest.h"
#include "Msg_Type.h"
//
#include "Goal_Boss_Goblin_Rest.h"
#include "Goal_Boss_Goblin_Summon.h"
#include "Goal_Boss_Goblin_Attack.h"


GoblinKing_Think::GoblinKing_Think( Boss_GoblinKing* pBoss)
	:Goal_Composite<Boss_GoblinKing>(pBoss, boss_goblin_think)
{
	//先进先出
	mGoalPrefabQueue.push(boss_goblin_summon);
	mGoalPrefabQueue.push(boss_goblin_rest);
	mGoalPrefabQueue.push(boss_goblin_attack);
	mGoalPrefabQueue.push(boss_goblin_rest);

}

GoblinKing_Think::~GoblinKing_Think()
{

}

void GoblinKing_Think::Arbitrate()
{
	int todo = mGoalPrefabQueue.front();
	switch (todo)
	{
	case boss_goblin_summon: AddGoal_Summon(); break;
	case boss_goblin_rest: AddGoal_Rest();break;
	case boss_goblin_attack: AddGoal_Attack();break;
	default:
		break;
	}
	//
	mGoalPrefabQueue.pop();
	mGoalPrefabQueue.push(todo);
}

bool GoblinKing_Think::notPresent( unsigned int GoalType ) const
{
	if (!m_SubGoals.empty())
	{
		return m_SubGoals.front()->GetType() != GoalType;
	}

	return true;
}
int GoblinKing_Think::Process()
{
	ActivateIfInactive();

	int SubgoalStatus = ProcessSubgoals();

	/*
	if (SubgoalStatus == completed || SubgoalStatus == failed)
	{
		if (!m_pOwner->IsPossessed())
		{
			m_iStatus = inactive;
		}
	}
	*/

	return m_iStatus;
}

void GoblinKing_Think::Activate()
{
	Arbitrate();

	m_iStatus = active;

}
//////////////////////////////////////////////////////////////////////////
//
//		
//
//////////////////////////////////////////////////////////////////////////
void GoblinKing_Think::AddGoal_Summon()
{
	if (notPresent(boss_goblin_summon))
	{
		RemoveAllSubgoals();
		AddSubgoal( new Goal_Boss_Goblin_Summon(m_pOwner));
	}
}

void GoblinKing_Think::AddGoal_Shake()
{

}

void GoblinKing_Think::AddGoal_Attack()
{
	if (notPresent(boss_goblin_attack))
	{
		RemoveAllSubgoals();
		AddSubgoal( new Goal_Boss_Goblin_Attack(m_pOwner));
	}
}

void GoblinKing_Think::AddGoal_Rest()
{
	if (notPresent(boss_goblin_rest))
	{
		RemoveAllSubgoals();
		AddSubgoal( new Goal_Boss_Goblin_Rest(m_pOwner));
	}
}

bool GoblinKing_Think::HandleMessage( const Telegram& telegram )
{
	Goal_Composite<Boss_GoblinKing>::HandleMessage(telegram);
	//
	if (telegram.Msg == Msg_AI_SetInactive)
	{
		m_iStatus = inactive;
	}

	return true;
}
