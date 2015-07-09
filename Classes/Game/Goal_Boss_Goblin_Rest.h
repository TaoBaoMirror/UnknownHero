/********************************************************************
	created:	2015/07/09
	created:	9:7:2015   17:49
	filename: 	E:\UnknownHero\Classes\Game\Goal_Boss_Goblin_Rest.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	Goal_Boss_Goblin_Rest
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef Goal_Boss_Goblin_Rest_h__
#define Goal_Boss_Goblin_Rest_h__

#pragma warning (disable:4786)

#include "Goal/Goal_Composite.h"
#include "Vector2D.h"
#include "GridPos.h"
#include "Goal_Type.h"
#include "Actor/Boss/Boss_GoblinKing.h"

class Goal_Boss_Goblin_Rest: public Goal<Boss_GoblinKing>
{
	Boss_GoblinKing*	m_pTargetBot;
public:
	Goal_Boss_Goblin_Rest(Boss_GoblinKing* pBot);

	void Activate();
	int  Process();
	void Terminate();

	bool HandleMessage(const Telegram& msg);
};

#endif // Goal_Boss_Goblin_Rest_h__
