#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "Game/Soldier.h"

class Actor : public Soldier
{
public:
	Actor(void);
	~Actor(void);

	virtual void Attack(){}
	virtual void Move(){}

};

#endif //__ACTOR_H__