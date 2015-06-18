#include "SoldierFeature.h"
#include "Soldier.h"
#include "AttackSystem.h"
#include "Weapon/GameSkill.h"
#include "Weapon/SkillList.h"

double SoldierFeature::Health( Soldier* pBot )
{
	return (double)pBot->CurHP / (double)pBot->MaxHP;
}

double SoldierFeature::TotalAttackStrength( Soldier* pBot )
{
	double str = 0.0f;
	if (pBot->GetSkillList() != nullptr && pBot->GetSkillList()->GetUsingSkill() != nullptr)
	{
		double a = pBot->GetSkillList()->GetUsingSkill()->GetCurAttackDataBase()->AttackPt;
		double b = (pBot->GetSkillList()->GetUsingSkill()->GetOriginalAttackDataBase()->AttackPt + 0.1);
		str = a/b;
			
	}
		
	return str;
}
