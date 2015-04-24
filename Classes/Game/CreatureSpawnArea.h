/********************************************************************
	created:	2015/04/24
	created:	24:4:2015   15:58
	filename: 	E:\UnknownHero\Classes\Game\CreatureSpawnArea.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	CreatureSpawnArea
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef CreatureSpawnArea_h__
#define CreatureSpawnArea_h__

#include "GridPosArea.h"
#include "ChunkMap.h"
#define  SPAWN_ACTION 1
class CreatureSpawnArea:public GridPosArea,public cocos2d::CCNode
{
public:
	CreatureSpawnArea();
	//
	bool Init(int CreatureType , float TimeGap , const GridPos& Pos,int w,int h,ChunkMap& Chunk);
	//
	void RegisterCreatureType(int CType);
	void UnregisterCreatureType(int CType);
	//
	void StartSpawn();
	void PauseSpawn();
	void StopSpawn();
	virtual void OnBegineSpawn();
	virtual void OnEndSpawn();
	void OnSpawn();
	virtual void ExecuteSpawn();


	virtual void update(float dt) override;

	//
protected:
	std::vector<int>		CreateTypes;
	float					fTimeGap;
private:
};
#endif // CreatureSpawnArea_h__
