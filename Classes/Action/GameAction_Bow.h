#ifndef __GAME_ACTION_BOW_H__
#define __GAME_ACTION_BOW_H__

#include "Action/GameAction.h"

class GameAction_Bow : public GameAction
{
public:
	GameAction_Bow(int typeID);
	~GameAction_Bow(void);

	virtual void UseAction(int level) override;
};

#endif //__GAME_ACTION_BOW_H__
