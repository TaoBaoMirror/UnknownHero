#include "EnemyManager.h"

#include "Actor/ActorStatus.h"
#include "Scene/GameManager.h"

#include "Data/TableManager.h"
#include "Game/SoldierManager.h"
#include "Game/Camp.h"
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
	m_pCurEnemy = nullptr;
}


EnemyManager::~EnemyManager(void)
{
}
//-------------------------------------------------------
void EnemyManager::Update(float dt)
{
	//1 检测如果当前正控制着敌人,且敌人已经死亡,放弃这个控制
	if (m_pCurEnemy != nullptr && m_pCurEnemy->m_pFSM->GetStatus() == Actor_Die::Instance())
	{
		//不在控制这个敌人 且让他自我销毁
		//m_pCurEnemy->destory();

		//放弃这个控制
		m_pCurEnemy = nullptr;
	}

	if (m_pCurEnemy != nullptr && m_pCurEnemy->m_pFSM->GetStatus() == Actor_Ready::Instance())
	{
		m_pCurEnemy->AIThink();
	}

	//2 找一个当前要控制的敌人
	//首先是有特殊动作的敌人
	if (m_pCurEnemy == nullptr)
	{
		//查找有没有正在
		for (int i=0; i<m_SpecialRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_SpecialRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurEnemy = pActor;
				
				//找到了一个空闲的actor,那么就让AI驱动他吧
				pActor->AIThink();
			}
		}
	}

	//远程敌人
	if (m_pCurEnemy == nullptr)
	{
		//查找有没有正在
		for (int i=0; i<m_LongRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_LongRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurEnemy = pActor;

				//找到了一个空闲的actor,那么就让AI驱动他吧
				pActor->AIThink();
				//pActor->MoveRight();
			}
		}
	}

	//近程敌人
	if (m_pCurEnemy == nullptr)
	{
		//查找有没有正在
		for (int i=0; i<m_ShortRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_ShortRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurEnemy = pActor;

				//找到了一个空闲的actor,那么就让AI驱动他吧
				pActor->AIThink();
			}
		}
	}
	
	//3 检测是否所有敌人都已经行动过了
	//行动完成的标准是进入Stand状态
	if (m_pCurEnemy != nullptr)
	{
		if (m_pCurEnemy->m_pFSM->GetStatus() == Actor_Stand::Instance())
		{
			m_pCurEnemy = nullptr;
		}
	}
	else
	{
		GameManager::GetInstance()->RoundPassed();
	}
}
//-------------------------------------------------------
void EnemyManager::ReadyFight()
{
	m_pCurEnemy = nullptr;

	//特殊敌人
	for (int i=0; i<m_SpecialRangeMonsters.size(); ++i)
	{
		Actor* pActor = m_SpecialRangeMonsters.at(i);
		if (pActor != nullptr)
		{
			pActor->m_pFSM->SetStatus(Actor_Ready::Instance());
		}
	}

	//远程敌人
	for (int i=0; i<m_LongRangeMonsters.size(); ++i)
	{
		Actor* pActor = m_LongRangeMonsters.at(i);
		if (pActor != nullptr)
		{
			pActor->m_pFSM->SetStatus(Actor_Ready::Instance());
		}
	}	

	//近程敌人
	for (int i=0; i<m_ShortRangeMonsters.size(); ++i)
	{
		Actor* pActor = m_ShortRangeMonsters.at(i);
		if (pActor != nullptr)
		{
			pActor->m_pFSM->SetStatus(Actor_Ready::Instance());
		}
	}
}
//-------------------------------------------------------
Monster* EnemyManager::CreateMonster(int monsterID)
{
	//1 根据怪物ID 读表 读取怪物基本信息

	int monsterType = TableManager::GetInstance()->GetTableIntData(TableType::Table_Monster,"MonsterType",monsterID);

	//2 根据怪物类型 创建怪物对象

	Monster* pMonster = nullptr;

	MonsterType mType = (MonsterType)monsterType;
	switch (mType)
	{
	case MonsterType::MonsterType_Special:
		pMonster = CreateSpecialMonster(monsterID);
		break;
	case MonsterType::MonsterType_LongRange:
		pMonster = CreateLongMonster(monsterID);
		break;
	case MonsterType::MonsterType_ShortRange:
		pMonster = CreateShortMonster(monsterID);
		break;
	default:
		break;
	}

	SoldierManager::Instance()->RegisterSoldier(pMonster);
	// add by Hitman [5/20/2015]
	Camp::GetCamp(CampType_Monster)->RegisterUnit(pMonster);

	//3 根据怪物射程(MonsterType) 将怪物对象分别放入三个队列中

	return pMonster;
}
Monster* EnemyManager::CreateSpecialMonster(int monsterID)
{
	//如果做了不同的敌人 这里要区分敌人 并分别创建
	Monster* pMonster = Monster_Special::createWithMonsterID(monsterID);

	m_SpecialRangeMonsters.push_back(pMonster);

	return pMonster;
}
Monster* EnemyManager::CreateLongMonster(int monsterID)
{
	Monster* pMonster = Monster_Long::createWithMonsterID(monsterID);

	m_LongRangeMonsters.push_back(pMonster);

	return pMonster;
}
Monster* EnemyManager::CreateShortMonster(int monsterID)
{
	Monster* pMonster = Monster_Short::createWithMonsterID(monsterID);

	m_ShortRangeMonsters.push_back(pMonster);

	return pMonster;
}
//-------------------------------------------------------
//void EnemyManager::CreateMonstersAtLayer(cocos2d::TMXLayer* pLayer, int zOrder)
//{
//	//1 根据怪物ID 读表 读取怪物基本信息
//
//	//2 根据怪物类型 创建怪物对象
//
//	//3 根据怪物射程(MonsterType) 将怪物对象分别放入三个队列中
//}
//-------------------------------------------------------
bool EnemyManager::IsAnyBodyHere()
{
	return false;
}
//-------------------------------------------------------
