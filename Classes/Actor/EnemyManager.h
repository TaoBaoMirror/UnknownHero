#ifndef __ENEMY_MANAGER_H__
#define __ENEMY_MANAGER_H__

#include "cocos2d.h"
#include <string.h>
#include <vector>

#include "Actor/Actor.h"
#include "Actor/Monster.h"

class EnemyManager
{
public:	
	static EnemyManager* GetInstance();

	~EnemyManager(void);

	void Init();

	void Update(float dt);

	bool IsAnyBodyHere();//查看是否还有敌人在当前场景上

	void CreateMonster(int monsterID);

private:
	EnemyManager(void);

	static EnemyManager* m_Instance;
	//--------------------------------------------------
	//要分成三个队列是因为,要让近程部队先动,远程后动,防止发生冲突
	//(比如近程怪会阻挡攻击线路)
	std::vector<Actor*> m_ShortRangeMonsters;

	std::vector<Actor*> m_LongRangeMonsters;

	std::vector<Actor*> m_SpecialRangeMonsters;
};

#endif //__ENEMY_MANAGER_H__