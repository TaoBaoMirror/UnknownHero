/********************************************************************
	created:	2015/03/09
	created:	9:3:2015   10:30
	filename: 	E:\cyvasse\TestAI\AttackRange_Cross.h
	file path:	E:\cyvasse\TestAI
	file base:	AttackRange_Cross
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef AttackRange_Cross_h__
#define AttackRange_Cross_h__

#include "AttackRange.h"
#include "CommonFunc.h"
#include "GridSceneMap.h"

class AttackRange_Cross : public AttackRange
{
public:
	AttackRange_Cross();
	~AttackRange_Cross();
	//
	virtual void UpdateRange(const GridPos& centerPos,const AttackRangeData& param);
protected:

private:
};


#endif // AttackRange_Cross_h__
