/********************************************************************
	created:	2015/03/15
	created:	15:3:2015   11:21
	filename: 	E:\cyvasse\TestAI\Goal_AttackTarget.h
	file path:	E:\cyvasse\TestAI
	file base:	Goal_AttackTarget
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Goal_AttackTarget_h__
#define Goal_AttackTarget_h__

#include "Goal/Goal_Composite.h"
#include "Vector2D.h"
#include "GridPos.h"
#include "Goal_Type.h"
#include "Soldier.h"

class Goal_AttackTarget : public Goal_Composite<Soldier>
{
public:

	Goal_AttackTarget(Soldier* pOwner):Goal_Composite<Soldier>(pOwner, goal_attack_target)
	{}

	void Activate();

	int  Process();

	void Terminate(){m_iStatus = completed;}

};

#endif // Goal_AttackTarget_h__
