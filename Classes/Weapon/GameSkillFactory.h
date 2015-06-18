#ifndef __GAMESKILL_FACTORY_H__
#define __GAMESKILL_FACTORY_H__

class GameSkill;
class Soldier;

class GameSkillFactory
{
public:
	static GameSkillFactory* GetInstance();

	~GameSkillFactory();

	GameSkill* CreateWeapon(int weaponID, Soldier* pOwner);
private:
	GameSkillFactory();
	static GameSkillFactory* m_Instance;
};

#endif //__GAMESKILL_FACTORY_H__
