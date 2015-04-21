#ifndef __MAIN_ROLE_H__
#define __MAIN_ROLE_H__

#include "Actor/Actor.h"
#include "Career/CareerBase.h"

class Hero : public Actor
{
public:
	Hero(void);
	~Hero(void);

private:
	//����
	std::string m_HeroName;
	int m_HeroID;

	//ְҵ
	CareerBase* m_pCareerData;

	//���� Я����

	//

	//�Ʋ���
	int m_AlreadyStep;
	int m_MaxStep;
};

#endif //__MAIN_ROLE_H__
