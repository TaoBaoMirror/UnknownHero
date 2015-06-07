#include "MapRule.h"
#include "Actor/EnemyManager.h"
#include "Actor/Actor.h"
#include "Actor/PlayerManager.h"
#include "Game/AttackData.h"
MapRuleBase* MapRuleSystem::RuleList[MapRule_Num] = 
{
	new MapRuleNull() ,
	new MapRulePoison(),		//
	new MapRuleFastMonster()
};

MapRuleSystem::MapRuleSystem() :mCurMapRule(nullptr)
{

}

MapRuleSystem::~MapRuleSystem()
{

}

void MapRuleSystem::ChangeRule( int ruleType )
{
	mCurMapRule->RuleEnd();
	//
	mCurMapRule = RuleList[ruleType];
	//
	mCurMapRule->RuleStart();
}

MapRuleBase* MapRuleSystem::CurrentState() const
{
	return mCurMapRule;
}

void MapRuleSystem::SetCurrentState( MapRuleBase* s )
{
	mCurMapRule = s;
}

void MapRuleSystem::SetCurrentState( int ruleType )
{
	mCurMapRule = RuleList[ruleType];
}

void MapRuleSystem::Update( float dt )
{
	if(mCurMapRule) mCurMapRule->RuleUpdate(dt);
}

void MapRuleSystem::BeginRound()
{
	if(mCurMapRule) mCurMapRule->BeginRound();
}

void MapRuleSystem::EndRound()
{
	if(mCurMapRule) mCurMapRule->EndRound();
}

//////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////
void MapRulePoison::RuleStart()
{

}

void MapRulePoison::RuleUpdate( float dt )
{

}

void MapRulePoison::RuleEnd()
{

}

void MapRulePoison::EndRound()
{
	std::vector<Actor*> monsters;
	DamageData DD(1,-1,-1);
	PlayerManager::GetInstance()->GetHero()->GetHurt(DD);
	//
	EnemyManager::GetInstance()->GetMonsters(monsters);
	for (int i = 0;i< monsters.size();++i)
	{
		auto m = monsters[i];

		if (m)
		{
			m->GetHurt(DD);
		}
	}
}
//////////////////////////////////////////////////////////////////////////

void MapRuleFastMonster::RuleStart()
{

}

void MapRuleFastMonster::RuleUpdate( float dt )
{

}

void MapRuleFastMonster::RuleEnd()
{

}

void MapRuleFastMonster::BeginRound()
{
	EnemyManager::GetInstance()->SetActiontTimesInOneRound(2);
}

void MapRuleFastMonster::EndRound()
{

}
