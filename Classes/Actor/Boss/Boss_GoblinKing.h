#ifndef __BOSS_GOBLINKING_H__
#define __BOSS_GOBLINKING_H__

#include "Actor/Boss/Boss.h"
#include <Goal/Goal_Composite.h>
#include "Game/Goal_Evaluator.h"

enum BOSSGoblinKingState
{
	BOSSGoblinKingState_Rest = 0,
	BOSSGoblinKingState_Summon,
	BOSSGoblinKingState_Shake,
	BOSSGoblinKingState_Stun,
};

class Boss_GoblinKing : public Boss
{
public:
	Boss_GoblinKing(void);
	~Boss_GoblinKing(void);

	//-----------------
	virtual void update(float delta) override;

	//-----------------
	virtual void UseBossSkill() override;

	virtual void UseBossAction( int m_ActionTypeID, int ilevel ) override;

	//-----------------
	void SetGoblinKingState(BOSSGoblinKingState st);

	//-----------------
	virtual void BossInit() override;

	virtual void InitSkills() override;

	//-----------------
	void UseMachine();

	void SkillAttack(int ilevel);

	void SkillSummon(int ilevel);

	void SkillShake(int ilevel);

	void BossOverwhelm();
	//-----------------
	//----------------------------------------------------------------
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
	//------------------------
	void  playStandAnimation();

	cocos2d::Animate* createUseMachineAnimation();
	cocos2d::Animate* createAttackAnimation();
	cocos2d::Animate*  createSummonAnimation();
	cocos2d::Animate*  createShakeAnimation();

	void CalcUseMachine(int index);	
	void CalcAttack(int ilevel);
	void CalcSummon(int ilevel);
	void CalcShake(int ilevel);
	//------------------------
	void SetActionFrame();

	//------------------------
	static Boss* CreateBoss();
	
	//------------------------
protected:
	BOSSGoblinKingState m_CurBossState;

	bool m_bBallistic; //是否已经暴走

	GridPos m_AllAttackPos[3]; //地精王的三个攻击点

	int m_SummonMonsterIDs[3];
};

#endif //__BOSS_GIANT_H__