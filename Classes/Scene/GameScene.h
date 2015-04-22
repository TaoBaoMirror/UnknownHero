#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "Game\ChunkMap.h"

class GameScene : cocos2d::Scene
{
public:
	GameScene();
	~GameScene();

	static cocos2d::Scene* createScene();

	bool init() override;

	virtual void update(float dt) override;

	void NewGame();

	void Continue();

	static int LayerTag;
protected: 
	void TestMap();
};

#endif //__GAME_SCENE_H__