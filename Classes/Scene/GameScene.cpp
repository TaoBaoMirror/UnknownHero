#include "GameScene.h"

#include "Scene/GameManager.h"
#include "Scene/SelectHeroLayer.h"
#include "UI/TellStoryLayer.h"
#include "Game/MapManager.h"
#include "UI/SkillBarUI.h"
#include "Actor/PlayerManager.h"
#include "Actor/EnemyManager.h"
#include "Actor/NPCManager.h"
#include "UI/MainControllerPanel.h"

USING_NS_CC;

int GameScene::LayerTag = 1;

GameScene::GameScene()
{
	setTag(LayerTag);
}


GameScene::~GameScene()
{
	//_eventDispatcher->removeEventListener(_touchListener);
	//_eventDispatcher->removeEventListener(_keyboardListener);
}

cocos2d::Scene* GameScene::createScene()
{
	auto ret = new GameScene();
	//
	if (ret && ret->init())
	{
		ret->autorelease();

		ret->SceneInit();

		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool GameScene::init()
{
	Scene::init();

	////--------------------------
	//auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);

	//listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	////_eventDispatcher->addEventListenerWithFixedPriority(listener, -10);
	//_touchListener = listener;
	////--------------------------
	//auto listenerKeyboard = EventListenerKeyboard::create();
	//listenerKeyboard->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	//listenerKeyboard->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
	//_keyboardListener = listenerKeyboard;
	////--------------------------

	TestMap();

	GameManager::GetInstance()->SetGameScene(this);

	scheduleUpdate();

	return true;
}

bool GameScene::SceneInit()
{
//<<<<<<< .mine
//	SaveData* pData = GameManager::GetInstance()->GetCurSaveData();
//=======
	
//>>>>>>> .r21
	//1 check ��ǰ���� ������½��� ��ô��ͷ��ʼ
//<<<<<<< .mine
//	if (pData->IsNewData)
//	{
//		NewGame();
//	}
//=======
	
	//2 ��������н��� ��ô����֮ǰ������

	//3 ����Updateѭ��!
	
	//else
	//{
	//	Continue();
	//}
	return true;
}

void GameScene::update( float dt )
{
	GameManager::GetInstance()->Update(dt);
}

void GameScene::NewGame()
{
	//1 �л����������±�����layer

	//test ������ʱ��ʹ�ý�����layer ֱ����ת��ѡ�˳���

	auto pLayer = SelectHeroLayer::create();
	this->addChild(pLayer,1,SelectHeroLayer::LayerTag);
}

void GameScene::Continue()
{
	SaveData* pData = GameManager::GetInstance()->GetCurSaveData();

	//1 ���ص�ǰ��ͼ
	int sceneid = pData->CurSceneID;
	//2 ���ص�ǰ����

	//3 ���ص���

	//4 
}

void GameScene::TestMap()
{
	MapManager::GetInstance()->EnterWorld(0);
	auto pChunk = MapManager::GetInstance()->GetCurChunkMap();
	pChunk->setPosition(39,39);
	addChild(pChunk,10);
	//
	//
	//pSkillBarUI = (SkillBarUI*)SkillBarUI::CreateWithTag(111);
	//addChild(pSkillBarUI,100);
	//

	//pMainPanel = new MainControllerPanel();
	pMainPanel = (MainControllerPanel*)MainControllerPanel::CreateWithTag(222);
	//pMainPanel->setPosition(800,80);
	//pMainPanel->Init();
	addChild(pMainPanel,101);

	GameManager::GetInstance()->SetGameST(ST_Fight);

}


bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchLocation = touch->getLocation();    

	auto nodePosition = convertToNodeSpace( touchLocation );
	log("GameScene::onTouchBegan, pos: %f,%f -> %f,%f", touchLocation.x, touchLocation.y, nodePosition.x, nodePosition.y);

	return GameManager::GetInstance()->MouseDown(touchLocation);
}

void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchLocation = touch->getLocation();    
	auto nodePosition = convertToNodeSpace( touchLocation );

	log("GameScene::onTouchMoved, pos: %f,%f -> %f,%f", touchLocation.x, touchLocation.y, nodePosition.x, nodePosition.y);

	GameManager::GetInstance()->MouseMove(nodePosition);  
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchLocation = touch->getLocation();    
	auto nodePosition = convertToNodeSpace( touchLocation );

	log("GameScene::onTouchEnded, pos: %f,%f -> %f,%f", touchLocation.x, touchLocation.y, nodePosition.x, nodePosition.y);

	GameManager::GetInstance()->MouseUp(nodePosition);
}


void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
	GameManager::GetInstance()->GameKeyPressed(code, event);
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
	GameManager::GetInstance()->GameKeyReleased(code, event);
}