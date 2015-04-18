/********************************************************************
	created:	2015/01/29
	created:	29:1:2015   17:13
	filename: 	E:\cyvasse\TestAI\AttackRange.h
	file path:	E:\cyvasse\TestAI
	file base:	AttackRange
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef AttackRange_h__
#define AttackRange_h__

#include "GridPos.h"
#include <vector>

enum RangeType
{
	CIRCLE,
	CROSS,
	QUAD,
	HORIZONTAL,
	VERTICAL
};

struct AttackRangeData
{
	AttackRangeData()
		:ExternalRadius(2),
		InternalRadius(1)
	{

	}
	int		ExternalRadius;
	int		InternalRadius;
};

class AttackRange
{
protected:
	std::vector<GridPos>	AttackGPosList;
	int						ARangeType;
	//
	AttackRange(int rangeType)
		:ARangeType(rangeType)
	{	
		AttackGPosList.reserve(32);
	}
public: 

	virtual void UpdateRange(const GridPos& centerPos,const AttackRangeData& param){}
	//
	bool	Inspect(const GridPos& GPos)
	{
		for (int i = 0 ;i<AttackGPosList.size();++i)
		{
			const GridPos& gpos = AttackGPosList[i];
			if (GPos.Equals(gpos))
			{
				return true;
			}
		}
		//
		return false;
	}
	//
	bool	Inspect(const std::vector<GridPos>& in_GPosList,std::vector<GridPos>& out_GPosList)
	{
		out_GPosList.clear();
		out_GPosList.reserve(in_GPosList.size());
		//
		for (int i = 0 ;i< in_GPosList.size();++i)
		{
			if (Inspect(in_GPosList[i]))
			{
				out_GPosList.push_back(in_GPosList[i]);
			}
		}
		//
		return ( out_GPosList.size() > 0 );
	}
	//
	const std::vector<GridPos>& GetRangeGPosList() const
	{
		return AttackGPosList;
	}
	//
	const int GetType() const {return ARangeType;}

};


#endif // AttackRange_h__
