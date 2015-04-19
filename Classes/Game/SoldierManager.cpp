#include "stdafx.h"
#include "SoldierManager.h"
#include "Soldier.h"

SoldierManager* SoldierManager::instance = NULL;

SoldierManager::SoldierManager()
{

}

SoldierManager::~SoldierManager()
{
	
}

void SoldierManager::Init()
{
	SoldierDict.clear();
}

bool SoldierManager::RegisterSoldier( Soldier* soldier )
{
	if (GetSoldier(soldier->ID))
	{
		//already in dict
		return false;
	}
	//
	SoldierDict.insert(std::make_pair(soldier->ID,soldier));
	return true;
}

bool SoldierManager::UnregisterSoldier( Soldier* soldier )
{
	return UnregisterSoldier(soldier->ID);
}

bool SoldierManager::UnregisterSoldier( int id )
{
	std::map<int,Soldier*>::iterator it = SoldierDict.find(id);
	if (it != SoldierDict.end())
	{
		SoldierDict.erase(it);
		return true;
	}
	//
	return false;
}

void SoldierManager::Update()
{
	std::map<int,Soldier*>::iterator it = SoldierDict.begin();
	while(it != SoldierDict.end())
	{
		it->second->Update();
		++it;
	}
}

void SoldierManager::Render()
{
	std::map<int,Soldier*>::iterator it = SoldierDict.begin();
	while(it != SoldierDict.end())
	{
		it->second->Render();
		++it;
	}
}

Soldier* SoldierManager::GetSoldier( int id )
{
	std::map<int,Soldier*>::iterator it = SoldierDict.find(id);
	if (it != SoldierDict.end())
	{
		return it->second;
	}
	return NULL;
}

Soldier* SoldierManager::GetSoldier( const GridPos& GPos )
{
	std::map<int,Soldier*>::iterator it = SoldierDict.begin();
	std::map<int,Soldier*>::iterator it_end = SoldierDict.end();

	while(it != it_end)
	{
		if (it->second->StayGridPos.Equals(GPos))
		{
			return it->second;
		}
		++it;
	}
	//
	return NULL;
}

void SoldierManager::ReleaseAllSoldier()
{
	DeleteSTLMap(SoldierDict);
	//
	SoldierDict.clear();
}

void SoldierManager::Release()
{
	ReleaseAllSoldier();

	delete instance;
}
