#include "ChunkMap.h"
#include "Graph/SparseGraph.h"
#include "Graph/GraphAlgorithms.h"
#include "Graph/GraphEdgeTypes.h"
#include "Graph/GraphNodeTypes.h"
#include "Graph/AStarHeuristicPolicies.h"

#include "SoldierManager.h"
#include "Soldier.h"
#include "SoldierPF.h"
#include "Messaging\MessageListenerManager.h"

#define GridLayer "GridLayer"	//网格数据层
#define CreatureLayer "CreatureLayer"	//生物体数据层
#define NULL_NODE -1

//
#include "Debug/GizmoSoldier.h"
//

ChunkMap::ChunkMap():EnableDebugDraw(true)
{
	pDebugDrawNode = cocos2d::DrawNode::create();
}

ChunkMap::~ChunkMap()
{

}

bool ChunkMap::InitChunkMap( std::string tmxFile )
{
	if (initWithTMXFile(tmxFile))
	{
		autorelease();
		//得到数据层
		auto pGridLayer = getLayer(GridLayer);
		auto sLayerSize = pGridLayer->getLayerSize();
		auto sTileSize = pGridLayer->getMapTileSize();
		//
		mGridMap.Init(sTileSize.width * sLayerSize.width,
					  sTileSize.height * sLayerSize.height,
					  sTileSize.width,sTileSize.height,
					  Vector2D(sTileSize.width * 0.5f,sTileSize.height * 0.5f));	//这里的LT的位置 还有待调整，可以根据，实际情况而定
		mGridMap.CreateMap(GridSceneMap::Quat);
		//
		mIM.Init(	sTileSize.width * sLayerSize.width,
					sTileSize.height * sLayerSize.height,
					sTileSize.width,sTileSize.height);
		//
		//地图数据MapNodeData的初始化
		int NodeNum = sLayerSize.width * sLayerSize.height;
		MapNodeDataList.reserve(NodeNum);

		for (int i = 0 ; i < NodeNum; ++i)
		{
			MapNodeData pMND;
			pMND.ID = i;
			MapNodeDataList.push_back(pMND);
			mGridMap.GMap().GetNode(i).SetExtraInfo(&MapNodeDataList.back());
		}
		//
		//从TMX读取的数据
		for (int lx = 0 ; lx < sLayerSize.width; ++lx)
		{
			for (int ly = 0 ; ly < sLayerSize.height; ++ly)
			{
				auto gid = pGridLayer->getTileGIDAt(cocos2d::Vec2(lx,ly));
				auto properties = getPropertiesForGID(gid).asValueMap();

				if (!properties.empty()) 
				{
					//Cost 部分
					auto nType = properties["Cost"].asInt();
					//调整一下Y的坐标
					int fix_y = sLayerSize.height - ly - 1 ;// 从0计数的
					int index = 0;
					mGridMap.GridPosToIndex(GridPos(lx,fix_y),index);
					auto& node = mGridMap.GetNode(index);
					if (nType == NULL_NODE)	//删除这个点
					{
						mGridMap.GMap().RemoveNode(index);
					}
					else
					{
						Cast_MapNodeData(node.ExtraInfo())->Type = nType;
					}

					
				}
			}
		}
		//生物体数据层加载
		auto pCreatureLayer = getLayer(CreatureLayer);
		auto sLayerSize = pGridLayer->getLayerSize();
		auto sTileSize = pGridLayer->getMapTileSize();
		//
		SetEnableDebugDraw(EnableDebugDraw);
		//
		return true;
	}
	//
	return false;
}

void ChunkMap::DebugRender()
{
	if(!EnableDebugDraw) return;
	//
	pDebugDrawNode->clear();
	//
	GridSceneMap::NavGraph::ConstNodeIterator NodeItr(mGridMap.GMap());
	const GridSceneMap::NavGraph::NodeType* pN;
	for (pN = NodeItr.begin(); !NodeItr.end(); pN=NodeItr.next())
	{
		const NavGraphNode<void*>* pNode = (const NavGraphNode<void*>*)pN;
		GridSceneMap::NavGraph::ConstEdgeIterator EdgeItr(mGridMap.GMap(), pN->Index());
		for (const GridSceneMap::NavGraph::EdgeType* pE = EdgeItr.begin(); 
			!EdgeItr.end(); 
			pE=EdgeItr.next())
		{

			const NavGraphNode<void*>& tNode = (const NavGraphNode<void*>&)( mGridMap.GMap().GetNode(pE->To()) );

			pDebugDrawNode->drawSegment(
				cocos2d::Vec2(pNode->Pos().x,pNode->Pos().y),
				cocos2d::Vec2(tNode.Pos().x,tNode.Pos().y),2,
				cocos2d::Color4F::RED);
		}
	}
	//
	for (pN = NodeItr.begin(); !NodeItr.end(); pN=NodeItr.next())
	{

		const NavGraphNode<void*>* pNode = (const NavGraphNode<void*>*)pN;

		MapNodeData* pMND = Cast_MapNodeData(pNode->ExtraInfo());
		cocos2d::Color4F color = cocos2d::Color4F::YELLOW;

		if (!pNode->Walkable())
		{
			color = cocos2d::Color4F::WHITE;

		}
		
		pDebugDrawNode->drawDot(cocos2d::Vec2(pNode->Pos().x,pNode->Pos().y),3,color);
	}
}


void ChunkMap::SetEnableDebugDraw( bool enableDraw )
{
	if (enableDraw)
	{
		addChild(pDebugDrawNode, 10);
		DebugRender();
	}
	else
	{
		pDebugDrawNode->removeFromParent();
		pDebugDrawNode->clear();
	}
	//
	EnableDebugDraw = enableDraw;
}

void ChunkMap::FreeChunkData()
{
	MapNodeDataList.clear();
}

bool ChunkMap::CheckCanArrived( const GridPos& A,const GridPos& B,std::list<GridPos>* GPosListPtr /*= NULL*/ )
{
	typedef Graph_SearchAStar<GridSceneMap::NavGraph, Heuristic_Euclid> AStarSearch;

	int iSource = -1;
	int iTarget = -1;

	mGridMap.GetIndex(A,iSource);
	mGridMap.GetIndex(B,iTarget);

	AStarSearch	AStar(mGridMap.GMap(),iSource,iTarget);
	std::list<int> path(AStar.GetPathToTarget());
	int path_node_num = path.size();
	if (path_node_num == 0)
	{
		return false;
	}
	//
	if (GPosListPtr != 0)
	{
		for(std::list<int>::iterator it = path.begin();it!= path.end();it++)
		{
			GridPos GPos;
			mGridMap.GetGridPos(*it,GPos);
			GPosListPtr->push_back(GPos);
		}
	}

	return true;
}

void ChunkMap::update( float delta )
{
	SoldierManager::Instance()->Update();

}

void ChunkMap::DeployCreature()
{
	SoldierManager::Instance()->Init();
	//
	int StartIndex = 0;

	GizmoSoldier* PlayerSoldier = GizmoSoldier::create();
	const GridPos& GPos_1 = GridPos(0,0);
	PlayerSoldier->SetToGPos(GPos_1);
	PlayerSoldier->SetID(StartIndex++);
	//
	SoldierManager::Instance()->RegisterSoldier(PlayerSoldier);
	MessageListenerManager::Instance()->RegisterMessageListener(PlayerSoldier);
	mIM.AddDynamicField(PlayerSoldier->GetSoldierPF());

	GizmoSoldier* EnemySoldier = GizmoSoldier::create();
	const GridPos& GPos_2 = GridPos(13,7);
	EnemySoldier->SetToGPos(GPos_2);
	EnemySoldier->SetID(StartIndex++);
	//
	SoldierManager::Instance()->RegisterSoldier(EnemySoldier);
	MessageListenerManager::Instance()->RegisterMessageListener(EnemySoldier);
	mIM.AddDynamicField(EnemySoldier->GetSoldierPF());

	addChild(PlayerSoldier,10);
	addChild(EnemySoldier,10);

}
