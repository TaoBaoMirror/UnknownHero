#include "stdafx.h"
#include "PlayerControllor.h"
#include "WindowUtils.h"
#include "GameWorld.h"
#include "MapNodeData.h"
#include "SoldierManager.h"
#include "SoldierPF.h"
//
#include "DebugClass/DebugConsole.h"

PlayerControllor::PlayerControllor()
{

}

PlayerControllor::~PlayerControllor()
{

}

void PlayerControllor::Init( int camp )
{
	mProxySoldier = 0;
	mLastSoldier = 0;

	mProxyCamp = camp;
}

void PlayerControllor::Update()
{
	bool PlayerMoved = false;
	if (mProxySoldier)
	{
		if(IS_KEY_PRESSED('W'))
		{
			if (mProxySoldier->MoveForward())
			{
				PlayerMoved = true;
			}
		}
		else if(IS_KEY_PRESSED('S'))
		{
			if (mProxySoldier->MoveBackward())
			{
				PlayerMoved = true;
			}
		}
		else if(IS_KEY_PRESSED('A'))
		{
			if (mProxySoldier->MoveLeft())
			{
				PlayerMoved = true;
			}
		}
		else if(IS_KEY_PRESSED('D'))
		{
			if (mProxySoldier->MoveRight())
			{
				PlayerMoved = true;
			}
		}
		//
		if (PlayerMoved)
		{
			mProxySoldier->UpdateNodeWithGPos();
		}
	}
	//
	//	TEST 代码！
	//
	if(IS_KEY_PRESSED('M'))
	{
		if (mProxySoldier)
		{
			std::vector<Soldier*>	SoldiersInRange;
			mProxySoldier->FindSoldiersInRange(5,true,RangeType::CIRCLE,SoldiersInRange);
			//
			Soldier* firstSoldier = NULL;
			if (SoldiersInRange.size() > 0)
			{
				firstSoldier = SoldiersInRange.front();
			}
			//
			if (firstSoldier)
			{
				GridPos GPos;
				mProxySoldier->MoveAwayFromGPos(firstSoldier->GetStayGPos(),GPos);
				if (mProxySoldier->CanSetTo(GPos))
				{
					mProxySoldier->SetToGPos(GPos);
				}
			}
		}
	}
	//
	if(IS_KEY_PRESSED('K'))
	{
		if (mProxySoldier)
		{
			std::vector<Soldier*>	SoldiersInRange;
			mProxySoldier->FindSoldiersInRange(5,true,RangeType::CIRCLE,SoldiersInRange);
			//
			Soldier* firstSoldier = NULL;
			if (SoldiersInRange.size() > 0)
			{
				firstSoldier = SoldiersInRange.front();
			}
			//
			if (firstSoldier)
			{
				GridPos GPos;
				mProxySoldier->MoveCloseToGPos(firstSoldier->GetStayGPos(),GPos);
				if (mProxySoldier->CanSetTo(GPos))
				{
					mProxySoldier->SetToGPos(GPos);
				}
			}
		}
	}
	//
	if (IS_KEY_PRESSED('R'))
	{
		ReleasePicked();
	}
	if (IS_KEY_PRESSED('Q'))
	{
		PickedPlayerSoldier();
	}
	if (IS_KEY_PRESSED('E'))
	{
		if (mProxySoldier)
		{
			mProxySoldier->GetSoldierPF()->DebugRender = !mProxySoldier->GetSoldierPF()->DebugRender;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//Pick();
}


void PlayerControllor::ResetMousePos( POINT& pos )
{

}

void PlayerControllor::PickedPlayerSoldier()
{
	auto soldier = SoldierManager::Instance()->GetSoldier(0);

	if (soldier)
	{
		mProxySoldier = soldier;
		mProxySoldier->SetShowAttackRange(true);
		mProxySoldier->TakePossession();
	}

}

void PlayerControllor::ReleasePicked()
{
	if (mProxySoldier)
	{
		mProxySoldier->SetShowAttackRange(false);
		mProxySoldier->Exorcise();
	}
	mProxySoldier = NULL;
	mLastSoldier = NULL;
}



void PlayerControllor::Pick()
{
	POINT pos = GetClientCursorPosition();
	ResetMousePos(pos);
	Soldier*	soldier = NULL;
	soldier = PickSoldier(Vector2D(pos.x,pos.y));
	if (soldier != NULL)
	{
		//如果选择的是同一阵营
		if (soldier->GetCampIndex() == mProxyCamp)
		{

			if (mLastSoldier && mLastSoldier != mProxySoldier)
			{
				mLastSoldier->SetShowAttackRange(false);
				mLastSoldier->Exorcise();
			}
			//
			mLastSoldier = mProxySoldier;
			//
			if (soldier && soldier != mProxySoldier)
			{
				mProxySoldier = soldier;
				mProxySoldier->SetShowAttackRange(true);
				mProxySoldier->TakePossession();
			}
		}
		else
		{
			
		}
	}
}

Soldier* PlayerControllor::PickSoldier( const Vector2D& worldPos )
{
	Soldier* soldier = NULL;
	int index = -1;
	GameWorld::Instance()->GetSceneMap().WorldPosToIndex(worldPos,index);
	if (index != -1)
	{
		auto node = GameWorld::Instance()->GetSceneMap().GetNode(index);
		MapNodeData* pMND = Cast_MapNodeData(node.ExtraInfo());
		if (pMND)
		{
			soldier = pMND->Creature;
		}
	}
	
	return soldier;
}


