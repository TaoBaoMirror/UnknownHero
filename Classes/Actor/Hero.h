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
	//名字
	std::string m_HeroName;
	int m_HeroID;

	//职业
	CareerBase* m_pCareerData;

	//背包 携带物

	//

	//计步器
	int m_AlreadyStep;
	int m_MaxStep;
};

#endif //__MAIN_ROLE_H__
