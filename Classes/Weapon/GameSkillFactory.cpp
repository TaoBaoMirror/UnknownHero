#include "GameSkillFactory.h"

#include "Weapon/Skill_Sword.h"
#include "Game/Soldier.h"

//---------------------------------------------------------
GameSkillFactory* GameSkillFactory::m_Instance = nullptr;

GameSkillFactory* GameSkillFactory::GetInstance()
{
	if (m_Instance != nullptr)
	{
		m_Instance = new GameSkillFactory();
	}

	return m_Instance;
}


GameSkillFactory::GameSkillFactory(void)
{
}


GameSkillFactory::~GameSkillFactory(void)
{
}

GameSkill* GameSkillFactory::CreateWeapon(int weaponID, Soldier* pOwner)
{
	GameSkill* pNewWeapon = nullptr;

	switch (weaponID)
	{
	case 0:
		{
			pNewWeapon = new Skill_Sword(pOwner);
			pNewWeapon->SetAttackRange(CIRCLE);
			pNewWeapon->SetOriginalAttackDataBase(0);
		}		
		break;
	case 1:
		{
			//pNewWeapon = new Skill_Sword(pOwner);
			//pNewWeapon->SetAttackRange(CIRCLE);
			//pNewWeapon->SetOriginalAttackDataBase(0);
		}		
		break;
	default:
		break;
	}

	return pNewWeapon;
}