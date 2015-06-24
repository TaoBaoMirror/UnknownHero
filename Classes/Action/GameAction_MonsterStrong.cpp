#include "GameAction_MonsterStrong.h"
#include "Scene\GameManager.h"
#include "Actor\Hero.h"
#include "Actor\PlayerManager.h"
#include "Weapon\SkillList.h"


GameAction_MonsterStrong::GameAction_MonsterStrong(int typeID) : 
	GameAction(typeID)
{
	m_IconID = 0;
	m_SkillID = 0;
}


GameAction_MonsterStrong::~GameAction_MonsterStrong(void)
{
}

void GameAction_MonsterStrong::UseAction(int nlevel)
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