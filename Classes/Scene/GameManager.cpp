#include "GameManager.h"

#include "Actor/PlayerManager.h";
#include "Actor/EnemyManager.h";
#include "Actor/NPCManager.h";
#include "Game/MapManager.h"

#include "GameStatus/GameStates.h"
#include "Actor/ActorStatus.h"

#include "ResDef.h"
//
// add by Hitman [5/20/2015]
#include "Game/Camp.h"

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
	m_SData1 = new SaveData();
	m_SData2 = new SaveData();
	m_SData3 = new SaveData();

	m_CurGameST = nullptr;

	Camp::CreateCamps(3);
}


GameManager::~GameManager()
{
}

void GameManager::SetGameST(GameStatus st)
{
	//----------------------------------
	if (m_GameST == st)
	{
		return;
	}
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
	case  SF_Wait:
		Wait_Post();
		break;
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
	case  SF_Wait:
		Wait_Pre();
		break;
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
void GameManager::Wait_Pre()
{
	;
}

void GameManager::HeroFight_Pre()
{
	//将所有的角色状态都清除为 Actor_Ready
	PlayerManager::GetInstance()->ReadyFight();
}
void GameManager::EnemyFight_Pre()
{
	EnemyManager::GetInstance()->ReadyFight();
	//if (EnemyManager::GetInstance()->IsAnyBodyHere() == false)
	//{
	//	RoundPassed();
	//}
}
void GameManager::NPCFight_Pre()
{
	NPCManager::GetInstance()->ReadyFight();
	//if (NPCManager::GetInstance()->IsAnyBodyHere() == false)
	//{
	//	RoundPassed();
	//}
}
//--------------
void GameManager::Wait_Post()
{
	;
}

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
	auto pChunk = MapManager::GetInstance()->GetCurChunkMap();

	pChunk->update(dt);

	switch (m_CurFightST)
	{
	case  SF_Wait:
		Wait_Update(dt);
		break;
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
		{
			SetFightST(FightStatus::SF_Hero);
		}
		break;
	default:
		break;
	}
}

void GameManager::Wait_Update(float dt)
{
	;
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
	m_SData1->LoadSaveFile(ResDef::g_SaveDataFileName_1);
	m_SData2->LoadSaveFile(ResDef::g_SaveDataFileName_2);
	m_SData3->LoadSaveFile(ResDef::g_SaveDataFileName_3);
}
//-----------------------------------------------------------------
void GameManager::SaveGameData()
{
	switch (m_CurSaveData)
	{
	case 1:
		m_SData1->WriteSaveFile(ResDef::g_SaveDataFileName_1);
		break;
	case 2:
		m_SData2->WriteSaveFile(ResDef::g_SaveDataFileName_2);
		break;
	case 3:
		m_SData3->WriteSaveFile(ResDef::g_SaveDataFileName_3);
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------
SaveData* GameManager::GetCurSaveData()
{
	switch (m_CurSaveData)
	{
	case 1:
		return m_SData1;
	case 2:
		return m_SData2;
	case 3:
		return m_SData3;
	}

	return nullptr;
}
//-----------------------------------------------------------------
bool GameManager::CheckPlotIsHappen(int id)
{
	return false;
}
void GameManager::PlotHappen(int id)
{
	;
}

int GameManager::GetCurSpecialHeroProcess()
{
	return 0;
}
void GameManager::SpecialHeroJoin()
{
	;
}
//-----------------------------------------------------------------
void GameManager::GameKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
	if (m_CurGameST != nullptr)
	{		
		if (m_CurGameST == GameState_Fight::Instance())
		{
			ProcessKeyPressed_Fight(code, event);
		}
	}
	
}
//-----------------------------------------------------------------
void GameManager::GameKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
	;
}
//-----------------------------------------------------------------
void GameManager::ProcessKeyPressed_Fight(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
	if (m_CurFightST == SF_Hero)
	{
		Hero* pHero = PlayerManager::GetInstance()->GetHero();

		if (pHero != nullptr)
		{
			if (pHero->m_pFSM->GetStatus() == Actor_Ready::Instance())
			{
				if (code == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
				{
					if (pHero->MoveBackward() == true)
					{
					}
				}	
				else if (code == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
				{
					if (pHero->MoveForward() == true)
					{
					}
				}
				else if (code == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
				{
					if (pHero->MoveLeft() == true)
					{
					}
				}
				else if (code == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
				{
					if (pHero->MoveRight() == true)
					{
					}
				}
			}
		}
		
	}	
}
void GameManager::ProcessKeyReleased_Fight(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
	if (code == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		int i = 100;
	}	
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
	}
}