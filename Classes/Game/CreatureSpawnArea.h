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

#include "cocos2d.h"
#include "GridPosArea.h"

#define  SPAWN_ACTION 1

class ChunkMap;
class CreatureSpawnArea:public GridPosArea,public cocos2d::CCNode
{
public:
	CreatureSpawnArea();
	//区域ID，生物体种类，时间间隔，Area的位置，宽，高，chunk
	bool Init(int AreaID,int CreatureType , float TimeGap , const GridPos& Pos,int w,int h,ChunkMap* Chunk);
	int	 GetAreaID() {return nAreaID;}
	//注册一个生物体种类
	void RegisterCreatureType(int CType);
	void UnregisterCreatureType(int CType);
	//开始产生
	void StartSpawn();
	//暂停
	void PauseSpawn();
	//恢复
	void ResumeSpawn();
	//停止产生
	void StopSpawn();
	//开始产卵的
	virtual void OnBegineSpawn();
	//结束产卵
	virtual void OnEndSpawn();
	//执行产卵
	virtual void ExecuteSpawn();

	virtual void update(float dt) override;

	int		GetRandomCreatureID();
	GridPos	GetRandomGPos();

	virtual bool IsSpawnGPosLegit(const GridPos& GPos);
protected:
	std::vector<int>		CreateTypes;
	const ChunkMap*			pChunkMap;
	//
	float					fTimeGap;
	int						nAreaID;				

public:
	void OnSpawn();

	static int	ParseCreatureIDs(const std::string& szParam,std::vector<int>& szVec);

private:
};
#endif // CreatureSpawnArea_h__
