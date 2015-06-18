#ifndef __GAME_ACTION_SYSTEM_H__
#define __GAME_ACTION_SYSTEM_H__

#include "Action/GameAction.h"
#include <map>
#include <vector>

enum GameActionType
{
	GameActionType_Sword = 0,	 //������
	GameActionType_Jump,		 //�ƶ��������
	GameActionType_Bomb,		 //ը��
	GameActionType_Coin,		 //���
	GameActionType_Cure,		 //��Ѫ
	GameActionType_MonsterStrong,//Debuf �����ڹ�����ǿ1~n��
	GameActionType_MonsterAppear,//Debuf �����ڳ��ָ���Ĺ���
	GameActionType_TrapAppear,	 //Debuf �����ڳ��ֺܶ࿴����������
	GameActionType_Magic_Fire,	 //��ʦ��ħ�� 1����������2 ������Χ1 2������3 aoe 3������4 aoe 4������5
	GameActionType_Magic_Freeze, //��ʦ��ħ�� ���� 1~n�غ�
	GameActionType_Bow,			 //����Ĺ��� �ߵȼ������䴩
	GameActionType_Trap_Hurt,	 //���޼�:�������Ϻ�,��Ѫ��һ�غϲ����ж�
};

enum ActionOrder
{
	NextNextAction = 0,
	NextAction,
	CurAction,
	PreAction,
	//PrePreAction,
	Total_Action,
};

class GameActionSystem
{
public:
	static GameActionSystem* GetInstance();
	~GameActionSystem(void);

	void InitCreateReserveWithList(std::vector<std::pair<GameActionType,int>> types);

	void CreateActionAtReserve(GameActionType type, int weight);

	void ClickAction(int GroupID);

	void UseAction(int GroupID);

	void CalculateActionsRate();
	
	void RollGroup(int nGroupID);	//ĳһ������ת��һ��

	void RoleMachine();				//ת�ϻ���

	void RollGroups();

	void LockSystem()	{m_LockSystem = true;}
	void UnLockSystem()	{m_LockSystem = false;}
	
	void ContinueAction();
	void OverAction();

	GameAction* GetAction(int groupID, int actionOrder);
private:
	GameActionSystem(void);

	static GameActionSystem* m_Instance;
	//--------------------------------------------
	GameAction* RandomAction();

	//--------------------------------------------
	
	//--------------------------------------------
	//----
	std::map<GameActionType,GameAction*> m_ActionReserve;
	//----
	float m_TotalWeight;

	int m_MaxUseGroup; //Ŀǰ�Ѿ�Ͷ��ʹ���˼���

	GameAction* m_Action_Group1[Total_Action];
	GameAction* m_Action_Group2[Total_Action];
	GameAction* m_Action_Group3[Total_Action];
	GameAction* m_Action_Group4[Total_Action];
	GameAction* m_Action_Group5[Total_Action];

	bool m_MustRoll[5];

	bool m_LockSystem;
};

#endif//__GAME_ACTION_SYSTEM_H__
