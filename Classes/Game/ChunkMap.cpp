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

#include "Actor/PlayerManager.h"
#include "Actor/Hero.h"
#include "Actor/Monster.h"
#include "Actor/EnemyManager.h"
#include "Actor/ActorPathFinderCalculateFunc.h"

#include "Game/Trigger/GameTrigger.h"
#include "Scene/GameManager.h"
#include "base/CCEventListenerTouch.h"
#include "Bullet/GameBullet.h"
#include "MapManager.h"
#include "Actor/BossManager.h"
#include "Actor/Boss/Boss.h"

#define GridLayer "GridLayer"	//网格数据层
#define CreatureLayer "CreatureLayer"	//生物体数据层
#define SpawnLayer "SpawnLayer"	//卵域数据层
#define RangeLayer "RangeLayer"	//显示的行走层
#define EffectLayer "EffectLayer"	//显示的特效层，包括子弹
#define TriggerLayer "TriggerLayer"	//显示的特效层，包括子弹
#define DoorLayer "DoorLayer"	//




#define GridLayerTag 0xa0	//网格数据层
#define CreatureLayerTag 0xa1	//生物体数据层
#define SpawnLayerTag 0xa2	//卵域数据层
#define RangeLayerTag 0xa3	//显示的行走范围层
#define EffectLayerTag 0xa4	//显示的行走范围层
#define TriggerLayerTag 0xa5	//显示的trigger范围层




#define NULL_NODE -1

//
#include "Debug/GizmoSoldier.h"
#include "CreatureSpawnArea.h"

///-------------------------
USING_NS_CC;
///-------------------------
// 静态函数
// add by Hitman [5/30/2015]
Actor* ChunkMap::InstantiateCreature(const std::string& CreatureType,const int TableID,const int DirectionType,const GridPos& GPos)
{
	static int nextID = 0;

	if (CreatureType.compare("Hero") == 0)
	{
		Hero* pHero = PlayerManager::GetInstance()->GetHero();
		pHero->SetToGPos(GPos);
		pHero->UpdatePosition();
		pHero->UpdateToCCWorldPos();
		return pHero;
	}

	if (CreatureType.compare("Monster") == 0)
	{
		Monster* pMonster = EnemyManager::GetInstance()->CreateMonster(DirectionType);
		pMonster->SetToGPos(GPos);
		pMonster->UpdatePosition();
		pMonster->UpdateToCCWorldPos();
		return pMonster;

	}

	return 0;
}

//ctor
ChunkMap::ChunkMap():EnableDebugDraw(true),mChunkFlag(unexplored)
{
	pDebugDrawNode = cocos2d::DrawNode::create();

	//可以输出一些信息
	ttfConfig = cocos2d::TTFConfig("fonts/arial.ttf", 12);
	//
	autorelease();

}

ChunkMap::~ChunkMap()
{

}

bool ChunkMap::InitChunkMap( std::string tmxFile )
{
	if (initWithTMXFile(tmxFile))
	{
		//得到数据层
		auto pGridLayer = getLayer(GridLayer);
		auto sLayerSize = pGridLayer->getLayerSize();
		auto sTileSize = pGridLayer->getMapTileSize();
		cocos2d::Size sMapSize(sLayerSize.width * sTileSize.width,sLayerSize.height * sTileSize.height);
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

		/*
		//	攻击范围层加载
		*/
		auto pRangeLayer = getLayer(RangeLayer);
		if (pRangeLayer != nullptr)
		{
			auto layer = cocos2d::Layer::create();
			this->addChild(layer,pRangeLayer->getLocalZOrder() + 1,RangeLayerTag);
			//
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
		}
		

		/*
		//	生物体数据层加载

			Creature在编辑的时候，他们的属性应该是一致的，
		*/
		auto pCreatureLayer = getLayer(CreatureLayer);
		cocos2d::Layer* pRenderCreatureLayer = nullptr;
		if (pCreatureLayer != nullptr)
		{
			pRenderCreatureLayer = cocos2d::Layer::create();
			this->addChild(pRenderCreatureLayer,pCreatureLayer->getLocalZOrder() + 4,CreatureLayerTag);
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
					std::string   type = dict["Type"].asString();
					int   tableID = dict["TableID"].asInt();
					//cocos2d::CCLog("type %d",type);
					//通过CreatureID去生产响应的生物
					// CreatureFactory
					int	  direction = dict["Direction"].asInt();
					//选择生物体
					int fix_y = sLayerSize.height - ly - 1 ;// 从0计数的
					GridPos Stay_GPos  = GridPos(lx,fix_y);
					auto actor = InstantiateCreature(type,tableID,direction,Stay_GPos);
					if (type.compare("Monster") == 0 )
					{
						DeployActor(actor,Stay_GPos);
					}
					
				}
				
			}
		}
		//2015-7-6 test
		
		Boss* pTestBoss = BossManager::GetInstance()->CreateBoss(BossType::BossType_GoblinKing);
		DeployActor(pTestBoss,GridPos(8,3));
		
		//end

		/*
			Create Spawn Area
		*/
		auto pSpawnLayer = this->getObjectGroup(SpawnLayer);
		if(pSpawnLayer != nullptr)
		{
			auto& objects = pSpawnLayer->getObjects();

			for (auto& obj : objects)
			{
				cocos2d::ValueMap& dict = obj.asValueMap();

				float x = dict["x"].asFloat();
				float y = dict["y"].asFloat();
				float width = dict["width"].asFloat();
				float height = dict["height"].asFloat();

				//下面都是AreaInit需要的
				int id = dict["AreaID"].asInt();
				std::vector<int>	IDVec;
				CreatureSpawnArea::ParseCreatureIDs(dict["CreatureIDs"].asString(),IDVec);
				float timegap = dict["TimeGap"].asFloat();
				cocos2d::Size size( width/sTileSize.width,height/sTileSize.height );	//转换为Tile个数
				GridPos BaseGPos(x/sTileSize.width,y/sTileSize.height);

				CreatureSpawnArea* area = new CreatureSpawnArea();
				if (!GetSpawnArea(id))
				{
					area->Init(id,IDVec.front(),timegap,BaseGPos,size.width,size.height,this);
					SpawnAreaList.insert(std::make_pair(id,area));
				}


			}
		}

		/*
			Trigger 
		*/
		auto pTriggerLayer = this->getObjectGroup(TriggerLayer);

		if(pTriggerLayer != nullptr)
		{
			this->addChild(cocos2d::Layer::create(),pCreatureLayer->getLocalZOrder() + 2,TriggerLayerTag);
			//如果是没有被探险的,则加载
			if (!IsExplored())
			{			
				auto& objects = pTriggerLayer->getObjects();

				for (auto& obj : objects)
				{
					cocos2d::ValueMap& dict = obj.asValueMap();

					float x = dict["x"].asFloat();
					float y = dict["y"].asFloat();

					//下面都是AreaInit需要的
					int type = dict["TriggerType"].asInt();
					GridPos BaseGPos(x/sTileSize.width,y/sTileSize.height);

					auto trigger = TriggerManager::GetInstance()->CreateTrigger(nullptr,type,BaseGPos,this);
					if (trigger)
					{
						trigger->Born();
					}
					//

				}
			}
		}
		/* DOOR */
		auto pDoorObjLayer = this->getObjectGroup(DoorLayer);

		if(pDoorObjLayer != nullptr)
		{
	
			auto& objects = pDoorObjLayer->getObjects();

			for (auto& obj : objects)
			{
				cocos2d::ValueMap& dict = obj.asValueMap();

				float x = dict["x"].asFloat();
				float y = dict["y"].asFloat();

				//下面都是AreaInit需要的
				int type = StringToDir(dict["Dir"].asString());
				GridPos BaseGPos(x/sTileSize.width,y/sTileSize.height);
				//
				mDoorGPosList.insert(std::make_pair(type,BaseGPos));
			}
		}
		//增加一些其他的图层
		{
			auto layer = cocos2d::Layer::create();
			this->addChild(layer,pCreatureLayer->getLocalZOrder() + 3 + 1,EffectLayerTag);
		}

		//auto s = cocos2d::Sprite::createWithSpriteFrameName("effect_posion_4.png");
		//GetEffectLayer()->addChild(s);

		//
		//SetEnableDebugDraw(EnableDebugDraw);
		//
		OnAfterInit();
		//

		//input
		_eventDispatcher->removeEventListener(_touchListener);
		_eventDispatcher->removeEventListener(_keyboardListener);
		//
		auto listener = cocos2d::EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);

		listener->onTouchBegan = CC_CALLBACK_2(ChunkMap::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(ChunkMap::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(ChunkMap::onTouchEnded, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		_touchListener = listener;
		//--------------------------
		auto listenerKeyboard = EventListenerKeyboard::create();
		listenerKeyboard->onKeyPressed = CC_CALLBACK_2(ChunkMap::onKeyPressed, this);
		listenerKeyboard->onKeyReleased = CC_CALLBACK_2(ChunkMap::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
		_keyboardListener = listenerKeyboard;
		//--------------------------
		//end
		bLoaded = true;
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
		if(pN == nullptr) break;
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
		_itoa(pNode->Index(),szIndex,10);
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

bool ChunkMap::CheckCanArrived( Soldier* who,const GridPos& A,const GridPos& B,std::list<GridPos>* GPosListPtr /*= NULL*/ )
{
	typedef Graph_SearchAStar<GridSceneMap::NavGraph, ActorPathFinderCalculateFunc> AStarSearch;

	int iSource = -1;
	int iTarget = -1;

	mGridMap.GetIndex(A,iSource);
	mGridMap.GetIndex(B,iTarget);

	AStarSearch	AStar(mGridMap.GMap(),iSource,iTarget,who);
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

	if (bLoaded == false) return;

	mMapRuleSys.Update(delta);

	SoldierManager::Instance()->Update();

	SoldierManager::Instance()->Render();

	//TEST 门的检测
	for (auto it = mDoorGPosList.begin();it != mDoorGPosList.end();++it)
	{
		const GridPos& DoorGPos = it->second;
		//
		if (FindSoldierAtGPos(DoorGPos) == PlayerManager::GetInstance()->GetHero())
		{
			MapManager::GetInstance()->TransToChunk(it->first);
		}
	}

}

void ChunkMap::DeployHero(const GridPos& GPos)
{
	Hero* pHero  = PlayerManager::GetInstance()->GetHero();
	//
	if (pHero!= nullptr)
	{
		DeployActor(pHero,GPos);
		//
		OnHeroEnter();
	}
	//
		
}


void ChunkMap::DeployActor( Actor* pActor , const GridPos& GPos )
{
	if (pActor != nullptr)
	{
		pActor->SetToGPos(GPos);
		pActor->UpdatePosition();
		pActor->UpdateToCCWorldPos();
		//
		GetCreatureLayer()->addChild(pActor);
		mIM.AddDynamicField(pActor->GetSoldierPF());
		//
		pActor->OnDeployChunk();
	}
}


void ChunkMap::UndeployHero()
{
	Hero* pHero  = PlayerManager::GetInstance()->GetHero();
	//
	if (pHero!= nullptr)
	{
		if (pHero->getParent() != nullptr)
		{
			//bug 不知道为啥，之前引用是2 ，但是removefromParent 就变成0了 然后就释放掉了hero

			pHero->retain();
			pHero->removeFromParent();
			mIM.RemoveDynamicField(pHero->GetSoldierPF());
			//
			OnHeroLeave();
		}

	}
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
	mChunkFlag = unexplored;
	bLoaded = false;

	//
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
	//仅仅清掉数据
	UndeployHero();
	//PlayerManager::GetInstance()->GetHero()->removeFromParentAndCleanup(true);
	EnemyManager::GetInstance()->ClearAllEnemy();
	//
	GameBulletManager::GetInstance()->ReleaseAllBullets();
	//
	if(GetCreatureLayer())	GetCreatureLayer()->removeAllChildrenWithCleanup(true);
	if(GetEffectLayer())	GetEffectLayer()->removeAllChildrenWithCleanup(true);
	if(GetTriggerLayer())	GetTriggerLayer()->removeAllChildrenWithCleanup(true);
	//
	removeAllChildrenWithCleanup(true);
	//SetEnableDebugDraw(false);
}

void ChunkMap::OnAfterInit()
{
	//设置规则
	mMapRuleSys.SetCurrentState(MapRule_FastMonster);
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


cocos2d::Layer* ChunkMap::GetTriggerLayer()
{
	return static_cast<cocos2d::Layer*>(this->getChildByTag(TriggerLayerTag));
}


cocos2d::Layer* ChunkMap::GetEffectLayer()
{
	return static_cast<cocos2d::Layer*>(this->getChildByTag(EffectLayerTag));
}


cocos2d::TMXLayer* ChunkMap::GetRangeLayer()
{
	cocos2d::TMXLayer* pRangeLayer = getLayer(RangeLayer);

	return pRangeLayer;
}

Soldier* ChunkMap::FindSoldierAtGPos( const GridPos& CenterGPos )
{
	int index = invalid_node_index;
	GetGridSceneMap().GetIndex(CenterGPos,index);
	if (index != invalid_node_index)
	{
		NavGraphNode<void*>& node = GetGridSceneMap().GetNode(index);
		auto pNMD = (MapNodeData*)node.ExtraInfo();
		if (pNMD)
		{
			Soldier* soldier = pNMD->Creature;
			if (soldier != NULL)
			{
				return soldier;
			}
		}
	}
	//
	return nullptr;
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
	//	搜索soldier的方法 可以遍历点，从点的NodeMapData的Creature中寻找，
	//	或者可以通过SoldierManager里面的GetSoldier（GPos）寻找
	//
	for (int i = 0;i<GPosList.size();++i)
	{
		const GridPos& GPos = GPosList[i];
		auto soldier = FindSoldierAtGPos(GPos);
		if ( soldier != nullptr)
		{
			out_SoldierList.push_back(soldier);
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

bool ChunkMap::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchLocation = touch->getLocation();    

	auto nodePosition = convertToNodeSpace( touchLocation );
	//log("GameScene::onTouchBegan, pos: %f,%f -> %f,%f", touchLocation.x, touchLocation.y, nodePosition.x, nodePosition.y);

	return GameManager::GetInstance()->MouseDown(touchLocation);
}

void ChunkMap::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchLocation = touch->getLocation();    
	auto nodePosition = convertToNodeSpace( touchLocation );

	//log("GameScene::onTouchMoved, pos: %f,%f -> %f,%f", touchLocation.x, touchLocation.y, nodePosition.x, nodePosition.y);

	GameManager::GetInstance()->MouseMove(nodePosition);  
}

void ChunkMap::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchLocation = touch->getLocation();    
	auto nodePosition = convertToNodeSpace( touchLocation );

	//log("GameScene::onTouchEnded, pos: %f,%f -> %f,%f", touchLocation.x, touchLocation.y, nodePosition.x, nodePosition.y);

	GameManager::GetInstance()->MouseUp(nodePosition);
}

void ChunkMap::onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
	GameManager::GetInstance()->GameKeyPressed(code, event);
}

void ChunkMap::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
	GameManager::GetInstance()->GameKeyReleased(code, event);
}

void ChunkMap::OnHeroEnter()
{
	//已经探险过了
	Explored();
	Staying();
	//

	//
	TriggerManager::GetInstance()->OnChunkEnter();

}

void ChunkMap::OnHeroLeave()
{
	Leave();
	//


	//
	TriggerManager::GetInstance()->OnChunkLeave();
}

bool ChunkMap::GetDoorGPos( int dir,GridPos& out_GPos )
{
	auto it = mDoorGPosList.find(dir);
	if (it != mDoorGPosList.end())
	{
		out_GPos = it->second;
		return true;
	}
	//
	return false;
}

void ChunkMap::GetDirOffset( int dir,GridPos& out_GPos )
{
	//
	if((dir & downdoor) > 0  &&  out_GPos.Y + 1  < GetGridSceneMap().GetSizeNumY() ) out_GPos.SetTo(out_GPos.X,out_GPos.Y + 1);
	if((dir & topdoor) > 0  &&  out_GPos.Y - 1  >= 0  ) out_GPos.SetTo(out_GPos.X,out_GPos.Y - 1); 
	if((dir & leftdoor) > 0  &&  out_GPos.X - 1  >= 0 ) out_GPos.SetTo(out_GPos.X-1,out_GPos.Y); 
	if((dir & rightdoor) > 0  &&  out_GPos.X + 1  < GetGridSceneMap().GetSizeNumX() ) out_GPos.SetTo(out_GPos.X+1,out_GPos.Y); 
	//
}


void ChunkMap::SetChunkSaveDataInWorld( ChunkSaveDataInWorld& data )
{
	mChunkFlag = data.ChunkState;
}

int ChunkMap::StringToDir( const std::string&  c )
{
	if(c == "N")	return topdoor;
	if(c == "S")	return downdoor;
	if(c == "W")	return leftdoor;
	if(c == "E")	return rightdoor;

	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////


MapWorld::MapWorld():
	mWorldLength(0),
	mWorldWidth(0),
	mCurChunkNumCounter(0)
{

}

MapWorld::~MapWorld()
{

}

bool MapWorld::CreateMaze()
{
	if(mWorldLength == 0 || mWorldWidth == 0) return false;
	//
	mMaze.clear();
	mFrontier.clear();
	//
	for (int i = 0;i< mWorldLength;++i)
	{
		mMaze.push_back(std::vector<int>(mWorldWidth,0));
	}
	//
	mark(RandInt(0,mWorldWidth - 1),RandInt(0,mWorldLength - 1));
	//
	while (breakCondition())
	{
		int index = RandInt(0,mFrontier.size() - 1);
		GridPos gpos = mFrontier[index];
		mFrontier.erase(mFrontier.begin() + index);
		std::vector<GridPos> n;
		neighbors(gpos.X, gpos.Y, n);
		GridPos npos = n[RandInt(0 , n.size() - 1)];
		int dir = direction(gpos.X, gpos.Y,npos.X, npos.Y);
		mMaze[gpos.Y][gpos.X] |= dir;
		mMaze[npos.Y][npos.X] |= opposite(dir);
		mark(gpos.X, gpos.Y);
	}
	//
	return true;
}

void MapWorld::SetWorldSize( int w,int l )
{
	mWorldLength = l;
	mWorldWidth = w;
}

bool MapWorld::breakCondition()
{
	return mFrontier.size() > 0;
}

void MapWorld::addFrontier( int x,int y )
{
	if (x >= 0 && y >= 0 && y < mMaze.size() && x < mMaze[y].size() && mMaze[y][x] == 0)
	{
		mMaze[y][x] |= frontier;
		mFrontier.push_back(GridPos(x,y));
	}
}

void MapWorld::mark( int x,int y )
{
	mMaze[y][x] |= visited;
	addFrontier(x-1, y);
	addFrontier(x+1, y);
	addFrontier(x, y-1);
	addFrontier(x, y+1);
	mCurChunkNumCounter += 1;
}

void MapWorld::neighbors( int x,int y,std::vector<GridPos>& out_neighbors )
{
	 if (x > 0 && ((mMaze[y][x-1] & visited )== 0)) out_neighbors.push_back(GridPos(x-1, y));
	 if (x+1 > mMaze[y].size() && ((mMaze[y][x+1] & visited) == 0)) out_neighbors.push_back(GridPos(x+1, y));

	 if (y > 0 && ((mMaze[y-1][x] & visited) == 0)) out_neighbors.push_back(GridPos(x, y-1));
	 if (y+1 < mMaze.size() && ((mMaze[y+1][x] & visited) == 0)) out_neighbors.push_back(GridPos(x, y+1));
}

int MapWorld::direction( int fx,int fy,int tx,int ty )
{
	if (fx < tx) return rightdoor;
	if (fx > tx) return leftdoor ;
	if (fy < ty) return downdoor;
	if (fy > ty) return topdoor;
}

int MapWorld::opposite( int dir )
{
	if (dir == leftdoor) return rightdoor;
	if (dir == rightdoor) return leftdoor ;
	if (dir == topdoor) return downdoor;
	if (dir == downdoor) return topdoor;
}

void MapWorld::DeployChunkMapToWorld()
{
	mChunkSaveDataInWorldMaze.clear();
	for (int i = 0;i< mWorldLength;++i)
	{
		mChunkSaveDataInWorldMaze.push_back(std::vector<ChunkSaveDataInWorld>(mWorldWidth));
	}
	//
	for (int l = 0;l< mWorldLength;l++)
	{
		for (int w = 0; w< mWorldLength;w++)
		{
// 			int doordir = mMaze[l][w];
// 			doordir &= 15;
			int doordir = GetDir(w,l,mMaze);
			auto it = mChunkMapPathDict.find(doordir);
			if(it == mChunkMapPathDict.end()) return;	//意味着 出错误了
			auto chunkindexes = it->second;
			int chunkIndex = RandInt(0,chunkindexes.size() - 1);
			//
			ChunkSaveDataInWorld& savedata = mChunkSaveDataInWorldMaze[l][w];
			savedata.ChunkResIndex = chunkIndex;
		}
	}
	//
	mEntranceChunkInMazeGPos.SetTo(0,0);
	mSpecialChunkInMazeGPos.SetTo(0,0);
	mHideChunkInMazeGPos.SetTo(0,0);
	mBossChunkInMazeGPos.SetTo(0,0);

}


bool MapWorld::LoadChunk( ChunkMap* chunk , const GridPos& mazePos )
{
	//GridPos mazePos;
	ChunkSaveDataInWorld& savedata = mChunkSaveDataInWorldMaze[mazePos.Y][mazePos.X];
	std::string firstChunkPath = GetChunkMapPath(savedata.ChunkResIndex,mazePos,mMaze);
	if (firstChunkPath.length() > 1)
	{
		//1 清理一下
		chunk->Reset();
		// 设置一下Maze GPos 等数据
		chunk->SetInMazeGPos(mazePos);
		chunk->SetChunkSaveDataInWorld(savedata);
		//2 加载这个chunk
		if(chunk->InitChunkMap(firstChunkPath))
		{
			return true;
		}

	}

	return false;
}


void MapWorld::Init()
{
	//添加一些地图的路径
	//根据 门的朝向去添加
	{
		int dir = topdoor|leftdoor|downdoor|rightdoor;
		std::vector<std::string>	ChunkMapPathList;
		ChunkMapPathList.push_back("map\\Dust_15_1.tmx");
		//
		mChunkMapPathDict.insert(std::make_pair(dir,ChunkMapPathList));
		//TEST
		mChunkMapPathDict.insert(std::make_pair(topdoor,ChunkMapPathList));
		mChunkMapPathDict.insert(std::make_pair(leftdoor,ChunkMapPathList));
		mChunkMapPathDict.insert(std::make_pair(downdoor,ChunkMapPathList));
		mChunkMapPathDict.insert(std::make_pair(rightdoor,ChunkMapPathList));
		//
		mChunkMapPathDict.insert(std::make_pair(topdoor|downdoor,ChunkMapPathList));
		mChunkMapPathDict.insert(std::make_pair(topdoor|leftdoor,ChunkMapPathList));
		mChunkMapPathDict.insert(std::make_pair(topdoor|leftdoor|downdoor,ChunkMapPathList));
		mChunkMapPathDict.insert(std::make_pair(topdoor|leftdoor|rightdoor,ChunkMapPathList));

		mChunkMapPathDict.insert(std::make_pair(topdoor|rightdoor,ChunkMapPathList));
		mChunkMapPathDict.insert(std::make_pair(topdoor|rightdoor|leftdoor,ChunkMapPathList));
		mChunkMapPathDict.insert(std::make_pair(topdoor|rightdoor|downdoor,ChunkMapPathList));

		mChunkMapPathDict.insert(std::make_pair(leftdoor|rightdoor,ChunkMapPathList));
		mChunkMapPathDict.insert(std::make_pair(leftdoor|rightdoor|downdoor,ChunkMapPathList));

		mChunkMapPathDict.insert(std::make_pair(downdoor|rightdoor,ChunkMapPathList));


		//

	}
}

void MapWorld::OnEnterWorld()
{



}

void MapWorld::OnLeaveWorld()
{
	TriggerManager::GetInstance()->ReleaseAllTrigger();
	//
	mChunkSaveDataInWorldMaze.clear();
}

std::string MapWorld::GetChunkMapPath( int chunkResIndex,const GridPos& mazePos,const std::vector< std::vector<int> >& Maze )
{
	std::string path  = "";
	int  chunkDir = GetDir(mazePos.X,mazePos.Y,Maze);
	auto it = mChunkMapPathDict.find(chunkDir);
	if (it != mChunkMapPathDict.end())
	{
		auto chunkpathes = it->second;
		path = chunkpathes[chunkResIndex];
	}
	
	return path;
}

ChunkSaveDataInWorld& MapWorld::GetChunkSaveDataInWorld( const GridPos& mazePos )
{
	ChunkSaveDataInWorld& savedata = mChunkSaveDataInWorldMaze[mazePos.Y][mazePos.X];
	return savedata;
}

bool MapWorld::GetMazePos( const GridPos& basePos,int dir ,GridPos& outGPos)
{
	GridPos newGPos;
	if (dir == leftdoor) newGPos.SetTo(basePos.X - 1,basePos.Y);
	if (dir == rightdoor) newGPos.SetTo(basePos.X + 1,basePos.Y);
	if (dir == topdoor) newGPos.SetTo(basePos.X ,basePos.Y - 1);
	if (dir == downdoor) newGPos.SetTo(basePos.X ,basePos.Y + 1);
	//
	if (newGPos.X >= 0 && newGPos.X < mWorldWidth && newGPos.Y >= 0 && newGPos.Y < mWorldLength)
	{
		outGPos = newGPos;
		return true;
	}

	return false;
}

int MapWorld::GetDir( int MazeX,int MazeY ,const std::vector< std::vector<int> >& Maze)
{
	return Maze[MazeY][MazeX] & 15;
}

bool MapWorld::EncordChunkSaveDataInWorld( ChunkMap* chunk )
{
	auto mazePos = chunk->GetInMazeGPos();
	ChunkSaveDataInWorld& savedata = mChunkSaveDataInWorldMaze[mazePos.Y][mazePos.X];
	savedata.ChunkState = chunk->GetChunkFlag();
	return true;
}

int MapWorld::sNextWorldID = 0;
