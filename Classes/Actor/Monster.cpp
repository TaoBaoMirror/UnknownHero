#include "Monster.h"
#include "Data/TableManager.h"

#include "Actor/ActorStatus.h"
#include "Game/CommonFunc.h"
#include "EnemyManager.h"

Monster::Monster(void)
{
	std::string test[5] = {"stand", "move", "attack", "die", "win"};
	//ActionsName = test; 
	for (int i=0; i<5; ++i)
	{
		ActionsName.push_back(test[i]);
	}

	m_pFSM = new ActorFSM(this);

	m_pFSM->SetStatus(Actor_Ready::Instance());
}


Monster::~Monster(void)
{
}

Monster* Monster::createWithMonsterID(int id)
{
	Monster* pMonster = new Monster();

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


void Monster::SetActionFrame()
{
	//1 读表 得到所有的ActionFrame
	int standFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"StandFrame",m_MonsterID);

	int moveFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"MoveFrame",m_MonsterID);

	int attackFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"AttackFrame",m_MonsterID);

	int dieFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"DieFrame",m_MonsterID);

	int winFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"WinFrame",m_MonsterID);

	//2 赋值
	int frameanim[5] = { standFrame, moveFrame, attackFrame, dieFrame, winFrame };
	m_ActionsFrameCount.clear();
	for (int i=0; i<5; ++i)
	{
		m_ActionsFrameCount.push_back(cocos2d::Value(frameanim[i]));
	}
}

void Monster::playMoveAnimation() 
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_Move];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);
	//animaction->setDuration(0.4f);

	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animaction);
	pRepeat->setTag((int)ActorAnimType::ActorAnim_Move);
	this->runAction(pRepeat);
}


void Monster::playAttackAnimation()
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_Attack];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);

	this->runAction(animaction);
}

void Monster::playDieAnimation()
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_Die];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);

	this->runAction(animaction);
}




//------------------------------------------------------------------------------------
void Monster::ActorReadyStart()
{
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Monster::ActorReadyUpdate(float dt)
{
	;
}
void Monster::ActorReadyEnd()
{
	;
}
//-----
void Monster::ActorStandStart()
{
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Monster::ActorStandUpdate(float dt)
{
	;
}
void Monster::ActorStandEnd()
{
	;
}
//-----
void Monster::ActorMoveStart()
{
	playMoveAnimation();
}
void Monster::ActorMoveUpdate(float dt)
{
	;
}
void Monster::ActorMoveEnd()
{
	;
}
//-----
void Monster::ActorAttackStart()
{
	Actor::ActorAttackStart();
}
void Monster::ActorAttackUpdate(float dt)
{
	;
}
void Monster::ActorAttackEnd()
{
	;
}
//-----
void Monster::ActorDieStart()
{
	Actor::ActorDieStart();
}
void Monster::ActorDieUpdate(float dt)
{
	Actor::ActorDieUpdate(dt);
}
void Monster::ActorDieEnd()
{
	Actor::ActorDieEnd();
}
//-----
void Monster::ActorWinStart()
{
}
void Monster::ActorWinUpdate(float dt)
{
	;
}
void Monster::ActorWinEnd()
{
	;
}
//----------------------------------------------
void Monster::AIThink()
{
	Actor::AIThink();
}
//----------------------------------------------
#include "Game/AttackData.h"
void Monster::CalcAttack( AttackData* pAtkData )
{
	Actor::CalcAttack(pAtkData);
	CommonFunc::CalcDamage(pAtkData);
	//
	m_pFSM->SetStatus(Actor_Stand::Instance());
}

void Monster::CalcDie()
{
	EnemyManager::GetInstance()->ClearCurEnemy(this);
	Actor::CalcDie();
}