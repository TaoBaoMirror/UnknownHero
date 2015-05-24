#include "BulletSystem.h"

BulletBase::BulletBase():
	mRoundCounter(0),
	mBulletDataPtr(nullptr),
	mAlive(true),
	mAttackDataPtr(nullptr),
	mBulletStatus(Bullet_Start)
{

}

BulletBase::~BulletBase()
{

}

void BulletBase::StepRound()
{
	if (mAlive)
	{
		mRoundCounter++;

		if (mRoundCounter>mBulletDataPtr->mAliveRoundNum)
		{
			mAlive = false;
		}
	}
}

void BulletBase::Init( int bullet_data_id , AttackData* pAtkData )
{
	BulletDataManager::GetInstance()->GetBulletData(bullet_data_id,mBulletDataPtr);
	mAttackDataPtr = pAtkData;
}

//////////////////////////////////////////////////////////////////////////
BulletDataManager* BulletDataManager::instance = nullptr;
BulletDataManager::BulletDataManager()
{
	mCSVFile = "";
	BulletDataDict.rehash(128);
	//
	// add by Hitman [5/24/2015]
	//TEST!!!!!
	ReadCSV("");
}

BulletDataManager::~BulletDataManager()
{
	FreeAll();
}

BulletDataManager* BulletDataManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new BulletDataManager();
	}
	return instance;
}

void BulletDataManager::ReadCSV( const std::string& csvName )
{
	//Test
	BulletData BD;
	BD.mId = 0;
	BD.mAliveRoundNum = 3;
	strcpy(BD.mBulletSpriteName,"effect_posion");
	BD.mNormalFrameNum = 8;
	strcpy(BD.mBulletExplodeName,"effect_StramBoom");
	BD.mExplodeFrameNum = 6;
	BD.mSpeed = 40;
	BD.mHitIfCollide = true;
	BD.mExplodeIfArrived = false;
	//
	BulletDataDict[BD.mId] = BD;
}

void BulletDataManager::FreeAll()
{
	BulletDataDict.clear();
}

bool BulletDataManager::GetBulletData( int Id,const BulletData*& BData ) const
{
	auto it = BulletDataDict.find(Id);

	if (it != BulletDataDict.end())
	{
		BData = &(it->second);

		return true;
	}

	return false;
}
