#include "AttackTargetGoal_Evaluator.h"
#include "Actor/Monster.h"
#include "Goal_SoldierThink.h"
#include "TargetingSystem.h"
#include "SoldierFeature.h"
//
//返回值在0~1之间
double AttackTargetGoal_Evaluator::CalculateDesirability( Monster* pBot )
{
	double Desirability = 0.0;

	//是否有人在视野里面
	if (pBot->GetTargetingSystem()->isTargetPresent()) 
	{
		const double Tweaker = 1.0;

		Desirability = Tweaker *
 			SoldierFeature::Health(pBot) * 
			SoldierFeature::TotalAttackStrength(pBot);

		//乘以角色的随机偏移值
		Desirability *= m_dCharacterBias;
	}

	return Desirability;
}

void AttackTargetGoal_Evaluator::SetGoal( Monster* pBot )
{
	pBot->GetBrain()->AddGoal_AttackTarget(); 
}
