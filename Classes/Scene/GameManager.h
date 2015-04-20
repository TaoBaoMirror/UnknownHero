#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "GameStatus/GameStates.h"
#include "Data/SaveData.h"

enum GameStatus
{
	ST_Null = 0,
	ST_Title,	//标题UI
	ST_Plot,		//发生剧情
	ST_Born,		//出生
	ST_SelectHero,	//选择英雄
	ST_City,		//主城中的自由探索
	ST_Fight,		//野外
	ST_GameOver,	//
};
//---------------------------------------------------------
enum FightStatus
{
	SF_Hero = 0,	//自己行动
	SF_Enemy,		//敌人行动
	SF_NPC,			//友军行动
	SF_OneFightOver,
};
//---------------------------------------------------------
class GameManager
{
public:	
	~GameManager();

	static GameManager* GetInstance();

	//------------------------------
	void SetGameStatus(GameStatus st);

	GameStatus GetGameStatus();

	//------------------------------
	void Init();

	void Update(float dt);

	//------------------------------
	void SetGameST(GameStatus st);

	GameStatus GetGameST();
	//------------------------------
	void SetFightST(FightStatus st);

	FightStatus GetFightST();

	void RoundPassed();

	void UpdateFight(float dt);	
	//------------------------------

	void LoadGameData();
	void SaveGameData();
	//------------------------------
	void SetCurSaveData(int index)
	{
		m_CurSaveData = index;
	}
private:
	//------------------------------
	static GameManager* m_Instance;
	GameManager();
	//------------------------------
	void HeroFight_Pre();
	void EnemyFight_Pre();
	void NPCFight_Pre();

	void HeroFight_Post();
	void EnemyFight_Post();
	void NPCFight_Post();

	void HeroFight_Update(float dt);
	void EnemyFight_Update(float dt);
	void NPCFight_Update(float dt);
	//------------------------------
	GameStatus m_GameST;
	GameStateProcess* m_CurGameST;

	FightStatus m_CurFightST;	
	//------------------------------
	//Save Data
	SaveData m_SData1;
	SaveData m_SData2;
	SaveData m_SData3;

	int m_CurSaveData;
	//------------------------------
};

#endif //__GAME_MANAGER_H__
