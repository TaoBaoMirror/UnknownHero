/********************************************************************
	created:	2015/03/09
	created:	9:3:2015   10:33
	filename: 	E:\cyvasse\TestAI\AttackRange_H.h
	file path:	E:\cyvasse\TestAI
	file base:	AttackRange_H
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef AttackRange_H_h__
#define AttackRange_H_h__

#include "AttackRange.h"
#include "CommonFunc.h"
#include "GridSceneMap.h"

class AttackRange_H : public AttackRange
{
public:
	AttackRange_H();
	~AttackRange_H();
	//
	virtual void UpdateRange(const GridPos& centerPos,const AttackRangeData& param);
protected:

private:
};
#endif // AttackRange_H_h__
