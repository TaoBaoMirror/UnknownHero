#ifndef __MAIN_ROLE_H__
#define __MAIN_ROLE_H__

#include "Actor/Actor.h"
#include "Career/CareerBase.h"

enum HeroType
{
	HeroType_SwordMan = 0,
};

class Hero : public Actor
{	
public:
	Hero();
	~Hero(void);

	static Hero* createWithHeroID(int id);

	void NotAnActor();

	void SetActionFrame();

	//------------------------------
	virtual void playMoveAnimation() override;
	virtual void playAttackAnimation() override;
	virtual void playStandAnimation() override;

	//------------------------------
	virtual void CalcAttack(AttackData* pAtkData) override;

	void SetHeroID(int id){m_HeroID = id;}

	void SetHeroTexID(std::string heroTexID){m_HeroTexID = heroTexID;}

	void SetHeroName(std::string name){m_HeroName = name;}
	//----------------------------------------
	virtual void InitSkills() override{}
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
	virtual void showAttackRange(const std::vector<GridPos>&	AttackGPosList) override;

	void ClickAttack(int groupID);

	void SelectGrid( const GridPos& GPos );

	void CancleSkill();
	void Attack(Soldier* other , int number) override;
protected:
	//HeroID
	int			m_HeroID;
	//����
	std::string m_HeroName;
	//ͼƬ
	std::string m_HeroTexID;
	

	//ְҵ
	CareerBase* m_pCareerData;

	//���� Я����

	//

	//�Ʋ���
	int m_AlreadyStep;
	int m_MaxStep;
	
};

#endif //__MAIN_ROLE_H__
