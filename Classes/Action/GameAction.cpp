#include "GameAction.h"


GameAction::GameAction(int typeID) :
	m_ActionTypeID(typeID)
{
}


GameAction::~GameAction(void)
{
}

void GameAction::ClickAction()
{
	;
}

void GameAction::UseAction(int level)
{
	;
}

bool GameAction::IsActionDirectly()
{
	return m_bIsDirectly;
}