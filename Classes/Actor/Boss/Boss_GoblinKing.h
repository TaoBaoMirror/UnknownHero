#ifndef __BOSS_GOBLINKING_H__
#define __BOSS_GOBLINKING_H__

//-lib
#include "Goal/Goal_Composite.h"
//- game
#include "Actor/Boss/Boss.h"
#include "Game/Goal_Evaluator.h"
#include "Game/GridPosArea.h"

enum BOSSGoblinKingState
{
	BOSSGoblinKingState_Rest = 0,
	BOSSGoblinKingState_Summon,
	BOSSGoblinKingState_Shake,
	BOSSGoblinKingState_Stun,
};


class GoblinKing_Think;
class Boss_GoblinKing : public Boss
{
public:
	Boss_GoblinKing(void);
	~Boss_GoblinKing(void);
	//-----------------
	virtual void update(float delta) override;
	//override Boss class
	virtual void BossInit() override;
	virtual void InitSkills() override;
	virtual void OnDeployChunk()override;
	virtual void FinishRound() override;
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
	cocos2d::Animate*  createUseMachineAnimation();
	cocos2d::Animate*  createAttackAnimation();
	cocos2d::Animate*  createSummonAnimation();
	cocos2d::Animate*  createShakeAnimation();

	void ShootBullet();	//����ӵ�
	virtual void CallBack_AttackFinish() override;	//Զ��Ҫ��д�������~~
	void CalcSummon(int ilevel);	//callback�к�
	void CalcShake(int ilevel);		//callback����
	//-----------------
	//void UseMachine();
	void SkillAttack();		//����
	void SkillSummon(int ilevel);		//�ٻ�
	void SkillShake(int ilevel);		//����
	//----------AI----
	virtual void CreateBrain() override;
	virtual void AIThink(float dt) override;
	virtual bool HandleMessage(const Telegram& telegram) override;
	//------------------------
	void SetActionFrame();

	//------------------------
	static Boss* CreateBoss();
	
	//------------------------
protected:
	// 0 top,1 left, 2 down, 3 right
	GridPos getDir(int dir);

	bool m_bBallistic; //�Ƿ��Ѿ�����

	int m_SummonMonsterIDs[3];

	GridPosArea		mObstructArea;

	GoblinKing_Think* m_pBrain;
};

//////////////////////////////////////////////////////////////////////////
//
//	Goblin Status
//
//////////////////////////////////////////////////////////////////////////


#endif //__BOSS_GIANT_H__