#include "GameActionSystem.h"
#include "base\ccMacros.h"

#include "Action/GameAction_Sword.h"
#include "GameAction_Jump.h"
#include "GameAction_Bomb.h"
#include "GameAction_Coin.h"
#include "GameAction_MonsterStrong.h"
#include "GameAction_Bow.h"


GameActionSystem* GameActionSystem::m_Instance = nullptr;

GameActionSystem* GameActionSystem::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameActionSystem();
	}

	return m_Instance;
}

GameActionSystem::GameActionSystem(void)
{
	for (int i=0; i<(int)Total_Action; ++i)
	{
		m_Action_Group1[i] = nullptr;
	}
	for (int i=0; i<(int)Total_Action; ++i)
	{
		m_Action_Group2[i] = nullptr;
	}
	for (int i=0; i<(int)Total_Action; ++i)
	{
		m_Action_Group3[i] = nullptr;
	}
	for (int i=0; i<(int)Total_Action; ++i)
	{
		m_Action_Group4[i] = nullptr;
	}
	for (int i=0; i<(int)Total_Action; ++i)
	{
		m_Action_Group5[i] = nullptr;
	}

	m_MaxUseGroup = 3;
}


GameActionSystem::~GameActionSystem(void)
{
}
//-----------------------------------------------------------
GameAction* GameActionSystem::RandomAction()
{
	float m = 0;
	float randvalue =CCRANDOM_0_1(); //r为0至1的随机数
	std::map<GameActionType,GameAction*>::iterator it = m_ActionReserve.begin();
	for (; it!=m_ActionReserve.end();++it)
	{
		float wt = it->second->GetWeight();
		if (m_TotalWeight != 0.0f)
		{
			float rate = wt/m_TotalWeight;
			m = m + rate;
			if(randvalue<=m) 
			{
				return it->second;
			}
		}		
	}

	return nullptr;
}

void GameActionSystem::CalculateActionsRate()
{
	m_TotalWeight = 0.0f;
	std::map<GameActionType,GameAction*>::iterator it = m_ActionReserve.begin();
	for (; it!=m_ActionReserve.end();++it)
	{
		float wt = it->second->GetWeight();
		m_TotalWeight += wt;
	}
}

void GameActionSystem::InitCreateReserveWithList(std::vector<std::pair<GameActionType,int>> types)
{
	std::vector<std::pair<GameActionType,int>>::iterator it = types.begin();
	for ( ; it != types.end(); ++it)
	{
		CreateActionAtReserve((*it).first, (*it).second);
	}
	
}

void GameActionSystem::CreateActionAtReserve(GameActionType type, int weight)
{
	GameAction* pNewAction = nullptr;

	switch (type)
	{
	case GameActionType_Sword:
		{
			pNewAction = new GameAction_Sword((int)type);
		}
		break;
	case GameActionType_Jump:
		{
			pNewAction = new GameAction_Jump((int)type);
		}
		break;
	case GameActionType_Bomb:
		{
			pNewAction = new GameAction_Bomb((int)type);
		}
		break;
	case GameActionType_Coin:
		{
			pNewAction = new GameAction_Coin((int)type);
		}
		break;
	case GameActionType_Cure:
		break;
	case GameActionType_MonsterStrong:
		{
			pNewAction = new GameAction_MonsterStrong((int)type);
		}
		break;
	case GameActionType_MonsterAppear:
		break;
	case GameActionType_TrapAppear:
		break;
	case GameActionType_Magic_Fire:
		break;
	case GameActionType_Magic_Freeze:
		break;
	case GameActionType_Bow:
		{
			pNewAction = new GameAction_Bow((int)type);
		}
		break;
	case GameActionType_Trap_Hurt:
		break;
	default:
		break;
	}

	if (pNewAction != nullptr)
	{
		pNewAction->SetWeight(weight);
		m_ActionReserve[type] = pNewAction;
	}	
}

void GameActionSystem::ClickAction(int GroupID)
{
	if (GroupID == 0)
	{
		if (m_Action_Group1[CurAction] != nullptr)
		{
			m_Action_Group1[CurAction]->ClickAction();
		}
	}
	else if (GroupID == 1)
	{
		if (m_Action_Group2[CurAction] != nullptr)
		{
			m_Action_Group2[CurAction]->ClickAction();
		}
	}
	else if (GroupID == 2)
	{
		if (m_Action_Group3[CurAction] != nullptr)
		{
			m_Action_Group3[CurAction]->ClickAction();
		}
	}
	else if (GroupID == 3)
	{
		if (m_Action_Group4[CurAction] != nullptr)
		{	
			m_Action_Group4[CurAction]->ClickAction();
		}
	}
	else if (GroupID == 4)
	{
		if (m_Action_Group5[CurAction] != nullptr)
		{			
			m_Action_Group5[CurAction]->ClickAction();
		}
	}
}

void GameActionSystem::UseAction(int GroupID)
{
	int level = 1;
	bool mustRoll[5];
	for (int i=0; i<5; ++i)
	{
		mustRoll[i] = false;
	}

	if (GroupID == 0)
	{
		if (m_Action_Group1[CurAction] != nullptr)
		{
			mustRoll[0] = true;
			if (m_Action_Group2[CurAction] != nullptr && 
				m_Action_Group1[CurAction]->GetTypeID() == m_Action_Group2[CurAction]->GetTypeID())
			{
				mustRoll[1] = true;
				level++;
			}
			if (m_Action_Group3[CurAction] != nullptr && 
				m_Action_Group1[CurAction]->GetTypeID() == m_Action_Group3[CurAction]->GetTypeID())
			{
				mustRoll[2] = true;
				level++;
			}
			if (m_Action_Group4[CurAction] != nullptr && 
				m_Action_Group1[CurAction]->GetTypeID() == m_Action_Group4[CurAction]->GetTypeID())
			{
				mustRoll[3] = true;
				level++;
			}
			if (m_Action_Group5[CurAction] != nullptr && 
				m_Action_Group1[CurAction]->GetTypeID() == m_Action_Group5[CurAction]->GetTypeID())
			{
				mustRoll[4] = true;
				level++;
			}
			m_Action_Group1[CurAction]->UseAction(level);
		}
	}
	else if (GroupID == 1)
	{
		if (m_Action_Group2[CurAction] != nullptr)
		{
			mustRoll[1] = true;
			if (m_Action_Group1[CurAction] != nullptr && 
				m_Action_Group2[CurAction]->GetTypeID() == m_Action_Group1[CurAction]->GetTypeID())
			{
				mustRoll[0] = true;
				level++;
			}
			if (m_Action_Group3[CurAction] != nullptr && 
				m_Action_Group2[CurAction]->GetTypeID() == m_Action_Group3[CurAction]->GetTypeID())
			{
				mustRoll[2] = true;
				level++;
			}
			if (m_Action_Group4[CurAction] != nullptr && 
				m_Action_Group2[CurAction]->GetTypeID() == m_Action_Group4[CurAction]->GetTypeID())
			{
				mustRoll[3] = true;
				level++;
			}
			if (m_Action_Group5[CurAction] != nullptr && 
				m_Action_Group2[CurAction]->GetTypeID() == m_Action_Group5[CurAction]->GetTypeID())
			{
				mustRoll[4] = true;
				level++;
			}
			m_Action_Group2[CurAction]->UseAction(level);
		}
	}
	else if (GroupID == 2)
	{
		if (m_Action_Group3[CurAction] != nullptr)
		{
			mustRoll[2] = true;
			if (m_Action_Group1[CurAction] != nullptr && 
				m_Action_Group3[CurAction]->GetTypeID() == m_Action_Group1[CurAction]->GetTypeID())
			{
				mustRoll[0] = true;
				level++;
			}
			if (m_Action_Group2[CurAction] != nullptr && 
				m_Action_Group3[CurAction]->GetTypeID() == m_Action_Group2[CurAction]->GetTypeID())
			{
				mustRoll[1] = true;
				level++;
			}
			if (m_Action_Group4[CurAction] != nullptr && 
				m_Action_Group3[CurAction]->GetTypeID() == m_Action_Group4[CurAction]->GetTypeID())
			{
				mustRoll[3] = true;
				level++;
			}
			if (m_Action_Group5[CurAction] != nullptr && 
				m_Action_Group3[CurAction]->GetTypeID() == m_Action_Group5[CurAction]->GetTypeID())
			{
				mustRoll[4] = true;
				level++;
			}
			m_Action_Group3[CurAction]->UseAction(level);
		}
	}
	else if (GroupID == 3)
	{
		mustRoll[3] = true;
		if (m_Action_Group4[CurAction] != nullptr)
		{
			if (m_Action_Group1[CurAction] != nullptr && 
				m_Action_Group4[CurAction]->GetTypeID() == m_Action_Group1[CurAction]->GetTypeID())
			{
				mustRoll[0] = true;
				level++;
			}
			if (m_Action_Group2[CurAction] != nullptr && 
				m_Action_Group4[CurAction]->GetTypeID() == m_Action_Group2[CurAction]->GetTypeID())
			{
				mustRoll[1] = true;
				level++;
			}
			if (m_Action_Group3[CurAction] != nullptr && 
				m_Action_Group4[CurAction]->GetTypeID() == m_Action_Group3[CurAction]->GetTypeID())
			{
				mustRoll[2] = true;
				level++;
			}
			if (m_Action_Group5[CurAction] != nullptr && 
				m_Action_Group4[CurAction]->GetTypeID() == m_Action_Group5[CurAction]->GetTypeID())
			{
				mustRoll[4] = true;
				level++;
			}
			m_Action_Group4[CurAction]->UseAction(level);
		}
	}
	else if (GroupID == 4)
	{
		mustRoll[4] = true;
		if (m_Action_Group5[CurAction] != nullptr)
		{			
			if (m_Action_Group1[CurAction] != nullptr && 
				m_Action_Group5[CurAction]->GetTypeID() == m_Action_Group1[CurAction]->GetTypeID())
			{
				mustRoll[0] = true;
				level++;
			}
			if (m_Action_Group2[CurAction] != nullptr && 
				m_Action_Group5[CurAction]->GetTypeID() == m_Action_Group2[CurAction]->GetTypeID())
			{
				mustRoll[1] = true;
				level++;
			}
			if (m_Action_Group3[CurAction] != nullptr && 
				m_Action_Group5[CurAction]->GetTypeID() == m_Action_Group3[CurAction]->GetTypeID())
			{
				mustRoll[2] = true;
				level++;
			}
			if (m_Action_Group4[CurAction] != nullptr && 
				m_Action_Group5[CurAction]->GetTypeID() == m_Action_Group4[CurAction]->GetTypeID())
			{
				mustRoll[3] = true;
				level++;
			}
			m_Action_Group5[CurAction]->UseAction(level);
		}
	}

	//2 ui表现不同使用等级的特效

	//3 滚动老虎机使用了技能那组
	if (mustRoll[0] == true)
	{
		RollGroup(0);
	}
	if (mustRoll[1] == true)
	{
		RollGroup(1);
	}
	if (mustRoll[2] == true)
	{
		RollGroup(2);
	}
	if (mustRoll[3] == true)
	{
		RollGroup(3);
	}
	if (mustRoll[4] == true)
	{
		RollGroup(4);
	}
	
}

void GameActionSystem::RollGroup(int nGroupID)
{
	GameAction* newAction = RandomAction();
	if (newAction != nullptr)
	{
		if (nGroupID == 0)
		{
			//one by one
			m_Action_Group1[PreAction] = m_Action_Group1[CurAction];
			m_Action_Group1[CurAction] = m_Action_Group1[NextAction];
			m_Action_Group1[NextAction] = m_Action_Group1[NextNextAction];
			m_Action_Group1[NextNextAction] = newAction;
		}
		else if (nGroupID == 1)
		{
			//one by one
			m_Action_Group2[PreAction] = m_Action_Group2[CurAction];
			m_Action_Group2[CurAction] = m_Action_Group2[NextAction];
			m_Action_Group2[NextAction] = m_Action_Group2[NextNextAction];
			m_Action_Group3[NextNextAction] = newAction;
		}
		else if (nGroupID == 2)
		{
			//one by one
			m_Action_Group3[PreAction] = m_Action_Group3[CurAction];
			m_Action_Group3[CurAction] = m_Action_Group3[NextAction];
			m_Action_Group3[NextAction] = m_Action_Group3[NextNextAction];
			m_Action_Group3[NextNextAction] = newAction;
		}
		else if (nGroupID == 3)
		{
			//one by one
			m_Action_Group4[PreAction] = m_Action_Group4[CurAction];
			m_Action_Group4[CurAction] = m_Action_Group4[NextAction];
			m_Action_Group4[NextAction] = m_Action_Group4[NextNextAction];
			m_Action_Group4[NextNextAction] = newAction;
		}
		else if (nGroupID == 4)
		{
			//one by one
			m_Action_Group5[PreAction] = m_Action_Group5[CurAction];
			m_Action_Group5[CurAction] = m_Action_Group5[NextAction];
			m_Action_Group5[NextAction] = m_Action_Group5[NextNextAction];
			m_Action_Group5[NextNextAction] = newAction;
		}
	}	
}

void GameActionSystem::RoleMachine()
{
	//group 1
	if(m_MaxUseGroup >= 1)
	{
		//one by one
		//m_Action_Group1[PrePreAction] = RandomAction();
		m_Action_Group1[PreAction] = RandomAction();
		m_Action_Group1[CurAction] = RandomAction();
		m_Action_Group1[NextAction] = RandomAction();
		m_Action_Group1[NextNextAction] = RandomAction();
	}
	//group 2
	if(m_MaxUseGroup >= 2)
	{
		//one by one
		//m_Action_Group2[PrePreAction] = RandomAction();
		m_Action_Group2[PreAction] = RandomAction();
		m_Action_Group2[CurAction] = RandomAction();
		m_Action_Group2[NextAction] = RandomAction();
		m_Action_Group2[NextNextAction] = RandomAction();
	}
	//group 3
	if(m_MaxUseGroup >= 3)
	{
		//one by one
		//m_Action_Group3[PrePreAction] = RandomAction();
		m_Action_Group3[PreAction] = RandomAction();
		m_Action_Group3[CurAction] = RandomAction();
		m_Action_Group3[NextAction] = RandomAction();
		m_Action_Group3[NextNextAction] = RandomAction();
	}
	//group 4
	if(m_MaxUseGroup >= 4)
	{
		//one by one
		//m_Action_Group4[PrePreAction] = RandomAction();
		m_Action_Group4[PreAction] = RandomAction();
		m_Action_Group4[CurAction] = RandomAction();
		m_Action_Group4[NextAction] = RandomAction();
		m_Action_Group4[NextNextAction] = RandomAction();
	}
	//group 5
	if(m_MaxUseGroup >= 5)
	{
		//one by one
		//m_Action_Group5[PrePreAction] = RandomAction();
		m_Action_Group5[PreAction] = RandomAction();
		m_Action_Group5[CurAction] = RandomAction();
		m_Action_Group5[NextAction] = RandomAction();
		m_Action_Group5[NextNextAction] = RandomAction();
	}
}

GameAction* GameActionSystem::GetAction(int groupID, int actionOrder)
{
	if (actionOrder >= (int)Total_Action || actionOrder < 0)
	{
		return nullptr;
	}

	if (groupID == 0)
	{
		return m_Action_Group1[actionOrder];
	}
	else if(groupID == 1)
	{
		return m_Action_Group2[actionOrder];
	}
	else if(groupID == 2)
	{
		return m_Action_Group3[actionOrder];
	}
	else if(groupID == 3)
	{
		return m_Action_Group4[actionOrder];
	}
	else if(groupID == 4)
	{
		return m_Action_Group5[actionOrder];
	}

	return nullptr;
}