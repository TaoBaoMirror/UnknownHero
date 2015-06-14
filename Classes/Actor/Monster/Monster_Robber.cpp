#include "Monster_Robber.h"


Monster_Robber::Monster_Robber(void)
{
}


Monster_Robber::~Monster_Robber(void)
{
}

//------------------------------------------------------------------------------------
void Monster_Robber::ActorReadyStart()
{
	Monster_Short::ActorReadyStart();
}
void Monster_Robber::ActorReadyUpdate(float dt)
{
	Monster_Short::ActorReadyUpdate(dt);
}
void Monster_Robber::ActorReadyEnd()
{
	Monster_Short::ActorReadyEnd();
}
//-----
void Monster_Robber::ActorStandStart()
{
}
void Monster_Robber::ActorStandUpdate(float dt)
{
	;
}
void Monster_Robber::ActorStandEnd()
{
	;
}
//-----
void Monster_Robber::ActorMoveStart()
{
	playMoveAnimation();
}
void Monster_Robber::ActorMoveUpdate(float dt)
{
	;
}
void Monster_Robber::ActorMoveEnd()
{
	;
}
//-----
void Monster_Robber::ActorAttackStart()
{
}
void Monster_Robber::ActorAttackUpdate(float dt)
{
	;
}
void Monster_Robber::ActorAttackEnd()
{
	;
}
//-----
void Monster_Robber::ActorDieStart()
{
	Monster_Short::ActorDieStart();
}
void Monster_Robber::ActorDieUpdate(float dt)
{
	Monster_Short::ActorDieUpdate(dt);
}
void Monster_Robber::ActorDieEnd()
{
	Monster_Short::ActorDieEnd();
}
//-----
void Monster_Robber::ActorWinStart()
{
}
void Monster_Robber::ActorWinUpdate(float dt)
{
	;
}
void Monster_Robber::ActorWinEnd()
{
	;
}