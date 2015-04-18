/********************************************************************
	created:	2015/01/29
	created:	29:1:2015   17:20
	filename: 	E:\cyvasse\TestAI\AttackRange_Round.h
	file path:	E:\cyvasse\TestAI
	file base:	AttackRange_Round
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef AttackRange_Round_h__
#define AttackRange_Round_h__

#include "AttackRange.h"
#include "CommonFunc.h"
#include "GridSceneMap.h"

class AttackRange_Round : public AttackRange
{
public:
	AttackRange_Round();
	~AttackRange_Round();
	//
	virtual void UpdateRange(const GridPos& centerPos,const AttackRangeData& param);
protected:
	
private:
};

#endif // AttackRange_Round_h__
