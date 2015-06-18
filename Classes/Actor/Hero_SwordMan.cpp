#include "Hero_SwordMan.h"
#include "Game\Soldier.h"
#include "Weapon\SkillList.h"
#include "PlayerManager.h"


Hero_SwordMan::Hero_SwordMan(void)
{
}


Hero_SwordMan::~Hero_SwordMan(void)
{
}


void Hero_SwordMan::InitSkills()
{
	if (GetSkillList() != nullptr)
	{
		GameSkill* pSkill = GetSkillList()->AddGameSkill(0);
		pSkill->SetIsTargetToGrid(true);
		PlayerManager::GetInstance()->AddWeightToList(GameActionType::GameActionType_Sword, 10);
	}
}