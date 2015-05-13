#include "EnemyManager.h"

#include "Actor/ActorStatus.h"
#include "Scene/GameManager.h"

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

	//2 ��һ����ǰҪ���Ƶĵ���
	//�����������⶯���ĵ���
	if (m_pCurEnemy == nullptr)
	{
		//������û������
		for (int i=0; i<m_SpecialRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_ShortRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurEnemy = pActor;
				
				//�ҵ���һ�����е�actor,��ô����AI��������
				//pActor->AIThink();
			}
		}
	}

	//Զ�̵���
	if (m_pCurEnemy == nullptr)
	{
		//������û������
		for (int i=0; i<m_LongRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_ShortRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurEnemy = pActor;

				//�ҵ���һ�����е�actor,��ô����AI��������
				//pActor->AIThink();
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
				//pActor->AIThink();
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
		Actor* pActor = m_ShortRangeMonsters.at(i);
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
