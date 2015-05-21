#ifndef __MARKTILE_MANAGER_H__
#define __MARKTILE_MANAGER_H__

#include "cocos2d.h"
#include <GridPos.h>

enum MarkTileType
{
	MarkTile_Move = 0,
	MarkTile_Attack,
};

class MarkTileManager
{
public:
	static MarkTileManager* GetInstance();

	~MarkTileManager(void);

	void Init();

	void Update(float dt);

	void SetMarkTiles(MarkTileType type, std::string key, const std::vector<GridPos>&	PointList);

	void ClearMarkTiles(std::string key);

	void ClearAllTiles();

private:
	MarkTileManager(void);

	static MarkTileManager* m_Instance;

	//-------------------

	//cocos2d::Vector<cocos2d::Sprite*> m_ShowMarkTiles;

	typedef cocos2d::Vector<cocos2d::Sprite*> MarkTileVec;
	std::map<std::string,MarkTileVec*> m_ShowMarkTiles;
};

#endif //__MARKTILE_MANAGER_H__
