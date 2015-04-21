#include "GridPos.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const GridPos& rhs)
{
	os << " " << rhs.X << " " << rhs.Y;

	return os;
}


std::ifstream& operator>>(std::ifstream& is, GridPos& lhs)
{
	is >> lhs.X >> lhs.Y;

	return is;
}