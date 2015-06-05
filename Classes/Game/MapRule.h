/********************************************************************
	created:	2015/06/04
	created:	4:6:2015   15:41
	filename: 	E:\UnknownHero\Classes\Game\MapRule.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	MapRule
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef MapRule_h__
#define MapRule_h__

enum MapRuleType
{
	MapRule_Null = 0,
	MapRule_Poison,
	MapRule_FastMonster,


	MapRule_Num,
};

class MapRuleBase
{
public:
	//
	virtual void RuleStart(){}
	virtual void RuleUpdate(float dt){}
	virtual void RuleEnd(){}
	//
	virtual void BeginRound(){}
	virtual void EndRound(){}
	//
	virtual int GetRuleType() = 0;
	//

};

class MapRuleNull:public MapRuleBase
{
public:
	virtual int GetRuleType() override { return MapRule_Null;}

};

class MapRulePoison:public MapRuleBase
{
public:
	//
	virtual void RuleStart();
	virtual void RuleUpdate(float dt);
	virtual void RuleEnd();	
	//
	virtual int GetRuleType() override { return MapRule_Poison;}

protected:
	int		mRoundCounter;
};

class MapRuleFastMonster : public MapRuleBase
{
public:
	virtual void RuleStart();
	virtual void RuleUpdate(float dt);
	virtual void RuleEnd();	
	//
	virtual void BeginRound();
	virtual void EndRound();
	//
	virtual int GetRuleType() override { return MapRule_FastMonster;}
protected:
};

class MapRuleSystem
{
	static MapRuleBase*	RuleList[MapRule_Num];

public:
	MapRuleSystem();

	~MapRuleSystem();
	void ChangeRule(int ruleType);
	//
	MapRuleBase* CurrentState() const;

	void SetCurrentState( MapRuleBase* s );
	void SetCurrentState( int ruleType );


	void Update( float dt );

	//
	void BeginRound();
	//void UpdateRound();
	void EndRound();
	//
protected:
	MapRuleBase*	mCurMapRule;

};

#endif // MapRule_h__
