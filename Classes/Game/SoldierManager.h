#ifndef SoldierManager_h__
#define SoldierManager_h__

#include <map>
#include "GridPos.h"
class Soldier;

class SoldierManager
{
public:
	static SoldierManager* Instance()
	{
		if(instance == NULL) instance = new SoldierManager();
		return instance;
	}
	~SoldierManager();
	//
	void Init();
	void Release();
	void ReleaseAllSoldier();
	//
	bool RegisterSoldier(Soldier* soldier);
	bool UnregisterSoldier(Soldier* soldier);
	bool UnregisterSoldier(int id);
	Soldier*	GetSoldier(int id);
	Soldier*	GetSoldier(const GridPos& GPos);

	//
	void Update();
	void Render();
	//

protected:
	SoldierManager();
	static SoldierManager*	instance;
	std::map<int,Soldier*>		SoldierDict;
private:
};
#endif // SoldierManager_h__
