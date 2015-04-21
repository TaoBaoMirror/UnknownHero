#include "CommonFunc.h"


const GridSceneMap& G_GetSceneMap()
{
	return MapManager::GetInstance()->GetCurChunkMap().GetGridSceneMap();
}
