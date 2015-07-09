/********************************************************************
	created:	2015/07/08
	created:	8:7:2015   15:05
	filename: 	E:\UnknownHero\Classes\Game\GeneralFSM.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	GeneralFSM
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef GeneralFSM_h__
#define GeneralFSM_h__

#include "GeneralStatus.h"

template <class entity_type>
class GeneralFSM
{
public:
	GeneralFSM(entity_type* pActor);
	~GeneralFSM(void);

	void SetStatus(GeneralStatus<entity_type>* pActorST);

	GeneralStatus<entity_type>* GetStatus();

	void update(float dt);

private:
	GeneralStatus<entity_type>* m_ActorStatus;

	entity_type* m_pActor;
};

template <class entity_type>
void GeneralFSM<entity_type>::update( float dt )
{
	if (m_ActorStatus != nullptr)
	{
		m_ActorStatus->Execute(m_pActor,dt);
	}
}

template <class entity_type>
GeneralStatus<entity_type>* GeneralFSM<entity_type>::GetStatus()
{
	return m_ActorStatus;
}

template <class entity_type>
void GeneralFSM<entity_type>::SetStatus( GeneralStatus<entity_type>* pActorST )
{
	if (m_ActorStatus != nullptr)
	{
		m_ActorStatus->Exit(m_pActor);
	}

	m_ActorStatus = pActorST;

	m_ActorStatus->Enter(m_pActor);
}

template <class entity_type>
GeneralFSM<entity_type>::~GeneralFSM( void )
{

}

template <class entity_type>
GeneralFSM<entity_type>::GeneralFSM( entity_type* pActor )
{
	m_pActor = pActor;
	m_ActorStatus = nullptr;
}

#endif // GeneralFSM_h__
