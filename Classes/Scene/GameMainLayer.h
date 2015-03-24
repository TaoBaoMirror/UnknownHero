#ifndef __MAIN_LAYER_H__
#define __MAIN_LAYER_H__

#include "cocos2d.h"

class GameMainLayer : public cocos2d::Layer
{
public:
	GameMainLayer();
	~GameMainLayer();

	cocos2d::TMXLayer*			m_MonsterInitLayer;

	cocos2d::TMXLayer*			m_NPCInitLayer;

	cocos2d::TMXLayer*			m_BuildingLayer; 

	cocos2d::TMXLayer*			m_TerrainLayer;

	cocos2d::TMXObjectGroup*	m_PathObjectGroup;

	cocos2d::TMXTiledMap*		m_TMXMap;

	void LoadMap(int mapindex);

	void StartNewGame();

	void ContinueGame();

private:
	void ParseAndBuild();
};

#endif //__MAIN_LAYER_H__
