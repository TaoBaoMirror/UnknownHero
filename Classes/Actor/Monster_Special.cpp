#include "Monster_Special.h"
#include "Data/TableManager.h"
#include "EnemyManager.h"
#include "Game/Soldier.h"
#include "Weapon/GameSkill.h"
#include "Weapon/SkillList.h"

Monster_Special::Monster_Special(void)
{
}


Monster_Special::~Monster_Special(void)
{
}

//------------------------------------------------------------------------------------
void Monster_Special::ActorReadyStart()
{
	//Vector2D realpos = this->GetPosition();
	//this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Monster_Special::ActorReadyUpdate(float dt)
{
	;
}
void Monster_Special::ActorReadyEnd()
{
	;
}
//-----
void Monster_Special::ActorStandStart()
{
	//Vector2D realpos = this->GetPosition();
	//this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Monster_Special::ActorStandUpdate(float dt)
{
	;
}
void Monster_Special::ActorStandEnd()
{
	;
}
//-----
void Monster_Special::ActorMoveStart()
{
	playMoveAnimation();
}
void Monster_Special::ActorMoveUpdate(float dt)
{
	;
}
void Monster_Special::ActorMoveEnd()
{
	;
}
//-----
void Monster_Special::ActorAttackStart()
{
}
void Monster_Special::ActorAttackUpdate(float dt)
{
	;
}
void Monster_Special::ActorAttackEnd()
{
	;
}
//-----
void Monster_Special::ActorDieStart()
{
}
void Monster_Special::ActorDieUpdate(float dt)
{
	;
}
void Monster_Special::ActorDieEnd()
{
	;
}
//-----
void Monster_Special::ActorWinStart()
{
}
void Monster_Special::ActorWinUpdate(float dt)
{
	;
}
void Monster_Special::ActorWinEnd()
{
	;
}
//----------------------------------------------
void Monster_Special::AIThink(float dt)
{
	;
}
//----------------------------------------------
void Monster_Special::CalcDie()
{
	EnemyManager::GetInstance()->RemoveSpecialMonster(this);

	Monster::CalcDie();
}
//----------------------------------------------
void Monster_Special::InitSkill()
{
	if (GetSkillList() != nullptr)
	{
		GameSkill* pSkill = GetSkillList()->AddGameSkill(0);
		pSkill->SetIsTargetToGrid(true);

		//对于Monster来说 就一个技能
		GetSkillList()->SetUsingSkill(pSkill);
	}
}
//----------------------------------------------