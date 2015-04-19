#include "AttackRange_V.h"

AttackRange_V::AttackRange_V()
	:AttackRange(RangeType::VERTICAL)
{

}

AttackRange_V::~AttackRange_V()
{

}

void AttackRange_V::UpdateRange( const GridPos& centerPos,const AttackRangeData& param )
{
	AttackRange::UpdateRange(centerPos,param);
	//
	G_GetSceneMap().FindTilesInV(centerPos,param.ExternalRadius,AttackGPosList);
}
