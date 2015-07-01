#include "PlayerManager.h"
#include "Game/SoldierManager.h"

#include "Scene/GameManager.h"
#include "Actor/ActorStatus.h"

#include "Game/Camp.h"

#include "Messaging/MessageListenerManager.h"

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
	//¼ì²âÓ¢ĞÛÊÇ·ñÒÆ¶¯¹¥»÷Íê±Ï Èç¹ûÍê±Ï ÇĞ»»µ½µĞÈË
	if (m_pMainRole != nullptr)
	{
		if (GameManager::GetInstance()->CheckNoDyingActor())
		{
			if(m_pMainRole->m_pFSM->GetStatus() == Actor_Stand::Instance())
			{
				GameManager::GetInstance()->RoundPassed();
			}
		}	

		m_pMainRole->update(dt);
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
bool PlayerManager::CheckNoDyingActor()
{
	if (m_pMainRole != nullptr && m_pMainRole->m_pFSM->GetStatus() != Actor_Die::Instance())
	{
		return true;
	}

	return false;
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
	// add by Hitman [5/20/2015]
	Camp::GetCamp(CampType_Player)->RegisterUnit(m_pMainRole);
	//
	MessageListenerManager::Instance()->RegisterMessageListener(m_pMainRole);

}
//-------------------------------------------------------
StandbyHero* PlayerManager::RandomStandbyHero()
{
	return nullptr;
}
//-------------------------------------------------------
void PlayerManager::ClearMainRoleWeightList()
{
	m_MainRoleWeightList.clear();
}
void PlayerManager::AddWeightToList(GameActionType pActType, int nWeight)
{
	m_MainRoleWeightList.push_back(std::make_pair(pActType,nWeight));
}

void PlayerManager::HeroDied()
{
	SoldierManager::Instance()->UnregisterSoldier(m_pMainRole);
	// add by Hitman [5/20/2015]
	Camp::GetCamp(CampType_Player)->UnregisterUnit(m_pMainRole->GetCampIndex());
	//
	MessageListenerManager::Instance()->UnregisterMessageListene(m_pMainRole);
}

//-------------------------------------------------------
