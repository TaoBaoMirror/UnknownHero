/********************************************************************
	created:	2015/03/15
	created:	15:3:2015   10:16
	filename: 	E:\cyvasse\TestAI\Goal_MoveStep.h
	file path:	E:\cyvasse\TestAI
	file base:	Goal_MoveStep
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Goal_MoveStep_h__
#define Goal_MoveStep_h__

#pragma warning (disable:4786)

#include "Goal/Goal_Composite.h"
#include "Vector2D.h"
#include "GridPos.h"
#include "Goal_Type.h"
#include "Soldier.h"

class Monster;
class Goal_MoveStep : public Goal<Monster>
{
private:

	GridPos From;

	GridPos To;

public:

	Goal_MoveStep(Monster* pBot,
		const GridPos&   from,
		const GridPos&   to); 

	void Activate();
	int  Process();
	void Terminate();

	bool HandleMessage(const Telegram& msg);
};

#endif // Goal_MoveStep_h__
