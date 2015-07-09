/********************************************************************
	created:	2015/07/08
	created:	8:7:2015   10:24
	filename: 	E:\UnknownHero\Classes\Game\StaticCreature.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	StaticCreature
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef StaticCreature_h__
#define StaticCreature_h__

#include "cocos2d.h"
#include "CreatureBase.h"
#include "Soldier.h"


#include "GeneralFSM.h"

class StaticCreature : public Soldier, public cocos2d::Sprite
{
protected:
	enum  StaticCreatureAnimType
	{
		StaticCreatureAnim_Stand = 0,
		StaticCreatureAnim_Die,
		//---------------------------
		StaticCreatureAnim_SP1,
		StaticCreatureAnim_SP2,
		StaticCreatureAnim_SP3,
	};
public:
	StaticCreature();
	~StaticCreature();
	//
	virtual void Init() override ;
	virtual void GetHurt(const DamageData& damageData) override;
	virtual void update(float delta) override;
	//
	cocos2d::Animate*	createAnimation(StaticCreatureAnimType Atype,float delay = 0.2f);
	virtual void SetActionFrame();
	void SetResource(std::string name);	
	void UpdateToCCWorldPos();
	//
	virtual void ActorStandStart();
	virtual void ActorStandUpdate(float dt);
	virtual void ActorStandEnd();
	//
	virtual void ActorDieStart();
	virtual void ActorDieUpdate(float dt);
	virtual void ActorDieEnd();
	//
	virtual void ActorHurtStart();
	virtual void ActorHurtUpdate(float dt);
	virtual void ActorHurtEnd();
	//这个移动是瞬间的，也就是说 设置在什么位置
	virtual void BeginMove();
	virtual void EndMove();
	//
	virtual void playDieAnimation(){};
	virtual void playStandAnimation(){};
	//
protected:
	GeneralFSM<StaticCreature>*		m_pFSM;
	//
	std::map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>> m_framesDict;

	std::vector<std::string> ActionsName;

	cocos2d::ValueVector m_ActionsFrameCount;	

	bool m_bFaceDirect; //true left; false right
};

//////////////////////////////////////////////////////////////////////////

class StaticCreature_Stand : public GeneralStatus<StaticCreature>
{
public:
	static StaticCreature_Stand* Instance();

	virtual void Enter(StaticCreature* pActor) override;
	virtual void Execute(StaticCreature* pActor, float dt) override;
	virtual void Exit(StaticCreature* pActor) override;
private:
	static StaticCreature_Stand* m_instance;
};

class StaticCreature_Die : public GeneralStatus<StaticCreature>
{
public:
	static StaticCreature_Die* Instance();

	virtual void Enter(StaticCreature* pActor) override;
	virtual void Execute(StaticCreature* pActor, float dt) override;
	virtual void Exit(StaticCreature* pActor) override;
private:
	static StaticCreature_Die* m_instance;
};

class StaticCreature_Hurt : public GeneralStatus<StaticCreature>
{
public:
	static StaticCreature_Hurt* Instance();

	virtual void Enter(StaticCreature* pActor) override;
	virtual void Execute(StaticCreature* pActor, float dt) override;
	virtual void Exit(StaticCreature* pActor) override;
private:
	static StaticCreature_Hurt* m_instance;
};


#endif // StaticCreature_h__
