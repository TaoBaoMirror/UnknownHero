/********************************************************************
	created:	2015/07/09
	created:	9:7:2015   0:13
	filename: 	E:\UnknownHero\Classes\Game\Goal_Rest.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	Goal_Rest
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Goal_Rest_h__
#define Goal_Rest_h__

#pragma warning (disable:4786)

#include "Goal/Goal_Composite.h"
#include "Vector2D.h"
#include "GridPos.h"
#include "Goal_Type.h"

class Monster;
class Soldier;
class Goal_Rest: public Goal<Monster>
{
public:
	Goal_Rest(Monster* pBot);

	void Activate();
	int  Process();
	void Terminate();

	bool HandleMessage(const Telegram& msg);
};

#endif // Goal_Rest_h__
