#include "TitleUI.h"
#include "ResDef.h"
#include "Sound/SoundManager.h"
#include "Scene/GameScene.h"
#include "Scene/GameManager.h"
#include "Scene/SelectHeroLayer.h"

USING_NS_CC;

int TitleUI::LayerTag = 10;

Scene* TitleUI::createScene()
{
	// 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleUI::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool TitleUI::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	this->setTag(LayerTag);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	pLogo = Sprite::create("images/logo.png");
	pLogo->setPosition(Vec2(405, visibleSize.height - 111));
	addChild(pLogo,1);
	pLogo_BG = Sprite::create("images/logo_bg.jpg");
    pLogo_BG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    addChild(pLogo_BG, 0);

	//Button StartGame
	{
		//new game btn
		{
			//SpriteFrame* normal = SpriteFrameCache::getInstance()->getSpriteFrameByName("story_normal.png");
			//SpriteFrame* select = SpriteFrameCache::getInstance()->getSpriteFrameByName("story_hover.png");
			
			Sprite* normal = Sprite::create("images//story_normal.png");
			Sprite* select = Sprite::create("images//story_hover.png");

			//Story_Btn = MenuItemSprite::create(Sprite::createWithSpriteFrame(normal), Sprite::createWithSpriteFrame(select), CC_CALLBACK_1(TitleUI::StartStory_Game,this));
			Story_Btn = MenuItemSprite::create(normal, select, CC_CALLBACK_1(TitleUI::StartStory_Game,this));
			Story_Btn->setPosition(0.0f, 50.0f);	
		}


		m_pStartMenu = Menu::create(Story_Btn, nullptr);

		m_pStartMenu->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 - 50));
		m_pStartMenu->setVisible(true);
		addChild(m_pStartMenu, 2);
	}

	{
		//Continue Lable
		ContinueGame_Lable = Sprite::create("Images//StartGame_label.png");
		ContinueGame_Lable->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		ContinueGame_Lable->setScale(1.0f);
		ContinueGame_Lable->setVisible(false);
		//ContinueGame_Lable->setUserData(0);
		addChild(ContinueGame_Lable, 109);

		SpriteFrame* Continue1_normal = SpriteFrameCache::getInstance()->getSpriteFrameByName("pvp_normal.png");
		SpriteFrame* Continue1_select = SpriteFrameCache::getInstance()->getSpriteFrameByName("pvp_hover.png");

		float texwidth = ContinueGame_Lable->getTexture()->getContentSize().width;
		float texheight = ContinueGame_Lable->getTexture()->getContentSize().height;

		Continue_Btn_1 = MenuItemSprite::create(Sprite::createWithSpriteFrame(Continue1_normal), Sprite::createWithSpriteFrame(Continue1_select), CC_CALLBACK_1(TitleUI::Continue_Game_1,this));
		Continue_Btn_1->setPosition(Vec2(texwidth/2.0f, texheight/2.0f + 60.0f));

		SpriteFrame* Continue2_normal = SpriteFrameCache::getInstance()->getSpriteFrameByName("pvp_normal.png");
		SpriteFrame* Continue2_select = SpriteFrameCache::getInstance()->getSpriteFrameByName("pvp_hover.png");

		Continue_Btn_2 = MenuItemSprite::create(Sprite::createWithSpriteFrame(Continue2_normal), Sprite::createWithSpriteFrame(Continue2_select), CC_CALLBACK_1(TitleUI::Continue_Game_2,this));
		Continue_Btn_2->setPosition(Vec2(texwidth/2.0f, texheight/2.0f));

		SpriteFrame* Continue3_normal = SpriteFrameCache::getInstance()->getSpriteFrameByName("pvp_normal.png");
		SpriteFrame* Continue3_select = SpriteFrameCache::getInstance()->getSpriteFrameByName("pvp_hover.png");

		Continue_Btn_3 = MenuItemSprite::create(Sprite::createWithSpriteFrame(Continue3_normal), Sprite::createWithSpriteFrame(Continue3_select), CC_CALLBACK_1(TitleUI::Continue_Game_3,this));
		Continue_Btn_3->setPosition(Vec2(texwidth/2.0f, texheight/2.0f - 60.0f));

		auto pContinueMenu = Menu::create(Continue_Btn_1,Continue_Btn_2,Continue_Btn_3, nullptr);
		pContinueMenu->setPosition(0.0f,0.0f);
		pContinueMenu->setVisible(true);
		ContinueGame_Lable->addChild(pContinueMenu, 2);
	}

	
	{
		//Button LeaveGame or not
		QuitGame_label = Sprite::create("Images//QuitGame_label.png");
		QuitGame_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		QuitGame_label->setScale(0.01f);
		QuitGame_label->setVisible(false);
		//QuitGame_label->setUserData(0);
		addChild(QuitGame_label, 109);

		quitGameBtn = MenuItemImage::create("Images//QuitYes.png","Images//QuitYes_hover.png",CC_CALLBACK_1(TitleUI::callback_OnPressQuitGame, this));
		auto pmenu = Menu::create(quitGameBtn, NULL);
        pmenu->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 40));
        addChild(pmenu, 110);

		quitGameCancleBtn = MenuItemImage::create("Images//QuitCancel","Images//QuitCancel_hover",CC_CALLBACK_1(TitleUI::callback_OnPressCancleQuit, this));
		auto pmenu2 = Menu::create(quitGameCancleBtn,NULL);
        pmenu2->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 + 40));
        addChild(pmenu2, 110);

		rateMeToUnlockBtn = MenuItemImage::create("Images//RateUnlock","Images//RateUnlock_hover",CC_CALLBACK_1(TitleUI::callback_OnPressRateMeToUnlock, this));
		auto pmenu3 = Menu::create(rateMeToUnlockBtn,NULL);
        pmenu3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 60));
        addChild(pmenu3, 110);
        //
		quitGameBtn->setVisible(false);
		quitGameBtn->setEnabled(false);
        quitGameCancleBtn->setVisible(false);
        quitGameCancleBtn->setEnabled(false);
        rateMeToUnlockBtn->setVisible(false);
        rateMeToUnlockBtn->setEnabled(false);
    }

	//test
	help_Btn = nullptr;
	rateme_Btn = nullptr;
	monster_Btn = nullptr;
	developer_Btn = nullptr;
	sound_enable_Btn = nullptr;
	sound_disable_Btn = nullptr;

	//end

	//
    pLogoProgressBar = new ProgressBar(100, 0, "images\\LesStep.png");
    addChild(pLogoProgressBar, 1);
	pLogoProgressBar->setPosition(Vec2((visibleSize.width - pLogoProgressBar->width) / 2,
                                                visibleSize.height  - 200));

    pLogoProgressBar->setVisible(true);

    //
	this->setTouchEnabled(true);
    //    

	//
    return true;
}





void TitleUI::callback_OnPressQuitGame(Ref* sender)
{
	ResDef::getInstance()->SaveConfig();
	CCDirector::getInstance()->end();
	//CCApplication::sharedApplication()->getInstance()->Game.Exit();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void TitleUI::callback_OnPressCancleQuit(Ref* sender)
{
    CloseQuitGameLayer();
}

void TitleUI::callback_OnPressRateMeToUnlock(Ref* sender)
{
    //rateMeToUnlockBtn.visible = false;
    //rateMeToUnlockBtn.Enabled = false;

    //MarketplaceReviewTask marketplaceReviewTask = new MarketplaceReviewTask();
    //marketplaceReviewTask.Show();

    //if (ResDef.IsRoleLocked((int)GamePlayerRole.GamePlayerRole_MATCHMAN) == true)
    //{
    //    ResDef.UnlockRoleID((int)GamePlayerRole.GamePlayerRole_MATCHMAN);
    //    ResDef.SaveConfig();
    //}
}

void TitleUI::CloseQuitGameLayer()
{
	QuitGame_label->stopAllActions();
	QuitGame_label->setScale(0.01f);
	QuitGame_label->setVisible(false);
	QuitGame_label->setUserData(0);

    quitGameBtn->setVisible(false);
	quitGameBtn->setEnabled(false);

    quitGameCancleBtn->setVisible(false);
    quitGameCancleBtn->setEnabled(false);

    rateMeToUnlockBtn->setVisible(false);
    rateMeToUnlockBtn->setEnabled(false);

    if (Story_Btn != NULL)
    {
        Story_Btn->setEnabled(true);
    }

    if (help_Btn != nullptr)
    {
        help_Btn->setEnabled(true);
    }
    if (rateme_Btn != NULL)
    {
        rateme_Btn->setEnabled(true);
    }
    if (developer_Btn != NULL)
    {
        developer_Btn->setEnabled(true);
    }
    if (monster_Btn != NULL)
    {
        monster_Btn->setEnabled(true);
    }
}

void TitleUI::QuitGame()
{
    QuitGame_label->setScale(0.01f);
    QuitGame_label->setVisible(true);
	//QuitGame_label->setUserData((void)1);

    //unable start game button
    if (Story_Btn != NULL)
    {
        Story_Btn->setEnabled(false);
    }

    if (help_Btn != nullptr)
    {
        help_Btn->setEnabled(false);
    }
    if (rateme_Btn != NULL)
    {
        rateme_Btn->setEnabled(false);
    }
    if (developer_Btn != NULL)
    {
        developer_Btn->setEnabled(false);
    }
    if (monster_Btn != NULL)
    {
        monster_Btn->setEnabled(false);
    }
    //end

	auto actionTo = ScaleTo::create(2.0f, 0.5f);
    auto actionBy = ScaleBy::create(2.0f, 1.0f, 10.0f);
    auto actionBy2 = ScaleBy::create(2.0f, 5.0f, 1.0f);

	auto scaleTo = ScaleTo::create(0.2f, 1.0f);

	auto callbackaction = Sequence::create(
        MoveBy::create(2.0f, Vec2(150,0)),
        CallFuncN::create( CC_CALLBACK_1(TitleUI::callback_QuitGameLable, this)),
        nullptr);

	QuitGame_label->runAction(Sequence::create(scaleTo, callbackaction, nullptr));
}

void TitleUI::callback_QuitGameLable(Ref* sender)
{
	quitGameBtn->setVisible(true);
	quitGameBtn->setEnabled(true);

    quitGameCancleBtn->setVisible(true);
    quitGameCancleBtn->setEnabled(true);

	//if (ResDef::getInstance()->IsRoleLocked((int)GamePlayerRole.GamePlayerRole_MATCHMAN) == true)
 //   {
 //       rateMeToUnlockBtn.visible = true;
 //       rateMeToUnlockBtn.Enabled = true;
 //   }
}

void TitleUI::StartStory_Game(Ref* sender)
{
	SoundManager::Instance()->PlayEffect(ResDef::g_SelectSound);
    //SoundManager::Instance()->StopMusic();

	//show savedata menu
	ContinueGame_Lable->setVisible(true);

	if (Story_Btn != nullptr)
	{
		Story_Btn->setEnabled(false);
	}

	if (help_Btn != nullptr)
	{
		help_Btn->setEnabled(false);
	}
	if (rateme_Btn != nullptr)
	{
		rateme_Btn->setEnabled(false);
	}
	if (developer_Btn != nullptr)
	{
		developer_Btn->setEnabled(false);
	}
	if (monster_Btn != nullptr)
	{
		monster_Btn->setEnabled(false);
	}

	//Director::getInstance()->replaceScene(GameScene::createScene(ResDef::getInstance()->g_ConfigStruct.CurrentArea));
}

void TitleUI::Continue_Game_1(Ref* sender)
{
	GameManager::GetInstance()->SetCurSaveData(1);

	SaveData* pData = GameManager::GetInstance()->GetCurSaveData();

	if (pData->IsNewData)
	{
		NewGame();
	}
	else
	{
		LoadGame();		
	}	
}

void TitleUI::Continue_Game_2(Ref* sender)
{
	//CircleRunScene.g_GameMode = RunGameMode.MODE_PVP;

	//CircleRunScene.UseAI = false;

	//if (ResDef.g_ConfigStruct.EnableAudio != 0)
	//{
	//    SimpleAudioEngine.sharedEngine().playEffect(ResDef.g_SelectSound);
	//    //SimpleAudioEngine.sharedEngine().stopBackgroundMusic();
	//}
	//MusicManager.Instance().PlayEffect(ResDef.g_SelectSound);
	//MusicManager.Instance().StopMusic();

	//Director::getInstance()->replaceScene(SelectRoleUI.scene());
	GameManager::GetInstance()->SetCurSaveData(2);
}

void TitleUI::Continue_Game_3(Ref* sender)
{
	//CircleRunScene.g_GameMode = RunGameMode.MODE_PVP;

	//CircleRunScene.UseAI = false;

	//if (ResDef.g_ConfigStruct.EnableAudio != 0)
	//{
	//    SimpleAudioEngine.sharedEngine().playEffect(ResDef.g_SelectSound);
	//    //SimpleAudioEngine.sharedEngine().stopBackgroundMusic();
	//}
	//MusicManager.Instance().PlayEffect(ResDef.g_SelectSound);
	//MusicManager.Instance().StopMusic();

	//Director::getInstance()->replaceScene(SelectRoleUI.scene());

	GameManager::GetInstance()->SetCurSaveData(2);

}

void TitleUI::NewGame()
{
	Director::getInstance()->replaceScene(SelectHeroLayer::createScene());
}

void TitleUI::LoadGame()
{
	SaveData* pData = GameManager::GetInstance()->GetCurSaveData();

	int changeScene = pData->GetCurScene();

	//临时--test
	changeScene = 2;
	//

	if (changeScene == 0) //选人场景
	{
		Director::getInstance()->replaceScene(SelectHeroLayer::createScene());
	}
	else if(changeScene == 1)//城市
	{

	}
	else //游戏场景
	{
		Director::getInstance()->replaceScene(GameScene::createScene());
	}
	
}