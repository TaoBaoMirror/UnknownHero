#include "MapManager.h"

MapManager* MapManager::m_Instance = 0;

MapManager* MapManager::GetInstance()
{
	if (m_Instance == 0)
	{
		m_Instance = new MapManager();
	}

	return m_Instance;
}

MapManager::MapManager()
{
}


MapManager::~MapManager()
{
}

ChunkMap* MapManager::ChangeMap(int index)
{
	m_CurLevelID = index;

	//LoadMapResName(realid);

	//2 load map
	std::stringstream ss;
	ss << index;
	std::string strIndex = ss.str();
	std::string mapName = "Map_" + strIndex;


	return &CurSceneMap;
}
/*
void MapManager::TileCoordForPosition(cocos2d::Size mapSize, cocos2d::Size tileSize, cocos2d::Vec2 position, int &coordX, int &coordY)
{
	coordX = (int)(position.x / tileSize.width);

	coordY = (int)(((mapSize.height * tileSize.height) - position.y) / tileSize.height);
}

void MapManager::PositionForTileCoord(cocos2d::Size mapSize, cocos2d::Size tileSize, int coordX, int coordY, cocos2d::Vec2 &position)
{
	position.x = tileSize.width * (float)coordX;
	position.y = mapSize.height * tileSize.height - tileSize.height * (float)coordY;

	coordX = (int)(position.x / tileSize.width);

	coordY = (int)(((mapSize.height * tileSize.height) - position.y) / tileSize.height);
}

void MapManager::PositionForTileCoord(cocos2d::Size mapSize, cocos2d::Size tileSize, int index, cocos2d::Vec2 &position)
{
	int coordX = index % (int)mapSize.width;

	int coordY = index / (int)mapSize.width;

	position.x = tileSize.width * (float)coordX;
	position.y = mapSize.height * tileSize.height - tileSize.height * (float)coordY;

	coordX = (int)(position.x / tileSize.width);

	coordY = (int)(((mapSize.height * tileSize.height) - position.y) / tileSize.height);
}
*/