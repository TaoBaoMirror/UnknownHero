#include "SkillList.h"
#include "base/ccRandom.h"
#include "Weapon/GameSkillFactory.h"
#include "Game/CommonFunc.h"
#include "Game/MapNodeData.h"
#include "Scene/MarkTileManager.h"
#include "Game/Soldier.h"


SkillList::SkillList(Soldier* pSoldier) :
	pCurUsingSkill(nullptr)
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

GameSkill* SkillList::AddGameSkill(int weaponID)
{
	GameSkill* pWeapon = GameSkillFactory::GetInstance()->CreateWeapon(weaponID,m_Onwer);
	m_pSkillsMap[weaponID] = pWeapon;

	return pWeapon;
}

void SkillList::UseSkill(int WeaponIndex, int lv)
{
	std::map<int,GameSkill*>::iterator itfind = m_pSkillsMap.find(WeaponIndex);
	if (itfind != m_pSkillsMap.end())
	{
		GameSkill* pSkill = itfind->second;
		if (pSkill != nullptr)
		{
			SetUsingSkill(pSkill);
			pSkill->SkillAim();			
		}
	}
}

bool SkillList::LaunchSkill(const GridPos& gpos)
{
	if (pCurUsingSkill == nullptr)
	{
		return false;
	}

	if (pCurUsingSkill->IsTargetToGrid())
	{
		if (CheckIsInRange(gpos))
		{
			m_Onwer->Attack(gpos,0);

			return true;
		}
	}
	else
	{
		Soldier* pTargetSoldier = CheckHasTarget(gpos);

		if (pTargetSoldier != nullptr)
		{				
			//attack
			m_Onwer->Attack(pTargetSoldier,0);

			return true;
		}
	}


	return false;
}

bool SkillList::CheckIsInRange(const GridPos& gpos)
{
	if (pCurUsingSkill == nullptr)
	{
		return false;
	}

	int index = -1;
	G_GetSceneMap().GetIndex(gpos,index);

	//auto attsys = this->GetAttackSystem();
	AttackRange* attrange = pCurUsingSkill->GetAttackRange();	

	if (attrange != nullptr && attrange->Inspect(gpos) == true)
	{
		if ((index < G_GetSceneMap().NodesCount()) &&
			(index >=0) )
		{
			NavGraphNode<void*>& node = G_GetSceneMap().GetNode(index);
			MapNodeData* pMND = static_cast<MapNodeData*>(node.ExtraInfo());
			//
			if (node.Index() != invalid_node_index && node.Walkable())
			{
				return true;
			}

		}
	}
	return false;
}

Soldier* SkillList::CheckHasTarget(const GridPos& gpos)
{
	if (pCurUsingSkill == nullptr)
	{
		return nullptr;
	}

	int index = -1;
	G_GetSceneMap().GetIndex(gpos,index);

	//auto attsys = this->GetAttackSystem();
	AttackRange* attrange = pCurUsingSkill->GetAttackRange();	

	if (attrange != nullptr && attrange->Inspect(gpos) == true)
	{
		if ((index < G_GetSceneMap().NodesCount()) &&
			(index >=0) )
		{
			NavGraphNode<void*>& node = G_GetSceneMap().GetNode(index);
			MapNodeData* pMND = static_cast<MapNodeData*>(node.ExtraInfo());
			//
			if (node.Index() != invalid_node_index && node.Walkable())
			{
				if (pMND->Creature != NULL)
				{
					return pMND->Creature;
				}
			}

		}
	}
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