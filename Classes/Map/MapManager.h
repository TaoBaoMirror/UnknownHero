#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include "cocos2d.h"

class MapManager
{
public:	
	~MapManager();

	static MapManager* getInstance();

	cocos2d::TMXTiledMap* ChangeMap(int index);

	void TileCoordForPosition(cocos2d::Size mapSize, cocos2d::Size tileSize, cocos2d::Vec2 position, int &coordX, int &coordY);

	void PositionForTileCoord(cocos2d::Size mapSize, cocos2d::Size tileSize, int coordX, int coordY, cocos2d::Vec2 &position);

	void PositionForTileCoord(cocos2d::Size mapSize, cocos2d::Size tileSize, int index, cocos2d::Vec2 &position);

protected:
	MapManager();
	static MapManager* m_Instance;

	int m_CurLevelID;
};

#endif //__MAP_MANAGER_H__