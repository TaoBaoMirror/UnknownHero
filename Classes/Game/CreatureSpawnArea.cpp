#include "CreatureSpawnArea.h"

bool CreatureSpawnArea::Init( int CreatureType , float TimeGap , const GridPos& Pos,int w,int h,ChunkMap& Chunk )
{
	if(cocos2d::CCNode::init())
	{
		autorelease();
		GridPosArea::Init(Pos,w,h,Chunk.GetGridSceneMap());
		RegisterCreatureType(CreatureType);
		fTimeGap = TimeGap;
		return true;
	}

	return false;
}

CreatureSpawnArea::CreatureSpawnArea()
{
	CreateTypes.reserve(8);
}

void CreatureSpawnArea::RegisterCreatureType( int CType )
{
	CreateTypes.push_back(CType);
}

void CreatureSpawnArea::UnregisterCreatureType( int CType )
{
	auto it = CreateTypes.begin();
	while (it != CreateTypes.end())
	{
		if (*it == CType)
		{
			CreateTypes.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void CreatureSpawnArea::update( float dt )
{

}

void CreatureSpawnArea::StartSpawn()
{
	cocos2d::CCDelayTime* dt = cocos2d::CCDelayTime::create(fTimeGap);
	cocos2d::CCCallFunc*  cf = cocos2d::CCCallFunc::create(this,callfunc_selector(CreatureSpawnArea::OnSpawn));
	cocos2d::CCSequence*  seq = cocos2d::CCSequence::create(dt,cf);
	cocos2d::CCRepeatForever* rf = cocos2d::CCRepeatForever::create(seq);
	rf->setTag(SPAWN_ACTION);
	this->runAction(rf);
}

void CreatureSpawnArea::PauseSpawn()
{
	this->pause();
}

void CreatureSpawnArea::StopSpawn()
{
	this->stopActionByTag(SPAWN_ACTION);
}

void CreatureSpawnArea::OnBegineSpawn()
{

}

void CreatureSpawnArea::OnEndSpawn()
{

}

void CreatureSpawnArea::OnSpawn()
{
	OnBegineSpawn();
	//
	ExecuteSpawn();
	//
	OnEndSpawn();
}

void CreatureSpawnArea::ExecuteSpawn()
{

}

void CreatureSpawnArea::ResumeSpawn()
{
	this->resume();
}

int CreatureSpawnArea::GetRandomCreatureID()
{
	if (CreateTypes.size())
	{
		int i = RandInt(0,CreateTypes.size());
		return CreateTypes[i];
	}

	return -1;

}

GridPos CreatureSpawnArea::GetRandomGPos()
{
	if (GPosArea.size())
	{
		int i = RandInt(0,GPosArea.size());
		return GPosArea[i];
	}
	
	return GridPos(-1,-1);

}

