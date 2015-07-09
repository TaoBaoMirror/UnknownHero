/********************************************************************
	created:	2014/11/30
	created:	30:11:2014   12:04
	filename: 	E:\BunkerAI\BunkerAI\Code\GridPos.h
	file path:	E:\BunkerAI\BunkerAI\Code
	file base:	GridPos
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef GridPos_h__
#define GridPos_h__

#include <iosfwd>
#include <math.h>

class GridPos
{
public:
	GridPos()
	{
		X = Y = 0;
	}

	GridPos(const GridPos &point)
	{
		X = point.X;
		Y = point.Y;
	}

	GridPos(int x,int y)
	{
		X = x;
		Y = y;
	}

	void SetTo(int x,int y)
	{
		X = x;
		Y = y;
	}

	int Distance(const GridPos &point) const
	{
		return abs(point.X - X) +  abs(point.Y - Y);
	}

	GridPos operator+(const GridPos& point) const
	{
		return GridPos(X + point.X,
			Y + point.Y);
	}

	GridPos operator-(const GridPos& point) const
	{
		return GridPos(X - point.X,
			Y - point.Y);
	}

	GridPos operator*(float c) const
	{
		return GridPos(X*c,Y*c);
	}

	GridPos operator=(const GridPos& point)
	{
		if (&point != this)
		{
			this->X = point.X;
			this->Y = point.Y;
		}	
		return *this;
	}

	bool Equals(const GridPos& point) const
	{
		return (X == point.X) && (Y == point.Y);
	}

public:

	int X;
	int Y;
};

std::ostream& operator<<(std::ostream& os, const GridPos& rhs);
std::ifstream& operator>>(std::ifstream& is, GridPos& lhs);



#endif // GridPos_h__