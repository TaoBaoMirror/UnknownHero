#include "StaticCreature.h"

StaticCreature::StaticCreature():Soldier(0),m_bFaceDirect(false)
{

}

StaticCreature::~StaticCreature()
{

}

void StaticCreature::Init()
{

}

void StaticCreature::GetHurt( const DamageData& damageData )
{

}

void StaticCreature::update( float delta )
{
	cocos2d::CCSprite::update(delta);

	if (m_pFSM != nullptr)
	{
		m_pFSM->update(delta);
	}	
}

cocos2d::Animate* StaticCreature::createAnimation( StaticCreatureAnimType Atype,float delay /*= 0.2f*/ )
{
	return nullptr;
}

void StaticCreature::SetResource( std::string name )
{
	if (m_framesDict.size() == 0)
	{
		int numAnim = m_ActionsFrameCount.size();
		m_framesDict.clear();
		for (int i = 0; i < numAnim; ++i)
		{
			cocos2d::Vector<cocos2d::SpriteFrame*> temp; //= new cocos2d::Vector<cocos2d::SpriteFrame*>();

			int numAction = m_ActionsFrameCount.at(i).asInt();
			for (int k = 0; k < numAction; ++k)
			{
				std::string frameName = ActionsName[i];

				std::stringstream ss;
				ss<<k; 
				std::string kStr = ss.str();
				frameName = name + "_" + frameName + "_" + kStr + ".png";

				cocos2d::SpriteFrame* spriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);

				if (spriteframe != nullptr)
				{
					temp.pushBack(spriteframe);
				}
				//
				if (k == numAction - 1)
				{
					if (temp.size() != 0)
					{
						m_framesDict.insert(std::pair<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>>(ActionsName[i],temp));
					}
					break;
				}
			}
		}
	}

	std::string initName = name + "_" + ActionsName[0] + "_0.png";
	initWithSpriteFrameName(initName);
	cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(initName);
}

void StaticCreature::UpdateToCCWorldPos()
{

}

void StaticCreature::ActorStandStart()
{

}

void StaticCreature::ActorStandUpdate( float dt )
{

}

void StaticCreature::ActorStandEnd()
{

}

void StaticCreature::ActorDieStart()
{

}

void StaticCreature::ActorDieUpdate( float dt )
{

}

void StaticCreature::ActorDieEnd()
{

}

void StaticCreature::ActorHurtStart()
{

}

void StaticCreature::ActorHurtUpdate( float dt )
{

}

void StaticCreature::ActorHurtEnd()
{

}

void StaticCreature::BeginMove()
{

}

void StaticCreature::EndMove()
{

}

void StaticCreature::SetActionFrame()
{

}
