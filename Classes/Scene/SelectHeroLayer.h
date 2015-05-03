#ifndef __SELECT_STORY_H__
#define __SELECT_STORY_H__

#include "cocos2d.h"

#include "Actor/Hero.h"
#include "Actor/StandbyHero.h"

enum SelectHeroState
{
	SelectHero_Dialog_BeforeHeroCallOn,
	SelectHero_Dialog_CallOn,
	SelectHero_Dialog_AfterHeroCallOn,
	SelectHero_Dialog_SelectHero,
	SelectHero_Dialog_AfterSelectHero,
};

class SelectHeroLayer : public cocos2d::Layer
{
public:
	SelectHeroLayer(void);
	~SelectHeroLayer(void);

	static cocos2d::Scene* createScene();

	virtual bool init() override;

	virtual void update(float dt) override;

	virtual void onEnter() override;
	virtual void onExit() override;

	CREATE_FUNC(SelectHeroLayer);

	void CreateStandbyHeros();

	void DecideHero();

	void HeroMove();

	void HeroCallOn();

	void HeroCallOnOver(Node* sender);

	void ClickHero(StandbyHero* pHero);
public:
	static int LayerTag;

	StandbyHero* m_pStandbyHero_1;
	StandbyHero* m_pStandbyHero_2;
	StandbyHero* m_pStandbyHero_3;

	StandbyHero* m_CurSelectHero;

	SelectHeroState m_SelectST;

private:	
	cocos2d::Sprite* SelectLayerBG;

	cocos2d::Sprite* Confirm_label;
	cocos2d::MenuItemImage* m_ConfirmBtn;
	cocos2d::MenuItemImage* m_CancleBtn;

	cocos2d::Sprite* HeroAttribute;

	bool m_bCanSelectHero;

	void CloseConfirmPanel();

	void ShowConfirmPanel();

	void callback_OnPressConfirm(Ref* sender);

	void callback_OnPressCancleCancle(Ref* sender);
};

#endif //__SELECT_STORY_H__
