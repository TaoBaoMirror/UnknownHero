#ifndef __GAME_ACTION_SYSTEM_H__
#define __GAME_ACTION_SYSTEM_H__

#include "Action/GameAction.h"
#include <map>
#include <vector>

enum GameActionType
{
	GameActionType_Sword = 0,	 //近身攻击
	GameActionType_Jump,		 //移动多个格子
	GameActionType_Bomb,		 //炸弹
	GameActionType_Coin,		 //金币
	GameActionType_Cure,		 //加血
	GameActionType_MonsterStrong,//Debuf 场景内怪物增强1~n级
	GameActionType_MonsterAppear,//Debuf 场景内出现更多的怪物
	GameActionType_TrapAppear,	 //Debuf 场景内出现很多看不见的陷阱
	GameActionType_Magic_Fire,	 //法师的魔法 1级攻击距离2 攻击范围1 2级距离3 aoe 3级距离4 aoe 4级距离5
	GameActionType_Magic_Freeze, //法师的魔法 冻结 1~n回合
	GameActionType_Bow,			 //射出的弓箭 高等级可以射穿
	GameActionType_Trap_Hurt,	 //捕兽夹:敌人碰上后,掉血且一回合不能行动
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
	
	void RollGroup(int nGroupID);	//某一组往下转动一格

	void RoleMachine();				//转老虎机

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

	int m_MaxUseGroup; //目前已经投入使用了几组

	GameAction* m_Action_Group1[Total_Action];
	GameAction* m_Action_Group2[Total_Action];
	GameAction* m_Action_Group3[Total_Action];
	GameAction* m_Action_Group4[Total_Action];
	GameAction* m_Action_Group5[Total_Action];

	bool m_MustRoll[5];

	bool m_LockSystem;
};

#endif//__GAME_ACTION_SYSTEM_H__
