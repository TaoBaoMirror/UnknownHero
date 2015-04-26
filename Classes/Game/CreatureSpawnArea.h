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
	//����ID�����������࣬ʱ������Area��λ�ã����ߣ�chunk
	bool Init(int AreaID,int CreatureType , float TimeGap , const GridPos& Pos,int w,int h,ChunkMap* Chunk);
	int	 GetAreaID() {return nAreaID;}
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
