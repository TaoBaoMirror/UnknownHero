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