#ifndef __GAME_ACTION_COIN_H__
#define __GAME_ACTION_COIN_H__

#include "Action/GameAction.h"

class GameAction_Coin : public GameAction
{
public:
	GameAction_Coin(int typeID);
	~GameAction_Coin(void);

	virtual void UseAction(int level) override;
protected:
	int m_SkillID;
};

#endif //__GAME_ACTION_COIN_H__
