#include "BossManager.h"
#include "Game/SoldierManager.h"

#include "Scene/GameManager.h"
#include "Actor/ActorStatus.h"

#include "Game/Camp.h"
#include "Boss/Boss_GoblinKing.h"
#include <Messaging/MessageListenerManager.h>

//-------------------------------------------------------
BossManager* BossManager::m_Instance = nullptr;

BossManager* BossManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new BossManager();
	}

	return m_Instance;
}
//-------------------------------------------------------
BossManager::BossManager(void)
{
	m_pBoss = nullptr;
}


BossManager::~BossManager(void)
{
}
//-------------------------------------------------------
void BossManager::Update(float dt)
{
	//¼ì²âÓ¢ÐÛÊÇ·ñÒÆ¶¯¹¥»÷Íê±Ï Èç¹ûÍê±Ï ÇÐ»»µ½µÐÈË
	if (m_pBoss != nullptr)
	{
		m_pBoss->update(dt);
	}

	if(m_pBoss == nullptr || (m_pBoss != nullptr && m_pBoss->m_pFSM->GetStatus() == Actor_Stand::Instance()) )
	{
		GameManager::GetInstance()->RoundPassed();
	}
}
//-------------------------------------------------------
void BossManager::ReadyFight()
{
	if (m_pBoss != nullptr)
	{
		m_pBoss->m_pFSM->SetStatus(Actor_Ready::Instance());
	}
}
//-------------------------------------------------------
//-------------------------------------------------------
void BossManager::ClearBossWeightList()
{
	m_BossWeightList.clear();
}
void BossManager::AddWeightToList(GameActionType pActType, int nWeight)
{
	m_BossWeightList.push_back(std::make_pair(pActType,nWeight));
}

bool BossManager::CheckNoDyingActor()
{
	if (m_pBoss == nullptr)
	{
		return true;
	}
	else if (m_pBoss->m_pFSM->GetStatus() != Actor_Die::Instance())
	{
		return true;
	}

	return false;
}

Boss* BossManager::CreateBoss(BossType type)
{
	Boss* newBoss = nullptr;

	switch (type)
	{
	case BossType_GoblinKing:
		newBoss = Boss_GoblinKing::CreateBoss();
		break;
	default:
		break;
	}

	m_pBoss = newBoss;

	if (m_pBoss != nullptr)
	{
		SoldierManager::Instance()->RegisterSoldier(m_pBoss);
		// add by Hitman [5/20/2015]
		Camp::GetCamp(CampType_Monster)->RegisterUnit(m_pBoss);
		// add by Hitman [5/26/2015]
		MessageListenerManager::Instance()->RegisterMessageListener(m_pBoss);
	}	

	return newBoss;
}

//-------------------------------------------------------
