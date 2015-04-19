#include "AttackRange_H.h"

AttackRange_H::AttackRange_H()
	:AttackRange(RangeType::HORIZONTAL)
{

}

AttackRange_H::~AttackRange_H()
{

}

void AttackRange_H::UpdateRange( const GridPos& centerPos,const AttackRangeData& param )
{
	AttackRange::UpdateRange(centerPos,param);
	//
	G_GetSceneMap().FindTilesInH(centerPos,param.ExternalRadius,AttackGPosList);
}
