#include "Monster_Long.h"
#include "Data/TableManager.h"

Monster_Long::Monster_Long(void)
{
}


Monster_Long::~Monster_Long(void)
{
}

//------------------------------------------------------------------------------------
void Monster_Long::ActorReadyStart()
{
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Monster_Long::ActorReadyUpdate(float dt)
{
	;
}
void Monster_Long::ActorReadyEnd()
{
	;
}
//-----
void Monster_Long::ActorStandStart()
{
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Monster_Long::ActorStandUpdate(float dt)
{
	;
}
void Monster_Long::ActorStandEnd()
{
	;
}
//-----
void Monster_Long::ActorMoveStart()
{
	playMoveAnimation();
}
void Monster_Long::ActorMoveUpdate(float dt)
{
	;
}
void Monster_Long::ActorMoveEnd()
{
	;
}
//-----
void Monster_Long::ActorAttackStart()
{
}
void Monster_Long::ActorAttackUpdate(float dt)
{
	;
}
void Monster_Long::ActorAttackEnd()
{
	;
}
//-----
void Monster_Long::ActorDieStart()
{
}
void Monster_Long::ActorDieUpdate(float dt)
{
	;
}
void Monster_Long::ActorDieEnd()
{
	;
}
//-----
void Monster_Long::ActorWinStart()
{
}
void Monster_Long::ActorWinUpdate(float dt)
{
	;
}
void Monster_Long::ActorWinEnd()
{
	;
}
//----------------------------------------------
void Monster_Long::AIThink()
{
	Monster::AIThink();
	//
	
}
//----------------------------------------------