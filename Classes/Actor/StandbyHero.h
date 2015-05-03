#ifndef __STANDBY_HERO_H__
#define __STANDBY_HERO_H__

#include "cocos2d.h"

class SelectHeroLayer;

enum StandbyHeroAnim
{
	StandbyHero_Stand = 0,
	StandbyHero_Move,
};
class StandbyHero : public cocos2d::Sprite
{
public:
	StandbyHero(void);
	virtual ~StandbyHero(void);

	cocos2d::Rect getRect();

	bool initWithTexture(cocos2d::Texture2D* aTexture);

	virtual void onEnter() override;
	virtual void onExit() override;

	bool containsTouchLocation(cocos2d::Touch* touch);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	static StandbyHero* createWithTextureHeroID(int id);

	void playMoveAnimation();
	
	void playStandAnimation();

	void SetSelectHeroLayer(SelectHeroLayer* pLayer){m_pSelectHeroLayer = pLayer;}

public:
	//Ãû×Ö
	std::string m_HeroName;
	int m_HeroID;

	std::string m_Career;

	int m_HP;

	int m_StartLevel;	

protected:
	void SetResource(std::string name);

	SelectHeroLayer* m_pSelectHeroLayer;

	std::map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>> m_framesDict;

	std::vector<std::string> ActionsName;

	cocos2d::ValueVector m_ActionsFrameCount;
};

#endif //__STANDBY_HERO_H__
