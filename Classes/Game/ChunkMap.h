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
	地图首先是分层的，这里单另着重数据层

	1、通过Tiled的图层去刷数据，用一个颜色层去刷地表网格，如，白色的tile意味着在GridMap上有节点，
	是可行走区域，黑色是没有节点的。然后其他颜色用来刷 地表节点的价值
	2、地图上面的Obj 通过Obj层去放置，然后在，Soldier生成的时候，去吸附在网格上~
	3、也许还有一个Obj的运动轨迹层，用来布置一些机关的轨迹，或者巡逻兵的轨迹

	这个ChunkMap可以是一直存在的，然后通过init去变换Map中的内容，然后MapManager这个实力去得到当前
	的ChunkMap，然后其他组件通过‘单件’去访问当前的这个ChunkMap的数据部分

	// add by Hitman [6/30/2015]
	MapWorld是组织起chunk的一个迷宫，MapWorld是在MapManager单件中的一个实例.也只有一个
	chunk根据 门的朝向去分类 上下左右 24种
	chunk在init的时候，不需要在部署hero，因为，要通过门位置去部署hero，通过chunkFrom 和 chunkTo的位置，得到 ，进入到
	chunkTo的方向的门的位置.然后 hero在DeployHero接口 进行调用.
	chunk在init的时候,trigger和箱子什么的加载是根据当前世界的中chunk的访问情况加载的.
	如果chunk已经访问过,则,trigger的指针都还在triggerManager里面.
	如果chunk没有被访问过,则,加载新的trigger到chunk.
	triggerManager是对于世界而言的.在第一次进入世界的时候.清空manager
	//
	流程
	-----
	进入世界
	1】CreateWorld 建立整个世界
	2】DeployChunkMapToWorld 根据生成的迷宫去部署chunk的资源，初始化chunksaveData相关的内容
	3】EnterWorld 进入世界
	4】找到入口chunk，LoadChunk
	5】部署Hero到chunk里面 DeployHero
	------
	切换chunk
	1】OldChunk 执行 UndeployHero 让英雄从chunk中脱离
	2】通过门的位置，得到Oldchunk的下一个NextChunk在Maze中的ResID
	3】LoadChunk
	4】得到NextChunk的相应的door的位置 然后 DeployHero

	@提示  在LoadChunk的时候，内部会InitChunk，在InitChunk的时候 应该通过MapManager的MapWorld记录的信息，进行，有条理的加载
	比如，根据是否进入过这个chunk的情况，去得知，是否应该加载 trigger等。而且在InitChunkMap的时候 不部署hero





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
	// 一些重写的函数
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
	//地图里面的数据信息
	std::vector<MapNodeData>			MapNodeDataList;
	//这里去管理Area
	//这里是只是保存指针，进行调用，而不想Ref++，所以没有使用cocos2d::Vector Map
	std::map<int,CreatureSpawnArea*>	SpawnAreaList;	
	//是否已经载入
	bool	bLoaded;
	int		mChunkFlag;
	std::map<int,GridPos>	mDoorGPosList;
	//
	MapRuleSystem		mMapRuleSys;
	//当前chunk在世界迷宫中的位置
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
	//加载一个chunk
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
	//这个int 要去 mChunkMapPathDict 里面的 Vector里面去寻找
	std::vector< std::vector<ChunkSaveDataInWorld> >		mChunkSaveDataInWorldMaze;
	//
	int		mCurChunkNumCounter;
	//
	std::map< int , std::vector<std::string> >	mChunkMapPathDict;
public:
	//入口chunkGPos
	GridPos	mEntranceChunkInMazeGPos;
	//特殊chunk
	GridPos	mSpecialChunkInMazeGPos;
	//隐藏chunk
	GridPos	mHideChunkInMazeGPos;
	//boss chunk
	GridPos	mBossChunkInMazeGPos;
};

#endif // ChunkMap_h__
