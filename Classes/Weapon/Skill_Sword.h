#ifndef __SKILL_SWORD_H__
#define __SKILL_SWORD_H__

#include "Weapon/GameSkill.h"

class Skill_Sword : public GameSkill
{
public:
	Skill_Sword(Soldier* pOwner);
	~Skill_Sword(void);

	virtual void SkillAim() override;

	virtual void SkillAttack( AttackData* pAtkData ) override;
};

#endif //__SKILL_SWORD_H__