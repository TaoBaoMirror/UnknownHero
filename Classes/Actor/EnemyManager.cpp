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
	//1 ���ݹ���ID ���� ��ȡ���������Ϣ

	//2 ���ݹ������� �����������

	//3 ���ݹ������(MonsterType) ���������ֱ��������������
}
//-------------------------------------------------------
bool EnemyManager::IsAnyBodyHere()
{
	return false;
}
//-------------------------------------------------------
