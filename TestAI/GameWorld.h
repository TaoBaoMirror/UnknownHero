#ifndef GameWorld_h__
#define GameWorld_h__

#include "GridSceneMap.h"
#include "GeomorphologyCreater.h"
#include <map>
#include <vector>

#include "GameInfluenceMap.h"

class MapNodeData;

class GameWorld
{
public:
	static	GameWorld* Instance()
	{
		if(instance == NULL) instance = new GameWorld();
		return instance;
	}
	~GameWorld();
	//
	virtual void Init();
	virtual void CreateWorld();
	void	ReleaseNodeDatas();
	void	Release();
	//
	bool SaveWorld(const char* fileName);
	bool LoadWorld(const char* fileName);
	//
	void Update();
	void Render();
	//
	const GridSceneMap& GetSceneMap() const {return mWorld;} 
	GridSceneMap& GetSceneMap(){return mWorld;} 
	GameInfluenceMap& GetGameInfluenceMap(){return mIM;}
	const GameInfluenceMap& GetGameInfluenceMap()const {return mIM;}
	bool  CheckCanArrived(const GridPos& A,const GridPos& B,std::list<GridPos>* GPosListPtr = NULL);
	//
protected:
	void randomCreateMap();
	void deploySoldier();
protected:
	GameWorld();
	GridSceneMap	mWorld;
	GameInfluenceMap	mIM;
	bool			m_bEnable;
	static	GameWorld* instance;			
	//这是MapNodeData是现实数据和网格结构结合的桥梁，网格ExtreInfo的东西void*
	std::vector<MapNodeData>	MapNodeDataList;
	//特殊点的GPos
	std::map<GeomorphologyKeyIndex,std::vector<int> >		SpecialKeyNodeIDMap;
public:
	bool GetSpecialGPos(GeomorphologyKeyIndex key,std::vector<GridPos>& GPosList);
private:
};

#endif // GameWorld_h__
