#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Actor/Actor.h"

class AttackData;
enum  MonsterType
{
	MonsterType_ShortRange = 0,
	MonsterType_LongRange,
	MonsterType_Special,
};

class Monster : public Actor
{
public:
	Monster(void);
	~Monster(void);

	static Monster* createWithMonsterID(int id);

	void SetActionFrame();

	//------------------------------
	virtual void playMoveAnimation() override;
	virtual void playAttackAnimation() override;
	virtual void playDieAnimation() override;

	//----------------------------------------
	virtual void ActorReadyStart() override;
	virtual void ActorReadyUpdate(float dt) override;
	virtual void ActorReadyEnd() override;

	virtual void ActorStandStart() override;
	virtual void ActorStandUpdate(float dt) override;
	virtual void ActorStandEnd() override;

	virtual void ActorMoveStart() override;
	virtual void ActorMoveUpdate(float dt) override;
	virtual void ActorMoveEnd() override;

	virtual void ActorAttackStart() override;
	virtual void ActorAttackUpdate(float dt) override;
	virtual void ActorAttackEnd() override;

	virtual void ActorDieStart() override;
	virtual void ActorDieUpdate(float dt) override;
	virtual void ActorDieEnd() override;

	virtual void ActorWinStart() override;
	virtual void ActorWinUpdate(float dt) override;
	virtual void ActorWinEnd() override;
	//----------------------------------------
	virtual void AIThink(float dt) override;
	//------------------------------
	virtual void CalcAttack( AttackData* pAtkData ) override;

	virtual void CalcDie() override;

	void SetMonsterName(std::string name)
	{
		m_MonsterName = name;
	}

	void SetMonsterID(int id)
	{
		m_MonsterID = id;
	}

	void SetMonsterTexID(std::string texID)
	{
		m_MonsterTexID = texID;
	}


protected:
	//Ãû×Ö
	std::string m_MonsterName;

	//MonsterType
	MonsterType	m_MonsterType;

	//HeroID
	int			m_MonsterID;

	//Í¼Æ¬
	std::string m_MonsterTexID;

	//Ö°Òµ
	//CareerBase* m_pCareerData;

};

#endif //__MONSTER_H__
