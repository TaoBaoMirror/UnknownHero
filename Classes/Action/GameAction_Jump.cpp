#include "GameAction_Jump.h"
#include "Scene\GameManager.h"
#include "Actor\Hero.h"
#include "Actor\PlayerManager.h"
#include "Weapon\SkillList.h"


GameAction_Jump::GameAction_Jump(int typeID) : 
	GameAction(typeID)
{
	m_IconID = 3;
	m_SkillID = 0;
}


GameAction_Jump::~GameAction_Jump(void)
{
}

void GameAction_Jump::UseAction(int nlevel)
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