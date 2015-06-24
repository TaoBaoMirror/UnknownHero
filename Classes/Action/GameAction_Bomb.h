#ifndef __GAME_ACTION_BOMB_H__
#define __GAME_ACTION_BOMB_H__

#include "Action/GameAction.h"

class GameAction_Bomb : public GameAction
{
public:
	GameAction_Bomb(int typeID);
	~GameAction_Bomb(void);

	virtual void UseAction(int level) override;
protected:
	int m_SkillID;
};

#endif //__GAME_ACTION_BOMB_H__
