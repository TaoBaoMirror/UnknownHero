#ifndef __WEAPON_SWORD_H__
#define __WEAPON_SWORD_H__

#include "Weapon/GameSkill.h"

class Weapon_Sword : public GameSkill
{
public:
	Weapon_Sword(Soldier* pOwner);
	~Weapon_Sword(void);
};

#endif //__WEAPON_SWORD_H__