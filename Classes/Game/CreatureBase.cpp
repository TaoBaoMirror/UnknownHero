#include "CreatureBase.h"
//

CreatureBase::CreatureBase() :MaxViewRadius(1),
	CurViewRadius(3),
	MaxHP(1),
	CurHP(1),
	MaxMP(1),
	CurMP(1),
	MaxSpeed(0),
	CurSpeed(0),
	RecoverHP(0),
	RecoverMP(0)
{

}
// add by Hitman [7/7/2015]
AIProperty::AIProperty() :
	Explore_LowRangeOfBias(0.5f),
	Explore_HighRangeOfBias(1.5f),
	AttackTarget_LowRangeOfBias(0.5f),
	AttackTarget_HighRangeOfBias(1.5f)
{

}
