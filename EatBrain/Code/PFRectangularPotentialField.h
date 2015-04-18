/********************************************************************
	created:	2014/11/30
	created:	30:11:2014   12:52
	filename: 	E:\BunkerAI\BunkerAI\Code\PFRectangularPotentialField.h
	file path:	E:\BunkerAI\BunkerAI\Code
	file base:	PFRectangularPotentialField
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef PFRectangularPotentialField_h__
#define PFRectangularPotentialField_h__

#include "PFPotentialField.h"

class PFRectangularPotentialField : public PFPotentialField
{
public:


	PFRectangularPotentialField(int max_potential_half_width, int max_potential_half_height);

	~PFRectangularPotentialField();

	inline void SetMaxPotentialHalfWidth(int value)
	{
		_maxPotentialHalfWidth = value;
		updateBounds();
	}

	inline int GetMaxPotentialHalfWidth()
	{
		return _maxPotentialHalfWidth;
	}

	inline void SetMaxPotentialHalfHeight(int value)
	{
		_maxPotentialHalfHeight = value;
		updateBounds();
	}

	inline int GetMaxPotentialHalfHeight()
	{
		return _maxPotentialHalfHeight;
	}

	inline void SetPotential(int value)
	{
		_potential = value;
		updateBounds();
	}

	inline void SetGradation(int value)
	{
		_gradation = value;
		updateBounds();
	}

	int GetPotential()
	{
		return _potential;
	}

	inline int GetGradation()
	{
		return _gradation;
	}

	inline int GetPotentialBoundsHalfWidth()
	{
		return _boundsHalfWidth;
	}

	inline int GetPotentialBoundsHalfHeight()
	{
		return _boundsHalfHeight;
	}

	inline int GetLocalPotential(int local_x, int local_y);
	
protected:
	
private:
	//
	int _potential;

	int _gradation;

	int _maxPotentialHalfWidth;
	int _maxPotentialHalfHeight;

	int _boundsHalfWidth;
	int _boundsHalfHeight;
	//
	void updateBounds();
};


#endif // PFRectangularPotentialField_h__
