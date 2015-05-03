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

	void HeroAdventureStart(); //Ӣ�۽���ս��������ʱ�������� ��ʼ��һЩ���ο�ս������

private:
	PlayerManager(void);

	static PlayerManager* m_Instance;

	//--------------------------

	Hero* m_pMainRole;
	
};

#endif //