/********************************************************************
	created:	2015/03/09
	created:	9:3:2015   10:27
	filename: 	E:\cyvasse\TestAI\AttackRange_Quad.h
	file path:	E:\cyvasse\TestAI
	file base:	AttackRange_Quad
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef AttackRange_Quad_h__
#define AttackRange_Quad_h__


#include "AttackRange.h"
#include "CommonFunc.h"
#include "GridSceneMap.h"

class AttackRange_Quad : public AttackRange
{
public:
	AttackRange_Quad();
	~AttackRange_Quad();
	//
	virtual void UpdateRange(const GridPos& centerPos,const AttackRangeData& param);
protected:

private:
};

#endif // AttackRange_Quad_h__
