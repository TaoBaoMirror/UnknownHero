/********************************************************************
	created:	2015/03/15
	created:	15:3:2015   9:36
	filename: 	E:\cyvasse\TestAI\Goal_FollowPath.h
	file path:	E:\cyvasse\TestAI
	file base:	Goal_FollowPath
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Goal_FollowPath_h__
#define Goal_FollowPath_h__

#include "Goal/Goal_Composite.h"
#include "Vector2D.h"
#include "GridPos.h"
#include "Goal_Type.h"

class Soldier;
class Monster;
class Goal_FollowPath : public Goal_Composite<Monster>
{
private:

	//a local copy of the path returned by the path planner
	std::list<GridPos>  m_Path;

public:

	Goal_FollowPath(Monster* pBot, std::list<GridPos> path);

	//the usual suspects
	void Activate();
	int Process();
	void Terminate(){}
};

#endif // Goal_FollowPath_h__
