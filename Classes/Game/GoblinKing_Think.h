/********************************************************************
	created:	2015/07/08
	created:	8:7:2015   23:14
	filename: 	E:\UnknownHero\Classes\Game\GoblinKing_Think.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	GoblinKing_Think
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef GoblinKing_Think_h__
#define GoblinKing_Think_h__

#include <vector>
#include <string>
#include "Goal/Goal_Composite.h"
#include "Soldier.h"
#include "Actor/Boss/Boss_GoblinKing.h"

class GoblinKing_Think:public Goal_Composite<Boss_GoblinKing>
{
private:
public:
	GoblinKing_Think(Boss_GoblinKing*);
	~GoblinKing_Think();
	//
	void Arbitrate();

	//returns true 如果所给的意图并不在子意图列表的最前面
	bool notPresent(unsigned int GoalType)const;

	int  Process();
	void Activate();
	void Terminate(){}

	//上层的意图类型
	void AddGoal_Summon();
	void AddGoal_Shake();
	void AddGoal_Attack();
	void AddGoal_Rest();
	//
	virtual bool HandleMessage(const Telegram& telegram) override;

protected:
	std::queue<int>		mGoalPrefabQueue;

};

#endif // GoblinKing_Think_h__
