#include "Boss.h"
#include "Data\TableManager.h"


Boss::Boss(void)
{
}


Boss::~Boss(void)
{
}

void Boss::playMoveAnimation() 
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_Move];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);

	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animaction);
	pRepeat->setTag((int)ActorAnimType::ActorAnim_Move);

	this->runAction(pRepeat);
}

void Boss::playAttackAnimation()
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_Attack];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);
	this->runAction(animaction);

}
//------------------------------------------------------------------------------------
void Boss::ActorReadyStart()
{
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Boss::ActorReadyUpdate(float dt)
{
	if ( m_NextUseBossSkillRound >0 )
	{
		m_NextUseBossSkillRound--;
	}
	else if(m_bCanUseBossSkill == true)
	{
		UseBossSkill();
	}
}
void Boss::ActorReadyEnd()
{
	;
}
//------------------------------------------------------------------------------------
void Boss::ActorStandStart()
{
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Boss::ActorStandUpdate(float dt)
{
	;
}
void Boss::ActorStandEnd()
{
	;
}
//-----
void Boss::ActorMoveStart()
{
	playMoveAnimation();
}
void Boss::ActorMoveUpdate(float dt)
{
	;
}
void Boss::ActorMoveEnd()
{
	;
}
//-----
void Boss::ActorAttackStart()
{
}
void Boss::ActorAttackUpdate(float dt)
{
	;
}
void Boss::ActorAttackEnd()
{
}
//-----
void Boss::ActorDieStart()
{
}
void Boss::ActorDieUpdate(float dt)
{
	;
}
void Boss::ActorDieEnd()
{
	;
}
//-----
void Boss::ActorWinStart()
{
}
void Boss::ActorWinUpdate(float dt)
{
	;
}
void Boss::ActorWinEnd()
{
	;
}

void Boss::update( float delta )
{
	Actor::update(delta);	
}
