#include "GameTrigger.h"
#include "Game/CommonFunc.h"
#include "GridPos.h"
#include "Game/MapNodeData.h"
#include "Game/AttackData.h"
#include "Game/Soldier.h"
#include "Game/SoldierManager.h"
#include "Actor/Actor.h"
#include "Game/MapManager.h"

GameTrigger::GameTrigger() : TriggerBase(),mOwner(nullptr)
{

}
GameTrigger::~GameTrigger()
{
	m_framesDict.clear();
}

//	Trigger资源图片格式
//	bullet_normal_1.png
//	flash_explode_4.png
//  参数传递： bullet_normal    flash_explode
void GameTrigger::SetResource( const std::string& NormalName,const std::string& ExplodeName )
{
	const int numAnim = 2 ;// 飞行普通动画，爆炸动画
	const std::string ActionsName[numAnim] = {"normal","explode"};
	if(mTriggerData == nullptr) return;
	int ActionsFrameCount[numAnim] = { mTriggerData->mNormalAnimationFrameNum , mTriggerData->mExplodeAnimationFrameNum};
	std::string nameList[numAnim] = {NormalName,ExplodeName};
	std::string name = "";

	if (m_framesDict.size() == 0)
	{
		m_framesDict.clear();

		for (int i = 0; i < numAnim; ++i)
		{
			cocos2d::Vector<cocos2d::SpriteFrame*> temp; //= new cocos2d::Vector<cocos2d::SpriteFrame*>();

			int numAction = ActionsFrameCount[i];

			name = nameList[i];

			for (int k = 0; k < numAction; ++k)
			{
				std::string frameName = /*ActionsName[i];*/ "";

				std::stringstream ss;
				ss<<k; 
				std::string kStr = ss.str();
				frameName = name /*+ "_" + frameName*/ + "_" + kStr + ".png";

				cocos2d::SpriteFrame* spriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);

				if (spriteframe != nullptr)
				{
					temp.pushBack(spriteframe);
				}
				else
				{
					continue;
				}
				//
				if (k == numAction - 1)
				{
					if (temp.size() != 0)
					{
						m_framesDict.insert(std::pair<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>>(ActionsName[i],temp));
					}
					break;
				}
			}
		}
	}

	std::string initName = name /*+ "_" + ActionsName[0] */+ "_0.png";
	initWithSpriteFrameName(initName);	
}

void GameTrigger::Init( const TriggerData* TD , const GridPos& Pos,ChunkMap* Chunk )
{
	TriggerBase::Init(TD,Pos,Chunk);

	SetResource(TD->mTriggerNormalTex,TD->mTriggerExplodeTex);

	Vector2D WPos;
	G_GetSceneMap().GridPosToWorldPos(Pos,WPos);
	setPosition(WPos.x,WPos.y);
}

void GameTrigger::PlayNormalAnimation()
{
	std::string name = "normal";
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animation = cocos2d::Animate::create(ani);
	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animation);

	pRepeat->setTag(0);

	this->runAction(pRepeat);
}

void GameTrigger::PlayExplodeAnimation()
{
	std::string name = "explode";
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.15f);
	cocos2d::Animate* animation = cocos2d::Animate::create(ani);
	//
	cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(GameTrigger::OnDestory,this));

	cocos2d::Sequence* pSec = cocos2d::Sequence::create(animation,pCallFunc,nullptr);
	//
	animation->setTag(1);

	this->runAction(pSec);
}

void GameTrigger::OnDestory()
{
	if (mState == TriggerDestory)
	{
		mActive = false;
		//
		TriggerManager::GetInstance()->RemoveTrigger(this);
		//
		removeFromParentAndCleanup(true);
	}

}

void GameTrigger::Born()
{
	Awake();

	PlayNormalAnimation();
}

void GameTrigger::Sleep()
{
	mState = TriggerSleep;
	mActive = false;

}

void GameTrigger::Awake()
{
	mState = TriggerActive;
	mActive = true;
}

void GameTrigger::DeployToCorrectChunk()
{
	if (mRecordOwnerChunk.X != -1 && mRecordOwnerChunk.Y != -1)
	{
		if (MapManager::GetInstance()->GetCurChunkMap()->GetInMazeGPos().Equals(mRecordOwnerChunk))
		{
			auto layer = MapManager::GetInstance()->GetCurChunkMap()->GetTriggerLayer();

			if (layer != nullptr)
			{
				layer->addChild(this);
				//激活
				Born();
			}
		}
	}
}

void GameTrigger::UndeployFromCurChunk()
{
	if (mRecordOwnerChunk.X != -1 && mRecordOwnerChunk.Y != -1)
	{
		if (MapManager::GetInstance()->GetCurChunkMap()->GetInMazeGPos().Equals(mRecordOwnerChunk))
		{
			this->removeFromParentAndCleanup(true);
			//睡眠
			Sleep();
		}
	}
}



//////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////
TriggerManager::TriggerManager():NextID(0)
{

}


TriggerManager::~TriggerManager()
{
	ReleaseAllTrigger();
}


void TriggerManager::ReleaseAllTrigger()
{
	auto it = TriggerPool.begin();
	auto end = TriggerPool.end();
	//
	while (it != end)
	{
		(*it)->OnDestory();
		it++;
	}
	//
	TriggerPool.clear();
}

void TriggerManager::RemoveTrigger( GameTrigger* trigger )
{
	TriggerPool.remove(trigger); 
	trigger->release();
	trigger = nullptr;
	//
	return;
}

GameTrigger* TriggerManager::CreateTrigger( Soldier* owner,int triggerType,const GridPos& GPos,ChunkMap* chunk)
{
	GameTrigger* trigger = nullptr;
	switch (triggerType)
	{
	case 0:
		trigger = new Poison_GameTrigger();
		break;
	default:
		break;
	}
	
	
	if (trigger != nullptr)
	{
		const TriggerData* pTD = nullptr;

		TriggerDataManager::GetInstance()->GetTriggerData(triggerType,pTD);
		trigger->Init(pTD,GPos,chunk);
		trigger->mOwner = owner;		//设置主人
		trigger->mID = NextID++;		//设置ID
		TriggerPool.push_back(trigger);
		//
// 		if (chunk != nullptr)
// 		{
// 			auto layer = MapManager::GetInstance()->GetCurChunkMap()->GetTriggerLayer();
// 
// 			if (layer != nullptr)
// 			{
// 				layer->addChild(trigger);
// 			}
// 		}

	}
	return trigger;
}

GameTrigger* TriggerManager::GetTrigger( int triggerID )
{
	for(std::list<GameTrigger*>::iterator it = TriggerPool.begin();
		it != TriggerPool.end(); ++ it)
	{
		GameTrigger* trigger = *it;

		if (trigger->mID = triggerID)
		{
			return trigger;
		}
	}
	//
	return nullptr;
}

void TriggerManager::Update( float dt )
{
	std::list<GameTrigger*>::iterator e = TriggerPool.end();
	for(std::list<GameTrigger*>::iterator it = TriggerPool.begin();
		it != e; ++ it)
	{
		GameTrigger* trigger = *it;

		if(trigger->mActive) trigger->UpdateTriggerFrame(dt);

	}
}

void TriggerManager::UpdateRound()
{
	std::list<GameTrigger*>::iterator e = TriggerPool.end();
	for(std::list<GameTrigger*>::iterator it = TriggerPool.begin();
		it != e; ++ it)
	{
		GameTrigger* trigger = *it;
		if(trigger->mActive == false) continue;
		//
		const std::vector<GridPos>&	area = trigger->GetArea();
		//
		for (int i = 0;i< area.size(); ++i)
		{
			const GridPos& GPos = area[i];
			//
			auto pChunk = MapManager::GetInstance()->GetCurChunkMap();
			auto node = pChunk->GetGridSceneMap().GetNode(GPos);
			auto data = Cast_MapNodeData(node.ExtraInfo());
			if (data && trigger->mActive)
			{
				//
				trigger->UpdateTriggerRound();
				//
				if (data->Creature != NULL)
				{
					if (trigger->mCollideCreature == nullptr)
					{
						trigger->mCollideCreature = data->Creature;
						trigger->EnterTrigger(data->Creature);
					}
					else if(trigger->mCollideCreature == data->Creature)
					{
						trigger->InsideTrigger(data->Creature);
					}
				}
				else
				{
					if (trigger->mCollideCreature != nullptr)
					{
						auto s = trigger->mCollideCreature;
						trigger->mCollideCreature = nullptr;
						trigger->ExitTrigger(s);
					}
				}

			}
		}

	}
}

void TriggerManager::OnChunkLeave()
{
	std::list<GameTrigger*>::iterator e = TriggerPool.end();
	for(std::list<GameTrigger*>::iterator it = TriggerPool.begin();
		it != e; ++ it)
	{
		GameTrigger* trigger = *it;

		trigger->UndeployFromCurChunk();

	}
}

void TriggerManager::OnChunkEnter()
{
	std::list<GameTrigger*>::iterator e = TriggerPool.end();
	for(std::list<GameTrigger*>::iterator it = TriggerPool.begin();
		it != e; ++ it)
	{
		GameTrigger* trigger = *it;

		trigger->DeployToCorrectChunk();

	}
}


void Poison_GameTrigger::EnterTrigger( Soldier* soldier )
{
	//
	MapManager::GetInstance()->GetCurChunkMap()->GetMapRuleSys().ChangeRule(MapRule_Poison);
	//
	stopAllActions();
	//
	mState = TriggerDestory;
	//
	PlayExplodeAnimation();
}
