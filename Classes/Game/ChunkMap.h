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
#include "MapRule.h"


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
class Actor;

class ChunkMap : public cocos2d::TMXTiledMap
{
public: 
	static Actor*	InstantiateCreature(const std::string& CreatureType,const int TableID,const int DirectionType,const GridPos& GPos);
public:
	ChunkMap();
	~ChunkMap();
	//
	bool	InitChunkMap(std::string tmxFile);
	virtual void OnAfterInit();
	void	Reset();
	//


	GridSceneMap&	GetGridSceneMap() { return mGridMap;}
	const GridSceneMap&	GetGridSceneMap() const { return mGridMap;}
	GameInfluenceMap&	GetGameInfluenceMap() { return mIM;}
	const GameInfluenceMap&	GetGameInfluenceMap() const{ return mIM;}
	CreatureSpawnArea* GetSpawnArea(int AreaID);

	cocos2d::TMXLayer* GetCreatureTMXLayer();
	cocos2d::Layer* GetCreatureLayer();
	cocos2d::Layer* GetEffectLayer();
	cocos2d::Layer* GetTriggerLayer();
	
	cocos2d::TMXLayer* GetRangeLayer();


	bool  CheckCanArrived(Soldier* who ,const GridPos& A,const GridPos& B,std::list<GridPos>* GPosListPtr = NULL);
	// һЩ��д�ĺ���
	void update(float delta) override;
	//
	void FreeChunkData();
	void DeployCreature();
	//
	void onEnter() override;

	void ShowRangeData(const std::vector<GridPos>&	AttackGPosList);

	void HideRangeData();

	//
	void FindSoldiersInRange(const GridPos& CenterGPos , int RangeSize , int RType ,std::vector<Soldier*>&	out_SoldierList);
	// add by Hitman [5/21/2015]
	bool GridPosToTiledGridPos(const GridPos& GPos,cocos2d::Vec2& out_TPos);
	bool TiledGridPosToGridPos(const cocos2d::Vec2& TPos,GridPos& out_GPos);

	//
	MapRuleSystem&	GetMapRuleSys(){return mMapRuleSys;}

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
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

	//
	MapRuleSystem		mMapRuleSys;

private:
public:
	void	DebugRender();
	void	SetEnableDebugDraw(bool enableDraw);
	cocos2d::DrawNode*	pDebugDrawNode;
	bool	EnableDebugDraw;
	cocos2d::TTFConfig ttfConfig;

	cocos2d::EventListenerTouchOneByOne* _touchListener;
	cocos2d::EventListenerKeyboard* _keyboardListener;
};

#endif // ChunkMap_h__
