#ifndef __MONSTER_SHORT_H__
#define __MONSTER_SHORT_H__

#include "Actor/Monster.h"

class Monster_Short : public Monster
{
public:
	Monster_Short(void);
	~Monster_Short(void);

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

	virtual void AIThink(float dt) override;

	virtual void CalcDie() override;
	//----------------------------------------
	//----------------------------------------------
	void InitSkill();
	//----------------------------------------------

};

#endif //__MONSTER_SHORT_H__
