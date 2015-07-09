/********************************************************************
	created:	2015/05/26
	created:	26:5:2015   11:52
	filename: 	E:\UnknownHero\Classes\Game\Goal_HuntTarget.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	Goal_HuntTarget
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Goal_HuntTarget_h__
#define Goal_HuntTarget_h__

#include "Goal/Goal_Composite.h"
#include "Vector2D.h"
#include "GridPos.h"
#include "Goal_Type.h"

class Soldier;
class Monster;
class Goal_HuntTarget : public Goal_Composite<Monster>
{
public:

	Goal_HuntTarget(Monster* pOwner):Goal_Composite<Monster>(pOwner, goal_hunt_target)
	{}

	void Activate();

	int  Process();

	void Terminate(){m_iStatus = completed;}

};

#endif // Goal_HuntTarget_h__
