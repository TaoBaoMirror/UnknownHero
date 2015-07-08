#include "Actor.h"
#include "Actor/ActorStatus.h"

#include "Game/MapManager.h"
#include "Game/AttackSystem.h"
#include "Game/TargetingSystem.h"
#include "Game/Goal_SoldierThink.h"
#include "Scene/MarkTileManager.h"
#include "Game/SoldierManager.h"
#include "Game/Camp.h"
#include "Messaging/MessageListenerManager.h"
#include "Game/Soldier.h"
#include "Weapon/GameSkill.h"
#include "Weapon/SkillList.h"
#include "Game/Trigger/GameTrigger.h"

const float Actor::g_ActorMoveTime = 0.5f;

Actor::Actor() :
	Soldier(0),m_OneRoundActionTimes(1),m_bFaceDirect(false)
{	
	Soldier::Init();
}


Actor::~Actor(void)
{
}

void Actor::update(float delta)
{
	cocos2d::CCSprite::update(delta);

	if (m_pFSM != nullptr)
	{
		m_pFSM->update(delta);
	}	
}

void Actor::SetResource(std::string name)
{
	if (m_framesDict.size() == 0)
	{
		int numAnim = m_ActionsFrameCount.size();
		//m_framesDict = new cocos2d::Map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>*>();
		m_framesDict.clear();
		for (int i = 0; i < numAnim; ++i)
		{
			cocos2d::Vector<cocos2d::SpriteFrame*> temp; //= new cocos2d::Vector<cocos2d::SpriteFrame*>();

			int numAction = m_ActionsFrameCount.at(i).asInt();
			for (int k = 0; k < numAction; ++k)
			{
				std::string frameName = ActionsName[i];

				std::stringstream ss;
				ss<<k; 
				std::string kStr = ss.str();
				frameName = name + "_" + frameName + "_" + kStr + ".png";

				cocos2d::SpriteFrame* spriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);

				if (spriteframe != nullptr)
				{
					temp.pushBack(spriteframe);
				}
				//
				if (k == numAction - 1)
				{
					if (temp.size() != 0)
					{
						m_framesDict.insert(std::pair<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>>(ActionsName[i],temp));
					}
					break;
				}
			}
		}
	}

	std::string initName = name + "_" + ActionsName[0] + "_0.png";
	initWithSpriteFrameName(initName);
	cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(initName);
}
//-------------------------
void Actor::BeginTraval()
{
	Soldier::BeginTraval();
}
//-------------------------
void Actor::EndTraval()
{
	Soldier::EndTraval();
	// add by Hitman [6/8/2015]
	//在移动完毕的时候，刷一遍Triggers
	TriggerManager::GetInstance()->UpdateRound();
	//
	FinishRound();
}
//-------------------------
bool Actor::TravalTo(const GridPos& GPos)
{
	int lastPosX = this->GetStayGPos().X;

	if(Soldier::TravalTo(GPos) == false) return false;

	if (GPos.X < lastPosX)
	{
		m_bFaceDirect = true;
	}
	else if(GPos.X > lastPosX)
	{
		m_bFaceDirect = false;
	}

	m_pFSM->SetStatus(Actor_Move::Instance());

	ChunkMap* pChunkMap = MapManager::GetInstance()->GetCurChunkMap();
	if (pChunkMap != nullptr)
	{
		Vector2D realPos;
		pChunkMap->GetGridSceneMap().GridPosToWorldPos(GPos,realPos);

		cocos2d::Vec2 cocosRealPos;
		cocosRealPos.x = realPos.x;
		cocosRealPos.y = realPos.y;

		cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

		cocos2d::MoveTo* pMoveto = cocos2d::MoveTo::create(g_ActorMoveTime,cocosRealPos);
		pAcs.pushBack(pMoveto);
		cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(Actor::EndTraval,this));
		pAcs.pushBack(pCallFunc);

		cocos2d::Sequence* pSec = cocos2d::Sequence::create(pAcs);

		this->runAction(pSec);
	}

	return true;
}
//-------------------------
void Actor::AIThink(float dt)
{
	GetTargetingSystem()->Update(dt);

	GetBrain()->Process();
}

void Actor::Attack( Soldier* other , int number)
{
	Soldier::Attack(other,number);

	if (GetSkillList() != nullptr && GetSkillList()->GetUsingSkill() != nullptr)
	{
		auto atkData = GetSkillList()->GetUsingSkill()->CreateAttackData(other->GetID());
		m_pTempAtkData = atkData;
	}		
	
	//
	m_pFSM->SetStatus(Actor_Attack::Instance());
}

void Actor::Attack( const GridPos& gPos , int number )
{
	Soldier::Attack(gPos,number);
	
	if (GetSkillList() != nullptr && GetSkillList()->GetUsingSkill() != nullptr)
	{
		auto atkData = GetSkillList()->GetUsingSkill()->CreateAttackData(gPos);
		m_pTempAtkData = atkData;
	}

	//
	m_pFSM->SetStatus(Actor_Attack::Instance());
}

//void Actor::UseDeputyWeapon( Soldier* other, int index )
//{
//	//Soldier::Attack(other);
//	//auto atkData = GetAttackSystem()->CreateAttackData(other->GetID());
//	GameActions* pGameActions = GetGameActions(index);
//	ActionBase* pDepWeapon = pGameActions->GetWeapon(index);
//	if (pDepWeapon != nullptr)
//	{
//		auto depData = pDepWeapon->CreateAttackData(other->GetID());
//
//		m_pTempAtkData = depData;
//
//		m_pFSM->SetStatus(Actor_Attack::Instance());
//	}
//}

void Actor::GetHurt(const DamageData& damageData)
{
	Soldier::GetHurt(damageData);

	if (CreatureBase::CurHP <= 0)
	{
		m_pFSM->SetStatus(Actor_Die::Instance());
	}
}

//-------------------------
void Actor::ActorAttackStart()
{
	if(getActionByTag(ActorAnim_Attack)) return;

	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;
	auto ani = createAnimation(ActorAnim_Attack);
	auto func_2 = cocos2d::CallFunc::create( CC_CALLBACK_0(Actor::CalcAttack , this , m_pTempAtkData));

	pAcs.pushBack(ani);
	pAcs.pushBack(func_2);

	auto seq = cocos2d::Sequence::create(pAcs);
	seq->setTag(ActorAnimType::ActorAnim_Attack);
	this->runAction(seq);
}
void Actor::ActorAttackUpdate(float dt)
{
	;
}
void Actor::ActorAttackEnd()
{
	;
}
//-------------------------
void Actor::ActorDieStart()
{
	if(getActionByTag(ActorAnim_Die)) return;
	//
	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	auto ani = createAnimation(ActorAnim_Die);

	auto func_2 = cocos2d::CallFunc::create( CC_CALLBACK_0(Actor::CalcDie , this));

	pAcs.pushBack(ani);
	pAcs.pushBack(func_2);

	auto seq = cocos2d::Sequence::create(pAcs);
	seq->setTag(ActorAnimType::ActorAnim_Die);
	this->runAction(seq);
}
void Actor::ActorDieUpdate(float dt)
{
	;
}
void Actor::ActorDieEnd()
{
	;
}
//-------------------------
void Actor::CalcAttack( AttackData* pAtkData )
{
	if (pAtkData != nullptr)
	{
		pAtkData->m_pWeapon->SkillAttack(pAtkData);
	}
}

void Actor::CallBack_AttackFinish()
{
	m_pFSM->SetStatus(Actor_Stand::Instance());
}

void Actor::CalcDie()
{

}
//-------------------------
void Actor::showAttackRange(const std::vector<GridPos>&	AttackGPosList)
{
	ChunkMap* pChunkMap = MapManager::GetInstance()->GetCurChunkMap();
	if (pChunkMap != nullptr)
	{
		//pChunkMap->HideRangeData();
		//pChunkMap->ShowRangeData(AttackGPosList);
	}

	
}

void Actor::UpdateToCCWorldPos()
{
	setPosition(GetPosition().x,GetPosition().y);
}

void Actor::SetActionTimesInRound( int n )
{
	m_OneRoundActionTimes = n;
}

cocos2d::Animate* Actor::createAnimation( ActorAnimType Atype ,float delay)
{
	std::string name = ActionsName[(int)Atype];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,delay);
	CC_ASSERT(ani);
	cocos2d::Animate* animate = cocos2d::Animate::create(ani);
	return animate;
}

void Actor::FinishRound()
{
	m_OneRoundActionTimes -= 1;

	if (m_OneRoundActionTimes <= 0)
	{
		m_OneRoundActionTimes = 1;
		m_pFSM->SetStatus(Actor_Stand::Instance());
	}
	else
	{
		m_pFSM->SetStatus(Actor_Ready::Instance());
	}
}
