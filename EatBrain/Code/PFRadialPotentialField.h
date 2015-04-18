/********************************************************************
	created:	2014/11/30
	created:	30:11:2014   13:28
	filename: 	E:\BunkerAI\BunkerAI\Code\PFRadialPotentialField.h
	file path:	E:\BunkerAI\BunkerAI\Code
	file base:	PFRadialPotentialField
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef PFRadialPotentialField_h__
#define PFRadialPotentialField_h__

#include "PFPotentialField.h"

class PFRadialPotentialField:public PFPotentialField
{
public:
	PFRadialPotentialField();
	~PFRadialPotentialField();
	//
	inline void SetPotential(int value)
	{
		_potential = value;
		updateRadius();
	}

	inline void SetGradation(int value)
	{
		_gradation = value;
		updateRadius();
	}

	inline int GetGradation()
	{
		return _gradation;
	}

	inline int GetPotentialBoundsHalfWidth()
	{
		return _radius;
	}

	inline int GetPotentialBoundsHalfHeight()
	{
		return _radius;
	}

	int GetLocalPotential(int local_x,  int local_y);

	
protected:
	
private:

	int _potential;

    int _gradation;

    int _radius;
	//
	void updateRadius();

};

#endif // PFRadialPotentialField_h__
