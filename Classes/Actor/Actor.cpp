#include "Actor.h"
#include "Actor/ActorStatus.h"

#include "Game/MapManager.h"
#include "Game/AttackSystem.h"
#include "Game/TargetingSystem.h"
#include "Game/Goal_SoldierThink.h"
#include "Scene/MarkTileManager.h"

const float Actor::g_ActorMoveTime = 0.5f;

Actor::Actor(void) :
	Soldier(0,0)
{	
}


Actor::~Actor(void)
{
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

	m_pFSM->SetStatus(Actor_Stand::Instance());
}
//-------------------------
bool Actor::TravalTo(const GridPos& GPos)
{
	if(Soldier::TravalTo(GPos) == false) return false;

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
void Actor::AIThink()
{
	GetTargetingSystem()->Update();

	GetBrain()->Process();
}

void Actor::Attack( Soldier* other )
{
	//Soldier::Attack(other);
	auto atkData = GetAttackSystem()->CreateAttackData(other->GetID());
	//
	m_pTempAtkData = atkData;
	//
	m_pFSM->SetStatus(Actor_Attack::Instance());

}

cocos2d::Animate* Actor::createAttackAnimation( int ani_type )
{
	std::string name = ActionsName[(int)ani_type];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);

	return animaction;
}


//-------------------------
void Actor::ActorAttackStart()
{
	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	auto anim = createAttackAnimation(ActorAnimType::ActorAnim_Attack);

	auto func_1 = cocos2d::CallFuncN::create( CC_CALLBACK_0(Actor::playMoveAnimation , this ) );
	auto func_2 = cocos2d::CallFunc::create( CC_CALLBACK_0(Actor::CalcAttack , this , m_pTempAtkData));

	pAcs.pushBack(anim);
	pAcs.pushBack(func_1);
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
void Actor::CalcAttack( AttackData* pAtkData )
{
	int i= 100;
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

	MarkTileManager::GetInstance()->SetMarkTiles(MarkTile_Attack,"ActorAttack",AttackGPosList);
}
//-------------------------