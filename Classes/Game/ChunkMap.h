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

	// add by Hitman [6/30/2015]
	MapWorld����֯��chunk��һ���Թ���MapWorld����MapManager�����е�һ��ʵ��.Ҳֻ��һ��
	chunk���� �ŵĳ���ȥ���� �������� 24��
	chunk��init��ʱ�򣬲���Ҫ�ڲ���hero����Ϊ��Ҫͨ����λ��ȥ����hero��ͨ��chunkFrom �� chunkTo��λ�ã��õ� �����뵽
	chunkTo�ķ�����ŵ�λ��.Ȼ�� hero��DeployHero�ӿ� ���е���.
	chunk��init��ʱ��,trigger������ʲô�ļ����Ǹ��ݵ�ǰ�������chunk�ķ���������ص�.
	���chunk�Ѿ����ʹ�,��,trigger��ָ�붼����triggerManager����.
	���chunkû�б����ʹ�,��,�����µ�trigger��chunk.
	triggerManager�Ƕ���������Ե�.�ڵ�һ�ν��������ʱ��.���manager
	//
	����
	-----
	��������
	1��CreateWorld ������������
	2��DeployChunkMapToWorld �������ɵ��Թ�ȥ����chunk����Դ����ʼ��chunksaveData��ص�����
	3��EnterWorld ��������
	4���ҵ����chunk��LoadChunk
	5������Hero��chunk���� DeployHero
	------
	�л�chunk
	1��OldChunk ִ�� UndeployHero ��Ӣ�۴�chunk������
	2��ͨ���ŵ�λ�ã��õ�Oldchunk����һ��NextChunk��Maze�е�ResID
	3��LoadChunk
	4���õ�NextChunk����Ӧ��door��λ�� Ȼ�� DeployHero

	@��ʾ  ��LoadChunk��ʱ���ڲ���InitChunk����InitChunk��ʱ�� Ӧ��ͨ��MapManager��MapWorld��¼����Ϣ�����У�������ļ���
	���磬�����Ƿ��������chunk�������ȥ��֪���Ƿ�Ӧ�ü��� trigger�ȡ�������InitChunkMap��ʱ�� ������hero





*/
class CreatureSpawnArea;

class TMXLayer;
class Actor;

enum ChunkMapFlag
{
	unexplored = 0,explored = 1,staying = 2
};

struct ChunkSaveDataInWorld
{
	ChunkSaveDataInWorld():ChunkResIndex(0),ChunkState(unexplored)
	{

	}
	int ChunkResIndex;
	int	ChunkState;
};

class ChunkMap : public cocos2d::TMXTiledMap
{
public: 
	static int StringToDir(const std::string& c);
	static Actor*	InstantiateCreature(const std::string& CreatureType,const int TableID,const int DirectionType,const GridPos& GPos);
public:
	ChunkMap();
	~ChunkMap();
	//
	bool	InitChunkMap(std::string tmxFile);
	virtual void OnAfterInit();
	void	Reset();
	//
	void	Explored(){ mChunkFlag |= explored;}
	void	Staying(){mChunkFlag |= staying;}
	void    Leave(){mChunkFlag |= ~staying;}
	bool    IsExplored(){return (mChunkFlag & explored) > 0;}
	bool	IsStaying(){return (mChunkFlag & staying) > 0;}
	void	SetChunkSaveDataInWorld(ChunkSaveDataInWorld& data);
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
	void DeployHero(const GridPos& GPos);
	void UndeployHero();
	void DeployActor(Actor* pActor , const GridPos& GPos);
	//
	void onEnter() override;

	void ShowRangeData(const std::vector<GridPos>&	AttackGPosList);

	void HideRangeData();

	//
	Soldier* FindSoldierAtGPos(const GridPos& CenterGPos);
	void FindSoldiersInRange(const GridPos& CenterGPos , int RangeSize , int RType ,std::vector<Soldier*>&	out_SoldierList);
	// add by Hitman [5/21/2015]
	bool GridPosToTiledGridPos(const GridPos& GPos,cocos2d::Vec2& out_TPos);
	bool TiledGridPosToGridPos(const cocos2d::Vec2& TPos,GridPos& out_GPos);

	//
	MapRuleSystem&	GetMapRuleSys(){return mMapRuleSys;}

	void	SetInMazeGPos(const GridPos& GPos){mMazeGPos = GPos;}
	const GridPos& GetInMazeGPos() const {return mMazeGPos;}
	bool  GetDoorGPos(int dir,GridPos& out_GPos);

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
	int		mChunkFlag;
	std::map<int,GridPos>	mDoorGPosList;
	//
	MapRuleSystem		mMapRuleSys;
	//��ǰchunk�������Թ��е�λ��
	GridPos				mMazeGPos;
	//
	void	OnHeroEnter();
	void	OnHeroLeave();

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


//////////////////////////////////////////////////////////////////////////
enum 
{
	block = 0,
	topdoor = 1,
	leftdoor = 2,
	downdoor = 4,
	rightdoor = 8,
	//
	transportdoor = 16,
	playerborndoor = 32,
	//
	visited = 0x100,
	frontier = 0x200,



};

class MapWorld
{
public:
	MapWorld();
	~MapWorld();
	//
	void	Init();
	//
	void	SetWorldSize(int w,int l);
	//
	bool	CreateMaze();
	//
	const std::vector< std::vector<int> >& GetMaze(){return mMaze;}
	//
	void    DeployChunkMapToWorld();
	//����һ��chunk
	bool	LoadChunk(ChunkMap* chunk , const GridPos& mazePos);
	bool	GetMazePos(const GridPos& basePos,int dir,GridPos& outGPos);
	void	OnEnterWorld();
	void	OnLeaveWorld();
	int		opposite(int dir);

	//
	std::string	GetChunkMapPath(int chunkResIndex,const GridPos& mazePos,const std::vector< std::vector<int> >& Maze);
	ChunkSaveDataInWorld&	GetChunkSaveDataInWorld(const GridPos& mazePos);
	int		GetDir(int MazeX,int MazeY,const std::vector< std::vector<int> >& Maze);
protected:
	void	addFrontier(int x,int y);
	void	mark(int x,int y);
	void	neighbors(int x,int y,std::vector<GridPos>& out_neighbors);
	int		direction(int fx,int fy,int tx,int ty);
	bool	breakCondition();
protected:
	int		mWorldID;
	static  int  sNextWorldID;
	int		mWorldWidth;
	int		mWorldLength;





	//
	std::vector< std::vector<int> >		mMaze;
	std::vector<GridPos>				mFrontier;
	//���int Ҫȥ mChunkMapPathDict ����� Vector����ȥѰ��
	std::vector< std::vector<ChunkSaveDataInWorld> >		mChunkSaveDataInWorldMaze;
	//
	int		mCurChunkNumCounter;
	//
	std::map< int , std::vector<std::string> >	mChunkMapPathDict;
public:
	//���chunkGPos
	GridPos	mEntranceChunkInMazeGPos;
	//����chunk
	GridPos	mSpecialChunkInMazeGPos;
	//����chunk
	GridPos	mHideChunkInMazeGPos;
	//boss chunk
	GridPos	mBossChunkInMazeGPos;
};

#endif // ChunkMap_h__
