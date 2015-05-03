#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"
#include "Actor/ActorBody.h"
#include "Game/Soldier.h"

class Actor : public Soldier, public cocos2d::Sprite
{
public:
	Actor(void);
	~Actor(void);

	virtual void Attack(){}
	virtual void Move(){}

	void SetResource(std::string name);	

protected:
	std::map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>> m_framesDict;

	std::vector<std::string> ActionsName;

	cocos2d::ValueVector m_ActionsFrameCount;
};

#endif //__ACTOR_H__