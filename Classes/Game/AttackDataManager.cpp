#include "AttackDataManager.h"
#include "AttackData.h"

AttackDataManager* AttackDataManager::Instance()
{
	static AttackDataManager instance;
	return &instance;
}

AttackDataManager::AttackDataManager()
{
	AttackDataDict.rehash(128);
}

AttackDataManager::~AttackDataManager()
{

}

void AttackDataManager::Init()
{
	AttackDataBase database;
	database.ID = 0;
	AttackDataDict[database.ID] = database;
}

void AttackDataManager::Release()
{
	AttackDataDict.clear();
}

void AttackDataManager::Load()
{

}

bool AttackDataManager::GetAttackData( int id , AttackDataBase& data ) const
{
	auto it = AttackDataDict.find(id);

	if (it != AttackDataDict.end())
	{
		data = (it->second);

		return true;
	}

	return false;
}
