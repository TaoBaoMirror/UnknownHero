#include "GameScene.h"

#include "Scene/GameManager.h"
#include "Game/MapManager.h"

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
	//1 check 当前进度 如果是新进度 那么从头开始
	TestMap();
	//2 如果是已有进度 那么继续之前的流程

	//3 加入Update循环!
	scheduleUpdate();
	return true;
}

void GameScene::update( float dt )
{
	//GameManager::GetInstance()->Update(dt);

	auto pChunk = MapManager::GetInstance()->GetCurChunkMap();
	pChunk->update(dt);

}

void GameScene::NewGame()
{
	;
}

void GameScene::Continue()
{
	;
}

void GameScene::TestMap()
{
	MapManager::GetInstance()->ChangeMap(0);
	auto pChunk = MapManager::GetInstance()->GetCurChunkMap();
	addChild(pChunk,10);
	//
	pChunk->DeployCreature();

}