#include "GameBullet.h"
#include "Game/CommonFunc.h"
#include "GridPos.h"
#include "Game/MapNodeData.h"
#include "Game/AttackData.h"
#include "Game/Soldier.h"
#include "Game/SoldierManager.h"
#include "Actor/Actor.h"
#include "Game/MapManager.h"

void GameBullet::Init( int bullet_data_id , AttackData* pAtkData )
{
	BulletBase::Init(bullet_data_id,pAtkData);
	//
	SetResource(GetBulletData()->mBulletSpriteName,GetBulletData()->mBulletExplodeName);
}

GameBullet::GameBullet():BulletBase()
{

}

GameBullet::~GameBullet()
{
	m_framesDict.clear();
}
//
//	子弹资源图片格式
//	bullet_normal_1.png
//	flash_explode_4.png
//  参数传递： bullet_normal    flash_explode
void GameBullet::SetResource( const std::string& ani_name,const std::string& explode_name )
{
	const int numAnim = 2 ;// 飞行普通动画，爆炸动画
	const std::string ActionsName[numAnim] = {"normal","explode"};

	if(GetBulletData() == nullptr) return;

	int ActionsFrameCount[numAnim] = { GetBulletData()->mNormalFrameNum , GetBulletData()->mExplodeFrameNum};
	std::string nameList[numAnim] = {ani_name,explode_name};
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

void GameBullet::OnEmitStart()
{
	PlayFlyAnimation();
	//子弹状态更新到下一个
	StepNextStatus();
}

void GameBullet::OnFly()
{
	if ((GetStatus() == Bullet_Flying || GetStatus() == Bullet_Arrived) &&
		GetBulletData()->mHitIfCollide)
	{
		auto pData = GetMapNodeDataWhereBulletStay();
		//
		Soldier* soldier = pData->Creature;

		if (soldier != nullptr)
		{
			if (GetAttackData()->ProviderID == soldier->GetID())
			{
				return;
			}
			//
			if (GetAttackData()->BearerID != -1 && 
				GetAttackData()->BearerID != soldier->GetID())
			{
				
				AttackData* pAtkData = new AttackData();
				memcpy(pAtkData,GetAttackData(),sizeof(AttackData));
				delete mAttackDataPtr;
				pAtkData->BearerID = soldier->GetID();
				mAttackDataPtr = pAtkData;
			}
			//
			stopAllActions();
			//
			PlayExplodeAnimation();
			//
			StepNextStatus(); //这个时候状态应该是 explode
		}
	}
}

void GameBullet::OnArriveDestination()
{
	//停止移动和飞行动画
	stopAllActions();
	//
	StepNextStatus(); //这个时候状态应该是 arrived
	//
	if( mOnArriveFunction )
	{
		mOnArriveFunction();
	}
	//
	if (GetBulletData()->mExplodeIfArrived)
	{
		PlayExplodeAnimation();
		//
		StepNextStatus(); //这个时候状态应该是 explode
	}


}

void GameBullet::OnHit()
{
	stopAllActions();
	//
	StepNextStatus();	//这个时候状态应该是 End
	//
	CommonFunc::CalcDamage(GetAttackData());
	//
	Destroy();
}

void GameBullet::OnDestroy()
{
	mAlive = false;
	//从管理器中删除自己
	removeFromParentAndCleanup(true);

}
bool GameBullet::Emit()
{
	auto atkData = GetAttackData();
	auto soldier = SoldierManager::Instance()->GetSoldier(atkData->ProviderID);
	auto actor = static_cast<Actor*>(soldier);
	cocos2d::Vec2 start = actor->getPosition();
	cocos2d::Vec2 end;
	//
	if (atkData->BearerID != -1)
	{
		auto soldier = SoldierManager::Instance()->GetSoldier(atkData->BearerID);
		auto actor = static_cast<Actor*>(soldier);
		end = actor->getPosition();
	}
	else
	{
		const GridPos& GPos = atkData->TargetGPos;
		Vector2D WPos;
		G_GetSceneMap().GridPosToWorldPos(GPos,WPos);
		end.set(WPos.x,WPos.y);
	}
	//
	return Emit(start,end);
}

bool GameBullet::Emit( const cocos2d::Vec2& start,const cocos2d::Vec2& end )
{
	setPosition(start);

	OnEmitStart();

	if (start == end)
	{
		setPosition(end);

		cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

		cocos2d::DelayTime* pDelayTime = cocos2d::DelayTime::create(0.5f);
		pAcs.pushBack(pDelayTime);
		cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(GameBullet::OnArriveDestination,this));
		pAcs.pushBack(pCallFunc);

		cocos2d::Sequence* pSec = cocos2d::Sequence::create(pAcs);

		this->runAction(pSec);

	}
	else
	{
		float len = (start - end).length();


		cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

		cocos2d::MoveTo* pMoveto = cocos2d::MoveTo::create(len / GetBulletData()->mSpeed,end);
		pAcs.pushBack(pMoveto);
		cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(GameBullet::OnArriveDestination,this));
		pAcs.pushBack(pCallFunc);

		cocos2d::Sequence* pSec = cocos2d::Sequence::create(pAcs);

		this->runAction(pSec);
	}

	//
	return true;
}

void GameBullet::PlayFlyAnimation()
{
	std::string name = "normal";
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animation = cocos2d::Animate::create(ani);
	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animation);

	pRepeat->setTag(0);

	this->runAction(pRepeat);
}

void GameBullet::PlayExplodeAnimation()
{
	std::string name = "explode";
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.15f);
	cocos2d::Animate* animation = cocos2d::Animate::create(ani);
	//
	cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(GameBullet::OnHit,this));

	cocos2d::Sequence* pSec = cocos2d::Sequence::create(animation,pCallFunc,nullptr);
	//
	animation->setTag(1);

	this->runAction(pSec);
}

void GameBullet::UpdateRound()
{
	StepRound();
	//
}

void GameBullet::Destroy()
{
	GameBulletManager::GetInstance()->RemoveBullet(this);
}

MapNodeData* GameBullet::GetMapNodeDataWhereBulletStay()
{
	GridPos GPos;
	G_GetSceneMap().WorldPosToGridPos(Vector2D(getPositionX(),getPositionY()),GPos);
	auto node = G_GetSceneMap().GetNode(GPos);
	MapNodeData* pData = static_cast<MapNodeData*>(node.ExtraInfo());
	return pData;
}

void GameBullet::SetArriveFunc( const std::function<void()>& func )
{
	mOnArriveFunction = func;
}

//////////////////////////////////////////////////////////////////////////
/*

	GameBulletManager

*/
GameBulletManager* GameBulletManager::GetInstance()
{
	static GameBulletManager T;
	return &T;
}

void GameBulletManager::ReleaseAllBullets()
{
	auto it = BulletPool.begin();
	auto end = BulletPool.end();
	//
	while (it != end)
	{
		(*it)->OnDestroy();
		(*it)->release();
		it++;
	}
	//
	BulletPool.clear();
}

GameBullet* GameBulletManager::CreateBullet(int bullet_data_id,AttackData* pAtkData)
{
	GameBullet* bullet = new	GameBullet();
	if (bullet != nullptr)
	{
		bullet->Init(bullet_data_id,pAtkData);
		BulletPool.push_back(bullet);
		//
		auto chunk = MapManager::GetInstance()->GetCurChunkMap();
		if (chunk != nullptr)
		{
			auto layer = MapManager::GetInstance()->GetCurChunkMap()->GetEffectLayer();

			if (layer != nullptr)
			{
				layer->addChild(bullet);
			}
		}
		
	}
	return bullet;
}

void GameBulletManager::RemoveBullet( GameBullet* bullet )
{	
	bullet->OnDestroy();
	BulletPool.remove(bullet);
	bullet->release();
	//
	return;
}

GameBulletManager::GameBulletManager()
{

}

GameBulletManager::~GameBulletManager()
{
	ReleaseAllBullets();
}

void GameBulletManager::UpdateFrame( float dt )
{
	auto it = BulletPool.begin();
	auto end = BulletPool.end();
	//
	while (it != end)
	{
		auto bullet = (*it);

		if (bullet->mAlive == false)
		{
			bullet->OnDestroy();
			bullet->release();
			it = BulletPool.erase(it);
		}
		else
		{
			bullet->OnFly();
			it++;
		}

	}
}

void GameBulletManager::UpdateRound()
{
	
	auto it = BulletPool.begin();
	auto end = BulletPool.end();
	//
	while (it != end)
	{
		(*it)->UpdateRound();
		it++;
	}
}
