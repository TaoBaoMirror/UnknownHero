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
	//��ʼ����������

	//���ܱ����ľ���(�����������ֽ���)

	//�������ܲ����꿪ʼ���ž���
}

void GameState_Born::Execute(float dt)
{
	//if(�������˶���)
	//{
		//��������ľ���
		GameManager::GetInstance()->SetGameST(GameStatus::ST_Plot);
		//������������ѡ��Ӣ��ְҵ
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
	//�л���ѡ��Layer
}

void GameState_SelectHero::Execute(float dt)
{
	//����Ѿ�ѡ���˽�ɫ
	//�л���City
	//if (ѡ����ʹ�õ�Ӣ��)
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
	//1 �������ǵ����г�����
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
	//�������� Ӧ���ǽ���wait Ȼ��ui���� "׼����ս"
	//���Ž��������SF_Hero
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