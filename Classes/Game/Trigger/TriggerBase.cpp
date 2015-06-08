#include "TriggerBase.h"


TriggerBase::TriggerBase():mActive(false),mCollideCreature(nullptr),mState(TriggerBorn),mTriggerData(nullptr)
{

}

TriggerBase::~TriggerBase()
{

}


void TriggerBase::Init( const TriggerData* TD , const GridPos& Pos,ChunkMap* Chunk )
{
	GridPosArea::Init(Pos,TD->mW,TD->mH,Chunk->GetGridSceneMap());
	//
	mTriggerData = TD;
	//
}

//////////////////////////////////////////////////////////////////////////
TriggerDataManager* TriggerDataManager::instance = nullptr;
TriggerDataManager* TriggerDataManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TriggerDataManager();
	}
	return instance;
}
TriggerDataManager::TriggerDataManager()
{
	mCSVFile = "";
	TriggerDataDict.rehash(128);
	//
	// add by Hitman [5/24/2015]
	//TEST!!!!!
	ReadCSV("");
}

TriggerDataManager::~TriggerDataManager()
{
	FreeAll();
}

void TriggerDataManager::ReadCSV( const std::string& csvName )
{
	//Test
	TriggerData BD;
	BD.mID = 0;
	BD.mW = 1;
	BD.mH = 1;

	strcpy(BD.mTriggerNormalTex,"effect_HeavyHit");
	BD.mNormalAnimationFrameNum = 5;
	strcpy(BD.mTriggerExplodeTex,"effect_StramBoom");
	BD.mExplodeAnimationFrameNum = 5;
	//
	TriggerDataDict[BD.mID] = BD;
}

void TriggerDataManager::FreeAll()
{
	TriggerDataDict.clear();
}

bool TriggerDataManager::GetTriggerData( int Id,const TriggerData*& BData ) const
{
	auto it = TriggerDataDict.find(Id);

	if (it != TriggerDataDict.end())
	{
		BData = &(it->second);

		return true;
	}

	return false;
}

