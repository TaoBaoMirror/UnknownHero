/********************************************************************
	created:	2015/03/09
	created:	9:3:2015   10:34
	filename: 	E:\cyvasse\TestAI\AttackRange_V.h
	file path:	E:\cyvasse\TestAI
	file base:	AttackRange_V
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef AttackRange_V_h__
#define AttackRange_V_h__

#include "AttackRange.h"
#include "CommonFunc.h"
#include "GridSceneMap.h"

class AttackRange_V : public AttackRange
{
public:
	AttackRange_V();
	~AttackRange_V();
	//
	virtual void UpdateRange(const GridPos& centerPos,const AttackRangeData& param);
protected:

private:
};

#endif // AttackRange_V_h__
