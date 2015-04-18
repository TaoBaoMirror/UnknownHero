#include "AttackRangeCreater.h"
//
#include "AttackRange_Round.h"
#include "AttackRange_Quad.h"
#include "AttackRange_Cross.h"
#include "AttackRange_H.h"
#include "AttackRange_V.h"
//
AttackRange* AttackRangeCreater::CreateAttackRange( int AtkRangeType )
{
	AttackRange* AR = 0;

	switch(AtkRangeType)
	{
	case RangeType::CIRCLE:
		AR = new AttackRange_Round();
		break;

	case RangeType::CROSS:
		AR = new AttackRange_Cross();
		break;

	case RangeType::QUAD:
		AR = new AttackRange_Quad();
		break;

	case RangeType::HORIZONTAL:
		AR = new AttackRange_H();
		break;

	case RangeType::VERTICAL:
		AR = new AttackRange_V();
		break;

	default:
		AR = new AttackRange_Round();
		break;
	}
	//
	return AR;
}
