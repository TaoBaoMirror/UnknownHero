#include "PlayerManager.h"

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
	;
}
//-------------------------------------------------------
