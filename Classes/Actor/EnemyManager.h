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

	bool IsAnyBodyHere();//�鿴�Ƿ��е����ڵ�ǰ������

	void CreateMonster(int monsterID);

private:
	EnemyManager(void);

	static EnemyManager* m_Instance;
	//--------------------------------------------------
	//Ҫ�ֳ�������������Ϊ,Ҫ�ý��̲����ȶ�,Զ�̺�,��ֹ������ͻ
	//(������ֻ̹��赲������·)
	std::vector<Actor*> m_ShortRangeMonsters;

	std::vector<Actor*> m_LongRangeMonsters;

	std::vector<Actor*> m_SpecialRangeMonsters;
};

#endif //__ENEMY_MANAGER_H__