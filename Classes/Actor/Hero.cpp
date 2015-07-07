#include "Hero.h"
#include "Actor/ActorStatus.h"

#include "Data/TableManager.h"
#include "Game/CommonFunc.h"
#include "Game/AttackSystem.h"
#include "Game/Soldier.h"
#include "Weapon/GameSkill.h"
#include "Weapon/SkillList.h"
#include "Action/GameActionSystem.h"
#include "Scene/MarkTileManager.h"
#include "Game/MapManager.h"
#include "Actor/Hero_SwordMan.h"
//----------------------------------------------
Hero::Hero()
{
	std::string test[7] = {"stand", "move", "attack", "die", "win", "jump", "coin"};
	//ActionsName = test; 
	for (int i=0; i<7; ++i)
	{
		ActionsName.push_back(test[i]);
	}

	m_pFSM = new ActorFSM(this);

}


Hero::~Hero(void)
{
}

Hero* Hero::createWithHeroID(int id)
{
	int iMainWeaponID = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"HeroType",id);
	HeroType createtype = (HeroType)iMainWeaponID;

	Hero* pHero = nullptr;

	switch (createtype)
	{
	case HeroType::HeroType_SwordMan:
		{
			pHero = new Hero_SwordMan();
		}
		break;
	default:
		break;
	}

	//Hero* pHero = new Hero();

	if (pHero == nullptr)
	{
		//报错
	}
	
	
	pHero->SetHeroID(id);

	std::string heroTexID = TableManager::GetInstance()->GetTableData(TableType::Table_Hero,"HeroTextureID",id);
	pHero->SetHeroTexID(heroTexID);

	//这里 名字不应该是读表的 应该是随机起个名字
	std::string heroName = TableManager::GetInstance()->GetTableData(TableType::Table_Hero,"HeroName",id);
	pHero->SetHeroName(heroName);

	pHero->SetActionFrame();


	//res
	std::string tex_hero = "Hero_" + heroTexID;
	pHero->SetResource(tex_hero);

	pHero->InitSkills();
	//
	pHero->m_pFSM->SetStatus(Actor_Ready::Instance());
	//release
	pHero->autorelease();

	return pHero;
}

void Hero::NotAnActor(void)
{
	//这里要处理很多东西

	// 1 析构这个对象,将管理器中存的指针干掉 SoldierManager

	// 2 记录死亡英雄的id到已死英雄信息中

	// 3 看看是否有什么数据要继承到下个英雄的
}

void Hero::SetActionFrame()
{
	//1 读表 得到所有的ActionFrame
	int standFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"StandFrame",m_HeroID);

	int moveFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"MoveFrame",m_HeroID);

	int attackFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"AttackFrame",m_HeroID);

	int dieFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"DieFrame",m_HeroID);

	int winFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"WinFrame",m_HeroID);

	int sp1Frame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"SP1Frame",m_HeroID);

	int sp2Frame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"SP2Frame",m_HeroID);

	//2 赋值
	int frameanim[7] = { standFrame, moveFrame, attackFrame, dieFrame, winFrame, sp1Frame, sp2Frame };
	m_ActionsFrameCount.clear();
	for (int i=0; i<7; ++i)
	{
		m_ActionsFrameCount.push_back(cocos2d::Value(frameanim[i]));
	}
}

void Hero::playMoveAnimation() 
{
	setFlippedX(m_bFaceDirect);
	cocos2d::Animate* animate = createAnimation(ActorAnimType::ActorAnim_Move);
	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animate);
	pRepeat->setTag((int)ActorAnimType::ActorAnim_Move);
	this->runAction(pRepeat);
}

void Hero::playAttackAnimation()
{
	setFlippedX(m_bFaceDirect);
	cocos2d::Animate* animate = createAnimation(ActorAnimType::ActorAnim_Attack);
	this->runAction(animate);

}


void Hero::playStandAnimation()
{
	setFlippedX(m_bFaceDirect);
	cocos2d::Animate* animate = createAnimation(ActorAnimType::ActorAnim_Stand);
	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animate);
	pRepeat->setTag((int)ActorAnimType::ActorAnim_Stand);
	this->runAction(pRepeat);
}


//------------------------------------------------------------------------------------
void Hero::ActorReadyStart()
{
	playStandAnimation();

	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));

	GameActionSystem::GetInstance()->UnLockSystem();
}
void Hero::ActorReadyUpdate(float dt)
{
	;
}
void Hero::ActorReadyEnd()
{
	stopActionByTag(ActorAnim_Stand);
	
}
//------------------------------------------------------------------------------------
void Hero::ActorStandStart()
{
	playStandAnimation();
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
	GameActionSystem::GetInstance()->LockSystem();
}
void Hero::ActorStandUpdate(float dt)
{
	;
}
void Hero::ActorStandEnd()
{
	stopActionByTag(ActorAnim_Stand);
}
//-----
void Hero::ActorMoveStart()
{
	playMoveAnimation();
}
void Hero::ActorMoveUpdate(float dt)
{
	;
}
void Hero::ActorMoveEnd()
{
	stopActionByTag(ActorAnim_Move);
}
//-----
void Hero::ActorAttackStart()
{
	if(getActionByTag(ActorAnim_Attack)) return;

	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	auto ani = createAnimation(Actor::ActorAnim_Attack);
	auto func_2 = cocos2d::CallFunc::create( CC_CALLBACK_0(Hero::CalcAttack , this , m_pTempAtkData));

	pAcs.pushBack(ani);
	pAcs.pushBack(func_2);

	auto seq = cocos2d::Sequence::create(pAcs);
	seq->setTag(ActorAnimType::ActorAnim_Attack);
	this->runAction(seq);

}
void Hero::ActorAttackUpdate(float dt)
{
	;
}
void Hero::ActorAttackEnd()
{
	stopActionByTag(ActorAnim_Attack);

	GameActionSystem::GetInstance()->OverAction();

	GetSkillList()->SetUsingSkill(nullptr);
}
//-----
void Hero::ActorDieStart()
{
}
void Hero::ActorDieUpdate(float dt)
{
	;
}
void Hero::ActorDieEnd()
{
	;
}
//-----
void Hero::ActorWinStart()
{
}
void Hero::ActorWinUpdate(float dt)
{
	;
}
void Hero::ActorWinEnd()
{
	;
}
#include "Game/AttackData.h"
void Hero::CalcAttack( AttackData* pAtkData )
{
	Actor::CalcAttack(pAtkData);
	
}

//------------------------------------------------------------------------------------
void Hero::ClickAttack(int groupID)
{
	GameActionSystem::GetInstance()->ClickAction(groupID);
	//1 显示攻击范围
	//if (this->IsShowAttackRange() == false)
	//{
	//	this->SetShowAttackRange(true);

	//	this->showAttackRange(GetAttackSystem()->GetAttackRange()->GetRangeGPosList());
	//}

	//2 直接攻击前方
}
//------------------------------------------------------------------------------------
void Hero::CancleSkill()
{
	GetSkillList()->SetUsingSkill(nullptr);

	GameActionSystem::GetInstance()->ContinueAction();
}
//------------------------------------------------------------------------------------
void Hero::Attack(Soldier* other , int number)
{
	Actor::Attack(other,number);
}
//------------------------------------------------------------------------------------
void Hero::SelectGrid( const GridPos& gridPos )
{
	//移动
	auto pChunk = MapManager::GetInstance()->GetCurChunkMap();

	std::list<GridPos> path;
	if (canSelect(gridPos) )
	{
		pChunk->CheckCanArrived(this,this->GetStayGPos(),gridPos,&path);

		if (this->IsUsingSkill())
		{
			MarkTileManager::GetInstance()->ClearMarkTiles("ActorAttack");
			SetShowAttackRange(false);

			if (this->GetSkillList()->LaunchSkill(gridPos) == false)
			{
				this->CancleSkill();
			}					
		}
		else
		{
			if (path.size() != 0)
			{
				path.pop_front();
				if (path.size() != 0)
				{
					GridPos firstpos = path.front();
					this->TravalTo(firstpos);
				}
			}
		}

		//MapNodeData
	}				
}
//------------------------------------------------------------------------------------
void Hero::showAttackRange(const std::vector<GridPos>&	AttackGPosList)
{
	Actor::showAttackRange(AttackGPosList);
	MarkTileManager::GetInstance()->SetMarkTiles(MarkTile_Attack,"ActorAttack",AttackGPosList);
}
//------------------------------------------------------------------------------------