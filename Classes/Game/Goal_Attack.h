/********************************************************************
	created:	2015/03/15
	created:	15:3:2015   11:40
	filename: 	E:\cyvasse\TestAI\Goal_Attack.h
	file path:	E:\cyvasse\TestAI
	file base:	Goal_Attack
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Goal_Attack_h__
#define Goal_Attack_h__

#pragma warning (disable:4786)

#include "Goal/Goal_Composite.h"
#include "Vector2D.h"
#include "GridPos.h"
#include "Goal_Type.h"
#include "Soldier.h"

class Goal_Attack: public Goal<Soldier>
{
	Soldier*	m_pTargetBot;
public:
	Goal_Attack(Soldier* pBot,Soldier* pTargetBot);

	void Activate();
	int  Process();
	void Terminate();

	bool HandleMessage(const Telegram& msg);
};


#endif // Goal_Attack_h__
