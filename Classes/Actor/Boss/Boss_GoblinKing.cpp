#include "Boss_GoblinKing.h"

#include "Game\Goal_Type.h"
#include "Game\ExploreGoal_Evaluator.h"
#include "Action\GameActionSystem.h"
#include "..\ActorStatus.h"
#include "Data\TableManager.h"
#include "Weapon\SkillList.h"
#include "Game\CommonFunc.h"
#include "UI\MainControllerPanel.h"
#include "Scene\GameScene.h"
#include "Scene\GameManager.h"
#include "..\EnemyManager.h"
#include "Game\MapManager.h"
#include "Bullet\GameBullet.h"
#include "Game\GoblinKing_Think.h"
#include "Game\Msg_Type.h"
#include "Messaging\MessageDispatcher.h"

Boss_GoblinKing::Boss_GoblinKing(void):Boss()
{
	m_bBallistic = false;

	std::string test[8] = {"stand", "move", "attack", "die", "win", "usemachine", "summon", "shake"};
	for (int i=0; i<8; ++i)
	{
		ActionsName.push_back(test[i]);
	}

	m_pFSM = new ActorFSM(this);

	//放大一些
	setScale(3);

	CreateBrain();
}


Boss_GoblinKing::~Boss_GoblinKing(void)
{
}

void Boss_GoblinKing::update( float delta )
{
	Boss::update(delta);
}
/*
void Boss_GoblinKing::UseMachine()
{
	
	//---------
	//随机三个里面的一个
	int IndexAction = 0;
	//ui系统中先显示选择的action
	int maxgroup = GameActionSystem::GetInstance()->GetMaxUseGroup();
	int findgroupID = -1;
	 
	while (findgroupID == -1)
	{
		float randvalue = CCRANDOM_0_1(); 
		float scalvalue = randvalue * maxgroup * 100;

		for (int i=maxgroup-1; i>=0; --i)
		{
			if (scalvalue > i*100)
			{
				if (GameActionSystem::GetInstance()->IsGroupLocked(i) == false)
				{
					findgroupID = i;
					break;
				}
			}
		}
	}
	
}
*/

void Boss_GoblinKing::SkillAttack()
{
	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	auto anim = createAttackAnimation();
	auto func_calsum = cocos2d::CallFunc::create( CC_CALLBACK_0(Boss_GoblinKing::ShootBullet, this ));


	pAcs.pushBack(anim);
	pAcs.pushBack(func_calsum);


	auto seq = cocos2d::Sequence::create(pAcs);
	seq->setTag(ActorAnim_Attack);
	this->runAction(seq);
}

void Boss_GoblinKing::SkillSummon(int ilevel)
{

	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	auto animSum1 = createSummonAnimation();
	auto func_calsum = cocos2d::CallFunc::create( CC_CALLBACK_0(Boss_GoblinKing::CalcSummon, this, ilevel ));

	pAcs.pushBack(animSum1);
	pAcs.pushBack(func_calsum);

	auto seq = cocos2d::Sequence::create(pAcs);
	seq->setTag(ActorAnimType::ActorAnim_SP2);
	this->runAction(seq);
}

void Boss_GoblinKing::SkillShake(int ilevel)
{
	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	auto anim = createShakeAnimation();
	auto func_calshake = cocos2d::CallFunc::create( CC_CALLBACK_0(Boss_GoblinKing::CalcShake, this, ilevel ));

	pAcs.pushBack(anim);
	pAcs.pushBack(func_calshake);


	auto seq = cocos2d::Sequence::create(pAcs);
	seq->setTag(ActorAnimType::ActorAnim_SP3);
	this->runAction(seq);
}

//-------------------------------------------------------------

void Boss_GoblinKing::ActorReadyStart()
{
	playMoveAnimation();

}

void Boss_GoblinKing::ActorReadyUpdate( float dt )
{
}

void Boss_GoblinKing::ActorReadyEnd()
{

}
//----------------------
void Boss_GoblinKing::ActorAttackStart()
{
	
}

void Boss_GoblinKing::ActorAttackUpdate( float dt )
{

}

void Boss_GoblinKing::ActorAttackEnd()
{

}
//----------------------
void Boss_GoblinKing::ActorStandStart()
{
	stopAllActions();
	//
	playStandAnimation();
}

void Boss_GoblinKing::ActorStandUpdate( float dt )
{

}

void Boss_GoblinKing::ActorStandEnd()
{

}
//----------------------
void Boss_GoblinKing::ActorMoveStart()
{

}

void Boss_GoblinKing::ActorMoveUpdate( float dt )
{

}

void Boss_GoblinKing::ActorMoveEnd()
{

}
//----------------------
void Boss_GoblinKing::ActorDieStart()
{

}

void Boss_GoblinKing::ActorDieUpdate( float dt )
{

}

void Boss_GoblinKing::ActorDieEnd()
{

}
//----------------------
void  Boss_GoblinKing::playStandAnimation()
{
	cocos2d::Animate* animaction = Actor::createAnimation(ActorAnimType::ActorAnim_Stand);
	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animaction);
	pRepeat->setTag((int)ActorAnimType::ActorAnim_Stand);

	this->runAction(pRepeat);
}


cocos2d::Animate* Boss_GoblinKing::createUseMachineAnimation()
{
	cocos2d::Animate* pAnimate = Actor::createAnimation(ActorAnimType::ActorAnim_SP1);
	return pAnimate;
}


cocos2d::Animate*  Boss_GoblinKing::createAttackAnimation()
{
	cocos2d::Animate* pAnimate = Actor::createAnimation(ActorAnimType::ActorAnim_Attack);
	return pAnimate;
}

cocos2d::Animate*  Boss_GoblinKing::createSummonAnimation()
{
	cocos2d::Animate* pAnimate = Actor::createAnimation(ActorAnimType::ActorAnim_SP2);
	return pAnimate;
}

cocos2d::Animate*  Boss_GoblinKing::createShakeAnimation()
{
	cocos2d::Animate* pAnimate = Actor::createAnimation(ActorAnimType::ActorAnim_SP3);
	return pAnimate;
}


void Boss_GoblinKing::CalcSummon(int ilevel)
{
	int numCreateMonster = 0;

	switch (ilevel)
	{
	case 1:
		numCreateMonster = 2;
		break;
	case 2:
		numCreateMonster = 3;
		break;
	case 3:
		numCreateMonster = 5;
		break;
	case 4:
		numCreateMonster = 7;
		break;
	case 5:
		numCreateMonster = 10;
		break;
	}

	for (int i=0; i<numCreateMonster; ++i)
	{
		float randvalue = CCRANDOM_0_1(); 

		float scalRandVal = randvalue * 1000.0f;

		int createMonsterType = 0;

		if (scalRandVal > 800.0f)
		{
			createMonsterType = m_SummonMonsterIDs[0];
		}
		else if(scalRandVal > 500.0f)
		{
			createMonsterType = m_SummonMonsterIDs[1];
		}
		else
		{
			createMonsterType = m_SummonMonsterIDs[2];
		}

		GridPos gpos;

		//这里有个跳出的判断

		int     safeLoopNum = 0;
		int     safeLoopNumLimit = 20;
		do
		{
			G_GetSceneMap().GetRandomNodeLocation(gpos);
			safeLoopNum++;

		}while( CanSetTo(gpos) == false || safeLoopNum > safeLoopNumLimit);

		if (safeLoopNum <= safeLoopNumLimit)
		{
			Actor* pMons = ChunkMap::InstantiateCreature("Monster",createMonsterType,0,gpos);
			if (pMons != nullptr)
			{
				ChunkMap* pChunkMap = MapManager::GetInstance()->GetCurChunkMap();
				if (pChunkMap != nullptr)
				{
					pChunkMap->DeployActor(pMons,gpos);
				}

				//1 生成怪

				//2 怪物脚下加上特效
			}
		}
		

		
	}
	
	FinishRound();

}

void Boss_GoblinKing::CalcShake(int ilevel)
{
	GameScene* pGScene = GameManager::GetInstance()->GetGameScene();
	if (pGScene != nullptr)
	{
		MainControllerPanel* pAB = pGScene->GetOneArmBandit();
		if (pAB != nullptr)
		{
			pAB->RollAll();
		}
		
	}
	
	FinishRound();
}

//----------------------

Boss* Boss_GoblinKing::CreateBoss()
{
	Boss_GoblinKing* pBoss = new Boss_GoblinKing();

	CC_ASSERT (pBoss != nullptr);

	pBoss->SetActionFrame();

	//res
	std::string tex_Boss = "Boss_GoblinKing";
	pBoss->SetResource(tex_Boss);
	pBoss->BossInit();
	pBoss->InitSkills();

	//release
	//pBoss->autorelease();

	return pBoss;
}

void Boss_GoblinKing::SetActionFrame()
{
	//1 读表 得到所有的ActionFrame
	int standFrame = 1;

	int moveFrame = 1;

	int attackFrame = 1;

	int dieFrame = 1;

	int winFrame = 1;

	int spFrame1 = 1;

	int spFrame2 = 1;

	int spFrame3 = 1;

	//2 赋值
	int frameanim[8] = { standFrame, moveFrame, attackFrame, dieFrame, winFrame, spFrame1, spFrame2, spFrame3 };
	m_ActionsFrameCount.clear();
	for (int i=0; i<8; ++i)
	{
		m_ActionsFrameCount.push_back(cocos2d::Value(frameanim[i]));
	}
}
void Boss_GoblinKing::InitSkills()
{
	if (GetSkillList() != nullptr)
	{
		GameSkill* pSkill = GetSkillList()->AddGameSkill(0);
		pSkill->SetIsTargetToGrid(true);
		GetSkillList()->SetUsingSkill(pSkill);
	}
}
void Boss_GoblinKing::BossInit()
{
	m_pFSM->SetStatus(Actor_Ready::Instance());


	m_SummonMonsterIDs[0] = 0;
	m_SummonMonsterIDs[1] = 0;
	m_SummonMonsterIDs[2] = 0;
}
//这里是给boss设置新AI的
void Boss_GoblinKing::CreateBrain()
{
	m_pBrain = new GoblinKing_Think(this);
}
////
//开火需要的
void Boss_GoblinKing::ShootBullet()
{
	//
	if (GetSkillList() != nullptr)
	{
		GameSkill* pSkill = GetSkillList()->GetUsingSkill();

		if (pSkill != nullptr)
		{
			auto m_pTempAtkData = pSkill->CreateAttackData(GetStayGPos() + getDir(RandInt(0,3)) * 3 );

			auto bullet = GameBulletManager::GetInstance()->CreateBullet(0,m_pTempAtkData);
			bullet->Emit();
			//
			stopAllActions();
			playStandAnimation();
		}
		else
		{
			FinishRound();
		}
	}
	//


}

void Boss_GoblinKing::CallBack_AttackFinish()
{
	FinishRound();
}

GridPos Boss_GoblinKing::getDir( int dir )
{
	if(dir == 0) return GridPos(0,-1);
	if(dir == 1) return GridPos(1,0);
	if(dir == 2) return GridPos(0,1);
	if(dir == 3) return GridPos(-1,0);
}

void Boss_GoblinKing::OnDeployChunk()
{
	// 左上角 half
	mObstructArea.Init(GetStayGPos() - GridPos(3/2,3/2),3,3,G_GetSceneMap());
	//
	auto area = mObstructArea.GetArea();
	//
	for (int i = 0;i< area.size();++i)
	{
		auto node = G_GetSceneMap().GetNode(area[i]);
		auto mnd = Cast_MapNodeData(node.ExtraInfo());
		if (mnd != nullptr)
		{
			mnd->Creature = this;
		}

	}
}

void Boss_GoblinKing::AIThink( float dt )
{
	Actor::AIThink(dt);
	//
	if(m_pBrain) m_pBrain->Process();
}

bool Boss_GoblinKing::HandleMessage( const Telegram& telegram )
{
	if(m_pBrain) m_pBrain->HandleMessage(telegram);

	return true;

}

void Boss_GoblinKing::FinishRound()
{
	Boss::FinishRound();
	//
	Dispatcher->DispatchMsg(0,GetListenerID(),GetListenerID(),Msg_AI_SetInactive,0,0);
}

//----------------------