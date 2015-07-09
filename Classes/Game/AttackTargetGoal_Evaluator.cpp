#include "AttackTargetGoal_Evaluator.h"
#include "Actor/Monster.h"
#include "Goal_SoldierThink.h"
#include "TargetingSystem.h"
#include "SoldierFeature.h"
//
//����ֵ��0~1֮��
double AttackTargetGoal_Evaluator::CalculateDesirability( Monster* pBot )
{
	double Desirability = 0.0;

	//�Ƿ���������Ұ����
	if (pBot->GetTargetingSystem()->isTargetPresent()) 
	{
		const double Tweaker = 1.0;

		Desirability = Tweaker *
 			SoldierFeature::Health(pBot) * 
			SoldierFeature::TotalAttackStrength(pBot);

		//���Խ�ɫ�����ƫ��ֵ
		Desirability *= m_dCharacterBias;
	}

	return Desirability;
}

void AttackTargetGoal_Evaluator::SetGoal( Monster* pBot )
{
	pBot->GetBrain()->AddGoal_AttackTarget(); 
}
