#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include "ChunkMap.h"

class MapManager
{
public:	
	~MapManager();

	static MapManager* GetInstance();

	void	EnterWorld(int WorldLevel);
	void	LeaveWorld();
	void	TransToChunk(int chunkDoorDir);	//触碰了门的方向

	ChunkMap* ChangeMap(int index);

	void CloseCurMap(){}//应该有这么个方法 这样当切换到选人界面或者城市界面,就应该去掉当前的chunkmap,changemap的时候也应该去掉前一个map

	ChunkMap*	GetCurChunkMap(){return CurChunkMap;}
	MapWorld*	GetWorld(){return &mWorld;}
protected:
	MapManager();
	static MapManager* m_Instance;
	//
	ChunkMap*	CurChunkMap;	
	//
	MapWorld	mWorld;
	//
	void	CreateWorld();

};

#endif //__MAP_MANAGER_H__