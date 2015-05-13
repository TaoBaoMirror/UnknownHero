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


#define GridLayer "GridLayer"	//�������ݲ�
#define CreatureLayer "CreatureLayer"	//���������ݲ�
#define SpawnLayer "SpawnLayer"	//�������ݲ�



#define NULL_NODE -1

//
#include "Debug/GizmoSoldier.h"
#include "CreatureSpawnArea.h"
//

ChunkMap::ChunkMap():EnableDebugDraw(true)
{
	pDebugDrawNode = cocos2d::DrawNode::create();

	//�������һЩ��Ϣ
	ttfConfig = cocos2d::TTFConfig("fonts/arial.ttf", 12);
}

ChunkMap::~ChunkMap()
{

}

bool ChunkMap::InitChunkMap( std::string tmxFile )
{
	if (initWithTMXFile(tmxFile))
	{
		autorelease();
		//�õ����ݲ�
		auto pGridLayer = getLayer(GridLayer);
		auto sLayerSize = pGridLayer->getLayerSize();
		auto sTileSize = pGridLayer->getMapTileSize();
		cocos2d::Size sMapSize(sLayerSize.width * sTileSize.width,sLayerSize.height * sTileSize.height);
		//
		mGridMap.Init(sTileSize.width * sLayerSize.width,
					  sTileSize.height * sLayerSize.height,
					  sTileSize.width,sTileSize.height,
					  Vector2D(sTileSize.width * 0.5f,sTileSize.height * 0.5f));	//�����LT��λ�� ���д����������Ը��ݣ�ʵ���������
		mGridMap.CreateMap(GridSceneMap::Quat);
		//
		mIM.Init(	sTileSize.width * sLayerSize.width,
					sTileSize.height * sLayerSize.height,
					sTileSize.width,sTileSize.height);
		//
		//��ͼ����MapNodeData�ĳ�ʼ��
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
		//��TMX��ȡ������
		for (int lx = 0 ; lx < sLayerSize.width; ++lx)
		{
			for (int ly = 0 ; ly < sLayerSize.height; ++ly)
			{
				auto gid = pGridLayer->getTileGIDAt(cocos2d::Vec2(lx,ly));
				auto properties = getPropertiesForGID(gid).asValueMap();

				if (!properties.empty()) 
				{
					//Cost ����
					auto nType = properties["Cost"].asInt();
					//����һ��Y������
					int fix_y = sLayerSize.height - ly - 1 ;// ��0������
					int index = 0;
					mGridMap.GridPosToIndex(GridPos(lx,fix_y),index);
					auto& node = mGridMap.GetNode(index);
					if (nType == NULL_NODE)	//ɾ�������
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
		/*
		//	���������ݲ����

			Creature�ڱ༭��ʱ�����ǵ�����Ӧ����һ�µģ�
		*/
		auto pCreatureLayer = getLayer(CreatureLayer);
		for (int lx = 0 ; lx < sLayerSize.width; ++lx)
		{
			for (int ly = 0 ; ly < sLayerSize.height; ++ly)
			{
				auto gid = pCreatureLayer->getTileGIDAt(cocos2d::Vec2(lx,ly));
				auto properties = getPropertiesForGID(gid);
				if (!properties.isNull())
				{
					cocos2d::ValueMap& dict = properties.asValueMap();
					int   type = dict["CreatureID"].asInt();
					//cocos2d::CCLog("type %d",type);
					//ͨ��CreatureIDȥ������Ӧ������
					// CreatureFactory
					int	  direction = dict["Direction"].asInt();
					//ѡ��������

				}
				
			}
		}
		/*
			Create Spawn Area
		*/
		auto pSpawnLayer = this->getObjectGroup(SpawnLayer);
		{
			auto& objects = pSpawnLayer->getObjects();

			for (auto& obj : objects)
			{
				cocos2d::ValueMap& dict = obj.asValueMap();

				float x = dict["x"].asFloat();
				float y = dict["y"].asFloat();
				float width = dict["width"].asFloat();
				float height = dict["height"].asFloat();

				//���涼��AreaInit��Ҫ��
				int id = dict["AreaID"].asInt();
				std::vector<int>	IDVec;
				CreatureSpawnArea::ParseCreatureIDs(dict["CreatureIDs"].asString(),IDVec);
				float timegap = dict["TimeGap"].asFloat();
				cocos2d::Size size( width/sTileSize.width,height/sTileSize.height );	//ת��ΪTile����
				GridPos BaseGPos(x/sTileSize.width,y/sTileSize.height);

				CreatureSpawnArea* area = new CreatureSpawnArea();
				if (!GetSpawnArea(id))
				{
					area->Init(id,IDVec.front(),timegap,BaseGPos,size.width,size.height,this);
					SpawnAreaList.insert(std::make_pair(id,area));
				}


			}


		}





		//
		SetEnableDebugDraw(EnableDebugDraw);
		//
		OnAfterInit();
		//
		return true;
	}
	//
	return false;
}

void ChunkMap::DebugRender()
{
	const int NodeIndexLabelTag = 0xf; 

	if(!EnableDebugDraw) return;
	//
	pDebugDrawNode->clear();
	pDebugDrawNode->removeChildByTag(NodeIndexLabelTag);
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
		pDebugDrawNode->removeChildByTag(NodeIndexLabelTag + pNode->Index());
		char szIndex[8];
		itoa(pNode->Index(),szIndex,10);
		auto label = cocos2d::Label::createWithTTF(ttfConfig,std::string(szIndex));
		label->setPosition(cocos2d::Vec2(pNode->Pos().x,pNode->Pos().y+10));
		label->setColor(cocos2d::Color3B::BLACK);
		pDebugDrawNode->addChild(label,1,NodeIndexLabelTag + pNode->Index());

	}

	//
	for (auto it = SpawnAreaList.begin();it != SpawnAreaList.end();++it)
	{
		CreatureSpawnArea* pArea = it->second;
		auto AreaGPos = pArea->GetArea();
		for (GridPos GPos : AreaGPos)
		{
			Vector2D pos;

			GetGridSceneMap().GridPosToWorldPos(GPos,pos);

			pDebugDrawNode->drawDot(cocos2d::Vec2(pos.x,pos.y),14,cocos2d::Color4F::GREEN);

		}
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

Soldier* ChunkMap::InstantiateCreature( const int CreatureID,const GridPos& GPos,const int DirectionType )
{
	return 0;
}

CreatureSpawnArea* ChunkMap::GetSpawnArea( int AreaID )
{
	auto it = SpawnAreaList.find(AreaID);

	if (it != SpawnAreaList.end())
	{
		return it->second;
	}

	return nullptr;
}

void ChunkMap::Reset()
{
	mIM.Clear();
	MapNodeDataList.clear();
	mGridMap.Clear();
	//
	auto it = SpawnAreaList.begin();
	while(it != SpawnAreaList.end())
	{
		it->second->release();
		++it;
	}
	SpawnAreaList.clear();
	//
	bLoaded = false;
	SetEnableDebugDraw(false);
}

void ChunkMap::OnAfterInit()
{

}

void ChunkMap::onEnter()
{
	cocos2d::TMXTiledMap::onEnter();

}

cocos2d::TMXLayer* ChunkMap::GetCreatureLayer()
{
	cocos2d::TMXLayer* pCreatureLayer = getLayer(CreatureLayer);

	return pCreatureLayer;
}