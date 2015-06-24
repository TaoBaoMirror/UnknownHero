#include "GameAction_Coin.h"
#include "Scene\GameManager.h"
#include "Actor\Hero.h"
#include "Actor\PlayerManager.h"
#include "Weapon\SkillList.h"


GameAction_Coin::GameAction_Coin(int typeID) : 
	GameAction(typeID)
{
	m_IconID = 2;
	m_SkillID = 0;

}


GameAction_Coin::~GameAction_Coin(void)
{
}

void GameAction_Coin::UseAction(int nlevel)
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