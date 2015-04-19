#include "ShieldDataManager.h"
#include "ShieldData.h"

ShieldDataManager* ShieldDataManager::Instance()
{
	static ShieldDataManager instance;
	return &instance;
}

ShieldDataManager::ShieldDataManager()
{
	ShieldDataDict.rehash(128);

}

ShieldDataManager::~ShieldDataManager()
{
	
}

void ShieldDataManager::Init()
{
	ShieldDataBase database;
	database.ID = 0;
	ShieldDataDict[database.ID] = database;
}

void ShieldDataManager::Release()
{
	ShieldDataDict.clear();
}

void ShieldDataManager::Load()
{

}

bool ShieldDataManager::GetShieldData( int id , ShieldDataBase& data ) const
{
	auto it = ShieldDataDict.find(id);

	if (it != ShieldDataDict.end())
	{
		data = (it->second);

		return true;
	}

	return false;
}

