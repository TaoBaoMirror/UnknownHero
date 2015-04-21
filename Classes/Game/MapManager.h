#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include "ChunkMap.h"

class MapManager
{
public:	
	~MapManager();

	static MapManager* GetInstance();

	ChunkMap* ChangeMap(int index);
	/*
	void TileCoordForPosition(cocos2d::Size mapSize, cocos2d::Size tileSize, cocos2d::Vec2 position, int &coordX, int &coordY);

	void PositionForTileCoord(cocos2d::Size mapSize, cocos2d::Size tileSize, int coordX, int coordY, cocos2d::Vec2 &position);

	void PositionForTileCoord(cocos2d::Size mapSize, cocos2d::Size tileSize, int index, cocos2d::Vec2 &position);
	*/
	ChunkMap&	GetCurChunkMap(){return CurSceneMap;}
protected:
	MapManager();
	static MapManager* m_Instance;
	int m_CurLevelID;
	//
	ChunkMap	CurSceneMap;	
};

#endif //__MAP_MANAGER_H__