#include "StandbyHero.h"
#include "Scene/SelectHeroLayer.h"

//----------------------------------------------
StandbyHero::StandbyHero(void)
{
	std::string test[2] = {"stand", "move"};
	//ActionsName = test; 
	for (int i=0; i<2; ++i)
	{
		ActionsName.push_back(test[i]);
	}

	int frameanim[2] = { 2,1 };
	m_ActionsFrameCount.clear();
	for (int i=0; i<2; ++i)
	{
		m_ActionsFrameCount.push_back(cocos2d::Value(frameanim[i]));
	}
}


StandbyHero::~StandbyHero(void)
{
}

cocos2d::Rect StandbyHero::getRect()
{
	auto s = getTexture()->getContentSize();
	return cocos2d::Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}


StandbyHero* StandbyHero::createWithTextureHeroID(int id)
{
	StandbyHero* pStandbyHero = new StandbyHero();

	pStandbyHero->m_HeroID = id;

	std::stringstream ss;
	ss<<id; 
	std::string idStr = ss.str();

	std::string tex_hero = "Hero_Standby_" + idStr;

	pStandbyHero->SetResource(tex_hero);
	pStandbyHero->autorelease();

	return pStandbyHero;
}

void StandbyHero::SetResource(std::string name)
{
	//Texture
	//init animation


	if (m_framesDict.size() == 0)
	{
		int numAnim = m_ActionsFrameCount.size();
		//m_framesDict = new cocos2d::Map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>*>();
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

bool StandbyHero::initWithTexture(cocos2d::Texture2D* aTexture)
{
	bool ret = cocos2d::Sprite::initWithTexture(aTexture);

	return ret;
}

void StandbyHero::onEnter()
{
	cocos2d::Sprite::onEnter();

	// Register Touch Event
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(StandbyHero::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void StandbyHero::onExit()
{
	//    auto director = Director::getInstance();
	//    director->getTouchDispatcher()->removeDelegate(this);
	cocos2d::Sprite::onExit();
}    

bool StandbyHero::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	CCLOG("StandbyHero::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);

	if ( !containsTouchLocation(touch) ) return false;

	//通知主界面或者游戏管理器 当前选择的英雄
	if (m_pSelectHeroLayer != nullptr)
	{
		m_pSelectHeroLayer->ClickHero(this);
	}
	
	//

	return true;
}

bool StandbyHero::containsTouchLocation(cocos2d::Touch* touch)
{
	return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

void StandbyHero::playMoveAnimation()
{
	std::string name = ActionsName[(int)StandbyHeroAnim::StandbyHero_Move];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);

	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animaction);

	this->runAction(pRepeat);
}

void StandbyHero::playStandAnimation()
{
	std::string name = ActionsName[(int)StandbyHeroAnim::StandbyHero_Stand];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);

	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animaction);

	this->runAction(pRepeat);
}