#include "AttackSystem.h"
#include "AttackDataManager.h"
#include "AttackRangeCreater.h"
#include "Soldier.h"



AttackSystem::AttackSystem( Soldier* pOwner ) :m_pOwner(pOwner),
	m_nOriginalAttackDataBaseID(-1),
	m_eRangeType(-1),
	m_pAttackRange(0)
{

}


AttackSystem::~AttackSystem()
{
	if(m_pAttackRange) { delete m_pAttackRange;m_pAttackRange = NULL;}

}


void AttackSystem::SetOriginalAttackDataBase( int data_id )
{
	if (m_nOriginalAttackDataBaseID != data_id)
	{
		m_nOriginalAttackDataBaseID = data_id;

		if(!AttackDataManager::Instance()->GetAttackData(m_nOriginalAttackDataBaseID,m_OriginalAttackDataBase))
		{
			
		}
		else
		{
			//如果添加成功了，就给现有的CurAtkDataBase赋值
			m_CurAttackDataBase = m_OriginalAttackDataBase;
		}
	}
}


const AttackDataBase* AttackSystem::GetOriginalAttackDataBase() const
{
	return &m_OriginalAttackDataBase;
}

AttackDataBase* AttackSystem::GetCurAttackDataBase()
{
	return &m_CurAttackDataBase;
}

void AttackSystem::SetAttackRange( int RTypt )
{
	if (m_eRangeType != RTypt)
	{
		m_eRangeType = RTypt;

		m_pAttackRange = AttackRangeCreater::CreateAttackRange(m_eRangeType);

	}
}

AttackRange* AttackSystem::GetAttackRange()
{
	return m_pAttackRange;
}

AttackRangeData* AttackSystem::GetAttackRangeData()
{
	return &m_AttackRangeData;
}

void AttackSystem::Update()
{
	if (m_pOwner && m_pAttackRange)
	{
		m_pAttackRange->UpdateRange(m_pOwner->GetStayGPos(),m_AttackRangeData);
	}
}

bool AttackSystem::Load( std::ifstream& is )
{
	return true;
}

bool AttackSystem::Save( std::ofstream& os )
{
	return true;

}

#include "CommonFunc.h"



//