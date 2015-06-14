/********************************************************************
	created:	2015/03/14
	created:	14:3:2015   13:36
	filename: 	E:\cyvasse\TestAI\AttackSystem.h
	file path:	E:\cyvasse\TestAI
	file base:	AttackSystem
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef AttackSystem_h__
#define AttackSystem_h__

#include <iostream>
#include "AttackRange.h"
#include "AttackData.h"


class AttackData;
struct AttackDataBase;
struct AttackRangeData;
class  AttackRange;
class  Soldier;

class AttackSystem
{
public:
	AttackSystem(Soldier* pOwner);
	~AttackSystem();
	//
	void SetOriginalAttackDataBase(int data_id);
	const AttackDataBase* GetOriginalAttackDataBase() const ;
	AttackDataBase*	GetCurAttackDataBase();
	void SetAttackRange(int RTypt);
	AttackRange*	GetAttackRange();
	AttackRangeData*	GetAttackRangeData();
	//
	virtual void	Update();
	//
	virtual bool	Load(std::ifstream& is);
	virtual bool	Save(std::ofstream& os);
	//
	AttackData*		CreateAttackData(int BearerID);
	AttackData*		CreateAttackData(const GridPos& Gpos);

	virtual void	AttackLogic(int WeaponOwerID, int HurtActorID){}
protected:

	Soldier*				m_pOwner;
	//
	int						m_nOriginalAttackDataBaseID;//原始的攻击数据ID
	AttackDataBase			m_OriginalAttackDataBase;	//原始的攻击数据，指向管理器，常量
	int						m_eRangeType;				//攻击范围类型
	AttackRange*			m_pAttackRange;				//攻击范围
	AttackRangeData			m_AttackRangeData;			//攻击范围数据		
	//
	AttackDataBase			m_CurAttackDataBase;		//当前攻击数据			
private:
};

#endif // AttackSystem_h__
