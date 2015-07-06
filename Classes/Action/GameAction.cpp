#include "GameAction.h"
#include "Scene\GameManager.h"
#include "Actor\Boss\Boss.h"
#include "Actor\BossManager.h"


GameAction::GameAction(int typeID) :
	m_ActionTypeID(typeID)
{
}


GameAction::~GameAction(void)
{
}

void GameAction::ClickAction()
{
	;
}

void GameAction::UseAction(int nlevel)
{
	if (GameManager::GetInstance()->GetFightST() == FightStatus::SF_BOSS)
	{
		Boss* pBoss = BossManager::GetInstance()->GetBoss();
		if (pBoss != nullptr)
		{
			pBoss->UseBossAction(m_ActionTypeID, nlevel);
		}
	}
}

bool GameAction::IsActionDirectly()
{
	return m_bIsDirectly;
}