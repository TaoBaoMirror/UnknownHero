#include "GameSkill.h"

//---------------------------------------------------------
GameSkill::GameSkill(Soldier* pOwner) :
	AttackSystem(pOwner)
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

void GameSkill::AttackLogic(int WeaponOwerID, int HurtActorID)
{
	;
}