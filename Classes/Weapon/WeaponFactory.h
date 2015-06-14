#ifndef __WEAPON_FACTORY_H__
#define __WEAPON_FACTORY_H__

class GameSkill;
class Soldier;

class WeaponFactory
{
public:
	static WeaponFactory* GetInstance();

	~WeaponFactory();

	GameSkill* CreateWeapon(int weaponID, Soldier* pOwner);
private:
	WeaponFactory();
	static WeaponFactory* m_Instance;
};

#endif //__WEAPON_FACTORY_H__
