#ifndef __NPC_MANAGER_H__
#define __NPC_MANAGER_H__

#include "cocos2d.h"
#include <string.h>
#include <vector>

#include "Actor/Actor.h"

class NPCManager
{
public:
	static NPCManager* GetInstance();
	
	~NPCManager(void);

	void Init();

	void Update(float dt);

	bool IsAnyBodyHere();//查看是否还有NPC在当前场景上

	void ReadyFight();

private:
	NPCManager(void);

	static NPCManager* m_Instance;

	std::vector<Actor*> m_ShortRangeMonsters;

	std::vector<Actor*> m_LongRangeMonsters;

	std::vector<Actor*> m_SpecialRangeMonsters;

	Actor* m_pCurNPC;
};

#endif //__NPC_MANAGER_H__