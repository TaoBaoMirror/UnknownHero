#ifndef __GAME_ACTION_MONSTERSTRONG_H__
#define __GAME_ACTION_MONSTERSTRONG_H__

#include "Action/GameAction.h"

class GameAction_MonsterStrong : public GameAction
{
public:
	GameAction_MonsterStrong(int typeID);
	~GameAction_MonsterStrong(void);

	virtual void UseAction(int level) override;
};

#endif //__GAME_ACTION_MONSTERSTRONG_H__
