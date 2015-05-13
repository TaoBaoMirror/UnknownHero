#include "PlayerManager.h"
#include "Game/SoldierManager.h"

#include "Scene/GameManager.h"
#include "Actor/ActorStatus.h"

//-------------------------------------------------------
PlayerManager* PlayerManager::m_Instance = nullptr;

PlayerManager* PlayerManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new PlayerManager();
	}

	return m_Instance;
}
//-------------------------------------------------------
PlayerManager::PlayerManager(void)
{
}


PlayerManager::~PlayerManager(void)
{
}
//-------------------------------------------------------
void PlayerManager::Update(float dt)
{
	//¼ì²âÓ¢ÐÛÊÇ·ñÒÆ¶¯¹¥»÷Íê±Ï Èç¹ûÍê±Ï ÇÐ»»µ½µÐÈË
	if (m_pMainRole != nullptr)
	{
		if(m_pMainRole->m_pFSM->GetStatus() == Actor_Stand::Instance())
		{
			GameManager::GetInstance()->RoundPassed();
		}	
	}
}
//-------------------------------------------------------
void PlayerManager::ReadyFight()
{
	if (m_pMainRole != nullptr)
	{
		m_pMainRole->m_pFSM->SetStatus(Actor_Ready::Instance());
	}
}
//-------------------------------------------------------
void PlayerManager::HeroBorn(StandbyHero* pTempleHero)
{
	if (m_pMainRole != nullptr)
	{
		m_pMainRole->NotAnActor();
	}

	m_pMainRole = Hero::createWithHeroID(pTempleHero->m_HeroID);

	SoldierManager::Instance()->RegisterSoldier(m_pMainRole);
}
//-------------------------------------------------------
StandbyHero* PlayerManager::RandomStandbyHero()
{
	return nullptr;
}
//-------------------------------------------------------
