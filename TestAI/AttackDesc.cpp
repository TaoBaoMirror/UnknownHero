#include "AttackDesc.h"
#include "CommonFunc.h"
#include "AttackRangeCreater.h"
AttackDesc::AttackDesc() :
	ID(-1),
	AttackRangeType(-1),
	AttackType(-1),
	IsEmitted(false),
	pAttackRange(0)
{

}
AttackDesc::~AttackDesc()
{
	if(pAttackRange)
	{
		delete pAttackRange;
		pAttackRange = 0;
	}
}

bool AttackDesc::Load( std::ifstream& is )
{
	is >> ID;
	is >> AttackRangeType;
	is >> AttackType;
	is >> IsEmitted;
	return true;
}

bool AttackDesc::Save( std::ofstream& os )
{
	//
	os << ID << std::endl;
	os << AttackRangeType << std::endl;
	os << AttackType << std::endl;
	os << IsEmitted << std::endl;
	return true;

}

AttackRange* AttackDesc::GetAttackRangePtr()
{
	return createAttackRange();
}

void AttackDesc::Runtime_SetAttackRangeType( int RType )
{
	if (RType != AttackRangeType)
	{
		delete pAttackRange; pAttackRange = NULL;
		//
		AttackRangeType = RType;
		pAttackRange = AttackRangeCreater::CreateAttackRange(AttackRangeType);
	}
}

AttackRange* AttackDesc::createAttackRange()
{
	if(pAttackRange) return pAttackRange;
	else pAttackRange = AttackRangeCreater::CreateAttackRange(AttackRangeType);
	return pAttackRange;
}
