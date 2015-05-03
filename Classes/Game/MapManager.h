#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include "ChunkMap.h"

class MapManager
{
public:	
	~MapManager();

	static MapManager* GetInstance();

	ChunkMap* ChangeMap(int index);

	void CloseCurMap(){}//应该有这么个方法 这样当切换到选人界面或者城市界面,就应该去掉当前的chunkmap,changemap的时候也应该去掉前一个map
	/*
	void TileCoordForPosition(cocos2d::Size mapSize, cocos2d::Size tileSize, cocos2d::Vec2 position, int &coordX, int &coordY);

	void PositionForTileCoord(cocos2d::Size mapSize, cocos2d::Size tileSize, int coordX, int coordY, cocos2d::Vec2 &position);

	void PositionForTileCoord(cocos2d::Size mapSize, cocos2d::Size tileSize, int index, cocos2d::Vec2 &position);
	*/
	ChunkMap*	GetCurChunkMap(){return CurSceneMap;}
protected:
	MapManager();
	static MapManager* m_Instance;
	int m_CurLevelID;
	//
	ChunkMap*	CurSceneMap;	
};

#endif //__MAP_MANAGER_H__