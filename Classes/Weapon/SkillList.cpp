#include "SkillList.h"
#include "Weapon/WeaponFactory.h"
#include "base/ccRandom.h"


SkillList::SkillList(Soldier* pSoldier)
{
	m_Onwer = pSoldier;
	//m_CurMaxWeaponAmount = 0;
}


SkillList::~SkillList(void)
{
}

void SkillList::Update()
{
	;
}

void SkillList::AddGameSkill(int weaponID)
{
	GameSkill* pWeapon = WeaponFactory::GetInstance()->CreateWeapon(weaponID,m_Onwer);
	m_pSkillsMap[weaponID] = pWeapon;
}

void SkillList::UseSkill(int WeaponIndex)
{
	;
}

GameSkill* SkillList::GetSkill(int weaponIndex)
{
	return nullptr;	 
}


//void GameActions::RandomDeployWeapon()
//{
//	std::vector<ActionBase*> pTempWeapons;
//	for (int i=0; i<m_pWeapons.size(); ++i)
//	{
//		pTempWeapons.push_back(m_pWeapons[i]);
//	}
//
//	m_CurMaxWeaponAmount = m_pWeapons.size();
//	int haveWeaponAmount = m_CurMaxWeaponAmount;
//	for (int i=0; i<m_CurMaxWeaponAmount; ++i)
//	{
//		int randomNum = CCRANDOM_0_1()*haveWeaponAmount;
//		ActionBase* pWp = pTempWeapons[randomNum];
//		m_pEquipWeapons[i] = pWp;
//		std::vector<ActionBase*>::iterator it = pTempWeapons.begin();
//		for ( ; it != pTempWeapons.end(); ++it)
//		{
//			if ((*it) == pWp)
//			{
//				pTempWeapons.erase(it);
//				haveWeaponAmount--;
//				break;
//			}
//		}
//	}
//}