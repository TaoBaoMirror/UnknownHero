#include "LogoUI.h"
#include "UI\TitleUI.h"
#include "ResDef.h"
#include <thread>

USING_NS_CC;

const float LogoUI::DelayTimeConst = 0.5f;
bool LogoUI::bFinishLoad = false;
bool LogoUI::bLoading = false;

Scene* LogoUI::createScene()
{
	// 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LogoUI::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool LogoUI::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	bFinishLoad = false;
    bLoading = false;

	this->setTouchEnabled(true);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bunkerBG = Sprite::create("images/BunkerBG.png");
	bunkerBG->retain();
	bunkerBG->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2));
    addChild(bunkerBG, 0);
    //
    bunkerTexture = Sprite::create("images/BunkerUI.png");
	bunkerTexture->retain();
	bunkerTexture->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height/2));
    addChild(bunkerTexture, 1);


    bunkerLoadingBarFrame = Sprite::create("images\\LoadingBarFrame.png");
	bunkerLoadingBarFrame->retain();
	bunkerLoadingBarFrame->setPosition(Vec2(visibleSize.width / 2, 70));

	std::string progressTexName = "images\\LesStep.png";
	pLogoProgressBar = new ProgressBar(100, 0, progressTexName.c_str());
	pLogoProgressBar->setVisible(true);

	pLogoProgressBar->setPosition(Vec2((visibleSize.width - (float)(pLogoProgressBar->width)) / 2.0f, 70.0f));

    //    
    return true;
}

void LogoUI::onEnter()
{
	//////////////////////////////
    // 1. super init first
    
	Layer::onEnter();

    scheduleUpdate();
    //
    if (bFinishLoad == false && bLoading == false)
    {
        bLoading = true;
		//std::thread loadThread(loadRes);
		//std::thread loadThread(std::bind( &LogoUI::loadRes, this));
		//ResDef::getInstance()->loadRes();
		//m_loadThread = new std::thread(&LogoUI::loadRes, this);

		loadRes();
		//m_loadThread->join();
    }
    //
	
}
//
void LogoUI::onExit()
{
	unscheduleUpdate();
	Layer::onExit();
}
//
void LogoUI::loadRes()
{	
	//LevelManager::Instance()->FillInfo();
	ResDef::getInstance()->loadRes();
	ResDef::getInstance()->initRes(pLogoProgressBar->CurrentProgress);
	pLogoProgressBar->setVisible(false);
	//bunkerLoadingBarFrame->setVisible(false);
    //
    GoToLogoUI();
}
//
void LogoUI::update(float dt)
{
	pLogoProgressBar->update(dt);
    //
}

void LogoUI::GoToLogoUI()
{
	cocos2d::DelayTime* pDelay = cocos2d::DelayTime::create(DelayTimeConst);
	cocos2d::FadeOut* pFadeOut = cocos2d::FadeOut::create(1.5f);
	//cocos2d::FadeTo* pFadeOut2 = pFadeOut->reverse();
	//pFadeOut->setReverseAction(pFadeOut2);
	cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(LogoUI::callback_GoToTitleUI,this));
 //   //
	//auto seq = Sequence::create( pDelay, pFadeOut, nullptr );

	////bunkerTexture->runAction(cocos2d::Sequence::create(pDelay,pFadeOut,pCallFunc));
	//bunkerTexture->runAction(cocos2d::Sequence::create(seq,pCallFunc,nullptr));

	auto seq = Sequence::create( pFadeOut, pCallFunc, nullptr );
	bunkerTexture->runAction(seq);
}

void LogoUI::callback_GoToTitleUI()
{
	Director::getInstance()->replaceScene(TitleUI::createScene());
}