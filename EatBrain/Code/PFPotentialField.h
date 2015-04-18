/********************************************************************
	created:	2014/11/30
	created:	30:11:2014   11:49
	filename: 	E:\BunkerAI\BunkerAI\Code\PFPotentialField.h
	file path:	E:\BunkerAI\BunkerAI\Code
	file base:	PFPotentialField
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef PFPotentialField_h__
#define PFPotentialField_h__

#include "GridPos.h"


class PFPotentialField
{
public:
	PFPotentialField()
	{
		type = PF_TYPE_REPEL;
	}
	~PFPotentialField()
	{

	}
	//
	static const int PF_TYPE_ATTRACT = -1;
	static const int PF_TYPE_REPEL = 1;

	GridPos position;
	int		Id;

	/** (PF_TYPE_ATTRACT | PF_TYPE_REPEL). */
	int type;

	void SetPotentialType(int t)
	{
		type = t;
	}

	int PotentialBoundsHalfWidth() 
	{
		return 0;
	}

	int PotentialBoundsHalfHeight() 
	{
		return 0;
	}

	virtual int GetLocalPotential(int local_x,  int local_y)
	{
		return 0;
	}

	int GetPotential(int map_x, int map_y)
	{
		return GetLocalPotential(map_x - position.X,  map_y - position.Y);
	}
protected:
	
private:
};

#endif // PFPotentialField_h__
