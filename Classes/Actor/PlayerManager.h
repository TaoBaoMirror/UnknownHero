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

	void ReadyFight();

	bool CheckNoDyingActor();

	StandbyHero* RandomStandbyHero();

	void HeroBorn(StandbyHero* pTempleHero);

	Hero* GetHero(){return m_pMainRole;}

	void HeroAdventureStart(); //Ӣ�۽���ս��������ʱ�������� ��ʼ��һЩ���ο�ս������

private:
	PlayerManager(void);

	static PlayerManager* m_Instance;

	//--------------------------

	Hero* m_pMainRole;
	
};

#endif //