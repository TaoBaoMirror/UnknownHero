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
	//Ҫ�ֳ�������������Ϊ,Ҫ�ý��̲����ȶ�,Զ�̺�,��ֹ������ͻ
	//(������ֻ̹��赲������·)
	std::vector<Monster_Short*> m_ShortRangeMonsters;

	std::vector<Monster_Long*> m_LongRangeMonsters;

	std::vector<Monster_Special*> m_SpecialRangeMonsters;

	Actor* m_pCurEnemy;
};

#endif //__ENEMY_MANAGER_H__