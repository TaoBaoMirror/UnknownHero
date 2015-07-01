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
	CurChunkMap = new ChunkMap();
	//
	mWorld.Init();
}


MapManager::~MapManager()
{
	CurChunkMap->removeFromParentAndCleanup(true);

}

ChunkMap* MapManager::ChangeMap(int index)
{
	EnterWorld(index);

	CurChunkMap->InitChunkMap("map\\CityMap.tmx");


	return CurChunkMap;
}

void MapManager::CreateWorld()
{
	mWorld.SetWorldSize(2,2);
	mWorld.CreateMaze();
	//
	mWorld.DeployChunkMapToWorld();
}

void MapManager::EnterWorld( int WorldLevel )
{
	CreateWorld();
	//
	//¼ÓÔØchunk
	mWorld.OnEnterWorld();
	if(mWorld.LoadChunk(CurChunkMap,mWorld.mEntranceChunkInMazeGPos))
	{
		GridPos bornPos;
		if (CurChunkMap->GetDoorGPos(downdoor,bornPos))
		{
			CurChunkMap->DeployHero(bornPos);
		}
	}
}

void MapManager::TransToChunk( int chunkDoorDir )
{
	//
	CurChunkMap->UndeployHero();
	//
	GridPos ToGird;
	if(mWorld.GetMazePos(CurChunkMap->GetInMazeGPos(),chunkDoorDir,ToGird))
	{
		if (mWorld.LoadChunk(CurChunkMap,ToGird))
		{
			GridPos bornPos;

			int toDir = mWorld.opposite(chunkDoorDir);

			if (CurChunkMap->GetDoorGPos(toDir,bornPos))
			{
				CurChunkMap->DeployHero(bornPos);
			}
		}
	}
}

void MapManager::LeaveWorld()
{
	CurChunkMap->UndeployHero();
	mWorld.OnLeaveWorld();
	//
}
