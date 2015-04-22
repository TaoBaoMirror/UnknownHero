/********************************************************************
	created:	2015/04/22
	created:	22:4:2015   21:18
	filename: 	E:\UnknownHero\Classes\Game\Debug\GizmoSoldier.h
	file path:	E:\UnknownHero\Classes\Game\Debug
	file base:	GizmoSoldier
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef GizmoSoldier_h__
#define GizmoSoldier_h__

#include "cocos2d.h"
#include "..\Soldier.h"

class GizmoSoldier : public cocos2d::Sprite ,public Soldier
{
public:
	GizmoSoldier();
	~GizmoSoldier();
	//
	static GizmoSoldier* create();
	virtual void Update() override;
	//
protected:
	
private:
};

#endif // GizmoSoldier_h__
