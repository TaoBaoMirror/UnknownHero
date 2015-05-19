#include "ActorStatus.h"

//----------------------------------------------------------------------------
Actor_Ready* Actor_Ready::m_instance = nullptr;
Actor_Ready* Actor_Ready::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Actor_Ready();
	}
	return m_instance;
}

void Actor_Ready::Enter(Actor* pActor) 
{
	pActor->ActorReadyStart();
}

void Actor_Ready::Execute(Actor* pActor, float dt) 
{
	pActor->ActorReadyUpdate(dt);
}

void Actor_Ready::Exit(Actor* pActor) 
{
	pActor->ActorReadyEnd();
}
//----------------------------------------------------------------------------
Actor_Stand* Actor_Stand::m_instance = nullptr;
Actor_Stand* Actor_Stand::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Actor_Stand();
	}
	return m_instance;
}

void Actor_Stand::Enter(Actor* pActor) 
{
	pActor->ActorStandStart();
}

void Actor_Stand::Execute(Actor* pActor, float dt) 
{
	pActor->ActorStandUpdate(dt);
}

void Actor_Stand::Exit(Actor* pActor) 
{
	pActor->ActorStandEnd();
}
//----------------------------------------------------------------------------
Actor_Move* Actor_Move::m_instance = nullptr;
Actor_Move* Actor_Move::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Actor_Move();
	}
	return m_instance;
}

void Actor_Move::Enter(Actor* pActor) 
{
	pActor->ActorMoveStart();
}

void Actor_Move::Execute(Actor* pActor, float dt) 
{
	pActor->ActorMoveUpdate(dt);
}

void Actor_Move::Exit(Actor* pActor) 
{
	pActor->ActorMoveEnd();
}

//----------------------------------------------------------------------------
Actor_Attack* Actor_Attack::m_instance = nullptr;
Actor_Attack* Actor_Attack::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Actor_Attack();
	}
	return m_instance;
}

void Actor_Attack::Enter(Actor* pActor) 
{
	pActor->ActorAttackStart();
}

void Actor_Attack::Execute(Actor* pActor, float dt) 
{
	pActor->ActorAttackUpdate(dt);
}

void Actor_Attack::Exit(Actor* pActor) 
{
	pActor->ActorAttackEnd();
}
//----------------------------------------------------------------------------
Actor_Die* Actor_Die::m_instance = nullptr;
Actor_Die* Actor_Die::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Actor_Die();
	}
	return m_instance;
}

void Actor_Die::Enter(Actor* pActor) 
{
	pActor->ActorDieStart();
}

void Actor_Die::Execute(Actor* pActor, float dt) 
{
	pActor->ActorDieUpdate(dt);
}

void Actor_Die::Exit(Actor* pActor) 
{
	pActor->ActorDieEnd();
}
//----------------------------------------------------------------------------
Actor_Win* Actor_Win::m_instance = nullptr;
Actor_Win* Actor_Win::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Actor_Win();
	}
	return m_instance;
}

void Actor_Win::Enter(Actor* pActor) 
{
	pActor->ActorWinStart();
}

void Actor_Win::Execute(Actor* pActor, float dt) 
{
	pActor->ActorWinUpdate(dt);
}

void Actor_Win::Exit(Actor* pActor) 
{
	pActor->ActorWinEnd();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
Actor_Hurt* Actor_Hurt::m_instance = nullptr;

Actor_Hurt* Actor_Hurt::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Actor_Hurt();
	}
	return m_instance;
}
void Actor_Hurt::Enter(Actor* pActor) 
{
	pActor->ActorHurtStart();
}

void Actor_Hurt::Execute(Actor* pActor, float dt) 
{
	pActor->ActorHurtUpdate(dt);
}

void Actor_Hurt::Exit(Actor* pActor) 
{
	pActor->ActorHurtEnd();
}