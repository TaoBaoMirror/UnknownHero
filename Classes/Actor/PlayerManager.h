#ifndef __PLAY_MANAGER_H__
#define __PLAY_MANAGER_H__

#include "Actor/Hero.h"
#include "Actor/StandbyHero.h"
#include "Action/GameActionSystem.h"

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

	void HeroDied();

	Hero* GetHero(){return m_pMainRole;}

	void HeroAdventureStart(); //Ӣ�۽���ս��������ʱ�������� ��ʼ��һЩ���ο�ս������

	void ClearMainRoleWeightList();
	void AddWeightToList(GameActionType pActType, int nWeight);

private:
	PlayerManager(void);

	static PlayerManager* m_Instance;

	//--------------------------

	Hero* m_pMainRole;

	std::vector<std::pair<GameActionType,int>> m_MainRoleWeightList;
	
};

#endif //