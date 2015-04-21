#include <math.h>
#include <xutility>
#include "PFRadialPotentialField.h"

PFRadialPotentialField::PFRadialPotentialField()
	:PFPotentialField()
{
	_potential = 1;
	_gradation = 1;
	updateRadius();
}

PFRadialPotentialField::~PFRadialPotentialField()
{

}

int PFRadialPotentialField::GetLocalPotential( int local_x, int local_y )
{
	int distance = abs(local_x) + abs(local_y);
	if (distance > _radius) return 0;

	if (type < 0) return std::min(0, type * (_potential - _gradation * distance) );
	return std::max(0, type * (_potential - _gradation * distance) );
}

inline void PFRadialPotentialField::updateRadius()
{
	_radius = ceil(float(_potential / _gradation)) - 1;
}
