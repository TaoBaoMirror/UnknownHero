/********************************************************************
	created:	2015/07/08
	created:	8:7:2015   10:24
	filename: 	E:\UnknownHero\Classes\Game\StaticCreature.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	StaticCreature
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef StaticCreature_h__
#define StaticCreature_h__

#include "CreatureBase.h"
#include "Soldier.h"

class StaticCreature : public Soldier
{
public:
	StaticCreature();
	~StaticCreature();
	//
	virtual void GetHurt(const DamageData& damageData) override;
protected:
	
private:
};
#endif // StaticCreature_h__
