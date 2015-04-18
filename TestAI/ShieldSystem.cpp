#include "ShieldSystem.h"
#include "ShieldDataManager.h"

ShieldSystem::ShieldSystem( Soldier* pOwner )
	:m_pOwner(pOwner),
	m_nOriginalShieldDataBaseID(-1)
{

}

ShieldSystem::~ShieldSystem()
{

}


void ShieldSystem::SetOriginalShieldDataBase( int data_id )
{
	if (m_nOriginalShieldDataBaseID != data_id)
	{
		m_nOriginalShieldDataBaseID = data_id;

		if(!ShieldDataManager::Instance()->GetShieldData(m_nOriginalShieldDataBaseID,m_OriginalShieldDataBase))
		{

		}
	}
}


const ShieldDataBase* ShieldSystem::GetOriginalShieldDataBase() const
{
	return &m_OriginalShieldDataBase;
}

ShieldDataBase* ShieldSystem::GetCurShieldDataBase()
{
	return &m_CurShieldDataBase;
}

void ShieldSystem::Update()
{

}

bool ShieldSystem::Load( std::ifstream& is )
{
	return true;

}

bool ShieldSystem::Save( std::ofstream& os )
{
	return true;

}
