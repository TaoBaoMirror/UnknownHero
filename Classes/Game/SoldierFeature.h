/********************************************************************
	created:	2015/03/15
	created:	15:3:2015   14:39
	filename: 	E:\cyvasse\TestAI\SoldierFeature.h
	file path:	E:\cyvasse\TestAI
	file base:	SoldierFeature
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef SoldierFeature_h__
#define SoldierFeature_h__

class Soldier;

class SoldierFeature
{
public:
	static double Health(Soldier* pBot);
	static double TotalAttackStrength(Soldier* pBot);

	
};

#endif // SoldierFeature_h__
