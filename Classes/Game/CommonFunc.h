/********************************************************************
	created:	2015/01/29
	created:	29:1:2015   17:38
	filename: 	E:\cyvasse\TestAI\CommonFunc.h
	file path:	E:\cyvasse\TestAI
	file base:	CommonFunc
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef CommonFunc_h__
#define CommonFunc_h__

#include "GridSceneMap.h"

const GridSceneMap& G_GetSceneMap();

class AttackData;
class CommonFunc
{
public:
	static void CalcDamage( const AttackData* atkData );
};


#endif // CommonFunc_h__
