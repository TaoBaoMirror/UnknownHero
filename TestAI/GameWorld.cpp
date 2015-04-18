#include "stdafx.h"
#include "GameWorld.h"
#include "Cgdi.h"
#include "Messaging/MessageListenerManager.h"
#include "SoldierManager.h"
#include "Soldier.h"
#include "MapNodeData.h"
#include "Graph/SparseGraph.h"
#include "Graph/GraphAlgorithms.h"
#include "Graph/GraphEdgeTypes.h"
#include "Graph/GraphNodeTypes.h"
#include "Graph/AStarHeuristicPolicies.h"
//
#include "PlayerControllor.h"
//
#include "GeomorphologyCreater.h"

#include "GameInfluenceMap.h"
#include "SoldierPF.h"
#include "Camp.h"

GameWorld* GameWorld::instance = NULL;

GameWorld::GameWorld():m_bEnable(false)
{
	srand((int)time(0));
}

GameWorld::~GameWorld()
{

}

void GameWorld::Update()
{
	//mWorld.FindTilesInCircle(GPosList,GridPos(4,4),2,2);
	mIM.Update();
	//
	//
	SoldierManager::Instance()->Update();
}

void GameWorld::Render()
{
	if(!m_bEnable) return;

	GridSceneMap::NavGraph::ConstNodeIterator NodeItr(mWorld.GMap());
	const GridSceneMap::NavGraph::NodeType* pN;
	for (pN = NodeItr.begin(); !NodeItr.end(); pN=NodeItr.next())
	{
		const NavGraphNode<void*>* pNode = (const NavGraphNode<void*>*)pN;
		GridSceneMap::NavGraph::ConstEdgeIterator EdgeItr(mWorld.GMap(), pN->Index());
		for (const GridSceneMap::NavGraph::EdgeType* pE = EdgeItr.begin(); 
			!EdgeItr.end(); 
			pE=EdgeItr.next())
		{

			const NavGraphNode<void*>& tNode = (const NavGraphNode<void*>&)( mWorld.GMap().GetNode(pE->To()) );

			gdi->SetPenColor(Cgdi::red);
			gdi->Line(pNode->Pos(),tNode.Pos());
		}
	}
	//
	for (pN = NodeItr.begin(); !NodeItr.end(); pN=NodeItr.next())
	{

		const NavGraphNode<void*>* pNode = (const NavGraphNode<void*>*)pN;

		MapNodeData* pMND = Cast_MapNodeData(pNode->ExtraInfo());

		if (pNode->Walkable())
		{
			gdi->SetPenColor(Cgdi::yellow);
			gdi->Circle(pNode->Pos(),2);

		}
		else
		{
			gdi->SetPenColor(Cgdi::white);
			gdi->Circle(pNode->Pos(),4);
		}
	}
	//
	std::map<GeomorphologyKeyIndex,std::vector<int> >::iterator special_it = SpecialKeyNodeIDMap.begin();
	std::map<GeomorphologyKeyIndex,std::vector<int> >::iterator special_it_end = SpecialKeyNodeIDMap.end();

	for (;special_it != special_it_end;++special_it)
	{
		switch(special_it->first)
		{
		case GeomorphologyKeyIndex::GKI_DOOR:
			{
				gdi->SetPenColor(Cgdi::green);
				gdi->GreenBrush();
				break;
			}
		case GeomorphologyKeyIndex::GKI_PLAYERBORN:
			{
				gdi->SetPenColor(Cgdi::orange);
				gdi->OrangeBrush();
				break;
			}
		case GeomorphologyKeyIndex::GKI_SHOP:
			{
				gdi->SetPenColor(Cgdi::blue);
				gdi->BlueBrush();
				break;
			}
		}
		//
		//
		auto indexList = special_it->second;

		for (int k = 0;k< indexList.size();++k)
		{
			Vector2D WPos;
			GridPos GPos;
			mWorld.IndexToGridPos(indexList[k],GPos);
			mWorld.GridPosToWorldPos(GPos,WPos);
			gdi->Circle(WPos,4);
		}

	}
	//
	SoldierManager::Instance()->Render();
	//
	mIM.Render();

}

bool GameWorld::SaveWorld( const char* fileName )
{
	std::ofstream out(fileName);

	if (!out)
	{
		throw std::runtime_error("Cannot open file: " + std::string(fileName));
		return false;
	}

	//保存地图描述信息 和 网格数据

	mWorld.Save(out);

	//保存MapNodeData数据

	out<<MapNodeDataList.size()<<std::endl;
	//
	for (int i = 0 ; i < MapNodeDataList.size() ; ++i)
	{
		auto pMND = MapNodeDataList[i];
		out<<pMND;
	}
	//
	out.close();

	return true;
}

bool GameWorld::LoadWorld( const char* fileName )
{
	std::ifstream in(fileName);

	if (!in)
	{
		throw std::runtime_error("Cannot open file: " + std::string(fileName));
		return false;
	}
	//读取地图描述信息 和 网格数据
	mWorld.Load(in);
	//读取MapNodeData数据
	int MapNodeDataPtrListLength = -1;
	in>>MapNodeDataPtrListLength;
	MapNodeDataList.reserve(MapNodeDataPtrListLength);
	for (int i = 0 ; i < MapNodeDataPtrListLength; ++i)
	{
		MapNodeData pMND(in);
		//
		MapNodeDataList.push_back(pMND);
		//这样添加非常不安全！ 因为vector内部元素的内部地址会变动！
		//MapNodeData* ptr = &(MapNodeDataList[MapNodeDataList.size() - 1]);
		//mWorld.GMap().GetNode(pMND.ID).SetExtraInfo(ptr);
	}
	for (int i = 0 ; i < MapNodeDataList.size(); ++i)
	{
		MapNodeData* ptr = &(MapNodeDataList[MapNodeDataList.size() - 1]);
		mWorld.GMap().GetNode(ptr->ID).SetExtraInfo(ptr);
	}
	//
	//CreateWorld();
	//



	in.close();


	m_bEnable = true;

	return true;
}

void GameWorld::Init()
{
	mWorld.Init(900,900,30,30,Vector2D(30,30));
	mWorld.CreateMap(GridSceneMap::Oct);
	CreateWorld();
	//Influence Map
	mIM.Init(900,900,30,30);
	Camp::CreateCamps(2);
	//
	m_bEnable = true;


	//////////////////////////////////////////////////////////////////////////
	deploySoldier();
	//
	PlayerControllor::Instance()->Init(Soldier::Human);
	//





}

void GameWorld::CreateWorld()
{
	//清除一下datas
	ReleaseNodeDatas();
	//填充生成地图的数据部分
	int nodesNumber = mWorld.NodesCount();

	MapNodeDataList.reserve(nodesNumber);
	for (int i = 0;i<nodesNumber;++i)
	{
		MapNodeData pMND;
		pMND.ID = i;
		MapNodeDataList.push_back(pMND);

		mWorld.GMap().GetNode(i).SetExtraInfo(&MapNodeDataList.back());
	}
	//
	//随机生成一些地貌
	randomCreateMap();

}

void GameWorld::ReleaseNodeDatas()
{
// 	for (int i = 0;i<MapNodeDataPtrList.size();++i)
// 	{
// 		auto ptr = MapNodeDataPtrList[i];
// 		delete ptr;
// 	}
	//
	MapNodeDataList.clear();
}

void GameWorld::randomCreateMap()
{
	int WX = mWorld.GetSizeNumX();
	int WY = mWorld.GetSizeNumY();

	GeomorphologyDisc	GD;
	GD.AddSpecialKey(GKI_PLAYERBORN,GeomorphologyDisc::IntRange(0,0),GeomorphologyDisc::IntRange(WX -1,WY/3));
	GD.AddSpecialKey(GKI_DOOR,GeomorphologyDisc::IntRange(0,2*WY/3),GeomorphologyDisc::IntRange(WX -1,WY - 1));
	GD.AddSpecialKey(GKI_SHOP,GeomorphologyDisc::IntRange(0,WY/3),GeomorphologyDisc::IntRange(WX -1,2*WY/3));
	GD.AddSpecialKey(GKI_ENEMYBORN,GeomorphologyDisc::IntRange(0,0),GeomorphologyDisc::IntRange(WX,WY));

	GD.SetEnemyNum(2);
	GD.SetPlayerNum(2);
	GD.SetUnwalkableNum(10);
	//
	GeomorphologyCreater GC(&mWorld);
	GC.CreateGeomorphology(GD);
	//
	GD.CopyFromSpecialKeyNodeIDMap(SpecialKeyNodeIDMap);

}

bool GameWorld::CheckCanArrived( const GridPos& A,const GridPos& B ,std::list<GridPos>* GPosListPtr)
{
	typedef Graph_SearchAStar<GridSceneMap::NavGraph, Heuristic_Euclid> AStarSearch;

	int iSource = -1;
	int iTarget = -1;

	GetSceneMap().GetIndex(A,iSource);
	GetSceneMap().GetIndex(B,iTarget);

	AStarSearch	AStar(GameWorld::Instance()->GetSceneMap().GMap(),iSource,iTarget);
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
			GetSceneMap().GetGridPos(*it,GPos);
			GPosListPtr->push_back(GPos);
		}
	}

	return true;

}

void GameWorld::deploySoldier()
{
	SoldierManager::Instance()->Init();
	//
	int StartIndex = 0;
	std::vector<GridPos>	GPosList;
	GetSpecialGPos(GeomorphologyKeyIndex::GKI_PLAYERBORN,GPosList);
	for(int i = 0;i< GPosList.size();++i)
	{
		Soldier* PlayerSoldier = new Soldier(1,Soldier::Human);
		const GridPos& GPos = GPosList[i];
		PlayerSoldier->SetToGPos(GPos);
		PlayerSoldier->SetID(StartIndex++);
		//
		SoldierManager::Instance()->RegisterSoldier(PlayerSoldier);
		MessageListenerManager::Instance()->RegisterMessageListener(PlayerSoldier);
		mIM.AddDynamicField(PlayerSoldier->GetSoldierPF());
		Camp::GetCamp(0)->RegisterUnit(PlayerSoldier);
	}
	//
	GetSpecialGPos(GeomorphologyKeyIndex::GKI_ENEMYBORN,GPosList);
	for (int i = 0;i< GPosList.size();++i)
	{
		Soldier* EnemySoldier = new Soldier(1,Soldier::Orc);
		const GridPos& GPos = GPosList[i];
		EnemySoldier->SetToGPos(GPos);
		EnemySoldier->SetID(StartIndex++);
		//
		SoldierManager::Instance()->RegisterSoldier(EnemySoldier);
		MessageListenerManager::Instance()->RegisterMessageListener(EnemySoldier);
		mIM.AddDynamicField(EnemySoldier->GetSoldierPF());
		Camp::GetCamp(1)->RegisterUnit(EnemySoldier);
	}

}

bool GameWorld::GetSpecialGPos( GeomorphologyKeyIndex key,std::vector<GridPos>& GPosList )
{
	auto rs = SpecialKeyNodeIDMap.find(key);
	if (rs != SpecialKeyNodeIDMap.end())
	{
		auto iList = rs->second;
		GPosList.resize(iList.size());
		for (int i = 0;i< iList.size();++i)
		{
			GridPos GPos;
			mWorld.IndexToGridPos(iList[i],GPos);
			GPosList[i] = GPos;
		}
		return true;
	}
	//
	return false;
}

void GameWorld::Release()
{
	ReleaseNodeDatas();
	SoldierManager::Instance()->Release();
	//
	delete instance;
}

