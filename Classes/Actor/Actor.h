#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"
#include "Actor/ActorBody.h"
#include "Game/Soldier.h"

#include "Actor/ActorFSM.h"

class Actor : public Soldier, public cocos2d::Sprite
{
protected:
	enum  ActorAnimType
	{
		ActorAnim_Stand = 0,
		ActorAnim_Move,
		ActorAnim_Attack,
		ActorAnim_Die,
		ActorAnim_Win,
		//------
		ActorAnim_SP1,
		ActorAnim_SP2,
		ActorAnim_SP3,
	};
public:
	Actor();
	~Actor(void);

	// add by Hitman [7/8/2015]
	virtual void FinishRound() override;


	virtual void update(float delta) override;
	virtual void BeginTraval() override;
	virtual void EndTraval() override;
	virtual bool TravalTo(const GridPos& GPos) override;

	virtual void Attack(Soldier* other , int number) override;
	virtual void Attack( const GridPos& gPos , int number ) override;
	//virtual void UseDeputyWeapon(Soldier* other, int DWeaponNumber) override;
	virtual void GetHurt(const DamageData& damageData) override;

	// add by Hitman [7/7/2015]
	// 这些动画播放是为了比如剧情什么时候 强制播放的，其他情况，在动作完成后有回调的时候，请用get/create动画的函数
	virtual void playMoveAnimation(){};
	virtual void playAttackAnimation(){};
	virtual void playDieAnimation(){};
	virtual void playStandAnimation(){};


	cocos2d::Animate*	createAnimation(ActorAnimType Atype,float delay = 0.2f);

	//------
	void SetResource(std::string name);	
	void UpdateToCCWorldPos();

	//------
	virtual void ActorReadyStart(){}
	virtual void ActorReadyUpdate(float dt){}
	virtual void ActorReadyEnd(){}

	virtual void ActorStandStart(){}
	virtual void ActorStandUpdate(float dt){}
	virtual void ActorStandEnd(){}

	virtual void ActorMoveStart(){}
	virtual void ActorMoveUpdate(float dt){}
	virtual void ActorMoveEnd(){}

	virtual void ActorAttackStart();
	virtual void ActorAttackUpdate(float dt);
	virtual void ActorAttackEnd();

	virtual void ActorDieStart();
	virtual void ActorDieUpdate(float dt);
	virtual void ActorDieEnd();

	virtual void ActorWinStart(){}
	virtual void ActorWinUpdate(float dt){}
	virtual void ActorWinEnd(){}
	//------
	virtual void AIThink(float dt);

	virtual void CalcAttack( AttackData* pAtkData );

	virtual void CallBack_AttackFinish() override;

	virtual void CalcDie();
	//------
	virtual void ActorHurtStart(){}
	virtual void ActorHurtUpdate(float dt){}
	virtual void ActorHurtEnd(){}
	//------

protected:
	virtual void showAttackRange(const std::vector<GridPos>&	AttackGPosList) override;

public:
	ActorFSM* m_pFSM;
	//
	int		m_OneRoundActionTimes;

	void	SetActionTimesInRound(int n);

	// add by Hitman [5/19/2015]
protected:
	AttackData* m_pTempAtkData;

protected:
	std::map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>> m_framesDict;

	std::vector<std::string> ActionsName;

	cocos2d::ValueVector m_ActionsFrameCount;	

	static const float g_ActorMoveTime;

	bool m_bFaceDirect; //true left; false right
};

#endif //__ACTOR_H__