#include "Skill_Sword.h"
#include "Scene\MarkTileManager.h"
#include "Game\AttackSystem.h"
#include "Game\Soldier.h"
#include "Game\CommonFunc.h"


Skill_Sword::Skill_Sword(Soldier* pOwner) :
	GameSkill(pOwner)
{
}


Skill_Sword::~Skill_Sword(void)
{
}

void Skill_Sword::SkillAim()
{
	GameSkill::SkillAim();	
}

void Skill_Sword::SkillAttack( AttackData* pAtkData )
{
	CommonFunc::CalcDamage(pAtkData);

	m_pOwner->CallBack_AttackFinish();
}
