#include "Monster_Long.h"
#include "Data/TableManager.h"

Monster_Long::Monster_Long(void)
{
}


Monster_Long::~Monster_Long(void)
{
}

Monster* Monster_Long::createWithMonsterID(int id)
{
	Monster_Long* pMonster = new Monster_Long();

	pMonster->m_MonsterID = id;

	std::string monsterTexID = TableManager::GetInstance()->GetTableData(TableType::Table_Monster,"MonsterTextureID",id);
	pMonster->SetMonsterTexID(monsterTexID);

	std::string monsterName = TableManager::GetInstance()->GetTableData(TableType::Table_Monster,"MonsterName",id);
	pMonster->SetMonsterName(monsterName);

	pMonster->SetActionFrame();

	//res
	std::string tex_monster = "Monster_" + monsterTexID;
	pMonster->SetResource(tex_monster);

	//release
	pMonster->autorelease();

	return pMonster;
}

//------------------------------------------------------------------------------------
void Monster_Long::ActorReadyStart()
{
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Monster_Long::ActorReadyUpdate(float dt)
{
	;
}
void Monster_Long::ActorReadyEnd()
{
	;
}
//-----
void Monster_Long::ActorStandStart()
{
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Monster_Long::ActorStandUpdate(float dt)
{
	;
}
void Monster_Long::ActorStandEnd()
{
	;
}
//-----
void Monster_Long::ActorMoveStart()
{
	playMoveAnimation();
}
void Monster_Long::ActorMoveUpdate(float dt)
{
	;
}
void Monster_Long::ActorMoveEnd()
{
	;
}
//-----
void Monster_Long::ActorAttackStart()
{
	Monster::ActorAttackStart();
}
void Monster_Long::ActorAttackUpdate(float dt)
{
	;
}
void Monster_Long::ActorAttackEnd()
{
	;
}
//-----
void Monster_Long::ActorDieStart()
{
}
void Monster_Long::ActorDieUpdate(float dt)
{
	;
}
void Monster_Long::ActorDieEnd()
{
	;
}
//-----
void Monster_Long::ActorWinStart()
{
}
void Monster_Long::ActorWinUpdate(float dt)
{
	;
}
void Monster_Long::ActorWinEnd()
{
	;
}
//----------------------------------------------
void Monster_Long::AIThink()
{
	Monster::AIThink();
	//
	
}
//----------------------------------------------
void Monster_Long::CalcAttack( AttackData* pAtkData )
{
	Monster::CalcAttack(pAtkData);

	int i=1000;
}
//----------------------------------------------