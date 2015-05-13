#include "Hero.h"
#include "Actor/ActorStatus.h"

#include "Data/TableManager.h"
//----------------------------------------------
Hero::Hero(void)
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


Hero::~Hero(void)
{
}

Hero* Hero::createWithHeroID(int id)
{
	Hero* pHero = new Hero();
	
	pHero->SetHeroID(id);

	std::string heroTexID = TableManager::GetInstance()->GetTableData(TableType::Table_Hero,"HeroTextureID",id);
	pHero->SetHeroTexID(heroTexID);

	//���� ���ֲ�Ӧ���Ƕ���� Ӧ��������������
	std::string heroName = TableManager::GetInstance()->GetTableData(TableType::Table_Hero,"HeroName",id);
	pHero->SetHeroName(heroName);

	pHero->SetActionFrame();


	//res
	std::string tex_hero = "Hero_" + heroTexID;
	pHero->SetResource(tex_hero);

	//release
	pHero->autorelease();

	return pHero;
}

void Hero::NotAnActor(void)
{
	//����Ҫ����ܶණ��

	// 1 �����������,���������д��ָ��ɵ� SoldierManager

	// 2 ��¼����Ӣ�۵�id������Ӣ����Ϣ��

	// 3 �����Ƿ���ʲô����Ҫ�̳е��¸�Ӣ�۵�
}

void Hero::SetActionFrame()
{
	//1 ���� �õ����е�ActionFrame
	int standFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"StandFrame",m_HeroID);

	int moveFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"MoveFrame",m_HeroID);

	int attackFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"AttackFrame",m_HeroID);

	int dieFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"DieFrame",m_HeroID);

	int winFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"WinFrame",m_HeroID);

	//2 ��ֵ
	int frameanim[5] = { standFrame, moveFrame, attackFrame, dieFrame, winFrame };
	m_ActionsFrameCount.clear();
	for (int i=0; i<5; ++i)
	{
		m_ActionsFrameCount.push_back(cocos2d::Value(frameanim[i]));
	}
}

void Hero::playMoveAnimation() 
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_Move];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);
	//animaction->setDuration(0.4f);

	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animaction);
	this->runAction(pRepeat);
}
void Hero::playAttackAnimation() 
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_Attack];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);
	//animaction->setDuration(0.4f);

	this->runAction(animaction);
}

//------------------------------------------------------------------------------------
void Hero::ActorReadyStart()
{
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Hero::ActorReadyUpdate(float dt)
{
	;
}
void Hero::ActorReadyEnd()
{
	;
}
//------------------------------------------------------------------------------------
void Hero::ActorStandStart()
{
	Vector2D realpos = this->GetPosition();
	this->setPosition(cocos2d::Vec2(realpos.x,realpos.y));
}
void Hero::ActorStandUpdate(float dt)
{
	;
}
void Hero::ActorStandEnd()
{
	;
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
	;
}
//-----
void Hero::ActorAttackStart()
{
}
void Hero::ActorAttackUpdate(float dt)
{
	;
}
void Hero::ActorAttackEnd()
{
	;
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
//------------------------------------------------------------------------------------