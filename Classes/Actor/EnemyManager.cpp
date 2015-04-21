#include "EnemyManager.h"

//-------------------------------------------------------
EnemyManager* EnemyManager::m_Instance = nullptr;

EnemyManager* EnemyManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new EnemyManager();
	}

	return m_Instance;
}
//-------------------------------------------------------
EnemyManager::EnemyManager(void)
{
}


EnemyManager::~EnemyManager(void)
{
}
//-------------------------------------------------------
void EnemyManager::Update(float dt)
{
	;
}
//-------------------------------------------------------
void EnemyManager::CreateMonster(int monsterID)
{
	//1 根据怪物ID 读表 读取怪物基本信息

	//2 根据怪物类型 创建怪物对象

	//3 根据怪物射程(MonsterType) 将怪物对象分别放入三个队列中
}
//-------------------------------------------------------
bool EnemyManager::IsAnyBodyHere()
{
	return false;
}
//-------------------------------------------------------
