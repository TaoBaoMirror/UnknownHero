#include "ChunkMap.h"

#define GridLayer "GridLayer"



ChunkMap::ChunkMap()
{

}

ChunkMap::~ChunkMap()
{

}

bool ChunkMap::InitChunkMap( std::string tmxFile )
{
	if (initWithTMXFile(tmxFile))
	{
		autorelease();
		//
		auto pGridLayer = getLayer(GridLayer);
		auto sLayerSize = pGridLayer->getLayerSize();
		auto sTileSize = pGridLayer->getMapTileSize();
		//
		mGridMap.Init();
		//
		return true;
	}
	//
	return false;
}
//////////////////////////////////////////////////////////////////////////
void ChunkMap::FreeChunkData()
{
	MapNodeDataList.clear();
}
