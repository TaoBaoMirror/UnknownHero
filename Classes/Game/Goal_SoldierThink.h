/********************************************************************
	created:	2015/03/13
	created:	13:3:2015   14:36
	filename: 	E:\cyvasse\TestAI\Goal_SoldierThink.h
	file path:	E:\cyvasse\TestAI
	file base:	Goal_SoldierThink
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Goal_Think_h__
#define Goal_Think_h__

#include <vector>
#include <string>
#include "Goal/Goal_Composite.h"
#include "Goal_Evaluator.h"
#include "GridPos.h"

class Monster;
class Goal_SoldierThink:public Goal_Composite<Monster>
{
private:
	typedef std::vector< Goal_Evaluator<Monster>* >   GoalEvaluators;
	GoalEvaluators  m_Evaluators;
public:
	Goal_SoldierThink(Monster*);
	~Goal_SoldierThink();
	//
	void Arbitrate();

	//returns true 如果所给的意图并不在子意图列表的最前面
	bool notPresent(unsigned int GoalType)const;

	int  Process();
	void Activate();
	void Terminate(){}

	//上层的意图类型
	void AddGoal_MoveToPosition(const GridPos& gpos);
	void AddGoal_GetItem(unsigned int ItemType);
	void AddGoal_Explore();
	void AddGoal_AttackTarget();
	void AddGoal_Rest();
protected:
	

};

#endif // Goal_Think_h__
