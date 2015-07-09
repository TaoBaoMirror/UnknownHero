/********************************************************************
	created:	2015/07/08
	created:	8:7:2015   15:09
	filename: 	E:\UnknownHero\Classes\Game\GeneralStatus.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	GeneralStatus
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef GeneralStatus_h__
#define GeneralStatus_h__

template <class entity_type>
class GeneralStatus
{
public:
	virtual void Enter(entity_type* pActor){}
	virtual void Execute(entity_type* pActor, float dt){}
	virtual void Exit(entity_type* pActor){}
};

#endif // GeneralStatus_h__
