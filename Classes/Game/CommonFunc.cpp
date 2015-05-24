#include "CommonFunc.h"
#include "ChunkMap.h"
#include "MapManager.h"
#include "SoldierManager.h"
#include "Soldier.h"
#include "ShieldData.h"
#include "AttackData.h"
#include "ShieldSystem.h"

const GridSceneMap& G_GetSceneMap()
{
	return MapManager::GetInstance()->GetCurChunkMap()->GetGridSceneMap();
}
//////////////////////////////////////////////////////////////////////////
void CommonFunc::CalcDamage( const AttackData* atkData )
{
	const AttackData* pAtkData = atkData;
	if(pAtkData == nullptr) return;
	auto provider = SoldierManager::Instance()->GetSoldier(pAtkData->ProviderID);
	std::vector<Soldier*> Soldiers;
	auto chunkMap = MapManager::GetInstance()->GetCurChunkMap();
	assert(chunkMap != 0);

	float hit_Rate = 1.0f;	//系数
	float center_Damage = 0.f;

	GridPos centerGPos;

	if (pAtkData->BearerID == -1)
	{
		//向地面发射的
		if (pAtkData->SputteringRadius > 0)
		{
			chunkMap->FindSoldiersInRange(pAtkData->TargetGPos,pAtkData->SputteringRadius,pAtkData->SputteringType,Soldiers);
		
			centerGPos = pAtkData->TargetGPos;
		}

	}
	else
	{
		//指向敌人的
		auto bearer = SoldierManager::Instance()->GetSoldier(pAtkData->BearerID);
		const ShieldDataBase* pShdData = bearer->GetShieldSystem()->GetCurShieldDataBase();
		//
		if (RandInt(0,100) < pShdData->MissRate)
		{
			//Missed
		}
		else
		{
			hit_Rate = 1.0f;	//这个应该由 攻击类型和防御类型 的关系得到
			int AtkPt = pAtkData->AttackPt;
			if (RandInt(0,100) < pAtkData->CritRate)
			{
				AtkPt = pAtkData->CritPt;
			}
			//中心的实际伤害值，这个值应该传给bearer的，然后，切换一下 bearer的状态并且播放动画
			center_Damage = (AtkPt - pShdData->ShieldPt) * hit_Rate;
			//TODO 
			//  e.g.Bearer.GetDamage(xxxxxxx);
			bearer->GetHurt(new DamageData(center_Damage,pAtkData->ProviderID,pAtkData->BearerID));



			//
			if (pAtkData->SputteringRadius > 0)
			{
				chunkMap->FindSoldiersInRange(pAtkData->TargetGPos,pAtkData->SputteringRadius,pAtkData->SputteringType,Soldiers);
			
				centerGPos = pAtkData->TargetGPos;
			}
		}
	}
	//
	for (int i = 0;i< Soldiers.size();++i)
	{
		Soldier* soldier = Soldiers[i];
		if (soldier->GetID() != provider->GetID())
		{
			//用于衰减，溅射伤害无法躲避，而且不计算护甲，直接造成伤害
			float newDamage = center_Damage * pAtkData->SputteringFallout;

			//TODO 
			//  e.g.Bearer.GetDamage(xxxxxxx);
			soldier->GetHurt(new DamageData(newDamage,pAtkData->ProviderID,pAtkData->BearerID));
		}
	}
	
}
