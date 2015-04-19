/********************************************************************
	created:	2015/03/17
	created:	17:3:2015   12:39
	filename: 	E:\cyvasse\TestAI\GameInfluenceMap.h
	file path:	E:\cyvasse\TestAI
	file base:	GameInfluenceMap
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef GameInfluenceMap_h__
#define GameInfluenceMap_h__

#include "InfluenceMap.h"
class SoldierPF;
class GameInfluenceMap:public InfluenceMap
{
public:
	void Update();
	//
	void Render(){}
protected:
	void updateSoldierPF(SoldierPF* S_PF , bool ExceptSelf = true);
};

#endif // GameInfluenceMap_h__
