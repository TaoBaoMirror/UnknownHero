/********************************************************************
	created:	2015/03/15
	created:	15:3:2015   14:52
	filename: 	E:\cyvasse\TestAI\ExploreGoal_Evaluator.h
	file path:	E:\cyvasse\TestAI
	file base:	ExploreGoal_Evaluator
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef ExploreGoal_Evaluator_h__
#define ExploreGoal_Evaluator_h__

#include "Goal_Evaluator.h"

class Monster;

class ExploreGoal_Evaluator : public Goal_Evaluator<Monster>
{ 
public:

	ExploreGoal_Evaluator(double bias):Goal_Evaluator<Monster>(bias){}

	double CalculateDesirability(Monster* pBot);

	void  SetGoal(Monster* pBot);
};

#endif // ExploreGoal_Evaluator_h__
