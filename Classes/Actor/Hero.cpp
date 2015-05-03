#include "Hero.h"

#include "Data/TableManager.h"
//----------------------------------------------
Hero::Hero(void)
{
	std::string test[5] = {"stand", "move", "attack", "die", "win"};
	//ActionsName = test; 
	for (int i=0; i<5; ++i)
	{
		ActionsName.push_back(test[i]);
	}

	
}


Hero::~Hero(void)
{
}

Hero* Hero::createWithHeroID(int id)
{
	Hero* pHero = new Hero();
	
	pHero->SetHeroID(id);

	std::string heroTexID = TableManager::GetInstance()->GetTableData(TableType::Table_Hero,"HeroTextureID",id);
	pHero->SetHeroTexID(heroTexID);

	//���� ���ֲ�Ӧ���Ƕ���� Ӧ��������������
	std::string heroName = TableManager::GetInstance()->GetTableData(TableType::Table_Hero,"HeroName",id);
	pHero->SetHeroName(heroName);

	pHero->SetActionFrame();


	//res
	std::string tex_hero = "Hero_" + heroTexID;
	pHero->SetResource(tex_hero);

	//release
	pHero->autorelease();

	return pHero;
}

void Hero::NotAnActor(void)
{
	//����Ҫ����ܶණ��

	// 1 �����������,���������д��ָ��ɵ� SoldierManager

	// 2 ��¼����Ӣ�۵�id������Ӣ����Ϣ��

	// 3 �����Ƿ���ʲô����Ҫ�̳е��¸�Ӣ�۵�
}

void Hero::SetActionFrame()
{
	//1 ���� �õ����е�ActionFrame
	int standFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"StandFrame",m_HeroID);

	int moveFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"MoveFrame",m_HeroID);

	int attackFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"AttackFrame",m_HeroID);

	int dieFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"DieFrame",m_HeroID);

	int winFrame = TableManager::GetInstance()->GetTableIntData(TableType::Table_Hero,"WinFrame",m_HeroID);

	//2 ��ֵ
	int frameanim[5] = { standFrame, moveFrame, attackFrame, dieFrame, winFrame };
	m_ActionsFrameCount.clear();
	for (int i=0; i<5; ++i)
	{
		m_ActionsFrameCount.push_back(cocos2d::Value(frameanim[i]));
	}
}