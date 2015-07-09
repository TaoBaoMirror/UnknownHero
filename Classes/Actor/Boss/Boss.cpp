#include "Boss.h"
#include "Data\TableManager.h"


Boss::Boss(void):Actor()
{
}


Boss::~Boss(void)
{
}

void Boss::playMoveAnimation() 
{
	setFlippedX(m_bFaceDirect);
	cocos2d::Animate* animate = createAnimation(ActorAnimType::ActorAnim_Move);
	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animate);
	pRepeat->setTag((int)ActorAnimType::ActorAnim_Move);
	this->runAction(pRepeat);
}

void Boss::playAttackAnimation()
{
	setFlippedX(m_bFaceDirect);
	cocos2d::Animate* animate = createAnimation(ActorAnimType::ActorAnim_Attack);
	this->runAction(animate);

}

void Boss::playStandAnimation()
{
	setFlippedX(m_bFaceDirect);
	cocos2d::Animate* animate = createAnimation(ActorAnimType::ActorAnim_Stand);
	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animate);
	pRepeat->setTag((int)ActorAnimType::ActorAnim_Stand);
	this->runAction(pRepeat);
}


//------------------------------------------------------------------------------------
void Boss::ActorReadyStart()
{
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Boss::ActorReadyUpdate(float dt)
{

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
