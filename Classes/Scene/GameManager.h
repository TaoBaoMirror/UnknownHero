#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "GameStatus/GameStates.h"
#include "Data/SaveData.h"

#include <map>

#include "cocos2d.h"

//---------------------------------------------------------
enum FightStatus
{
	SF_Wait = 0,	//等待
	SF_Hero,		//自己行动
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
	void Init();

	void Update(float dt);

	//------------------------------
	void SetGameST(GameStatus st);

	GameStatus GetGameST();
	//------------------------------
	void SetFightST(FightStatus st);

	FightStatus GetFightST();

	void RoundPassed();

	bool CheckNoDyingActor();

	void UpdateFight(float dt);	
	//------------------------------
	void UpdateCity(float dt);
	//------------------------------

	void LoadGameData();
	void SaveGameData();
	//------------------------------
	void SetCurSaveData(int index)
	{
		m_CurSaveData = index;
	}

	SaveData* GetCurSaveData();

	bool CheckPlotIsHappen(int id);
	void PlotHappen(int id);

	int GetCurSpecialHeroProcess();
	void SpecialHeroJoin();

	bool MouseDown(const cocos2d::Vec2& p);
	void MouseUp(const cocos2d::Vec2& p);
	void MouseMove(const cocos2d::Vec2& p);

	void GameKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	void GameKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
private:
	//------------------------------
	static GameManager* m_Instance;
	GameManager();
	//------------------------------
	void Wait_Pre();
	void HeroFight_Pre();
	void EnemyFight_Pre();
	void NPCFight_Pre();

	void Wait_Post();
	void HeroFight_Post();
	void EnemyFight_Post();
	void NPCFight_Post();

	void Wait_Update(float dt);
	void HeroFight_Update(float dt);
	void EnemyFight_Update(float dt);
	void NPCFight_Update(float dt);

	//------------------------------
	void ProcessKeyPressed_Fight(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	void ProcessKeyReleased_Fight(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	//------------------------------
	GameStatus m_GameST;
	GameStateProcess* m_CurGameST;

	FightStatus m_CurFightST;	
	//------------------------------
	//Save Data
	SaveData* m_SData1;
	SaveData* m_SData2;
	SaveData* m_SData3;

	int m_CurSaveData;
	//------------------------------
	//已发生的剧情
	std::map<int,bool> m_GamePlotMap;
	//已经启用到第几个特殊英雄
	int m_SpecialHeroProcess;
	//------------------------------
};

#endif //__GAME_MANAGER_H__
