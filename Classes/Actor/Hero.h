#ifndef __MAIN_ROLE_H__
#define __MAIN_ROLE_H__

#include "Actor/Actor.h"
#include "Career/CareerBase.h"

class Hero : public Actor
{
public:
	Hero(void);
	~Hero(void);

	static Hero* createWithHeroID(int id);

	void NotAnActor();

	void SetActionFrame();
	//------------------------------
	void SetHeroID(int id){m_HeroID = id;}

	void SetHeroTexID(std::string heroTexID){m_HeroTexID = heroTexID;}

	void SetHeroName(std::string name){m_HeroName = name;}

protected:
	//HeroID
	int			m_HeroID;
	//����
	std::string m_HeroName;
	//ͼƬ
	std::string m_HeroTexID;
	

	//ְҵ
	CareerBase* m_pCareerData;

	//���� Я����

	//

	//�Ʋ���
	int m_AlreadyStep;
	int m_MaxStep;
	
};

#endif //__MAIN_ROLE_H__
