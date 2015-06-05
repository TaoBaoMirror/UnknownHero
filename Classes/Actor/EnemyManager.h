#ifndef __ENEMY_MANAGER_H__
#define __ENEMY_MANAGER_H__

#include "cocos2d.h"
#include <string.h>
#include <vector>

#include "Actor/Monster_Special.h"
#include "Actor/Monster_Long.h"
#include "Actor/Monster_Short.h"

class EnemyManager
{
public:	
	static EnemyManager* GetInstance();

	~EnemyManager(void);

	void Init();

	void Update(float dt);

	bool IsAnyBodyHere();//查看是否还有敌人在当前场景上

	bool CheckNoDyingActor();

	Monster* CreateMonster(int monsterID);

	void ReadyFight();

	void ClearCurEnemy(Actor* checkActor);

	void RemoveShortMonster(Monster_Short* pMonster);
	void RemoveLongMonster(Monster_Long* pMonster);
	void RemoveSpecialMonster(Monster_Special* pMonster);

	void SetActiontTimesInOneRound(int n);

private:
	EnemyManager(void);

	static EnemyManager* m_Instance;
	//--------------------------------------------------
	Monster* CreateSpecialMonster(int monsterID);
	Monster* CreateLongMonster(int monsterID);
	Monster* CreateShortMonster(int monsterID);
	//--------------------------------------------------
	//要分成三个队列是因为,要让近程部队先动,远程后动,防止发生冲突
	//(比如近程怪会阻挡攻击线路)
	std::vector<Monster_Short*> m_ShortRangeMonsters;

	std::vector<Monster_Long*> m_LongRangeMonsters;

	std::vector<Monster_Special*> m_SpecialRangeMonsters;

	Actor* m_pCurEnemy;
};

#endif //__ENEMY_MANAGER_H__