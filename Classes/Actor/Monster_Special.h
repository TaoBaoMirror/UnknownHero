#ifndef __MONSTER_SPECIAL_H__
#define __MONSTER_SPECIAL_H__

#include "Actor/Monster.h"

class Monster_Special : public Monster
{
public:
	Monster_Special(void);
	~Monster_Special(void);

	//----------------------------------------
	virtual void ActorReadyStart() override;
	virtual void ActorReadyUpdate(float dt) override;
	virtual void ActorReadyEnd() override;

	virtual void ActorStandStart() override;
	virtual void ActorStandUpdate(float dt) override;
	virtual void ActorStandEnd() override;

	virtual void ActorMoveStart() override;
	virtual void ActorMoveUpdate(float dt) override;
	virtual void ActorMoveEnd() override;

	virtual void ActorAttackStart() override;
	virtual void ActorAttackUpdate(float dt) override;
	virtual void ActorAttackEnd() override;

	virtual void ActorDieStart() override;
	virtual void ActorDieUpdate(float dt) override;
	virtual void ActorDieEnd() override;

	virtual void ActorWinStart() override;
	virtual void ActorWinUpdate(float dt) override;
	virtual void ActorWinEnd() override;
	//----------------------------------------

	virtual void AIThink() override;

	//----------------------------------------
};

#endif //__MONSTER_H__
