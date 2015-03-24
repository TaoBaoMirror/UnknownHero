#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : cocos2d::Scene
{
public:
	GameScene();
	~GameScene();

	virtual bool init();

	virtual void update(float dt) override;

	static cocos2d::Scene NewGame();

	static cocos2d::Scene Continue();
};

#endif //__GAME_SCENE_H__