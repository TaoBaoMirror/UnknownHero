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
	3、也许还有一个Obj的运动轨迹层，用来布置一些机关的轨迹，或者巡逻兵的轨迹
	这个ChunkMap可以是一直存在的，然后通过init去变换Map中的内容，然后MapManager这个实力去得到当前
	的ChunkMap，然后其他组件通过‘单件’去访问当前的这个ChunkMap的数据部分





*/
class CreatureSpawnArea;

class TMXLayer;

class ChunkMap : public cocos2d::TMXTiledMap
{
public:
	ChunkMap();
	~ChunkMap();
	//
	bool	InitChunkMap(std::string tmxFile);
	virtual void OnAfterInit();
	void	Reset();
	//
	Soldier*	InstantiateCreature(const int CreatureID,const GridPos& GPos,const int DirectionType);


	GridSceneMap&	GetGridSceneMap() { return mGridMap;}
	const GridSceneMap&	GetGridSceneMap() const { return mGridMap;}
	GameInfluenceMap&	GetGameInfluenceMap() { return mIM;}
	const GameInfluenceMap&	GetGameInfluenceMap() const{ return mIM;}
	CreatureSpawnArea* GetSpawnArea(int AreaID);

	cocos2d::TMXLayer* GetCreatureTMXLayer();
	cocos2d::Layer* GetCreatureLayer();


	bool  CheckCanArrived(const GridPos& A,const GridPos& B,std::list<GridPos>* GPosListPtr = NULL);
	// 一些重写的函数
	void update(float delta) override;
	//
	void FreeChunkData();
	void DeployCreature();
	//
	void onEnter() override;


	//
	void FindSoldiersInRange(const GridPos& CenterGPos , int RangeSize , int RType ,std::vector<Soldier*>&	out_SoldierList);

	
protected:
	GridSceneMap		mGridMap;
	GameInfluenceMap	mIM;
	//地图里面的数据信息
	std::vector<MapNodeData>			MapNodeDataList;
	//这里去管理Area
	//这里是只是保存指针，进行调用，而不想Ref++，所以没有使用cocos2d::Vector Map
	std::map<int,CreatureSpawnArea*>	SpawnAreaList;	
	//是否已经载入
	bool	bLoaded;

private:
public:
	void	DebugRender();
	void	SetEnableDebugDraw(bool enableDraw);
	cocos2d::DrawNode*	pDebugDrawNode;
	bool	EnableDebugDraw;
	cocos2d::TTFConfig ttfConfig;
};

#endif // ChunkMap_h__
