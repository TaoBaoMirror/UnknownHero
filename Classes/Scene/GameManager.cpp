#include "GameManager.h"


GameManager* GameManager::m_Instance = nullptr;

GameManager* GameManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameManager();
	}

	return m_Instance;
}

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}
