#include "WeaponFactory.h"

#include "Weapon/Weapon_Sword.h"
#include "Game/Soldier.h"

//---------------------------------------------------------
WeaponFactory* WeaponFactory::m_Instance = nullptr;

WeaponFactory* WeaponFactory::GetInstance()
{
	if (m_Instance != nullptr)
	{
		m_Instance = new WeaponFactory();
	}

	return m_Instance;
}


WeaponFactory::WeaponFactory(void)
{
}


WeaponFactory::~WeaponFactory(void)
{
}

GameSkill* WeaponFactory::CreateWeapon(int weaponID, Soldier* pOwner)
{
	GameSkill* pNewWeapon = nullptr;

	switch (weaponID)
	{
	case 0:
		{
			//pNewWeapon = new Weapon_Sword(pOwner);
			//pNewWeapon->SetAttackRange(CIRCLE);
			//pNewWeapon->SetOriginalAttackDataBase(0);
		}		
		break;
	default:
		break;
	}

	return pNewWeapon;
}