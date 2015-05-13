#ifndef __ACTOR_STATUS_H__
#define __ACTOR_STATUS_H__

#include "Actor/Actor.h"

class ActorStatus
{
public:
	virtual void Enter(Actor* pActor){}
	virtual void Execute(Actor* pActor, float dt){}
	virtual void Exit(Actor* pActor){}
};
//--------------------------------------------------------------
class Actor_Ready : public ActorStatus
{
public:
	static Actor_Ready* Instance();

	virtual void Enter(Actor* pActor) override;
	virtual void Execute(Actor* pActor, float dt) override;
	virtual void Exit(Actor* pActor) override;
private:
	static Actor_Ready* m_instance;
};
//--------------------------------------------------------------
class Actor_Stand : public ActorStatus
{
public:
	static Actor_Stand* Instance();

	virtual void Enter(Actor* pActor) override;
	virtual void Execute(Actor* pActor, float dt) override;
	virtual void Exit(Actor* pActor) override;
private:
	static Actor_Stand* m_instance;
};
//--------------------------------------------------------------
class Actor_Move : public ActorStatus
{
public:
	static Actor_Move* Instance();

	virtual void Enter(Actor* pActor) override;
	virtual void Execute(Actor* pActor, float dt) override;
	virtual void Exit(Actor* pActor) override;
private:
	static Actor_Move* m_instance;
};
//--------------------------------------------------------------
class Actor_Attack : public ActorStatus
{
public:
	static Actor_Attack* Instance();

	virtual void Enter(Actor* pActor) override;
	virtual void Execute(Actor* pActor, float dt) override;
	virtual void Exit(Actor* pActor) override;
private:
	static Actor_Attack* m_instance;
};
//--------------------------------------------------------------
class Actor_Die : public ActorStatus
{
public:
	static Actor_Die* Instance();

	virtual void Enter(Actor* pActor) override;
	virtual void Execute(Actor* pActor, float dt) override;
	virtual void Exit(Actor* pActor) override;
private:
	static Actor_Die* m_instance;
};
//--------------------------------------------------------------
class Actor_Win : public ActorStatus
{
public:
	static Actor_Win* Instance();

	virtual void Enter(Actor* pActor) override;
	virtual void Execute(Actor* pActor, float dt) override;
	virtual void Exit(Actor* pActor) override;
private:
	static Actor_Win* m_instance;
};
//--------------------------------------------------------------

#endif //__ACTOR_STATUS_H__