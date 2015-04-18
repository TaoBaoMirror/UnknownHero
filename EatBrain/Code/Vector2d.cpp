#include "stdafx.h"
#include "Vector2D.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Vector2D& rhs)
{
  os << "PosX: " << rhs.x << " PosY: " << rhs.y;

  return os;
}

  
std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs)
{
  char buff[32];

  is >> buff >> lhs.x >> buff >> lhs.y;

  return is;
}

