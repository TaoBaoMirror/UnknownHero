#include "SoldierPF.h"
#include "InfluenceMap.h"
#include "Soldier.h"
#include "Camp.h"

SoldierPF::SoldierPF(Soldier* s) : 
	PerceiveRadius(2),pOwner(s)
{

}

SoldierPF::~SoldierPF()
{

}

void SoldierPF::SetPerceiveRadius( int r )
{
	PerceiveRange.reserve(r*r);
	PerceiveValueRange.reserve(r*r);
	CrossOverGPosList.reserve(r*r);
	PerceiveRadius = r;
}

int SoldierPF::GetPerceiveRadius() const
{
	return PerceiveRadius;
}

std::vector<GridPos> SoldierPF::GetPerceiveRange() const
{
	return PerceiveRange;
}

std::vector<GridPos> SoldierPF::GetCrossoverIndexs() const
{
	return CrossOverGPosList;
}

void SoldierPF::PreUpdate()
{
	if (pOwner)
	{
		Camp* camp = Camp::GetCamp(pOwner->GetCampIndex());

		SetCampPFType(camp,-1);

		std::vector<int>	camps;

		Camp::GetOtherCampFlags(pOwner->GetCampIndex(),camps);
		
		for (int i = 0; i< camps.size();++i)
		{
			SetCampPFType(Camp::GetCamp(camps[i]),1);
		}
	}
}

void SoldierPF::SetCampPFType(Camp* camp, int type /*= PF_TYPE_ATTRACT*/ )
{
	if (camp)
	{
		auto crops = camp->GetCrops();
		auto it = crops.begin();
		for (;it != crops.end();++it)
		{
			Soldier* pSoldier = it->second;
			auto pf = pSoldier->GetSoldierPF();
			if (pf)
			{
				pf->SetPotentialType(type);
			}
		}

	}
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#endif
