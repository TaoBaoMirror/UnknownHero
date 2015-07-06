#ifndef __BOSS_MANAGER_H__
#define __BOSS_MANAGER_H__

#include "Actor/Boss/Boss.h"
#include "Action/GameActionSystem.h"

class BossManager
{
public:
	static BossManager* GetInstance();
	
	~BossManager(void);

	void Init();

	void Update(float dt);

	void ReadyFight();

	bool CheckNoDyingActor();

	Boss* CreateBoss(BossType type);
	Boss* GetBoss(){return m_pBoss;}

	void ClearBossWeightList();
	void AddWeightToList(GameActionType pActType, int nWeight);


private:
	BossManager(void);

	static BossManager* m_Instance;

	//--------------------------

	Boss* m_pBoss;

	std::vector<std::pair<GameActionType,int>> m_BossWeightList;
	
};

#endif //