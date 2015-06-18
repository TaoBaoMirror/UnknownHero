#ifndef __GAME_ACTIONS_H__
#define __GAME_ACTIONS_H__

#include "Weapon/GameSkill.h"
#include "list"

#define MaxShowActions 3

class Soldier;

class SkillList
{
public:
	SkillList(Soldier* pSoldier);
	~SkillList(void);

public:
	GameSkill* AddGameSkill(int skillID);

	void UseSkill(int WeaponIndex, int lv);//0~4

	bool LaunchSkill(const GridPos& Gpos);

	GameSkill* GetSkill(int WeaponIndex);

	void SetUsingSkill(GameSkill* pSkill){pCurUsingSkill = pSkill;}
	GameSkill* GetUsingSkill(){return pCurUsingSkill;}

	void Update();

	//int GetCurActionsAmount();

	bool		CheckIsInRange(const GridPos& gpos);
	Soldier*	CheckHasTarget(const GridPos& gpos);

private:
	std::map<int,GameSkill*> m_pSkillsMap;

	GameSkill*	pCurUsingSkill;

	Soldier* m_Onwer;
};

#endif //__GAME_ACTIONS_H__
