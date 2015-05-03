#include "SelectHeroLayer.h"
#include "Scene/GameManager.h"
#include "Scene/GameScene.h"
#include "VisibleRect.h"

#include "Actor/PlayerManager.h"

#include <vector>

int SelectHeroLayer::LayerTag = 10;

const static cocos2d::Vec2 HeroStartPos_1; //�м�
const static cocos2d::Vec2 HeroStartPos_2; //��
const static cocos2d::Vec2 HeroStartPos_3; //��

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
		//1 ���ȶԻ�,����Ի�����,��ѡӢ�۳���
		m_SelectST = SelectHeroState::SelectHero_Dialog_CallOn;
		HeroCallOn();
		break;
	case SelectHero_Dialog_CallOn:
		//2 Ӣ�۳���,�ƶ���
		break;
	case SelectHero_Dialog_AfterHeroCallOn:
		//3 ���Ӣ�۳���,Ӣ���ߵ���λ����ô����˵��
		m_SelectST = SelectHeroState::SelectHero_Dialog_SelectHero;
		break;
	case SelectHero_Dialog_SelectHero:
		//4 ����Ի��ֽ�����,�����ѡӢ��״̬
		break;
	case SelectHero_Dialog_AfterSelectHero:
		//5 �Ѿ�ѡ����Ӣ��,���ĶԻ�,�Ի������󻻳���
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
	//1 ��ȡ��ǰ���� ���Ƿ񴴽�����Ӣ�۳���
	{
		//--��ȡ��ǰ�ó���������Ӣ��ID
		curSpecHeroId = GameManager::GetInstance()->GetCurSpecialHeroProcess();

		//--�������Ӣ���Ƿ���ϳ�������
		//�ȶ���ȡ����ǰ����Ӣ�۳�������
		//TableManager::GetInstance()->GetTableData();
		
		//Ȼ�����������ȫ������,��ô����
		//bSpecialHeroJoin = true;
	}

	//2 ���û������Ӣ�۳��� ��ô ���������ͨӢ��,���õ�����λ���Ϲ������ѡ.������3��Ӣ����������һ����ť	
	if (bSpecialHeroJoin == false)
	{
		//--��ȡ����Ӣ�۵�Ӣ��ID
		int heroID_1 = 0; //��0~5֮�����,��ս�ĸ���ͼ
		int heroID_2 = 0; //��5~10֮�����,Զ�̵ĸ���ͼ
		int heroID_3 = 0; //��10~15ֱ�����,��������

		cocos2d::Vec2 HeroStartPos_1 = VisibleRect::bottom() - cocos2d::Vec2(-100.0f,-20.0f);	//�м�
		cocos2d::Vec2 HeroStartPos_2 = VisibleRect::bottom() - cocos2d::Vec2(0.0f,-20.0f);		//��
		cocos2d::Vec2 HeroStartPos_3 = VisibleRect::bottom() - cocos2d::Vec2(100.0f,-20.0f);	//��

		//--����������ѡӢ��
		
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
	//3 ���������Ӣ����,����,�����ɱ���д��������ɼ���
	else
	{
		//�����⵱ǰ����Ӣ�۵���ϸ����
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

	//show hero��Ϣ 
	//show ȷ����ť
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
	//1 ��¼������ʹ�õ�Ӣ��
	PlayerManager::GetInstance()->HeroBorn(m_CurSelectHero);

	//2 ��״̬  ֮�󻻳���
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