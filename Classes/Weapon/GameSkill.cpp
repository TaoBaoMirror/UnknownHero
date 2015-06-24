#include "GameSkill.h"
#include "Game\AttackSystem.h"
#include "Game\Soldier.h"
#include "Game\AttackRange.h"

//---------------------------------------------------------
GameSkill::GameSkill(Soldier* pOwner) :
	AttackSystem(pOwner),
	m_IsTargetToGrid(false)
{
}


GameSkill::~GameSkill(void)
{
}

void GameSkill::Update()
{
	AttackSystem::Update();
}

bool GameSkill::Load(std::ifstream& is)
{
	return true;
}

bool GameSkill::Save(std::ofstream& os)
{
	return true;
}

void GameSkill::SkillAim()
{
	if (m_pOwner->IsShowAttackRange() == false)
	{
		m_pOwner->SetShowAttackRange(true);

		m_pOwner->showAttackRange(this->GetAttackRange()->GetRangeGPosList());
	}
}

bool GameSkill::IsTargetToGrid()
{
	return m_IsTargetToGrid;
}

void GameSkill::SkillAttack( AttackData* pAtkData )
{
	m_pOwner->CallBack_AttackFinish();
}

AttackData* GameSkill::CreateAttackData( const GridPos& Gpos )
{
	return new AttackData(m_CurAttackDataBase,m_pOwner->GetID(),Gpos,this);
}

AttackData* GameSkill::CreateAttackData( int BearerID )
{
	return new AttackData(m_CurAttackDataBase,m_pOwner->GetID(),BearerID,this);
}
