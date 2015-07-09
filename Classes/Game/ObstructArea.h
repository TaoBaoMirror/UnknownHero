/********************************************************************
	created:	2015/07/09
	created:	9:7:2015   17:12
	filename: 	E:\UnknownHero\Classes\Game\ObstructArea.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	ObstructArea
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef ObstructArea_h__
#define ObstructArea_h__

#include "GridPosArea.h"

class ObstructArea : public GridPosArea
{
public:
	ObstructArea();
	//
	void SetObstruct(int GPosAreaIndex);
	void ClearObstruct(int GPosAreaIndex);
	//
	void EnableObstruct(bool b);
};

#endif // ObstructArea_h__
