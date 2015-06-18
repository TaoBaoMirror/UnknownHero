#ifndef __GAME_SKILL_BASE_H__
#define __GAME_SKILL_BASE_H__

#include <string>

#include "Game/AttackSystem.h"

class GameSkill : public AttackSystem
{
public:
	GameSkill(Soldier* pOwner);
	~GameSkill(void);

	virtual void	Update() override;

	virtual bool	Load(std::ifstream& is) override;
	virtual bool	Save(std::ofstream& os) override;

	virtual void	SkillAim();

	void			SetIsTargetToGrid(bool bSet){m_IsTargetToGrid = bSet;}
	bool			IsTargetToGrid();

protected:
	std::string		ActionType;

	bool			m_IsTargetToGrid;

	//WPAttackType m_Type;
};

#endif //__GAME_SKILL_BASE_H__