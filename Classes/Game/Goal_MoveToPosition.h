/********************************************************************
	created:	2015/03/14
	created:	14:3:2015   22:56
	filename: 	E:\cyvasse\TestAI\Goal_MoveToPosition.h
	file path:	E:\cyvasse\TestAI
	file base:	Goal_MoveToPosition
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Goal_MoveToPosition_h__
#define Goal_MoveToPosition_h__

#pragma warning (disable:4786)

#include "Goal/Goal_Composite.h"
#include "Vector2D.h"
#include "GridPos.h"
#include "Goal_Type.h"
#include "Soldier.h"


class Goal_MoveToPosition : public Goal_Composite<Soldier>
{
private:

	GridPos m_Destination;

public:

	Goal_MoveToPosition(Soldier* pBot,
		GridPos   gpos):

	Goal_Composite<Soldier>(pBot,
		goal_move_to_position),
		m_Destination(gpos)
	{}

	void Activate();
	int  Process();
	void Terminate();

	//bool HandleMessage(const Telegram& msg);
};





#endif
