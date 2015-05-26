#include "GameStates.h"

#include "Actor/PlayerManager.h"
#include "Actor/EnemyManager.h"
#include "Actor/NPCManager.h"

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
	m_NextST = GameStatus::ST_Null;
}

GameState_Plot::~GameState_Plot(void)
{
}

GameState_Plot* GameState_Plot::Instance()
{
	static GameState_Plot instance;

	return &instance;
}

void GameState_Plot::SetNextStatus(GameStatus st)
{
	m_NextST = st;
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
	m_NextST = GameStatus::ST_Null;
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
	//初始化所有数据

	//介绍背景的剧情(几个画和文字交代)

	//背景介绍播放完开始播放剧情
}

void GameState_Born::Execute(float dt)
{
	//if(播放完了动画)
	//{
		//播放最初的剧情
		GameManager::GetInstance()->SetGameST(GameStatus::ST_Plot);
		//剧情结束后进入选择英雄职业
		GameState_Plot::Instance()->SetNextStatus(ST_SelectHero);
	//}
	
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
	//切换到选人Layer
}

void GameState_SelectHero::Execute(float dt)
{
	//如果已经选择了角色
	//切换到City
	//if (选定了使用的英雄)
	//{
		GameManager::GetInstance()->SetGameST(GameStatus::ST_City);
	//}	
	//
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
	//1 放置主角到城市出生点
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
	//正常流程 应该是进入wait 然后ui播放 "准备开战"
	//播放结束后进入SF_Hero
	//GameManager::GetInstance()->SetFightST(SF_Wait);
	GameManager::GetInstance()->SetFightST(SF_Hero);
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