#ifndef __TITLE_UI_H__
#define __TITLE_UI_H__

#include "cocos2d.h"
#include "BaseUI\ProgressBar.h"
#include <thread>


NS_CC_BEGIN

class TitleUI : public cocos2d::Layer
{
public:
	cocos2d::Sprite* pLogo;
	cocos2d::Sprite* pLogo_BG;
    ProgressBar* pLogoProgressBar;
    static int LayerTag;
private:
    //
	Menu* m_pStartMenu;

	cocos2d::Size winsize;

	cocos2d::MenuItemImage* sound_enable_Btn;
    cocos2d::MenuItemImage* sound_disable_Btn;

    cocos2d::MenuItemImage* rateme_Btn;
    cocos2d::MenuItemImage* monster_Btn;
    cocos2d::MenuItemImage* developer_Btn;
    cocos2d::MenuItemImage* help_Btn;

	cocos2d::Sprite* QuitGame_label;
    cocos2d::MenuItemImage* quitGameBtn;
    cocos2d::MenuItemImage* quitGameCancleBtn;
    cocos2d::MenuItemImage* rateMeToUnlockBtn;

    cocos2d::MenuItemSprite* Continue_Btn_1;
	cocos2d::MenuItemSprite* Continue_Btn_2;
	cocos2d::MenuItemSprite* Continue_Btn_3;
    cocos2d::MenuItemSprite* Story_Btn;
	cocos2d::Sprite* ContinueGame_Lable;

public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(TitleUI);

	void CloseQuitGameLayer();
	void QuitGame();

private:
	void callback_OnPressQuitGame(Ref* sender);
    void callback_OnPressCancleQuit(Ref* sender);
    void callback_OnPressRateMeToUnlock(Ref* sender);

	void callback_QuitGameLable(Ref* sender);

	void StartStory_Game(Ref* sender);
	void Continue_Game_1(Ref* sender);
	void Continue_Game_2(Ref* sender);
	void Continue_Game_3(Ref* sender);

	//virtual void onEnter() override;

};

NS_CC_END

#endif //__TITLE_UI_H__

