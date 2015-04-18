/********************************************************************
	created:	2015/03/15
	created:	15:3:2015   11:53
	filename: 	E:\cyvasse\TestAI\AttackTargetGoal_Evaluator.h
	file path:	E:\cyvasse\TestAI
	file base:	AttackTargetGoal_Evaluator
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef AttackTargetGoal_Evaluator_h__
#define AttackTargetGoal_Evaluator_h__

#include "Goal_Evaluator.h"

class Soldier;

class AttackTargetGoal_Evaluator : public Goal_Evaluator
{ 
public:

	AttackTargetGoal_Evaluator(double bias):Goal_Evaluator(bias){}

	double CalculateDesirability(Soldier* pBot);

	void  SetGoal(Soldier* pBot);

};


#endif // AttackTargetGoal_Evaluator_h__
