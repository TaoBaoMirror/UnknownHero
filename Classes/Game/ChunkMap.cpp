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

#include "AttackRange.h"


#define GridLayer "GridLayer"	//�������ݲ�
#define CreatureLayer "CreatureLayer"	//���������ݲ�
#define SpawnLayer "SpawnLayer"	//�������ݲ�
#define RangeLayer "RangeLayer"	//��ʾ�����߲�

#define GridLayerTag 0xa0	//�������ݲ�
#define CreatureLayerTag 0xa1	//���������ݲ�
#define SpawnLayerTag 0xa2	//�������ݲ�
#define RangeLayerTag 0xa0	//��ʾ�����߷�Χ��


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
		//	������Χ�����

			Creature�ڱ༭��ʱ�����ǵ�����Ӧ����һ�µģ�
		*/
		auto pRangeLayer = getLayer(RangeLayer);
		if (pRangeLayer != nullptr)
		{
			this->addChild(cocos2d::Layer::create(),pRangeLayer->getLocalZOrder() + 1,RangeLayerTag);
		}
		
		for (int lx = 0 ; lx < sLayerSize.width; ++lx)
		{
			for (int ly = 0 ; ly < sLayerSize.height; ++ly)
			{
				cocos2d::Sprite* pSprite = pRangeLayer->getTileAt(cocos2d::Vec2(lx,ly));
				if (pSprite != nullptr)
				{
					pSprite->setVisible(false);
				}				
			}
		}
		/*
		//	���������ݲ����

			Creature�ڱ༭��ʱ�����ǵ�����Ӧ����һ�µģ�
		*/
		auto pCreatureLayer = getLayer(CreatureLayer);
		if (pCreatureLayer != nullptr)
		{
			this->addChild(cocos2d::Layer::create(),pCreatureLayer->getLocalZOrder() + 1,CreatureLayerTag);
		}
		
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

	SoldierManager::Instance()->Render();
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

cocos2d::TMXLayer* ChunkMap::GetCreatureTMXLayer()
{
	cocos2d::TMXLayer* pCreatureLayer = getLayer(CreatureLayer);

	return pCreatureLayer;
}

cocos2d::Layer* ChunkMap::GetCreatureLayer()
{
	return static_cast<cocos2d::Layer*>(this->getChildByTag(CreatureLayerTag));
}

cocos2d::TMXLayer* ChunkMap::GetRangeLayer()
{
	cocos2d::TMXLayer* pRangeLayer = getLayer(RangeLayer);

	return pRangeLayer;
}

void ChunkMap::FindSoldiersInRange( const GridPos& CenterGPos , int RangeSize , int RType ,std::vector<Soldier*>& out_SoldierList )
{
	std::vector<GridPos>	GPosList;
	switch(RType)
	{
	case RangeType::CIRCLE:
		GetGridSceneMap().FindTilesInCircle(GPosList,CenterGPos,RangeSize);
		break;
	case RangeType::QUAD:
		GetGridSceneMap().FindTilesInQuad(CenterGPos,RangeSize,GPosList);
		break;
	case RangeType::CROSS:
		GetGridSceneMap().FindTilesInCross(CenterGPos,RangeSize,RangeSize,GPosList);
		break;
	}
	//
	out_SoldierList.reserve(16);
	//
	//	����soldier�ķ��� ���Ա����㣬�ӵ��NodeMapData��Creature��Ѱ�ң�
	//	���߿���ͨ��SoldierManager�����GetSoldier��GPos��Ѱ��
	//
	for (int i = 0;i<GPosList.size();++i)
	{
		const GridPos& GPos = GPosList[i];
		int index = invalid_node_index;
		GetGridSceneMap().GetIndex(GPos,index);
		if (index != invalid_node_index)
		{
			NavGraphNode<void*>& node = GetGridSceneMap().GetNode(index);
			auto pNMD = (MapNodeData*)node.ExtraInfo();
			if (pNMD)
			{
				Soldier* soldier = pNMD->Creature;
				if (soldier != NULL)
				{
					out_SoldierList.push_back(soldier);
				}
			}

		}
	}
}

void ChunkMap::ShowRangeData(const std::vector<GridPos>&	AttackGPosList)
{
	auto pRangeLayer = GetRangeLayer();
	if (pRangeLayer != nullptr)
	{
		for (int i = 0 ; i < AttackGPosList.size(); ++i)
		{
			GridPos pGPos = AttackGPosList[i];

			cocos2d::Vec2 vecPos;

			GridPosToTiledGridPos(pGPos,vecPos);

			cocos2d::Sprite* pSprite = pRangeLayer->getTileAt(vecPos);
			if (pSprite != nullptr)
			{
				pSprite->setVisible(true);
			}				
		}
	}	
}

void ChunkMap::HideRangeData()
{
	auto pRangeLayer = GetRangeLayer();
	if (pRangeLayer != nullptr)
	{
		cocos2d::Size getsize = this->getMapSize();
		for (int lx = 0 ; lx < getsize.width; ++lx)
		{
			for (int ly = 0 ; ly < getsize.height; ++ly)
			{
				cocos2d::Sprite* pSprite = pRangeLayer->getTileAt(cocos2d::Vec2(lx,ly));
				if (pSprite != nullptr)
				{
					pSprite->setVisible(false);
				}				
			}
		}
	}
}
//------------------------------------------------------------=======

bool ChunkMap::GridPosToTiledGridPos(const GridPos& GPos,cocos2d::Vec2& out_TPos)
{
	auto pGridLayer = getLayer(GridLayer);
	if(pGridLayer == nullptr) return false;
	auto sLayerSize = pGridLayer->getLayerSize();
	//
	out_TPos.set(GPos.X,sLayerSize.height - GPos.Y - 1);
	return true;
}

bool ChunkMap::TiledGridPosToGridPos( const cocos2d::Vec2& TPos,GridPos& out_GPos )
{
	auto pGridLayer = getLayer(GridLayer);
	if(pGridLayer == nullptr) return false;
	auto sLayerSize = pGridLayer->getLayerSize();
	//
	out_GPos.SetTo(TPos.x,sLayerSize.height - TPos.y - 1);
	return true;
}
