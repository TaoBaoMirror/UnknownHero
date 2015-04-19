/********************************************************************
	created:	2015/01/17
	created:	17:1:2015   18:17
	filename: 	E:\cyvasse\TestAI\AttackType.h
	file path:	E:\cyvasse\TestAI
	file base:	AttackType
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef AttackType_h__
#define AttackType_h__

#include <iostream>

class AttackRange;

class AttackDesc
{
public: 
	AttackDesc();
	virtual ~AttackDesc();
	//[ÐòÁÐ»¯µÄ]
	int		ID;
	int		AttackRangeType;
	int		AttackType;
	bool	IsEmitted;
	//
protected:
	AttackRange*	pAttackRange;
	//////////////////////////////////////////////////////////////////////////
	AttackRange*	createAttackRange();
public: 
	bool	Load(std::ifstream& is);
	bool	Save(std::ofstream& os);

	AttackRange*	GetAttackRangePtr();
	void	Runtime_SetAttackRangeType(int RType);

};



#endif // AttackType_h__
