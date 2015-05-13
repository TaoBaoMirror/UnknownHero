#include "ActorFSM.h"

#include "Actor/Actor.h"
#include "Actor/ActorStatus.h"


ActorFSM::ActorFSM(Actor* pActor)
{
	m_pActor = pActor;
	m_ActorStatus = nullptr;
}


ActorFSM::~ActorFSM(void)
{
}

void ActorFSM::SetStatus(ActorStatus* status)
{
	if (m_ActorStatus != nullptr)
	{
		m_ActorStatus->Exit(m_pActor);
	}

	m_ActorStatus = status;

	m_ActorStatus->Enter(m_pActor);
}

ActorStatus* ActorFSM::GetStatus()
{
	return m_ActorStatus;
}

void ActorFSM::update(float dt)
{
	if (m_ActorStatus != nullptr)
	{
		m_ActorStatus->Execute(m_pActor,dt);
	}
}