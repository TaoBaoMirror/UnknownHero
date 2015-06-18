#ifndef _HERO_SWORDMAN_H__
#define _HERO_SWORDMAN_H__

#include "Actor/Hero.h"

class Hero_SwordMan : public Hero
{
public:
	Hero_SwordMan(void);
	~Hero_SwordMan(void);

	virtual void InitSkills() override;
};

#endif //_HERO_SWORDMAN_H__