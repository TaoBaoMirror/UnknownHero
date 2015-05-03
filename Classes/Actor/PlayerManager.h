#ifndef __PLAY_MANAGER_H__
#define __PLAY_MANAGER_H__

#include "Actor/Hero.h"
#include "Actor/StandbyHero.h"

class PlayerManager
{
public:
	static PlayerManager* GetInstance();
	
	~PlayerManager(void);

	void Init();

	void Update(float dt);

	StandbyHero* RandomStandbyHero();

	void HeroBorn(StandbyHero* pTempleHero);

	void HeroAdventureStart(); //英雄进入战斗场景的时候调用这个 初始化一些初次开战的数据

private:
	PlayerManager(void);

	static PlayerManager* m_Instance;

	//--------------------------

	Hero* m_pMainRole;
	
};

#endif //