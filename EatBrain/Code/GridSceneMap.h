#ifndef GridSceneMap_h__
#define GridSceneMap_h__


#include "Graph/SparseGraph.h"
#include "Graph/GraphEdgeTypes.h"
#include "Graph/GraphNodeTypes.h"

#include "GridPos.h"
#include "AITypeDef.h"
#include "Vector2D.h"


class GridSceneMap
{
public: 

	enum MapType
	{
		Quat, Oct
	};

	typedef SparseGraph<NavGraphNode<void*>,GraphEdge>	NavGraph;
private:

	MapType m_eMapType;

public:
	GridSceneMap();
	~GridSceneMap();
	//
	void Init(int WorldWidth,int WorldHeight,int tileWidth,int tileHeight , Vector2D& BaseLTPos);
	bool Load(std::ifstream& in);
	bool Save(std::ofstream& out);
	int GetTileWidth()const {return TileWidth;}                        
	int GetTileHeight()const {return TileHeight;}

	int GetSizeNumX()const {return SizeNumX;}							           
	int GetSizeNumY()const {return SizeNumY;}						
	//
	void CreateMap(MapType map_type);
	//
	void FillFourNodes(int index);
	void FillOctNodes(int index);
	//
	int NodesCount() const;
	//
	NavGraph&	GMap() const {return *MapGraph;}
	//
	void  GetGridPos(int index,GridPos& out_GPos) const;
	void  GetIndex(const GridPos& GPos,int&	out_index) const;
	void  IndexToGridPos(int index,GridPos& out_GPos) const { GetGridPos(index,out_GPos); }
	void  GridPosToIndex(const GridPos& GPos,int&	out_index) const { GetIndex(GPos,out_index); }
	void  GridPosToWorldPos(const GridPos& GPos,Vector2D& out_Pos) const;
	void  WorldPosToGridPos(const Vector2D& WPos,GridPos& out_Pos) const;
	void  WorldPosToIndex(const Vector2D& WPos,int& out_index) const;
	void  GetNearestGridPos(const Vector2D& worldPos,GridPos& out_GPos) const;
	//
	NavGraphNode<void*>&	GetNode(int index) const {return MapGraph->GetNode(index);}
	NavGraphNode<void*>&	GetNode(const GridPos& GPos) const ;

	//
	void GetRandomNodeLocation(GridPos& out_GPos) const;
public: 
	void    FindTilesInQuad(const GridPos& GPos,int length,std::vector<GridPos>& out_NodeIndexes) const;
	void	FindTilesInV(const GridPos& GPos,int length,std::vector<GridPos>& out_NodeIndexes) const;
	void	FindTilesInH(const GridPos& GPos,int length,std::vector<GridPos>& out_NodeIndexes) const;
	void    FindTilesInCross(const GridPos& GPos,int V_length,int H_length,std::vector<GridPos>& out_NodeIndexes) const;
	void    FindTilesInCircle(std::vector<GridPos>& out_NodeIndexes,const GridPos& GPos,int maxRange, int minRange = 0) const;
	//////////////////////////////////////////////////////////////////////////
	static int GetRound(float iValue, int iBase);


protected:

	NavGraph*	MapGraph;
	
	Vector2D	BaseLT_Pos;

	int TileWidth;                        //横着格子的间隔，既是 一个格子的宽度                                    
	int TileHeight;                       //行间距格子的间隔，既是 一个格子的高度      

	int SizeNumX;							//第一行点的个数           
	int SizeNumY;							//总共有多少行 

	int nWorldWidth;
	int nWorldHeight;

	std::string SceneFileName;

protected:
	std::vector< std::vector<Vector2D> >	TilesByDistance;
	void initTilesByDistance(int max);
	void findTilesInAnnulus(std::vector<GridPos>& out_NodeIndexes,const GridPos& GPos, int minRange, int maxRange) const;
	class csort  
	{  
	public:  
		bool operator () (Vector2D& a,Vector2D& b) const  
		{  
			auto al = a.LengthSq();
			auto bl = b.LengthSq();
			if (al != bl) return al >= bl;
			if (a.x != b.x) return a.x >= b.x;
			if (a.y != b.y) return a.y >= b.y;
			return false;
		};  
	};  

private:

	void floodFillScanLineWithStack(MapType map_type,int grid_x, int grid_y,NavGraph& GridMap);
};

#endif // GridSceneMap_h__
