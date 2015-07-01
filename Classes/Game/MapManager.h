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
	void	TransToChunk(int chunkDoorDir);	//�������ŵķ���

	ChunkMap* ChangeMap(int index);

	void CloseCurMap(){}//Ӧ������ô������ �������л���ѡ�˽�����߳��н���,��Ӧ��ȥ����ǰ��chunkmap,changemap��ʱ��ҲӦ��ȥ��ǰһ��map

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