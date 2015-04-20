#include "NPCManager.h"

//-------------------------------------------------------
NPCManager* NPCManager::m_Instance = nullptr;

NPCManager* NPCManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new NPCManager();
	}

	return m_Instance;
}
//-------------------------------------------------------

NPCManager::NPCManager(void)
{
}


NPCManager::~NPCManager(void)
{
}
//-------------------------------------------------------
void NPCManager::Update(float dt)
{
	;
}
//-------------------------------------------------------

//-------------------------------------------------------
bool NPCManager::IsAnyBodyHere()
{
	return false;
}
//-------------------------------------------------------

