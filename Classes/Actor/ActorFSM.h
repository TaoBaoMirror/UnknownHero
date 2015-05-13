#ifndef __ACTOR_FSM_H__
#define __ACTOR_FSM_H__

class Actor;
class ActorStatus;

class ActorFSM
{
public:
	ActorFSM(Actor* pActor);
	~ActorFSM(void);

	void SetStatus(ActorStatus* pActorST);

	ActorStatus* GetStatus();

	void update(float dt);

private:
	ActorStatus* m_ActorStatus;

	Actor* m_pActor;
};

#endif //__ACTOR_FSM_H__

