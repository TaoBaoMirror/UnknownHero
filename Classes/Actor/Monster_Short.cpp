#include "Monster_Short.h"
#include "Data/TableManager.h"
#include "EnemyManager.h"
#include "Weapon/GameSkill.h"
#include "Weapon/SkillList.h"

Monster_Short::Monster_Short(void)
{
}


Monster_Short::~Monster_Short(void)
{
}

//------------------------------------------------------------------------------------
void Monster_Short::ActorReadyStart()
{
	//Vector2D realpos = this->GetPosition();
	//this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Monster_Short::ActorReadyUpdate(float dt)
{
	;
}
void Monster_Short::ActorReadyEnd()
{
	;
}
//-----
void Monster_Short::ActorStandStart()
{
	//Vector2D realpos = this->GetPosition();
	//this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Monster_Short::ActorStandUpdate(float dt)
{
	;
}
void Monster_Short::ActorStandEnd()
{
	;
}
//-----
void Monster_Short::ActorMoveStart()
{
	playMoveAnimation();
}
void Monster_Short::ActorMoveUpdate(float dt)
{
	;
}
void Monster_Short::ActorMoveEnd()
{
	;
}
//-----
void Monster_Short::ActorAttackStart()
{
}
void Monster_Short::ActorAttackUpdate(float dt)
{
	;
}
void Monster_Short::ActorAttackEnd()
{
	;
}
//-----
void Monster_Short::ActorDieStart()
{
	Monster::ActorDieStart();
}
void Monster_Short::ActorDieUpdate(float dt)
{
	Monster::ActorDieUpdate(dt);
}
void Monster_Short::ActorDieEnd()
{
	Monster::ActorDieEnd();
}
//-----
void Monster_Short::ActorWinStart()
{
}
void Monster_Short::ActorWinUpdate(float dt)
{
	;
}
void Monster_Short::ActorWinEnd()
{
	;
}
//----------------------------------------------
void Monster_Short::AIThink(float dt)
{
	;
}

void Monster_Short::CalcDie()
{
	EnemyManager::GetInstance()->RemoveShortMonster(this);

	Monster::CalcDie();
}
//----------------------------------------------
void Monster_Short::InitSkill()
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