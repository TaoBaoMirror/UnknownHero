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
	//1 检测如果当前正控制着敌人,且敌人已经死亡,放弃这个控制
	if (m_pCurNPC != nullptr && m_pCurNPC->m_pFSM->GetStatus() == Actor_Die::Instance())
	{
		//不在控制这个敌人 且让他自我销毁
		//m_pCurNPC->destory();

		//放弃这个控制
		m_pCurNPC = nullptr;
	}

	//2 找一个当前要控制的敌人
	//首先是有特殊动作的敌人
	if (m_pCurNPC == nullptr)
	{
		//查找有没有正在
		for (int i=0; i<m_SpecialRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_ShortRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurNPC = pActor;

				//找到了一个空闲的actor,那么就让AI驱动他吧
				//pActor->AIThink();
			}
		}
	}

	//远程敌人
	if (m_pCurNPC == nullptr)
	{
		//查找有没有正在
		for (int i=0; i<m_LongRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_ShortRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurNPC = pActor;

				//找到了一个空闲的actor,那么就让AI驱动他吧
				//pActor->AIThink();
			}
		}
	}

	//近程敌人
	if (m_pCurNPC == nullptr)
	{
		//查找有没有正在
		for (int i=0; i<m_ShortRangeMonsters.size(); ++i)
		{
			Actor* pActor = m_ShortRangeMonsters.at(i);
			if (pActor != nullptr && pActor->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				m_pCurNPC = pActor;

				//找到了一个空闲的actor,那么就让AI驱动他吧
				//pActor->AIThink();
			}
		}
	}

	//3 检测是否所有敌人都已经行动过了
	//行动完成的标准是进入Stand状态
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
		Actor* pActor = m_ShortRangeMonsters.at(i);
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

//-------------------------------------------------------
bool NPCManager::IsAnyBodyHere()
{
	return false;
}
//-------------------------------------------------------

