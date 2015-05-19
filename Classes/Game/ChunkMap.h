/********************************************************************
	created:	2015/04/18
	created:	18:4:2015   16:21
	filename: 	E:\UnknownHero\Classes\Map\ChunkMap.h
	file path:	E:\UnknownHero\Classes\Map
	file base:	ChunkMap
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef ChunkMap_h__
#define ChunkMap_h__

#include "cocos2d.h"
#include "GridSceneMap.h"
#include "GameInfluenceMap.h"
#include "MapNodeData.h"


/*
	��ͼ�����Ƿֲ�ģ����ﵥ���������ݲ�

	1��ͨ��Tiled��ͼ��ȥˢ���ݣ���һ����ɫ��ȥˢ�ر������磬��ɫ��tile��ζ����GridMap���нڵ㣬
	�ǿ��������򣬺�ɫ��û�нڵ�ġ�Ȼ��������ɫ����ˢ �ر�ڵ�ļ�ֵ
	2����ͼ�����Obj ͨ��Obj��ȥ���ã�Ȼ���ڣ�Soldier���ɵ�ʱ��ȥ������������~
	3��Ҳ����һ��Obj���˶��켣�㣬��������һЩ���صĹ켣������Ѳ�߱��Ĺ켣
	���ChunkMap������һֱ���ڵģ�Ȼ��ͨ��initȥ�任Map�е����ݣ�Ȼ��MapManager���ʵ��ȥ�õ���ǰ
	��ChunkMap��Ȼ���������ͨ����������ȥ���ʵ�ǰ�����ChunkMap�����ݲ���





*/
class CreatureSpawnArea;

class TMXLayer;

class ChunkMap : public cocos2d::TMXTiledMap
{
public:
	ChunkMap();
	~ChunkMap();
	//
	bool	InitChunkMap(std::string tmxFile);
	virtual void OnAfterInit();
	void	Reset();
	//
	Soldier*	InstantiateCreature(const int CreatureID,const GridPos& GPos,const int DirectionType);


	GridSceneMap&	GetGridSceneMap() { return mGridMap;}
	const GridSceneMap&	GetGridSceneMap() const { return mGridMap;}
	GameInfluenceMap&	GetGameInfluenceMap() { return mIM;}
	const GameInfluenceMap&	GetGameInfluenceMap() const{ return mIM;}
	CreatureSpawnArea* GetSpawnArea(int AreaID);

	cocos2d::TMXLayer* GetCreatureTMXLayer();
	cocos2d::Layer* GetCreatureLayer();


	bool  CheckCanArrived(const GridPos& A,const GridPos& B,std::list<GridPos>* GPosListPtr = NULL);
	// һЩ��д�ĺ���
	void update(float delta) override;
	//
	void FreeChunkData();
	void DeployCreature();
	//
	void onEnter() override;


	//
	void FindSoldiersInRange(const GridPos& CenterGPos , int RangeSize , int RType ,std::vector<Soldier*>&	out_SoldierList);

	
protected:
	GridSceneMap		mGridMap;
	GameInfluenceMap	mIM;
	//��ͼ�����������Ϣ
	std::vector<MapNodeData>			MapNodeDataList;
	//����ȥ����Area
	//������ֻ�Ǳ���ָ�룬���е��ã�������Ref++������û��ʹ��cocos2d::Vector Map
	std::map<int,CreatureSpawnArea*>	SpawnAreaList;	
	//�Ƿ��Ѿ�����
	bool	bLoaded;

private:
public:
	void	DebugRender();
	void	SetEnableDebugDraw(bool enableDraw);
	cocos2d::DrawNode*	pDebugDrawNode;
	bool	EnableDebugDraw;
	cocos2d::TTFConfig ttfConfig;
};

#endif // ChunkMap_h__
