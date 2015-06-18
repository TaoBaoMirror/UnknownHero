#ifndef __GAME_ACTION_SWORD_H__
#define __GAME_ACTION_SWORD_H__

#include "Action/GameAction.h"

class GameAction_Sword : public GameAction
{
public:
	GameAction_Sword(int typeID);
	~GameAction_Sword(void);

	virtual void UseAction(int level) override;

protected:
	int m_SkillID;
};

#endif //__GAME_ACTION_SWORD_H__
