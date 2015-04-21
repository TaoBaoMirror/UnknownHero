#include "GameStates.h"

#include "Actor/PlayerManager.h";
#include "Actor/EnemyManager.h";
#include "Actor/NPCManager.h";

#include "Scene/GameManager.h"

//------------------------------------------------------------
GameState_Title::GameState_Title(void)
{
}

GameState_Title::~GameState_Title(void)
{
}

GameState_Title* GameState_Title::Instance()
{
	static GameState_Title instance;

	return &instance;
}

void GameState_Title::Enter()
{
	;
}

void GameState_Title::Execute(float dt)
{
	;
}

void GameState_Title::Exit()
{
	;
}
//------------------------------------------------------------
GameState_Plot::GameState_Plot(void)
{
}

GameState_Plot::~GameState_Plot(void)
{
}

GameState_Plot* GameState_Plot::Instance()
{
	static GameState_Plot instance;

	return &instance;
}

void GameState_Plot::Enter()
{
	;
}

void GameState_Plot::Execute(float dt)
{
	;
}

void GameState_Plot::Exit()
{
	;
}
//------------------------------------------------------------
GameState_Born::GameState_Born(void)
{
}

GameState_Born::~GameState_Born(void)
{
}

GameState_Born* GameState_Born::Instance()
{
	static GameState_Born instance;

	return &instance;
}

void GameState_Born::Enter()
{
	;
}

void GameState_Born::Execute(float dt)
{
	;
}

void GameState_Born::Exit()
{
	;
}
//------------------------------------------------------------
GameState_SelectHero::GameState_SelectHero(void)
{
}

GameState_SelectHero::~GameState_SelectHero(void)
{
}

GameState_SelectHero* GameState_SelectHero::Instance()
{
	static GameState_SelectHero instance;

	return &instance;
}

void GameState_SelectHero::Enter()
{
	;
}

void GameState_SelectHero::Execute(float dt)
{
	;
}

void GameState_SelectHero::Exit()
{
	;
}
//------------------------------------------------------------
GameState_City::GameState_City(void)
{
}

GameState_City::~GameState_City(void)
{
}

GameState_City* GameState_City::Instance()
{
	static GameState_City instance;

	return &instance;
}

void GameState_City::Enter()
{
	;
}

void GameState_City::Execute(float dt)
{
	GameManager::GetInstance()->UpdateCity(dt);
}

void GameState_City::Exit()
{
	;
}
//------------------------------------------------------------
GameState_Fight::GameState_Fight(void)
{
}

GameState_Fight::~GameState_Fight(void)
{
}

GameState_Fight* GameState_Fight::Instance()
{
	static GameState_Fight instance;

	return &instance;
}

void GameState_Fight::Enter()
{
	;
}

void GameState_Fight::Execute(float dt)
{
	//fight update
	GameManager::GetInstance()->UpdateFight(dt);
}

void GameState_Fight::Exit()
{
	;
}
//------------------------------------------------------------
GameState_GameOver::GameState_GameOver(void)
{
}

GameState_GameOver::~GameState_GameOver(void)
{
}

GameState_GameOver* GameState_GameOver::Instance()
{
	static GameState_GameOver instance;

	return &instance;
}

void GameState_GameOver::Enter()
{
	;
}

void GameState_GameOver::Execute(float dt)
{
	;
}

void GameState_GameOver::Exit()
{
	;
}
//------------------------------------------------------------