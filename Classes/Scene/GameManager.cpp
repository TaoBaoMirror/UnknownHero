#include "GameManager.h"

#include "Actor/PlayerManager.h";
#include "Actor/EnemyManager.h";
#include "Actor/NPCManager.h";

#include "ResDef.h"

GameManager* GameManager::m_Instance = nullptr;

GameManager* GameManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameManager();
	}

	return m_Instance;
}

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::SetGameST(GameStatus st)
{
	//----------------------------------
	m_GameST = st;
	//----------------------------------
	if (m_CurGameST != nullptr)
	{
		m_CurGameST->Exit();
	}

	switch (m_GameST)
	{
	case ST_Title:
		{
			m_CurGameST = GameState_Title::Instance();
		}
		break;
	case ST_Plot:
		{
			m_CurGameST = GameState_Plot::Instance();
		}
		break;
	case ST_Born:
		{
			m_CurGameST = GameState_Born::Instance();
		}
		break;
	case ST_SelectHero:
		{
			m_CurGameST = GameState_SelectHero::Instance();
		}
		break;
	case ST_City:
		{
			m_CurGameST = GameState_City::Instance();
		}
		break;
	case ST_Fight:
		{
			m_CurGameST = GameState_Fight::Instance();
		}
		break;
	case ST_GameOver:
		{
			m_CurGameST = GameState_GameOver::Instance();
		}
		break;
	default:
		break;
	}

	if (m_CurGameST != nullptr)
	{
		m_CurGameST->Enter();
	}
}

GameStatus GameManager::GetGameST()
{
	return m_GameST;
}

void GameManager::Update(float dt)
{
	if (m_CurGameST != nullptr)
	{
		m_CurGameST->Execute(dt);
	}
}
//-----------------------------------------------------------------
void GameManager:: RoundPassed()
{
	if (m_CurFightST == FightStatus::SF_Hero)
	{
		SetFightST(FightStatus::SF_Enemy);
	}
	else if (m_CurFightST == FightStatus::SF_Enemy)
	{
		SetFightST(FightStatus::SF_NPC);
	}
	else if (m_CurFightST == FightStatus::SF_NPC)
	{
		SetFightST(FightStatus::SF_OneFightOver);		 
	}
}

void GameManager::SetFightST(FightStatus st)
{
	switch (m_CurFightST)
	{
	case SF_Hero:
		HeroFight_Post();
		break;
	case SF_Enemy:
		EnemyFight_Post();
		break;
	case SF_NPC:
		NPCFight_Post();
		break;
	case SF_OneFightOver:
		break;
	default:
		break;
	}

	m_CurFightST = st;

	switch (m_CurFightST)
	{
	case SF_Hero:
		HeroFight_Pre();
		break;
	case SF_Enemy:
		EnemyFight_Pre();
		break;
	case SF_NPC:
		NPCFight_Pre();
		break;
	case SF_OneFightOver:
		break;
	default:
		break;
	}
}
//--------------
void GameManager::HeroFight_Pre()
{
	;
}
void GameManager::EnemyFight_Pre()
{
	if (EnemyManager::GetInstance()->IsAnyBodyHere() == false)
	{
		RoundPassed();
	}
}
void GameManager::NPCFight_Pre()
{
	if (NPCManager::GetInstance()->IsAnyBodyHere() == false)
	{
		RoundPassed();
	}
}
//--------------
void GameManager::HeroFight_Post()
{
	;
}
void GameManager::EnemyFight_Post()
{
	;
}
void GameManager::NPCFight_Post()
{
	;
}
//--------------
void GameManager::UpdateFight(float dt)
{
	switch (m_CurFightST)
	{
	case SF_Hero:
		HeroFight_Update(dt);
		break;
	case SF_Enemy:
		EnemyFight_Update(dt);
		break;
	case SF_NPC:
		NPCFight_Update(dt);
		break;
	case SF_OneFightOver:
		break;
	default:
		break;
	}
}

void GameManager::HeroFight_Update(float dt)
{
	PlayerManager::GetInstance()->Update(dt);
}
void GameManager::EnemyFight_Update(float dt)
{
	EnemyManager::GetInstance()->Update(dt);
}
void GameManager::NPCFight_Update(float dt)
{
	NPCManager::GetInstance()->Update(dt);
}
//-----------------------------------------------------------------
void GameManager::UpdateCity(float dt)
{
	;
}
//-----------------------------------------------------------------
void GameManager::LoadGameData()
{
	m_SData1.LoadSaveFile(ResDef::g_SaveDataFileName_1);
	m_SData2.LoadSaveFile(ResDef::g_SaveDataFileName_2);
	m_SData3.LoadSaveFile(ResDef::g_SaveDataFileName_3);
}
//-----------------------------------------------------------------
void GameManager::SaveGameData()
{
	switch (m_CurSaveData)
	{
	case 1:
		m_SData1.WriteSaveFile(ResDef::g_SaveDataFileName_1);
		break;
	case 2:
		m_SData2.WriteSaveFile(ResDef::g_SaveDataFileName_2);
		break;
	case 3:
		m_SData3.WriteSaveFile(ResDef::g_SaveDataFileName_3);
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------