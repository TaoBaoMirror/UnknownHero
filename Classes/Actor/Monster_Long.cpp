#include "Monster_Long.h"
#include "Data/TableManager.h"
#include "EnemyManager.h"
#include "Bullet/GameBullet.h"
#include "Actor/ActorStatus.h"
#include "Game/MapManager.h"
#include "Weapon/GameSkill.h"
#include "Weapon/SkillList.h"
#include "Game/Soldier.h"

Monster_Long::Monster_Long(void):Monster()
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
	//Monster::ActorAttackStart();	// 这个是远程攻击，不再走基础攻击流程

	if(getActionByTag(ActorAnim_Attack)) return;

	//
	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	auto func_1 = cocos2d::CallFuncN::create(  CC_CALLBACK_0( Actor::playMoveAnimation  , this ));
	auto func_2 = cocos2d::CallFuncN::create(  CC_CALLBACK_0( Monster_Long::ShootBullet , this ));

	pAcs.pushBack(func_1);
	pAcs.pushBack(func_2);

	auto seq = cocos2d::Sequence::create(pAcs);
	seq->setTag(ActorAnimType::ActorAnim_Attack);
	this->runAction(seq);
}
void Monster_Long::ActorAttackUpdate(float dt)
{
	;
}
void Monster_Long::ActorAttackEnd()
{
	stopActionByTag(ActorAnim_Attack);
	
}
//-----
void Monster_Long::ActorDieStart()
{
	Monster::ActorDieStart();
}
void Monster_Long::ActorDieUpdate(float dt)
{
	Monster::ActorDieUpdate(dt);
}
void Monster_Long::ActorDieEnd()
{
	Monster::ActorDieEnd();
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
void Monster_Long::AIThink(float dt)
{
	Monster::AIThink(dt);
	//
	
}
//----------------------------------------------
void Monster_Long::CalcAttack( AttackData* pAtkData )
{
	//Monster::CalcAttack(pAtkData);
}
//----------------------------------------------
void Monster_Long::CalcDie()
{
	EnemyManager::GetInstance()->RemoveLongMonster(this);

	Monster::CalcDie();
}
//----------------------------------------------

void Monster_Long::ShootBullet()
{
	auto bullet = GameBulletManager::GetInstance()->CreateBullet(0,m_pTempAtkData);
	bullet->Emit();
}

void Monster_Long::CallBack_AttackFinish()
{
	FinishRound();
}
//----------------------------------------------
void Monster_Long::InitSkill()
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