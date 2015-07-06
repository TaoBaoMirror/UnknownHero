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
	//1 check 当前进度 如果是新进度 那么从头开始
//<<<<<<< .mine
//	if (pData->IsNewData)
//	{
//		NewGame();
//	}
//=======
	
	//2 如果是已有进度 那么继续之前的流程

	//3 加入Update循环!
	
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
	//1 切换到讲述故事背景的layer

	//test 调试暂时不使用讲故事layer 直接跳转到选人场景

	auto pLayer = SelectHeroLayer::create();
	this->addChild(pLayer,1,SelectHeroLayer::LayerTag);
}

void GameScene::Continue()
{
	SaveData* pData = GameManager::GetInstance()->GetCurSaveData();

	//1 加载当前地图
	int sceneid = pData->CurSceneID;
	//2 加载当前主角

	//3 加载敌人

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
	pSkillBarUI = (SkillBarUI*)SkillBarUI::CreateWithTag(111);
	//addChild(pSkillBarUI,100);
	//
	pSkillBarUI->SetSkillIcon(0,"skill_0");
	pSkillBarUI->SetSkillIcon(1,"skill_1");
	pSkillBarUI->SetSkillIcon(2,"skill_2");
	pSkillBarUI->SetSkillIcon(3,"skill_3");

	pMainPanel = new MainControllerPanel();
	pMainPanel->setPosition(800,80);
	pMainPanel->Init();
	addChild(pMainPanel,101);

	/*

	Hero* pHero = PlayerManager::GetInstance()->GetHero();

	if (pHero != nullptr)
	{
		auto* pLayer = pChunk->GetCreatureLayer();
		if (pLayer != nullptr)
		{
			//pChunk->addChild(pHero,pLayer->getTag());
			pHero->SetToGPos(GridPos(0,0));
			pHero->UpdatePosition();
			pHero->UpdateToCCWorldPos();
			pLayer->addChild(pHero,99);

		}		
	}

	//EnemyManager::GetInstance()->CreateMonstersAtLayer(pChunk,pLayer->getTag());
	Monster* pMonster = EnemyManager::GetInstance()->CreateMonster(0);
	if (pMonster != nullptr)
	{
		auto* pLayer = pChunk->GetCreatureLayer();
		if (pLayer != nullptr)
		{
			//pChunk->addChild(pMonster,pLayer->getTag());
			pMonster->SetToGPos(GridPos(3,6));
			pMonster->UpdatePosition();
			pMonster->UpdateToCCWorldPos();
			pLayer->addChild(pMonster,99);

		}
	}

	*/

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