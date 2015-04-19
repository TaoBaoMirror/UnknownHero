#include "AttackRange_Round.h"


AttackRange_Round::AttackRange_Round()
	:AttackRange(RangeType::CIRCLE)
{

}

AttackRange_Round::~AttackRange_Round()
{

}


void AttackRange_Round::UpdateRange( const GridPos& centerPos,const AttackRangeData& param )
{
	AttackRange::UpdateRange(centerPos,param);
	//
	G_GetSceneMap().FindTilesInCircle(AttackGPosList,centerPos,param.ExternalRadius,param.InternalRadius);
	//
}