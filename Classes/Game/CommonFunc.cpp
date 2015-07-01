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
	Soldier* bearer = nullptr;

	if(provider != nullptr) provider->CallBack_AttackFinish();

	std::vector<Soldier*> Soldiers;
	auto chunkMap = MapManager::GetInstance()->GetCurChunkMap();
	assert(chunkMap != 0);

	float hit_Rate = 1.0f;	//ϵ��
	float center_Damage = 0.f;
	{		
		int AtkPt = pAtkData->AttackPt;
		if (RandInt(0,100) < pAtkData->CritRate)
		{
			AtkPt = pAtkData->CritPt;
		}
		//������Ϊ���㻤�׵�ֵ
		center_Damage = AtkPt;
	}

	GridPos centerGPos;

	if (pAtkData->BearerID == -1)
	{
		//����淢���
		if (pAtkData->SputteringRadius > 0)
		{
			chunkMap->FindSoldiersInRange(pAtkData->TargetGPos,pAtkData->SputteringRadius,pAtkData->SputteringType,Soldiers);
		
			centerGPos = pAtkData->TargetGPos;
		}
		else
		{
			auto s = chunkMap->FindSoldierAtGPos(pAtkData->TargetGPos);

			if (s != nullptr)
			{
				bearer = s;
			}
		}

	}
	else
	{
		//ָ����˵�
		bearer = SoldierManager::Instance()->GetSoldier(pAtkData->BearerID);

		if(bearer == nullptr) return;
	}

	if(bearer != nullptr)
	{

		const ShieldDataBase* pShdData = bearer->GetShieldSystem()->GetCurShieldDataBase();
		//
		if (RandInt(0,100) < pShdData->MissRate)
		{
			//Missed
		}
		else
		{
			hit_Rate = 1.0f;	//���Ӧ���� �������ͺͷ������� �Ĺ�ϵ�õ�

			center_Damage = (center_Damage - pShdData->ShieldPt) * hit_Rate;
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
		if(bearer != nullptr && ((soldier->GetID() == bearer->GetID())))
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
