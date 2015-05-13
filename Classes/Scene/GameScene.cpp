#include "GameScene.h"

#include "Scene/GameManager.h"
#include "Scene/SelectHeroLayer.h"
#include "UI/TellStoryLayer.h"
#include "Game/MapManager.h"
#include "UI/SkillBarUI.h"
#include "Actor/PlayerManager.h"
#include "Actor/EnemyManager.h"
#include "Actor/NPCManager.h"


USING_NS_CC;

int GameScene::LayerTag = 1;

GameScene::GameScene()
{
	setTag(LayerTag);
}


GameScene::~GameScene()
{
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

	//--------------------------
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
	//--------------------------

	TestMap();

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
	MapManager::GetInstance()->ChangeMap(0);
	auto pChunk = MapManager::GetInstance()->GetCurChunkMap();
	addChild(pChunk,10);
	//
	pChunk->setPosition(100,100);
	pChunk->DeployCreature();
	//
	pSkillBarUI = (SkillBarUI*)SkillBarUI::CreateWithTag(111);
	addChild(pSkillBarUI);
	//
	pSkillBarUI->SetSkillIcon(0,"skill_0");
	pSkillBarUI->SetSkillIcon(1,"skill_1");
	pSkillBarUI->SetSkillIcon(2,"skill_2");
	pSkillBarUI->SetSkillIcon(3,"skill_3");

	Hero* pHero = PlayerManager::GetInstance()->GetHero();

	if (pHero != nullptr)
	{
		cocos2d::TMXLayer* pLayer = pChunk->GetCreatureLayer();
		if (pLayer != nullptr)
		{
			//pChunk->addChild(pHero,pLayer->getTag());
			pChunk->addChild(pHero,99);
		}		
	}
	

	GameManager::GetInstance()->SetGameST(ST_Fight);

}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
	GameManager::GetInstance()->GameKeyPressed(code, event);
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
	GameManager::GetInstance()->GameKeyReleased(code, event);
}