/********************************************************************
	created:	2015/04/24
	created:	24:4:2015   11:41
	filename: 	E:\UnknownHero\Classes\Game\GridPosArea.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	GridPosArea
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef GridPosArea_h__
#define GridPosArea_h__

#include <vector>
#include "GridPos.h"
#include "GridSceneMap.h"

class GridPosArea
{
public:
	static GridPosArea*	Create(const GridPos& Pos,int w,int h,const GridSceneMap& GridMap);
	~GridPosArea(){}
	//
	const GridPos&	GetBaseGPos() {return BaseGPos;}
	const std::vector<GridPos>&	GetArea() {return GPosArea;}
	//
	int	 GetWidth(){return Width;}
	int	 GetHeight(){return Height;}
	//
	virtual void Init(const GridPos& Pos,int w,int h,const GridSceneMap& GridMap);
protected:
	GridPosArea();
	GridPos		BaseGPos;
	int			Width;
	int			Height;
	//
	std::vector<GridPos>	GPosArea;
private:
};

#endif // GridPosArea_h__
