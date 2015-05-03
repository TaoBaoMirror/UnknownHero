#include "PlayerManager.h"
#include "Game/SoldierManager.h"

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
	//���Ӣ���Ƿ��ƶ�������� ������ �л�������
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
