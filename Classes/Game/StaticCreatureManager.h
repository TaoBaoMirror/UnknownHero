/********************************************************************
	created:	2015/07/08
	created:	8:7:2015   15:00
	filename: 	E:\UnknownHero\Classes\Game\StaticCreatureManager.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	StaticCreatureManager
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef StaticCreatureManager_h__
#define StaticCreatureManager_h__

#include "StaticCreature.h"

class StaticCreatureManager
{
public:
	static StaticCreatureManager*	GetInstance()
	{
		static StaticCreatureManager T;
		return &T;
	}
	~StaticCreatureManager();
	//////////////////////////////////////////////////////////////////////////
	void Init();
	void ReleaseAll();

protected:
	StaticCreatureManager();

private:
};

#endif // StaticCreatureManager_h__
