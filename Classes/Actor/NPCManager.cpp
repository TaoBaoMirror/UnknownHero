#include "NPCManager.h"

#include "Actor/ActorStatus.h"
#include "Scene/GameManager.h"

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
	//1 ��������ǰ�������ŵ���,�ҵ����Ѿ�����,�����������
	if (m_pCurNPC != nullptr && m_pCurNPC->m_pFSM->GetStatus() == Actor_Die::Instance())
	{
		//���ڿ���������� ��������������
		//m_pCurNPC->destory();

		//�����������
		m_pCurNPC = nullptr;
	}

	//2 ��һ����ǰҪ���Ƶĵ���
	//�����������⶯���ĵ���
	if (m_pCurNPC == nullptr)
	{
		//������û������
		for (int i=0; i<m_SpecialRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_ShortRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurNPC = pActor;

				//�ҵ���һ�����е�actor,��ô����AI��������
				//pActor->AIThink();
			}
		}
	}

	//Զ�̵���
	if (m_pCurNPC == nullptr)
	{
		//������û������
		for (int i=0; i<m_LongRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_ShortRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurNPC = pActor;

				//�ҵ���һ�����е�actor,��ô����AI��������
				//pActor->AIThink();
			}
		}
	}

	//���̵���
	if (m_pCurNPC == nullptr)
	{
		//������û������
		for (int i=0; i<m_ShortRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_ShortRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurNPC = pActor;

				//�ҵ���һ�����е�actor,��ô����AI��������
				//pActor->AIThink();
			}
		}
	}

	//3 ����Ƿ����е��˶��Ѿ��ж�����
	//�ж���ɵı�׼�ǽ���Stand״̬
	if (m_pCurNPC != nullptr)
	{
		if (m_pCurNPC->m_pFSM->GetStatus() == Actor_Stand::Instance())
		{
			m_pCurNPC = nullptr;
		}
	}
	else
	{
		GameManager::GetInstance()->RoundPassed();
	}
}
//-------------------------------------------------------
void NPCManager::ReadyFight()
{
	m_pCurNPC = nullptr;

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

//-------------------------------------------------------
bool NPCManager::IsAnyBodyHere()
{
	return false;
}
//-------------------------------------------------------

