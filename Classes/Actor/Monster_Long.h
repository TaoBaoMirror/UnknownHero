#ifndef __MONSTER_LONG_H__
#define __MONSTER_LONG_H__

#include "Actor/Monster.h"

class Monster_Long : public Monster
{
public:
	Monster_Long(void);
	~Monster_Long(void);

	static Monster* createWithMonsterID(int id);
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
	//如果是远程怪物，则 攻击计算 是子弹触发的
	void CalcAttack( AttackData* pAtkData );
	void CalcDie();

	//----------------------------------------
	void ShootBullet();
	virtual void CallBack_AttackFinish() override;

};

#endif //__MONSTER_LONG_H__
