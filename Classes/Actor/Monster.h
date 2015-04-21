#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Actor/Actor.h"

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

private:
	//Ãû×Ö
	std::string m_MonsterName;

	//MonsterType
	MonsterType	m_MonsterType;

};

#endif //__MONSTER_H__
