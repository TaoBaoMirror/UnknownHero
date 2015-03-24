#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

enum GameStatus
{
	ST_City_Born = 0,
	ST_City,
	ST_Fight,
	ST_Fight_Hero_Die,

};

enum FightStage
{
	SF_Hero = 0,
	SF_Enemy,
	SF_NPC,
};

class GameManager
{
public:	
	~GameManager();

	GameManager* GetInstance();

	//------------------------------
	void SetGameStatus(GameStatus st);

	GameStatus GetGameStatus();

	//------------------------------
	void Init();

	void Update(float dt);

	//------------------------------
	void RoundPassed();

	

private:
	GameManager();

	static GameManager* m_Instance;

	GameStatus m_GameST;

	FightStage m_CurFightST;
};

#endif //__GAME_MANAGER_H__
