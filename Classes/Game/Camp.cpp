#include "Camp.h"
#include "Soldier.h"

Camp Camp::CampList[MaxCamps];

Camp::Camp():CampFlag(-1),CampState(wait_use)
{

}

Camp::~Camp()
{

}

void Camp::Reset()
{
	Corps.clear();
	CampState = wait_use;
}

void Camp::RegisterUnit( Soldier* unit )
{
	if (unit)
	{
		unit->SetCampIndex(CampFlag);
		Corps.insert(std::make_pair(unit->GetID(),unit));
	}

}

void Camp::UnregisterUnit( int unit_id )
{
	Corps.erase(unit_id);
}
///

void Camp::CreateCamps( int CampsNum )
{
	if(CampsNum > MaxCamps) return;
	for (int i = 0;i<MaxCamps;++i)
	{
		CampList[i].CampFlag = i;
		CampList[i].Reset();
		//
		if (i<CampsNum)
		{
			CampList[i].CampState = in_use;
		}
	}
}

Camp* Camp::GetCamp( int Flag )
{
	if (Flag < MaxCamps)
	{
		if (CampList[Flag].CampState == in_use)
		{
			return &CampList[Flag];
		}
	}

	return NULL;
}

std::map<int,Soldier*>& Camp::GetCrops()
{
	return Corps;
}

Soldier* Camp::GetUnit( int unit_id )
{
	auto it = Corps.find(unit_id);
	if ( it != Corps.end())
	{
		return it->second;
	}
	return NULL;
}

void Camp::GetOtherCampFlags( int flag,std::vector<int>& campFlags )
{
	campFlags.reserve(MaxCamps);

	for (int i = 0 ; i< MaxCamps ; ++i)
	{
		if (i != flag && CampList[i].CampState == in_use)
		{
			campFlags.push_back(i);
		}
	}
}
