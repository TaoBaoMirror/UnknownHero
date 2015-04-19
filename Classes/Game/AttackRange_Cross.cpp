#include "AttackRange_Cross.h"

AttackRange_Cross::AttackRange_Cross()
	:AttackRange(RangeType::CROSS)
{

}

AttackRange_Cross::~AttackRange_Cross()
{

}

void AttackRange_Cross::UpdateRange( const GridPos& centerPos,const AttackRangeData& param )
{
	AttackRange::UpdateRange(centerPos,param);
	//
	G_GetSceneMap().FindTilesInCross(centerPos,param.ExternalRadius,param.InternalRadius,AttackGPosList);
}
