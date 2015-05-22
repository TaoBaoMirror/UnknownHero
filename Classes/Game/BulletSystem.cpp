#include "BulletSystem.h"

BulletBase::BulletBase():mRoundCounter(0),mBulletDataPtr(nullptr),mAlive(false),mAttackDataPtr(nullptr)
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

void BulletDataManager::ReadCSV( std::string& csvName )
{

}

void BulletDataManager::FreeAll()
{
	BulletDataDict.clear();
}

bool BulletDataManager::GetBulletData( int Id,const BulletData* BData ) const
{
	auto it = BulletDataDict.find(Id);

	if (it != BulletDataDict.end())
	{
		BData = &(it->second);

		return true;
	}

	return false;
}
