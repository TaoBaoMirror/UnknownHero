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
	;
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