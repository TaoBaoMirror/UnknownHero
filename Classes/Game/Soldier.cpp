
#include "Soldier.h"
#include "Vector2D.h"
#include "GridPos.h"
#include "MapNodeData.h"

//
#include "GridSceneMap.h"
#include "Graph/GraphAlgorithms.h"
#include "Graph/GraphEdgeTypes.h"
#include "Graph/GraphNodeTypes.h"
#include "Graph/AStarHeuristicPolicies.h"
#include "SoldierManager.h"
#include "AttackSystem.h"
#include "ShieldSystem.h"
#include "TargetingSystem.h"

#include "Goal_SoldierThink.h"


#include "SoldierPF.h"

Soldier::Soldier( int atk,int race ):
	CreatureBase(),
	MessageListener(),
	bPossessed(false),
	RaceIndex(race),
	CampIndex(-1)
{
	ID = -1;
	bShowAttackRange = false;
	pBrain = new Goal_SoldierThink(this);
	//
	pAttackSystem = new AttackSystem(this);
	pAttackSystem->SetAttackRange(CIRCLE);
	pAttackSystem->SetOriginalAttackDataBase(0);
	//
	pShieldSystem = new ShieldSystem(this);
	pShieldSystem->SetOriginalShieldDataBase(0);
	//
	pTargetingSystem = new TargetingSystem(this);
	//
	pSoldierPF = new SoldierPF(this);
	pSoldierPF->SetPerceiveRadius(2);
	pSoldierPF->SetPotential(5);
	pSoldierPF->SetGradation(2);
	//
}


Soldier::~Soldier()
{
	if(pAttackSystem) { delete pAttackSystem; pAttackSystem = NULL;}
	if(pShieldSystem) { delete pShieldSystem; pShieldSystem = NULL;}
	if(pTargetingSystem) { delete pTargetingSystem; pTargetingSystem = NULL;}


}

void Soldier::Update()
{
	UpdatePosition();
	//
	pAttackSystem->Update();
	//
	pTargetingSystem->Update();
	//
	pBrain->Process();
	
}

void Soldier::Render()
{
	if (RaceIndex == Human)
	{
		gdi->SetPenColor(Cgdi::orange);
		gdi->OrangeBrush();

	}
	else
	{
		gdi->SetPenColor(Cgdi::blue);
		gdi->BlueBrush();

	}
	//
	gdi->Circle(Position,9);
	//
	//攻击范围
	if (bShowAttackRange)
	{
		showAttackRange(pAttackSystem->GetAttackRange()->GetRangeGPosList());
	}

}

bool Soldier::MoveForward( int step /*= 1*/ )
{
	GridPos NewGPos(StayGridPos);

	NewGPos.Y = NewGPos.Y - 1;
	//
	MoveTo(NewGPos);
	//
	return false;

}

bool Soldier::MoveBackward( int step /*= 1*/ )
{
	GridPos NewGPos(StayGridPos);

	NewGPos.Y = NewGPos.Y + 1;
	//
	MoveTo(NewGPos);
	//
	return false;

}

bool Soldier::MoveLeft( int step /*= 1*/ )
{
	GridPos NewGPos(StayGridPos);

	NewGPos.X = NewGPos.X - 1;
	//
	MoveTo(NewGPos);
	//
	return false;
}

bool Soldier::MoveRight( int step /*= 1*/ )
{
	GridPos NewGPos(StayGridPos);

	NewGPos.X = NewGPos.X + 1;
	//
	MoveTo(NewGPos);
	//
	return false;

}


bool Soldier::MoveTo( const GridPos& GPos )
{
	if (canStay(GPos))
	{
		BeginMove();

		SetToGPos(GPos);
		//
		EndMove();

		return true;
	}

	return false;
}


void Soldier::UpdatePosition()
{
	GameWorld::Instance()->GetSceneMap().GridPosToWorldPos(StayGridPos,Position);
}

void Soldier::MoveCloseToGPos( const GridPos& other,GridPos& out_nextGPos )
{
	std::list<GridPos>	Path;
	//先 测试是否可以到那个点
	//如果可以,靠近一步;如果不行,随机一步
	if(GameWorld::Instance()->CheckCanArrived(StayGridPos,other,&Path))
	{
		if (Path.begin() != Path.end())
		{
			out_nextGPos = *(++Path.begin());
		}
		else
		{
			out_nextGPos = StayGridPos;
		}
	}
	else
	{

	}


}

void Soldier::MoveAwayFromGPos( const GridPos& other,GridPos& out_nextGPos )
{
	std::vector<GridPos>	GPosList;
	Vector2D other_wp;

	GameWorld::Instance()->GetSceneMap().GridPosToWorldPos(other,other_wp);
	///

	GameWorld::Instance()->GetSceneMap().FindTilesInCircle(GPosList,StayGridPos,1);
	//
	int k = 0;
	float far_dis = -1;
	for (int i = 0;i<GPosList.size();++i)
	{
		const GridPos& GPos = GPosList[i];
		Vector2D wp;
		//如果可以运动到这个GPos上

		if (canStay(GPos))
		{
			GameWorld::Instance()->GetSceneMap().GridPosToWorldPos(GPos,wp);
			//
			float dis = other_wp.DistanceSq(wp);
			if (dis > far_dis)
			{
				far_dis = dis;
				k = i;
			}
		}
	}
	//
	out_nextGPos = GPosList[k];
}

void Soldier::FindSoldiersInRange( int RangeSize , bool ExceptSelf , RangeType RType ,std::vector<Soldier*>& out_SoldierList )
{
	std::vector<GridPos>	GPosList;
	switch(RType)
	{
	case RangeType::CIRCLE:
		GameWorld::Instance()->GetSceneMap().FindTilesInCircle(GPosList,StayGridPos,RangeSize);
		break;
	case RangeType::QUAD:
		GameWorld::Instance()->GetSceneMap().FindTilesInQuad(StayGridPos,RangeSize,GPosList);
		break;
	case RangeType::CROSS:
		GameWorld::Instance()->GetSceneMap().FindTilesInCross(StayGridPos,RangeSize,RangeSize,GPosList);
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
		int index = -1;
		GameWorld::Instance()->GetSceneMap().GetIndex(GPos,index);
		if (index != -1)
		{
			NavGraphNode<void*>& node = GameWorld::Instance()->GetSceneMap().GetNode(index);
			auto pNMD = (MapNodeData*)node.ExtraInfo();
			if (pNMD)
			{
				Soldier* soldier = pNMD->Creature;
				if (soldier != NULL)
				{
					if (ExceptSelf)
					{
						if(soldier == this) continue;
					}
					out_SoldierList.push_back(soldier);
				}
			}

		}
	}

}

void Soldier::showAttackRange(const std::vector<GridPos>&	AttackGPosList)
{
	gdi->SetPenColor(Cgdi::green);
	gdi->GreenBrush();


	for (int i = 0;i< AttackGPosList.size();++i)
	{
		const GridPos&	GP = AttackGPosList[i];
		int index = -1;
		GameWorld::Instance()->GetSceneMap().GetIndex(GP,index);
		auto tNode = GameWorld::Instance()->GetSceneMap().GetNode(index);
		//
		gdi->Circle(tNode.Pos(),4);

	}
}

bool Soldier::canStay( const GridPos& GPos )
{
	int index = -1;
	GameWorld::Instance()->GetSceneMap().GetIndex(GPos,index);
	//
	if ((index < GameWorld::Instance()->GetSceneMap().NodesCount()) &&
		(index >=0) )
	{
		NavGraphNode<void*>& node = GameWorld::Instance()->GetSceneMap().GetNode(index);
		MapNodeData* pMND = static_cast<MapNodeData*>(node.ExtraInfo());
		//
		if (node.Walkable())
		{
			if (pMND->Creature == NULL)
			{
				return true;
			}
		}

	}
	
	return false;

}

void Soldier::UpdateNodeWithGPos()
{
	int index = -1;
	GameWorld::Instance()->GetSceneMap().GetIndex(LastStayGridPos,index);

	if ((index < GameWorld::Instance()->GetSceneMap().NodesCount()) &&
		(index >=0) )
	{
		NavGraphNode<void*>& node = GameWorld::Instance()->GetSceneMap().GetNode(index);
		MapNodeData* pMND = static_cast<MapNodeData*>(node.ExtraInfo());
		//
		//node.SetWalkable(true);
		pMND->Creature = NULL;
	}
	//
	GameWorld::Instance()->GetSceneMap().GetIndex(StayGridPos,index);

	if ((index < GameWorld::Instance()->GetSceneMap().NodesCount()) &&
		(index >=0) )
	{
		NavGraphNode<void*>& node = GameWorld::Instance()->GetSceneMap().GetNode(index);
		MapNodeData* pMND = static_cast<MapNodeData*>(node.ExtraInfo());
		//
		//node.SetWalkable(false);
		pMND->Creature = this;
	}
	//

	
}

void Soldier::SetToGPos( const GridPos& GPos )
{
	LastStayGridPos = StayGridPos;

	StayGridPos.SetTo(GPos.X,GPos.Y);

	UpdateSoldierPFPosition();

	UpdateNodeWithGPos();
}

void Soldier::BeginMove()
{

}

void Soldier::EndMove()
{

}

void Soldier::TakePossession()
{
	bPossessed = true;
}

void Soldier::Exorcise()
{
	pBrain->AddGoal_Explore();

	bPossessed = false;
}

void Soldier::Attack( Soldier* other )
{

}

void Soldier::UpdateSoldierPFPosition()
{
	pSoldierPF->position.X = StayGridPos.X;
	pSoldierPF->position.Y = StayGridPos.Y;

}
