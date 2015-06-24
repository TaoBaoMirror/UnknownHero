#include "GameAction_Bow.h"
#include "Scene\GameManager.h"
#include "Actor\Hero.h"
#include "Actor\PlayerManager.h"
#include "Weapon\SkillList.h"


GameAction_Bow::GameAction_Bow(int typeID) : 
	GameAction(typeID)
{
	m_IconID = 1;
	m_SkillID = 0;

}


GameAction_Bow::~GameAction_Bow(void)
{
}

void GameAction_Bow::UseAction(int nlevel)
{
	//test
	if (GameManager::GetInstance()->GetFightST() == FightStatus::SF_Hero)
	{
		Hero* pHero = PlayerManager::GetInstance()->GetHero();
		if (pHero != nullptr && pHero->GetSkillList()!=nullptr)
		{
			pHero->GetSkillList()->UseSkill(m_SkillID, nlevel);
		}
	}
	//end
}