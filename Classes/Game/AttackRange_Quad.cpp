#include "AttackRange_Quad.h"

AttackRange_Quad::AttackRange_Quad()
	:AttackRange(RangeType::QUAD)
{

}

AttackRange_Quad::~AttackRange_Quad()
{

}

void AttackRange_Quad::UpdateRange( const GridPos& centerPos,const AttackRangeData& param )
{
	AttackRange::UpdateRange(centerPos,param);
	//
	G_GetSceneMap().FindTilesInQuad(centerPos,param.ExternalRadius,AttackGPosList);
}
