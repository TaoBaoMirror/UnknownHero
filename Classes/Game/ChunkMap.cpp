#include "ChunkMap.h"
#include "Graph/SparseGraph.h"
#include "Graph/GraphAlgorithms.h"
#include "Graph/GraphEdgeTypes.h"
#include "Graph/GraphNodeTypes.h"
#include "Graph/AStarHeuristicPolicies.h"

#define GridLayer "GridLayer"
#define NULL_NODE -1



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
					  sLayerSize.width,sLayerSize.height,
					  Vector2D(0,0));	//这里的LT的位置 还有待调整，可以根据，实际情况而定
		mGridMap.CreateMap(GridSceneMap::Quat);
		//
		mIM.Init(	sTileSize.width * sLayerSize.width,
					sTileSize.height * sLayerSize.height,
					sLayerSize.width,sLayerSize.height);
		//
		//地图数据MapNodeData的初始化
		int NodeNum = sLayerSize.width * sLayerSize.height;
		MapNodeDataList.reserve(NodeNum);

		for (int i = 0 ; i < NodeNum; ++i)
		{
			MapNodeData pMND;
			MapNodeDataList.push_back(pMND);	//这样添加的数据，内存地址不会变动的
		}
		for (int i = 0 ; i < MapNodeDataList.size(); ++i)
		{
			MapNodeData* ptr = &(MapNodeDataList[MapNodeDataList.size() - 1]);
			mGridMap.GMap().GetNode(ptr->ID).SetExtraInfo(ptr);
		}
		//
		//从TMX读取的数据
		for (int lx = 0 ; lx < sLayerSize.width; ++lx)
		{
			for (int ly = 0 ; lx < sLayerSize.height; ++ly)
			{
				auto gid = pGridLayer->getTileGIDAt(cocos2d::Vec2(lx,ly));
				for(const auto& value : getPropertiesForGID(gid).asValueMap())
				{
					std::string szFirst = value.first;
					//std::string szSecond = value.second.asString();
					//调整一下Y的坐标
					int fix_y = sLayerSize.height - ly;
					int index = 0;
					mGridMap.GridPosToIndex(GridPos(lx,fix_y),index);
					auto& node = mGridMap.GetNode(index);
					//
					if (szFirst == "Cost")
					{
						int nType = value.second.asInt();
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
		}

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
