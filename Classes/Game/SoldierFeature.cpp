#include "SoldierFeature.h"
#include "Soldier.h"
#include "AttackSystem.h"
#include "Weapon/GameSkill.h"

double SoldierFeature::Health( Soldier* pBot )
{
	return (double)pBot->CurHP / (double)pBot->MaxHP;
}

double SoldierFeature::TotalAttackStrength( Soldier* pBot )
{
	double str = pBot->GetAttackSystem()->GetCurAttackDataBase()->AttackPt /
		(pBot->GetAttackSystem()->GetOriginalAttackDataBase()->AttackPt + 0.1);
	return str;
}
