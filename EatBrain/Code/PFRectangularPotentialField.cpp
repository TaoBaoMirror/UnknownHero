#include "stdafx.h"
#include <math.h>
#include <xutility>
#include "PFRectangularPotentialField.h"

PFRectangularPotentialField::PFRectangularPotentialField( int max_potential_half_width, int max_potential_half_height ) 
	:PFPotentialField()
{
	_potential = 1;
	_gradation = 1;
	_maxPotentialHalfWidth = max_potential_half_width;
	_maxPotentialHalfHeight = max_potential_half_height;
	updateBounds();
}

int PFRectangularPotentialField::GetLocalPotential( int local_x, int local_y )
{
	if (abs(local_x) < _maxPotentialHalfWidth && abs(local_y) < _maxPotentialHalfHeight) 
		return type * _potential;

	if (abs(local_x) < _boundsHalfWidth && abs(local_y) < _boundsHalfHeight) 
	{

		int distance = 1;

		if (abs(local_x) > _maxPotentialHalfWidth && abs(local_y) > _maxPotentialHalfHeight) 
		{
			distance = abs(local_x) - _maxPotentialHalfWidth + abs(local_y) - _maxPotentialHalfHeight;
		}
		else if (abs(local_x) > _maxPotentialHalfWidth) 
		{
			distance = abs(local_x) - _maxPotentialHalfWidth;
		}
		else if (abs(local_y) > _maxPotentialHalfHeight) 
		{
			distance = abs(local_y) - _maxPotentialHalfHeight;
		}

		if (type < 0)
		{
			return std::min(0, type * (_potential - _gradation * distance) );
		}

		return std::max(0, type * (_potential - _gradation * distance) );
	}

	return 0;
}

void PFRectangularPotentialField::updateBounds()
{
	_boundsHalfWidth = _maxPotentialHalfWidth + ceil(float(_potential / _gradation)) - 1;
	_boundsHalfHeight = _maxPotentialHalfHeight + ceil(float(_potential / _gradation)) - 1;
}

PFRectangularPotentialField::~PFRectangularPotentialField()
{

}
