#include "GameScene.h"

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
	return true;
}

void GameScene::update( float dt )
{

}

void GameScene::SceneInit()
{
	//1 check ��ǰ���� ������½��� ��ô��ͷ��ʼ

	//2 ��������н��� ��ô����֮ǰ������

}

void GameScene::NewGame()
{
	;
}

void GameScene::Continue()
{
	;
}
