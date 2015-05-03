#ifndef __GAME_STATUS_H__
#define __GAME_STATUS_H__

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
class GameStateProcess
{
public:
	virtual void Enter(){}

	virtual void Execute(float dt){}

	virtual void Exit(){}
};
//---------------------------------------------------------
class GameState_Title : public GameStateProcess
{
public:
	GameState_Title(void);
	~GameState_Title(void);

	static GameState_Title* Instance();

	void Enter();

	void Execute(float dt);

	void Exit();
};
//---------------------------------------------------------
class GameState_Plot : public GameStateProcess
{
public:
	GameState_Plot(void);
	~GameState_Plot(void);

	void SetNextStatus(GameStatus st);

	static GameState_Plot* Instance();

	void Enter();

	void Execute(float dt);

	void Exit();

private:
	GameStatus m_NextST;
};
//---------------------------------------------------------
class GameState_Born : public GameStateProcess
{
public:
	GameState_Born(void);
	~GameState_Born(void);

	static GameState_Born* Instance();

	void Enter();

	void Execute(float dt);

	void Exit();
};
//---------------------------------------------------------
class GameState_SelectHero : public GameStateProcess
{
public:
	GameState_SelectHero(void);
	~GameState_SelectHero(void);

	static GameState_SelectHero* Instance();

	void Enter();

	void Execute(float dt);

	void Exit();
};
//---------------------------------------------------------
class GameState_City : public GameStateProcess
{
public:
	GameState_City(void);
	~GameState_City(void);

	static GameState_City* Instance();

	void Enter();

	void Execute(float dt);

	void Exit();
};
//---------------------------------------------------------
class GameState_Fight : public GameStateProcess
{
public:
	GameState_Fight(void);
	~GameState_Fight(void);

	static GameState_Fight* Instance();

	void Enter();

	void Execute(float dt);

	void Exit();
	
};
//---------------------------------------------------------
class GameState_GameOver : public GameStateProcess
{
public:
	GameState_GameOver(void);
	~GameState_GameOver(void);

	static GameState_GameOver* Instance();

	void Enter();

	void Execute(float dt);

	void Exit();
};
//---------------------------------------------------------
#endif //