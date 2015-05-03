#include "SelectHeroLayer.h"
#include "Scene/GameManager.h"
#include "Scene/GameScene.h"
#include "VisibleRect.h"

#include "Actor/PlayerManager.h"

#include <vector>

int SelectHeroLayer::LayerTag = 10;

const static cocos2d::Vec2 HeroStartPos_1; //中间
const static cocos2d::Vec2 HeroStartPos_2; //左
const static cocos2d::Vec2 HeroStartPos_3; //右

SelectHeroLayer::SelectHeroLayer(void)
{	
	m_bCanSelectHero = true;
}


SelectHeroLayer::~SelectHeroLayer(void)
{
}

cocos2d::Scene* SelectHeroLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = cocos2d::Scene::create();

	// 'layer' is an autorelease object
	auto layer = SelectHeroLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool SelectHeroLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	//-------------------------
	CreateStandbyHeros();

	m_SelectST = SelectHeroState::SelectHero_Dialog_BeforeHeroCallOn;

	//-------------------------

	SelectLayerBG = cocos2d::Sprite::create("images/logo.png");
	SelectLayerBG->setPosition(VisibleRect::center());
	addChild(SelectLayerBG,1);


	//Button Confirm Select Hero
	Confirm_label = cocos2d::Sprite::create("Images//QuitGame_label.png");
	Confirm_label->setPosition(VisibleRect::center());
	Confirm_label->setVisible(true);
	//QuitGame_label->setUserData(0);
	addChild(Confirm_label, 109);

	float texwidth = Confirm_label->getTexture()->getContentSize().width;
	float texheight = Confirm_label->getTexture()->getContentSize().height;

	m_ConfirmBtn = cocos2d::MenuItemImage::create("Images//QuitYes.png","Images//QuitYes_hover.png",CC_CALLBACK_1(SelectHeroLayer::callback_OnPressConfirm, this));
	auto pmenu = cocos2d::Menu::create(m_ConfirmBtn, NULL);
	pmenu->setPosition(cocos2d::Vec2(VisibleRect::center().x - 100.0f, VisibleRect::center().y + 40.0f));
	addChild(pmenu, 110);

	m_CancleBtn = cocos2d::MenuItemImage::create("Images//QuitCancel.png","Images//QuitCancel_hover.png",CC_CALLBACK_1(SelectHeroLayer::callback_OnPressCancleCancle, this));
	auto pmenu2 = cocos2d::Menu::create(m_CancleBtn,NULL);
	pmenu2->setPosition(cocos2d::Vec2(VisibleRect::center().x + 100.0f, VisibleRect::center().y + 40.0f));
	addChild(pmenu2, 110);

	//cocos2d::Sprite* HeroAttribute;
	HeroAttribute = nullptr;


	CloseConfirmPanel();
	//-------------------------

	return true;
}

void SelectHeroLayer::update(float dt)
{
	switch (m_SelectST)
	{
	case SelectHero_Dialog_BeforeHeroCallOn:
		//1 首先对话,如果对话结束,可选英雄出现
		m_SelectST = SelectHeroState::SelectHero_Dialog_CallOn;
		HeroCallOn();
		break;
	case SelectHero_Dialog_CallOn:
		//2 英雄出场,移动中
		break;
	case SelectHero_Dialog_AfterHeroCallOn:
		//3 如果英雄出现,英雄走到了位置那么继续说话
		m_SelectST = SelectHeroState::SelectHero_Dialog_SelectHero;
		break;
	case SelectHero_Dialog_SelectHero:
		//4 如果对话又结束了,进入可选英雄状态
		break;
	case SelectHero_Dialog_AfterSelectHero:
		//5 已经选择了英雄,最后的对话,对话结束后换场景
		break;
	default:
		break;
	}
	
}

void SelectHeroLayer::onEnter()
{
	Layer::onEnter();

	scheduleUpdate();
}

void SelectHeroLayer::onExit()
{
	unscheduleUpdate();

	Layer::onExit();
}

void SelectHeroLayer::CreateStandbyHeros()
{
	bool bSpecialHeroJoin = false;
	int curSpecHeroId = 0;
	//1 读取当前进度 看是否创建特殊英雄出场
	{
		//--获取当前该出场的特殊英雄ID
		curSpecHeroId = GameManager::GetInstance()->GetCurSpecialHeroProcess();

		//--检测特殊英雄是否符合出场条件
		//先读表取出当前特殊英雄出场条件
		//TableManager::GetInstance()->GetTableData();
		
		//然后检测如果条件全部符合,那么出场
		//bSpecialHeroJoin = true;
	}

	//2 如果没有特殊英雄出场 那么 随机三个普通英雄,放置到三个位置上供玩家挑选.并且在3个英雄下面各提高一个按钮	
	if (bSpecialHeroJoin == false)
	{
		//--获取三个英雄的英雄ID
		int heroID_1 = 0; //在0~5之间随机,近战的各种图
		int heroID_2 = 0; //在5~10之间随机,远程的各种图
		int heroID_3 = 0; //在10~15直接随机,特殊的随机

		cocos2d::Vec2 HeroStartPos_1 = VisibleRect::bottom() - cocos2d::Vec2(-100.0f,-20.0f);	//中间
		cocos2d::Vec2 HeroStartPos_2 = VisibleRect::bottom() - cocos2d::Vec2(0.0f,-20.0f);		//左
		cocos2d::Vec2 HeroStartPos_3 = VisibleRect::bottom() - cocos2d::Vec2(100.0f,-20.0f);	//右

		//--创建三个可选英雄
		
		m_pStandbyHero_1 = StandbyHero::createWithTextureHeroID(heroID_1);
		m_pStandbyHero_1->setPosition(HeroStartPos_1);
		m_pStandbyHero_1->SetSelectHeroLayer(this);
		m_pStandbyHero_1->playStandAnimation();
		addChild(m_pStandbyHero_1);

		m_pStandbyHero_2 = StandbyHero::createWithTextureHeroID(heroID_2);
		m_pStandbyHero_2->setPosition(HeroStartPos_2);
		m_pStandbyHero_2->SetSelectHeroLayer(this);
		m_pStandbyHero_2->playStandAnimation();
		addChild(m_pStandbyHero_2);

		//auto standbyHeroTexture_3 = cocos2d::Director::getInstance()->getTextureCache()->addImage(tex_hero3);
		m_pStandbyHero_3 = StandbyHero::createWithTextureHeroID(heroID_3);
		m_pStandbyHero_3->setPosition(HeroStartPos_3);
		m_pStandbyHero_3->SetSelectHeroLayer(this);
		m_pStandbyHero_3->playStandAnimation();
		addChild(m_pStandbyHero_3);

	}
	//3 如果有特殊英雄了,读表,看生成表里写的这次生成几个
	else
	{
		//读表检测当前特殊英雄的详细属性
	}
}

void SelectHeroLayer::ClickHero(StandbyHero* pHero)
{
	if (m_SelectST != SelectHeroState::SelectHero_Dialog_SelectHero)
	{
		return;
	}

	if (m_bCanSelectHero == false)
	{
		return;
	}

	m_CurSelectHero = pHero;

	//show hero信息 
	//show 确定按钮
	ShowConfirmPanel();
}

void SelectHeroLayer::HeroMove()
{
	if (m_pStandbyHero_1 != nullptr)
	{
		auto callbackaction = cocos2d::Sequence::create(
			cocos2d::MoveBy::create(0.0f,cocos2d::Vec2(0.0f, 200.0f)),
			cocos2d::CallFuncN::create( CC_CALLBACK_1(SelectHeroLayer::HeroCallOnOver, this)),
			nullptr);

		m_pStandbyHero_1->runAction(callbackaction);
	}

	if (m_pStandbyHero_2 != nullptr)
	{
		m_pStandbyHero_2->runAction(cocos2d::MoveBy::create(0.0f,cocos2d::Vec2(0.0f, 200.0f)));
	}

	if (m_pStandbyHero_3 != nullptr)
	{
		m_pStandbyHero_3->runAction(cocos2d::MoveBy::create(0.0f,cocos2d::Vec2(0.0f, 200.0f)));
	}
	
}

void SelectHeroLayer::HeroCallOn()
{
	HeroMove();
}

void SelectHeroLayer::HeroCallOnOver(Node* sender)
{
	m_SelectST = SelectHeroState::SelectHero_Dialog_AfterHeroCallOn;
}

void SelectHeroLayer::DecideHero()
{
	m_SelectST = SelectHeroState::SelectHero_Dialog_AfterSelectHero;
}

void SelectHeroLayer::callback_OnPressConfirm(Ref* sender)
{
	//1 记录下来将使用的英雄
	PlayerManager::GetInstance()->HeroBorn(m_CurSelectHero);

	//2 切状态  之后换场景
	GameManager::GetInstance()->SetGameST(GameStatus::ST_Fight);

	cocos2d::Director::getInstance()->replaceScene(GameScene::createScene());
}

void SelectHeroLayer::callback_OnPressCancleCancle(Ref* sender)
{
	CloseConfirmPanel();
}

void SelectHeroLayer::ShowConfirmPanel()
{
	Confirm_label->setVisible(true);

	m_ConfirmBtn->setVisible(true);
	m_ConfirmBtn->setEnabled(true);

	m_CancleBtn->setVisible(true);
	m_CancleBtn->setEnabled(true);

	if (HeroAttribute != nullptr)
	{
		HeroAttribute->setVisible(true);
	}

	m_bCanSelectHero = false;
}

void SelectHeroLayer::CloseConfirmPanel()
{
	Confirm_label->stopAllActions();
	Confirm_label->setVisible(false);

	m_ConfirmBtn->setVisible(false);
	m_ConfirmBtn->setEnabled(false);

	m_CancleBtn->setVisible(false);
	m_CancleBtn->setEnabled(false);

	if (HeroAttribute != nullptr)
	{
		HeroAttribute->setVisible(false);
	}

	m_bCanSelectHero = true;
}