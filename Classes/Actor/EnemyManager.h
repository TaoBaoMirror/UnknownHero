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

	bool IsAnyBodyHere();//�鿴�Ƿ��е����ڵ�ǰ������

	Monster* CreateMonster(int monsterID);

	void ReadyFight();

private:
	EnemyManager(void);

	static EnemyManager* m_Instance;
	//--------------------------------------------------
	Monster* CreateSpecialMonster(int monsterID);
	Monster* CreateLongMonster(int monsterID);
	Monster* CreateShortMonster(int monsterID);
	//--------------------------------------------------
	//Ҫ�ֳ�������������Ϊ,Ҫ�ý��̲����ȶ�,Զ�̺�,��ֹ������ͻ
	//(������ֻ̹��赲������·)
	std::vector<Monster*> m_ShortRangeMonsters;

	std::vector<Monster*> m_LongRangeMonsters;

	std::vector<Monster*> m_SpecialRangeMonsters;

	Actor* m_pCurEnemy;
};

#endif //__ENEMY_MANAGER_H__