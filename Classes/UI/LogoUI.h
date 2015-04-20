#ifndef __LOGO_UI_H__
#define __LOGO_UI_H__

#include "cocos2d.h"
#include "BaseUI\ProgressBar.h"

NS_CC_BEGIN

class LogoUI : public cocos2d::Layer
{
private:		
    ProgressBar* pLogoProgressBar;
    static	bool bFinishLoad;
    static	bool bLoading;

	Size	winSize;
	Sprite*	bunkerTexture;
    Sprite*	bunkerBG;

    Sprite*	bunkerLoadingBarFrame;

	std::thread* m_loadThread;
public:
	static const float DelayTimeConst;

private:
	void loadRes();
	void GoToLogoUI();

	void callback_GoToTitleUI();
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  

	virtual void update(float dt) override;

	virtual void onEnter() override;
	virtual void onExit() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(LogoUI);
};

NS_CC_END

#endif //__LOGO_UI_H__

