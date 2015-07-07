#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "Game\ChunkMap.h"

class SkillBarUI;
class MainControllerPanel;

class GameScene : cocos2d::Scene
{
public:
	GameScene();
	~GameScene();

	static cocos2d::Scene* createScene();

	bool SceneInit();
	bool init() override;

	virtual void update(float dt) override;

	void NewGame();

	void Continue();

	MainControllerPanel* GetOneArmBandit(){return pMainPanel;}  

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);

	static int LayerTag;
protected: 
	void TestMap();
	//SkillBarUI*	pSkillBarUI;
	MainControllerPanel*	pMainPanel;

	//cocos2d::EventListenerTouchOneByOne* _touchListener;
	//cocos2d::EventListenerKeyboard* _keyboardListener;
};

#endif //__GAME_SCENE_H__