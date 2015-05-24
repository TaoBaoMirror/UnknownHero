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

	float hit_Rate = 1.0f;	//ϵ��
	float center_Damage = 0.f;

	GridPos centerGPos;

	if (pAtkData->BearerID == -1)
	{
		//����淢���
		if (pAtkData->SputteringRadius > 0)
		{
			chunkMap->FindSoldiersInRange(pAtkData->TargetGPos,pAtkData->SputteringRadius,pAtkData->SputteringType,Soldiers);
		
			centerGPos = pAtkData->TargetGPos;
		}

	}
	else
	{
		//ָ����˵�
		auto bearer = SoldierManager::Instance()->GetSoldier(pAtkData->BearerID);
		const ShieldDataBase* pShdData = bearer->GetShieldSystem()->GetCurShieldDataBase();
		//
		if (RandInt(0,100) < pShdData->MissRate)
		{
			//Missed
		}
		else
		{
			hit_Rate = 1.0f;	//���Ӧ���� �������ͺͷ������� �Ĺ�ϵ�õ�
			int AtkPt = pAtkData->AttackPt;
			if (RandInt(0,100) < pAtkData->CritRate)
			{
				AtkPt = pAtkData->CritPt;
			}
			//���ĵ�ʵ���˺�ֵ�����ֵӦ�ô���bearer�ģ�Ȼ���л�һ�� bearer��״̬���Ҳ��Ŷ���
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
			//����˥���������˺��޷���ܣ����Ҳ����㻤�ף�ֱ������˺�
			float newDamage = center_Damage * pAtkData->SputteringFallout;

			//TODO 
			//  e.g.Bearer.GetDamage(xxxxxxx);
			soldier->GetHurt(new DamageData(newDamage,pAtkData->ProviderID,pAtkData->BearerID));
		}
	}
	
}
