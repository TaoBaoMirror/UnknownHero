#ifndef __BOSS_H__
#define __BOSS_H__

#include "Actor/Actor.h"

enum BossType
{
	BossType_GoblinKing = 0,
};

class Boss : public Actor
{
public:
	Boss(void);
	~Boss(void);
	//----------------------------------------
	virtual void update(float delta);
	//------------------------------
	virtual void playMoveAnimation() override;
	virtual void playAttackAnimation() override;
	virtual void playStandAnimation() override;

	//----------------------------------------
	virtual void BossInit(){}
	virtual void InitSkills() override{}
	//------------------------------
	
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
protected:

};

#endif//__BOSS_H__