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
#include "Soldier.h"

class Goal_Evaluator;
class Goal_SoldierThink:public Goal_Composite<Soldier>
{
private:
	typedef std::vector<Goal_Evaluator*>   GoalEvaluators;
	GoalEvaluators  m_Evaluators;
public:
	Goal_SoldierThink(Soldier*);
	~Goal_SoldierThink();
	//
	void Arbitrate();

	//returns true �����������ͼ����������ͼ�б����ǰ��
	bool notPresent(unsigned int GoalType)const;

	int  Process();
	void Activate();
	void Terminate(){}

	//�ϲ����ͼ����
	void AddGoal_MoveToPosition(const GridPos& gpos);
	void AddGoal_GetItem(unsigned int ItemType);
	void AddGoal_Explore();
	void AddGoal_AttackTarget();

	//������ͼ�б�����������ƶ���ͼ
	void QueueGoal_MoveToPosition(const GridPos& pos);
protected:
	

};

#endif // Goal_Think_h__
