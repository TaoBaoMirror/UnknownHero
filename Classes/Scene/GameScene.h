#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : cocos2d::Scene
{
public:
	GameScene();
	~GameScene();

	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float dt) override;

	void SceneInit();

	void NewGame();

	void Continue();

	static int LayerTag;
};

#endif //__GAME_SCENE_H__