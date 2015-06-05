#include "EnemyManager.h"

#include "Actor/ActorStatus.h"
#include "Scene/GameManager.h"

#include "Data/TableManager.h"
#include "Game/SoldierManager.h"
#include "Game/Camp.h"

#include "Messaging/MessageListenerManager.h"
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
	//1 ��������ǰ�������ŵ���,�ҵ����Ѿ�����,�����������
	if (m_pCurEnemy != nullptr && m_pCurEnemy->m_pFSM->GetStatus() == Actor_Die::Instance())
	{
		//���ڿ���������� ��������������
		//m_pCurEnemy->destory();

		//�����������
		m_pCurEnemy = nullptr;
	}

	if (m_pCurEnemy != nullptr && m_pCurEnemy->m_pFSM->GetStatus() == Actor_Ready::Instance())
	{
		m_pCurEnemy->AIThink(dt);
	}

	//2 ��һ����ǰҪ���Ƶĵ���
	//�����������⶯���ĵ���
	if (m_pCurEnemy == nullptr)
	{
		//������û������
		for (int i=0; i<m_SpecialRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_SpecialRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurEnemy = pActor;
				
				//�ҵ���һ�����е�actor,��ô����AI��������
				pActor->AIThink(dt);
				break;
			}
		}
	}

	//Զ�̵���
	if (m_pCurEnemy == nullptr)
	{
		//������û������
		for (int i=0; i<m_LongRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_LongRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurEnemy = pActor;

				//�ҵ���һ�����е�actor,��ô����AI��������
				pActor->AIThink(dt);
				//pActor->MoveRight();
				break;
			}
		}
	}

	//���̵���
	if (m_pCurEnemy == nullptr)
	{
		//������û������
		for (int i=0; i<m_ShortRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_ShortRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurEnemy = pActor;

				//�ҵ���һ�����е�actor,��ô����AI��������
				pActor->AIThink(dt);
				break;
			}
		}
	}
	
	//3 ����Ƿ����е��˶��Ѿ��ж�����
	//�ж���ɵı�׼�ǽ���Stand״̬
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

	//�������
	for (int i=0; i<m_SpecialRangeMonsters.size(); ++i)
	{
		Actor* pActor = m_SpecialRangeMonsters.at(i);
		if (pActor != nullptr)
		{
			pActor->m_pFSM->SetStatus(Actor_Ready::Instance());
		}
	}

	//Զ�̵���
	for (int i=0; i<m_LongRangeMonsters.size(); ++i)
	{
		Actor* pActor = m_LongRangeMonsters.at(i);
		if (pActor != nullptr)
		{
			pActor->m_pFSM->SetStatus(Actor_Ready::Instance());
		}
	}	

	//���̵���
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
void EnemyManager::ClearCurEnemy(Actor* checkActor)
{
	if (checkActor == m_pCurEnemy)
	{
		m_pCurEnemy = nullptr;
	}
}
//-------------------------------------------------------
Monster* EnemyManager::CreateMonster(int monsterID)
{
	//1 ���ݹ���ID ���� ��ȡ���������Ϣ

	int monsterType = TableManager::GetInstance()->GetTableIntData(TableType::Table_Monster,"MonsterType",monsterID);

	//2 ���ݹ������� �����������

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
	// add by Hitman [5/26/2015]
	MessageListenerManager::Instance()->RegisterMessageListener(pMonster);

	//3 ���ݹ������(MonsterType) ���������ֱ��������������

	return pMonster;
}
Monster* EnemyManager::CreateSpecialMonster(int monsterID)
{
	//������˲�ͬ�ĵ��� ����Ҫ���ֵ��� ���ֱ𴴽�
	Monster_Special* pMonster = (Monster_Special*)Monster_Special::createWithMonsterID(monsterID);

	m_SpecialRangeMonsters.push_back(pMonster);

	return pMonster;
}
Monster* EnemyManager::CreateLongMonster(int monsterID)
{
	Monster_Long* pMonster = (Monster_Long*)Monster_Long::createWithMonsterID(monsterID);

	m_LongRangeMonsters.push_back(pMonster);

	return pMonster;
}
Monster* EnemyManager::CreateShortMonster(int monsterID)
{
	Monster_Short* pMonster = (Monster_Short*)Monster_Short::createWithMonsterID(monsterID);

	m_ShortRangeMonsters.push_back(pMonster);

	return pMonster;
}

void EnemyManager::RemoveShortMonster(Monster_Short* pMonster)
{
	std::vector<Monster_Short*>::iterator it = m_ShortRangeMonsters.begin();
	for ( ; it != m_ShortRangeMonsters.end(); ++it)
	{
		if ((*it) == pMonster)
		{
			m_ShortRangeMonsters.erase(it);
			break;
		}
	}
}

void EnemyManager::RemoveLongMonster(Monster_Long* pMonster)
{
	std::vector<Monster_Long*>::iterator it = m_LongRangeMonsters.begin();
	for ( ; it != m_LongRangeMonsters.end(); ++it)
	{
		if ((*it) == pMonster)
		{
			m_LongRangeMonsters.erase(it);
			break;
		}
	}
}

void EnemyManager::RemoveSpecialMonster(Monster_Special* pMonster)
{
	std::vector<Monster_Special*>::iterator it = m_SpecialRangeMonsters.begin();
	for ( ; it != m_SpecialRangeMonsters.end(); ++it)
	{
		if ((*it) == pMonster)
		{
			m_SpecialRangeMonsters.erase(it);
			break;
		}
	}
}
//-------------------------------------------------------
//void EnemyManager::CreateMonstersAtLayer(cocos2d::TMXLayer* pLayer, int zOrder)
//{
//	//1 ���ݹ���ID ���� ��ȡ���������Ϣ
//
//	//2 ���ݹ������� �����������
//
//	//3 ���ݹ������(MonsterType) ���������ֱ��������������
//}
//-------------------------------------------------------
bool EnemyManager::IsAnyBodyHere()
{
	if (m_ShortRangeMonsters.size() != 0 ||
		m_LongRangeMonsters.size() != 0 ||
		m_SpecialRangeMonsters.size() != 0)
	{
		return true;
	}
	return false;
}
//-------------------------------------------------------
bool EnemyManager::CheckNoDyingActor()
{
	for (int i=0; i<m_SpecialRangeMonsters.size(); ++i)
	{
		Actor* pActor = m_SpecialRangeMonsters.at(i);
		if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Die::Instance())
		{
			return false;
		}
	}

	//Զ�̵���
	for (int i=0; i<m_LongRangeMonsters.size(); ++i)
	{
		Actor* pActor = m_LongRangeMonsters.at(i);
		if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Die::Instance())
		{
			return false;
		}
	}	

	//���̵���
	for (int i=0; i<m_ShortRangeMonsters.size(); ++i)
	{
		Actor* pActor = m_ShortRangeMonsters.at(i);
		if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Die::Instance())
		{
			return false;
		}
	}

	return true;
}

void EnemyManager::SetActiontTimesInOneRound( int n )
{

	for(int i = 0 ;i< m_ShortRangeMonsters.size();++i)
	{
		Actor* monster = m_ShortRangeMonsters[i];
		monster->SetActionTimesInRound(n);
	}

	for(int i = 0 ;i< m_LongRangeMonsters.size();++i)
	{
		Actor* monster = m_LongRangeMonsters[i];
		monster->SetActionTimesInRound(n);
	}

	for(int i = 0 ;i< m_SpecialRangeMonsters.size();++i)
	{
		Actor* monster = m_SpecialRangeMonsters[i];
		monster->SetActionTimesInRound(n);
	}
}

//-------------------------------------------------------
