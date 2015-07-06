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


Boss_GoblinKing::Boss_GoblinKing(void)
{
	m_bBallistic = false;

	std::string test[8] = {"stand", "move", "attack", "die", "win", "usemachine", "summon", "shake"};
	for (int i=0; i<8; ++i)
	{
		ActionsName.push_back(test[i]);
	}

	m_pFSM = new ActorFSM(this);

	m_pFSM->SetStatus(Actor_Ready::Instance());

	m_SummonMonsterIDs[0] = 0;
	m_SummonMonsterIDs[1] = 0;
	m_SummonMonsterIDs[2] = 0;

	struct timeval nowtime;
	cocos2d::gettimeofday(&nowtime, NULL);

	//��ʼ���������
	//timeval�Ǹ��ṹ�壬���������������һ��������Ϊ��λ�ģ�һ������΢��Ϊ��λ�� 
	unsigned rand_seed = (unsigned)(nowtime.tv_sec*1000 + nowtime.tv_usec/1000);    //��ת��Ϊ���� 
	srand(rand_seed);
}


Boss_GoblinKing::~Boss_GoblinKing(void)
{
}

void Boss_GoblinKing::update( float delta )
{
	Boss::update(delta);
}

void Boss_GoblinKing::UseBossSkill()
{
	m_bCanUseBossSkill = false;

	switch (m_CurBossState)
	{
	case BOSSGoblinKingState_Rest:
		{
			//��Ϣ���˾����ϻ��� ���������Ϣ ������ ������ʹ���ϻ���
			UseMachine();
		}
		break;
	case BOSSGoblinKingState_Stun:
		{
			m_pFSM->SetStatus(Actor_Stand::Instance());
		}
		break;
	default:
		break;
	}
}


void Boss_GoblinKing::UseBossAction( int m_ActionTypeID, int ilevel )
{
	//���֧�ֵ�action ����
	switch (m_ActionTypeID)
	{
	case 0:
		{
			SkillAttack(ilevel);
		}		
		break;
	case 2:
		{
			SkillShake(ilevel);
		}
		break;
	case 3:
		{
			SkillSummon(ilevel);
		}
		break;
	default:
		{
			BossOverwhelm();
		}
		break;
	}
}


void Boss_GoblinKing::SetGoblinKingState( BOSSGoblinKingState st )
{
	switch (m_CurBossState)
	{
	case BOSSGoblinKingState_Rest:
		{
			m_NextUseBossSkillRound = 2;
		}
		break;
	case BOSSGoblinKingState_Stun:
		{
			;
		}
		break;
	default:
		break;
	}

	m_CurBossState = st;

	switch (m_CurBossState)
	{
	case BOSSGoblinKingState_Rest:
		{
		}
		break;
	case BOSSGoblinKingState_Stun:
		{
			;
		}
		break;
	default:
		break;
	}
}

void Boss_GoblinKing::UseMachine()
{
	//---------
	//������������һ��
	int IndexAction = 0;
	//uiϵͳ������ʾѡ���action
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
	

	//---------
	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	auto anim = createUseMachineAnimation();

	auto func_1 = cocos2d::CallFuncN::create( CC_CALLBACK_0(Boss_GoblinKing::playStandAnimation , this ) );
	auto func_2 = cocos2d::CallFunc::create( CC_CALLBACK_0(Boss_GoblinKing::CalcUseMachine , this, findgroupID ));

	pAcs.pushBack(anim);
	pAcs.pushBack(func_1);
	pAcs.pushBack(func_2);

	auto seq = cocos2d::Sequence::create(pAcs);
	seq->setTag(ActorAnimType::ActorAnim_Attack);
	this->runAction(seq);
}


void Boss_GoblinKing::SkillAttack(int ilevel)
{
	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	auto anim = createAttackAnimation();

	auto func_calsum = cocos2d::CallFunc::create( CC_CALLBACK_0(Boss_GoblinKing::CalcAttack, this, ilevel ));
	auto func_stand = cocos2d::CallFuncN::create( CC_CALLBACK_0(Boss_GoblinKing::playStandAnimation , this ) );

	pAcs.pushBack(anim);
	pAcs.pushBack(func_calsum);
	pAcs.pushBack(func_stand);

	auto seq = cocos2d::Sequence::create(pAcs);
	//seq->setTag(ActorAnimType::ActorAnim_Attack);
	this->runAction(seq);
}

void Boss_GoblinKing::SkillSummon(int ilevel)
{

	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	auto animSum1 = createSummonAnimation();
	auto animSum2 = createSummonAnimation();

	auto func_calsum = cocos2d::CallFunc::create( CC_CALLBACK_0(Boss_GoblinKing::CalcSummon, this, ilevel ));
	auto func_stand = cocos2d::CallFuncN::create( CC_CALLBACK_0(Boss_GoblinKing::playStandAnimation , this ) );

	pAcs.pushBack(animSum1);
	pAcs.pushBack(func_calsum);
	pAcs.pushBack(animSum2);
	pAcs.pushBack(func_stand);

	auto seq = cocos2d::Sequence::create(pAcs);
	//seq->setTag(ActorAnimType::ActorAnim_Attack);
	this->runAction(seq);
}

void Boss_GoblinKing::SkillShake(int ilevel)
{
	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	auto anim = createShakeAnimation();

	auto func_calshake = cocos2d::CallFunc::create( CC_CALLBACK_0(Boss_GoblinKing::CalcShake, this, ilevel ));
	auto func_stand = cocos2d::CallFuncN::create( CC_CALLBACK_0(Boss_GoblinKing::playStandAnimation , this ) );

	pAcs.pushBack(anim);
	pAcs.pushBack(func_calshake);
	pAcs.pushBack(func_stand);

	auto seq = cocos2d::Sequence::create(pAcs);
	//seq->setTag(ActorAnimType::ActorAnim_Attack);
	this->runAction(seq);
}

void Boss_GoblinKing::BossOverwhelm()
{
	SetGoblinKingState(BOSSGoblinKingState_Rest);

	m_pFSM->SetStatus(Actor_Stand::Instance());
}

//-------------------------------------------------------------

void Boss_GoblinKing::ActorReadyStart()
{
	m_bCanUseBossSkill = true;
}

void Boss_GoblinKing::ActorReadyUpdate( float dt )
{
	Boss::ActorReadyUpdate(dt);

	switch (m_CurBossState)
	{
	case BOSSGoblinKingState_Rest:
		{
		}
		break;
	case BOSSGoblinKingState_Stun:
		{
			;
		}
		break;
	default:
		break;
	}
}

void Boss_GoblinKing::ActorReadyEnd()
{

}
//----------------------
void Boss_GoblinKing::ActorAttackStart()
{
	//���Ź�������
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
cocos2d::Animate* Boss_GoblinKing::createUseMachineAnimation()
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_SP1];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);

	return animaction;
}

void  Boss_GoblinKing::playStandAnimation()
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_Stand];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);

	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animaction);
	pRepeat->setTag((int)ActorAnimType::ActorAnim_Move);

	this->runAction(pRepeat);
}

cocos2d::Animate*  Boss_GoblinKing::createAttackAnimation()
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_Attack];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* pAnimation = cocos2d::Animate::create(ani);

	return pAnimation;
}

cocos2d::Animate*  Boss_GoblinKing::createSummonAnimation()
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_SP2];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* pAnimation = cocos2d::Animate::create(ani);
	
	return pAnimation;
}

cocos2d::Animate*  Boss_GoblinKing::createShakeAnimation()
{
	std::string name = ActionsName[(int)ActorAnimType::ActorAnim_SP3];
	cocos2d::Vector<cocos2d::CCSpriteFrame*> temp = m_framesDict.at(name);
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,0.1f);
	cocos2d::Animate* pAnimation = cocos2d::Animate::create(ani);
	
	return pAnimation;
}


//----------------------

void Boss_GoblinKing::CalcUseMachine(int index)
{
	GameActionSystem::GetInstance()->UseAction(index); //�ص���ʹ��ѡ���action
}

void Boss_GoblinKing::CalcAttack(int ilevel)
{
	//�ж�������boss��λ�ù�ϵ ������������ѡ��һ�������ͷŹ���

	int attdir = 0;

	if (GetSkillList() != nullptr)
	{
		GameSkill* pSkill = GetSkillList()->GetSkill((int)SkillType_GoblinKingAttack);
		if (pSkill != nullptr)
		{
			auto atkData = pSkill->CreateAttackData(m_AllAttackPos[attdir]);

			CommonFunc::CalcDamage(atkData);
		}
	}

	m_pFSM->SetStatus(Actor_Stand::Instance());

	SetGoblinKingState(BOSSGoblinKingState::BOSSGoblinKingState_Rest);
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
		G_GetSceneMap().GetRandomNodeLocation(gpos);

		Actor* pMons = ChunkMap::InstantiateCreature("Monster",createMonsterType,0,gpos);
		if (pMons != nullptr)
		{
			ChunkMap* pChunkMap = MapManager::GetInstance()->GetCurChunkMap();
			if (pChunkMap != nullptr)
			{
				pChunkMap->DeployActor(pMons,gpos);
			}
			
			//1 ���ɹ�
			//pMons->;

			//2 ������¼�����Ч
		}

		
	}
	
	m_pFSM->SetStatus(Actor_Stand::Instance());
	SetGoblinKingState(BOSSGoblinKingState::BOSSGoblinKingState_Rest);
}

void Boss_GoblinKing::CalcShake(int ilevel)
{
	//Director::getInstance()->getRunningScene();
	//cocos2d::Scene* pScene = this->getScene();
	//GameScene* pGScene = (GameScene*)pScene;
	GameScene* pGScene = GameManager::GetInstance()->GetGameScene();
	if (pGScene != nullptr)
	{
		MainControllerPanel* pAB = pGScene->GetOneArmBandit();
		if (pAB != nullptr)
		{
			pAB->RollAll();
		}
		
	}
	
	m_pFSM->SetStatus(Actor_Stand::Instance());
	SetGoblinKingState(BOSSGoblinKingState::BOSSGoblinKingState_Rest);
}

//----------------------

Boss* Boss_GoblinKing::CreateBoss()
{
	Boss_GoblinKing* pBoss = new Boss_GoblinKing();

	if (pBoss == nullptr)
	{
		//����
	}

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
	//1 ���� �õ����е�ActionFrame
	int standFrame = 1;

	int moveFrame = 1;

	int attackFrame = 1;

	int dieFrame = 1;

	int winFrame = 1;

	int spFrame1 = 1;

	int spFrame2 = 1;

	int spFrame3 = 1;

	//2 ��ֵ
	int frameanim[8] = { standFrame, moveFrame, attackFrame, dieFrame, winFrame, spFrame1, spFrame2, spFrame3 };
	m_ActionsFrameCount.clear();
	for (int i=0; i<8; ++i)
	{
		m_ActionsFrameCount.push_back(cocos2d::Value(frameanim[i]));
	}
}
//----------------------

void Boss_GoblinKing::InitSkills()
{
	if (GetSkillList() != nullptr)
	{
		GameSkill* pSkill = GetSkillList()->AddGameSkill(SkillType::SkillType_Sword);
		pSkill->SetIsTargetToGrid(true);
	}
}


void Boss_GoblinKing::BossInit()
{
	SetGoblinKingState(BOSSGoblinKingState_Rest);
	m_NextUseBossSkillRound = 1;
}
//----------------------