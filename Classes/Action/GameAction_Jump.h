#ifndef __GAME_ACTION_JUMP_H__
#define __GAME_ACTION_JUMP_H__

#include "Action/GameAction.h"

class GameAction_Jump : public GameAction
{
public:
	GameAction_Jump(int typeID);
	~GameAction_Jump(void);

	virtual void UseAction(int level) override;
protected:
	int m_SkillID;
};

#endif //__GAME_ACTION_JUMP_H__
