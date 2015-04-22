#include "CommonFunc.h"
#include "ChunkMap.h"
#include "MapManager.h"

const GridSceneMap& G_GetSceneMap()
{
	return MapManager::GetInstance()->GetCurChunkMap()->GetGridSceneMap();
}
