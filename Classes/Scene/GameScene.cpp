#include "GameScene.h"

#include "Scene/GameManager.h"

int GameScene::LayerTag = 1;

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

cocos2d::Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	//auto uilayer = GameUILayer::create();

	// add layer as a child to scene
	scene->addChild(layer,1,GameScene::LayerTag);
	//scene->addChild(uilayer,2,GameUILayer::LayerTag);

	// return the scene
	return scene;
}

bool GameScene::init()
{
	//1 check 当前进度 如果是新进度 那么从头开始

	//2 如果是已有进度 那么继续之前的流程
	return true;
}

void GameScene::update( float dt )
{
	GameManager::GetInstance()->Update(dt);

}

void GameScene::NewGame()
{
	;
}

void GameScene::Continue()
{
	;
}
