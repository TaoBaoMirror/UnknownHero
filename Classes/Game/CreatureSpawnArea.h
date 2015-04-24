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
	//���������࣬ʱ������Area��λ�ã����ߣ�chunk
	bool Init(int CreatureType , float TimeGap , const GridPos& Pos,int w,int h,ChunkMap& Chunk);
	//ע��һ������������
	void RegisterCreatureType(int CType);
	void UnregisterCreatureType(int CType);
	//��ʼ����
	void StartSpawn();
	//��ͣ
	void PauseSpawn();
	//�ָ�
	void ResumeSpawn();
	//ֹͣ����
	void StopSpawn();
	//��ʼ���ѵ�
	virtual void OnBegineSpawn();
	//��������
	virtual void OnEndSpawn();
	//ִ�в���
	virtual void ExecuteSpawn();

	virtual void update(float dt) override;

	int		GetRandomCreatureID();
	GridPos	GetRandomGPos();
protected:
	std::vector<int>		CreateTypes;
	float					fTimeGap;
public:
	void OnSpawn();

private:
};
#endif // CreatureSpawnArea_h__
