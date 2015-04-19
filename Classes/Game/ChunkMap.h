/********************************************************************
	created:	2015/04/18
	created:	18:4:2015   16:21
	filename: 	E:\UnknownHero\Classes\Map\ChunkMap.h
	file path:	E:\UnknownHero\Classes\Map
	file base:	ChunkMap
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef ChunkMap_h__
#define ChunkMap_h__

#include "cocos2d.h"
#include "GridSceneMap.h"
#include "GameInfluenceMap.h"
#include "MapNodeData.h"
/*
	地图首先是分层的，这里单另着重数据层

	1、通过Tiled的图层去刷数据，用一个颜色层去刷地表网格，如，白色的tile意味着在GridMap上有节点，
	是可行走区域，黑色是没有节点的。然后其他颜色用来刷 地表节点的价值
	2、地图上面的Obj 通过Obj层去放置，然后在，Soldier生成的时候，去吸附在网格上~

	这个ChunkMap可以是一直存在的，然后通过init去变换Map中的内容，然后MapManager这个实力去得到当前
	的ChunkMap，然后其他组件通过‘单件’去访问当前的这个ChunkMap的数据部分





*/
class ChunkMap : public cocos2d::TMXTiledMap
{
public:
	ChunkMap();
	~ChunkMap();
	//
	bool	InitChunkMap(std::string tmxFile);
	//
protected:
	GridSceneMap		mGridMap;
	GameInfluenceMap	mIM;
	std::vector<MapNodeData>	MapNodeDataList;
private:
};

#endif // ChunkMap_h__
