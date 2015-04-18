/********************************************************************
	created:	2015/01/17
	created:	17:1:2015   11:20
	filename: 	E:\cyvasse\TestAI\PlayerControllor.h
	file path:	E:\cyvasse\TestAI
	file base:	PlayerControllor
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef PlayerControllor_h__
#define PlayerControllor_h__
#include "Soldier.h"
class PlayerControllor
{
public:
	static PlayerControllor*	Instance()
	{
		static PlayerControllor instance;
		return &instance;
	}
	~PlayerControllor();
	//
public: 
	void Init(int camp);
	void Update();
	//
	void ResetMousePos(POINT& pos);
	void Pick();
	void ReleasePicked();
	void PickedPlayerSoldier();
	Soldier*  PickSoldier(const Vector2D& worldPos);
	Soldier*  GetProxySoldier(){return mProxySoldier;}
	//
protected:
	PlayerControllor();
	Soldier*	mProxySoldier;
	Soldier*	mLastSoldier;
	int			mProxyCamp;
private:
};


#endif // PlayerControllor_h__
