#include "GridPosArea.h"
GridPosArea* GridPosArea::Create( const GridPos& Pos,int w,int h,const GridSceneMap& GridMap )
{
	GridPosArea* a = new GridPosArea();
	//
	a->Init(Pos,w,h,GridMap);
	//
	return a;

}

GridPosArea::GridPosArea():Width(0),Height(0)
{

}

void GridPosArea::Init( const GridPos& Pos,int w,int h,const GridSceneMap& GridMap )
{
	BaseGPos = Pos;
	Width = w;
	Height = h;
	//a->pGridMap = GridMap;
	//
	GPosArea.reserve(w*h);
	//
	for (int x = Pos.X;x< Pos.X + w;++x)
	{
		for (int y = Pos.Y;y< Pos.Y + h;++y)
		{
			int i = -1;
			GridMap.GridPosToIndex(GridPos(x,y),i);
			if (i != -1)
			{
				GPosArea.push_back(GridPos(x,y));
			}
		}
	}
}
