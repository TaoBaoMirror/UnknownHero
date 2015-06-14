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
	void AddGameSkill(int skillID);

	void UseSkill(int WeaponIndex);//0~2

	GameSkill* GetSkill(int WeaponIndex);

	void Update();

	//int GetCurActionsAmount();

private:
	std::map<int,GameSkill*> m_pSkillsMap;

	

	Soldier* m_Onwer;
};

#endif //__GAME_ACTIONS_H__
