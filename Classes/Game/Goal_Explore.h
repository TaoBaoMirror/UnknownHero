/********************************************************************
	created:	2015/03/14
	created:	14:3:2015   23:43
	filename: 	E:\cyvasse\TestAI\Goal_Explore.h
	file path:	E:\cyvasse\TestAI
	file base:	Goal_Explore
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Goal_Explore_h__
#define Goal_Explore_h__

#pragma warning (disable:4786)

#include "Goal/Goal_Composite.h"
#include "Vector2D.h"
#include "GridPos.h"
#include "Goal_Type.h"


class Soldier;

class Goal_Explore : public Goal_Composite<Soldier>
{
private:

	GridPos  m_CurrentDestination;

	//set to true when the destination for the exploration has been established
	bool      m_bDestinationIsSet;

public:

	Goal_Explore(Soldier* pOwner):Goal_Composite<Soldier>(pOwner,
		goal_explore),
		m_bDestinationIsSet(false)
	{}


	void Activate();

	int Process();

	void Terminate(){}

	bool HandleMessage(const Telegram& msg);
};

#endif // Goal_Explore_h__
