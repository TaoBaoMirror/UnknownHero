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

	if(provider != nullptr) provider->CallBack_AttackFinish();

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

		if(bearer == nullptr) return;

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
			DamageData DD(center_Damage,pAtkData->ProviderID,pAtkData->BearerID);
			if(provider != nullptr) provider->CallBack_AttackSuccess(DD);
			bearer->GetHurt(DD);
			//
			if (pAtkData->SputteringRadius > 0)
			{
				centerGPos = bearer->GetStayGPos();

				chunkMap->FindSoldiersInRange(centerGPos,pAtkData->SputteringRadius,pAtkData->SputteringType,Soldiers);
			
			}
		}
	}
	//
	for (int i = 0;i< Soldiers.size();++i)
	{
		Soldier* soldier = Soldiers[i];
		if(provider != nullptr && ((soldier->GetID() == provider->GetID())))
		{
			continue;
		}
		//
		{
			//����˥���������˺��޷���ܣ����Ҳ����㻤�ף�ֱ������˺�
			float newDamage = center_Damage * pAtkData->SputteringFallout;

			//TODO 
			//  e.g.Bearer.GetDamage(xxxxxxx);
			DamageData DD(center_Damage,pAtkData->ProviderID,pAtkData->BearerID);
			if(provider != nullptr) provider->CallBack_AttackSuccess(DD);
			soldier->GetHurt(DD);
		}
	}
	//
}
