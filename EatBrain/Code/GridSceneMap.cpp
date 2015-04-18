#include "stdafx.h"
#include "GridSceneMap.h"
#include <stack>
#include <math.h>
#include <algorithm>

GridSceneMap::GridSceneMap()
{
	MapGraph = 0;
}

GridSceneMap::~GridSceneMap()
{

}



void GridSceneMap::CreateMap( MapType map_type )
{
	if (MapGraph == 0) 
	{
		MapGraph = new NavGraph(false);
	}
	//从0开始
	int counter = 0;
	for (int i = 0; i < SizeNumY;++i )
	{
		for (int j = 0; j < SizeNumX; j++)
		{
			Vector2D Pos;
			Pos.x = BaseLT_Pos.x + TileWidth * j;
			Pos.y = BaseLT_Pos.y + TileHeight * i;
			//
			NavGraphNode<void*> Node;

			Node.SetIndex(counter++);
			Node.SetPos( Pos );
			MapGraph->AddNode(Node);
		}
	}
	//
	int beginIndex = 0;

	for (int i = 0 ;i< MapGraph->NumNodes();++i)
	{
		GraphNode& Node = MapGraph->GetNode(i);

		if (Node.Index() != invalid_node_index)
		{
			beginIndex = Node.Index();
			break;
		}
	}
	//
	m_eMapType = map_type;

	if (m_eMapType == MapType::Quat)
	{
		FillFourNodes(beginIndex);
	}
	else
	{
		FillOctNodes(beginIndex);
	}

	//
	initTilesByDistance(50);
}

void GridSceneMap::FillFourNodes( int index )
{
	floodFillScanLineWithStack(m_eMapType,0,0,GMap());
}

void GridSceneMap::FillOctNodes( int index )
{
	floodFillScanLineWithStack(m_eMapType,0,0,GMap());
}

//
void GridSceneMap::floodFillScanLineWithStack(MapType map_type,int grid_x, int grid_y,NavGraph& GridMap)  
{  
	typedef int GridIndex;

	std::stack<Vector2D>	stack;

	std::vector<bool>	Visited(GridMap.NumNodes(),false);
	
	stack.push(Vector2D(grid_x,grid_y));

	while(!stack.empty())  
	{      
		const Vector2D& gridPos = stack.top();

		stack.pop();

		int tmp_y = grid_y;

		while(tmp_y < SizeNumY)  
		{  
			Vector2D base(gridPos.x,tmp_y);

			GridIndex BaseIndex = base.y * SizeNumX + base.x;
			//
			//
			if (GridMap.GetNode(BaseIndex).Index() == invalid_node_index ||
				Visited[BaseIndex] == true)
			{
				tmp_y++;
				continue;
			}

			Visited[BaseIndex] = true;

			//
			GridIndex LIndex = -1;
			GridIndex RIndex = -1;
			GridIndex TIndex = -1;
			GridIndex BIndex = -1;
			GridIndex LTIndex = -1;
			GridIndex RTIndex = -1;
			GridIndex LBIndex = -1;
			GridIndex RBIndex = -1;

			if (base.x - 1 >= 0)
			{
				LIndex = base.y * SizeNumX + (base.x - 1);

				if (GridMap.GetNode(LIndex).Index() == invalid_node_index|| Visited[LIndex] == true)
				{
					LIndex = -1;
				}
				else
				{
					stack.push(Vector2D(base.x - 1,base.y));
				}
			}

			if (base.x + 1 < SizeNumX)
			{
				RIndex = base.y * SizeNumX + (base.x + 1);

				if (GridMap.GetNode(RIndex).Index() == invalid_node_index || Visited[RIndex] == true)
				{
					RIndex = -1;
				}
				else
				{
					stack.push(Vector2D(base.x + 1,base.y));
				}
			}

			if (base.y - 1 >= 0)
			{
				TIndex = (base.y - 1) * SizeNumX + base.x;

				if (GridMap.GetNode(TIndex).Index() == invalid_node_index|| Visited[TIndex] == true)
				{
					TIndex = -1;
				}
				else
				{
					stack.push(Vector2D(base.x,base.y-1));
				}
			}

			if (base.y + 1 < SizeNumY)
			{
				BIndex = (base.y + 1) * SizeNumX + base.x;

				if (GridMap.GetNode(BIndex).Index() == invalid_node_index|| Visited[BIndex] == true)
				{
					BIndex = -1;
				}
				else
				{
					stack.push(Vector2D(base.x,base.y+1));
				}
			}

			if (map_type == Oct)
			{
				if (base.x - 1 >= 0 && base.y - 1 >= 0)
				{
					LTIndex = (base.y - 1)* SizeNumX + (base.x - 1);

					if (GridMap.GetNode(LTIndex).Index() == invalid_node_index|| Visited[LTIndex] == true)
					{
						LTIndex = -1;
					}
					else
					{
						stack.push(Vector2D(base.x - 1,base.y-1));
					}

				}

				if (base.x + 1 < SizeNumX && base.y - 1 >= 0)
				{
					RTIndex = (base.y - 1)* SizeNumX + (base.x + 1);

					if (GridMap.GetNode(RTIndex).Index() == invalid_node_index|| Visited[RTIndex] == true)
					{
						RTIndex = -1;
					}
					else
					{
						stack.push(Vector2D(base.x + 1,base.y-1));
					}
				}

				if (base.x - 1 >= 0 && base.y + 1 < SizeNumY)
				{
					LBIndex = (base.y + 1)* SizeNumX + (base.x - 1);

					if (GridMap.GetNode(LBIndex).Index() == invalid_node_index|| Visited[LBIndex] == true)
					{
						LBIndex = -1;
					}
					else
					{
						stack.push(Vector2D(base.x - 1,base.y+1));
					}
				}

				if (base.x + 1 < SizeNumX && base.y + 1 < SizeNumY)
				{
					RBIndex = (base.y + 1)* SizeNumX + (base.x + 1);

					if (GridMap.GetNode(RBIndex).Index() == invalid_node_index|| Visited[RBIndex] == true)
					{
						RBIndex = -1;
					}
					else
					{
						stack.push(Vector2D(base.x + 1,base.y+1));
					}
				}
			}
			

			if (LIndex != -1) {GridMap.AddEdge(GraphEdge(BaseIndex,LIndex));}
			if (RIndex != -1) {GridMap.AddEdge(GraphEdge(BaseIndex,RIndex));}
			if (TIndex != -1) {GridMap.AddEdge(GraphEdge(BaseIndex,TIndex));}
			if (BIndex != -1) {GridMap.AddEdge(GraphEdge(BaseIndex,BIndex));}

			if (map_type == Oct)
			{
				if (LTIndex != -1) {GridMap.AddEdge(GraphEdge(BaseIndex,LTIndex));}
				if (RTIndex != -1) {GridMap.AddEdge(GraphEdge(BaseIndex,RTIndex));}
				if (LBIndex != -1) {GridMap.AddEdge(GraphEdge(BaseIndex,LBIndex));}
				if (RBIndex != -1) {GridMap.AddEdge(GraphEdge(BaseIndex,RBIndex));}
			}


			tmp_y++;  
		}  
	}  

}  

int GridSceneMap::NodesCount() const
{
	if(MapGraph)
	{
		return MapGraph->NumNodes();
	}
	else
	{
		return -1;
	}
}

int GridSceneMap::GetRound( float iValue, int iBase )
{
	int iFactor;
	float iMod;

	iFactor = (int)(iValue / iBase);
	iMod = iValue - iFactor*iBase;
	iFactor = (iMod * 2 > iBase) ? (iFactor + 1) : iFactor;
	int iRtn = iFactor * iBase;
	return iRtn;
}

void GridSceneMap::Init( int WorldWidth,int WorldHeight,int tileWidth,int tileHeight , Vector2D& BaseLTPos)
{
	TileWidth = tileWidth;                        //横着格子的间隔，既是 一个格子的宽度                                    
	TileHeight = tileHeight;                       //行间距格子的间隔，既是 一个格子的高度      


	nWorldWidth = WorldWidth;
	nWorldHeight = WorldHeight;



	SizeNumX = WorldWidth / TileWidth;							//第一行点的个数           
	SizeNumY = WorldHeight/TileHeight;							//总共有多少行 

	BaseLT_Pos = BaseLTPos;
}

bool GridSceneMap::Load( std::ifstream& in )
{
	//1 ParamLoad

	in >> BaseLT_Pos;
	in >> TileWidth;
	in >> TileHeight;
	in >> SizeNumX;
	in >> SizeNumY;
	in >> nWorldWidth;
	in >> nWorldHeight;

	//2 GraphLoad
	if (MapGraph == 0) 
	{
		MapGraph = new NavGraph(false);
	}

	return GMap().Load(in);

}

bool GridSceneMap::Save(  std::ofstream& out )
{
	//1 ParamSave
	out << BaseLT_Pos << std::endl;
	out << TileWidth << std::endl;
	out << TileHeight << std::endl;
	out << SizeNumX << std::endl;
	out << SizeNumY << std::endl;
	out << nWorldWidth << std::endl;
	out << nWorldHeight << std::endl;

	//2 GraphSave
	return GMap().Save(out);

	
}


void GridSceneMap::FindTilesInV( const GridPos& GPos,int length,std::vector<GridPos>& out_NodeIndexes ) const
{
	out_NodeIndexes.clear();
	out_NodeIndexes.reserve(length*2 + 1);
	out_NodeIndexes.push_back(GPos);
	for (int i = -length;i<=length;++i)
	{
		if(i == 0) continue;
		int newY = GPos.Y + i;
		if (newY >= 0 && newY< SizeNumY)
		{
			out_NodeIndexes.push_back(GridPos(GPos.X,newY));
		}
	}
}

void GridSceneMap::FindTilesInH( const GridPos& GPos,int length,std::vector<GridPos>& out_NodeIndexes ) const
{
	out_NodeIndexes.clear();
	out_NodeIndexes.reserve(length*2 + 1);
	out_NodeIndexes.push_back(GPos);

	for (int i = -length;i<=length;++i)
	{
		if(i == 0) continue;
		int newX = GPos.X + i;
		if (newX >= 0 && newX< SizeNumX)
		{
			out_NodeIndexes.push_back(GridPos(newX,GPos.Y));
		}
	}
}

void GridSceneMap::FindTilesInQuad( const GridPos& GPos,int length,std::vector<GridPos>& out_NodeIndexes ) const
{
	int x_upper = std::min(GPos.X + length,SizeNumX - 1);
	int x_lower = std::max(GPos.X - length,0);
	int y_upper = std::min(GPos.Y + length,SizeNumY - 1);
	int y_lower = std::max(GPos.Y - length,0);
	//
	out_NodeIndexes.clear();
	out_NodeIndexes.reserve((y_upper - y_lower + 1) * (x_upper - x_lower + 1));
	out_NodeIndexes.push_back(GPos);
	//
	for (int i = y_lower ; i <= y_upper ; ++i)
	{
		for (int k = x_lower ; k <= x_upper ; ++k)
		{
			if(i == 0 && k == 0) continue;
			//
			GridPos pos(k,i);
			//
			out_NodeIndexes.push_back(pos);
		}
	}

}

void GridSceneMap::FindTilesInCross( const GridPos& GPos,int V_length,int H_length,std::vector<GridPos>& out_NodeIndexes ) const
{
	std::vector<GridPos> NodeIndexes_V;
	std::vector<GridPos> NodeIndexes_H;
	NodeIndexes_V.reserve(V_length);
	NodeIndexes_H.reserve(H_length);
	out_NodeIndexes.clear();
	out_NodeIndexes.reserve(V_length * 2 + H_length * 2 + 1);
	//
	FindTilesInV(GPos,V_length,NodeIndexes_V);
	FindTilesInH(GPos,H_length,NodeIndexes_H);
	//
	out_NodeIndexes.push_back(GPos);
	for (int i = 1;i< NodeIndexes_V.size();++i)
	{
		out_NodeIndexes.push_back(NodeIndexes_V[i]);
	}
	for (int i = 1;i< NodeIndexes_H.size();++i)
	{
		out_NodeIndexes.push_back(NodeIndexes_H[i]);
	}
}

void GridSceneMap::initTilesByDistance(int max)
{
	TilesByDistance.resize(max+1,std::vector<Vector2D>());

	for (auto j = -max; j <= max; j++)
		for (auto i = -max; i <= max; i++)
			if (max * max >= i * i + j * j)
				TilesByDistance[(int)ceil(sqrtf(i * i + j * j))].push_back( Vector2D(i, j) );

	for (int i = 0 ; i<TilesByDistance.size();++i)
	{
		auto vecList = TilesByDistance[i];

		std::sort(TilesByDistance[i].begin(),TilesByDistance[i].end(),csort());
	}
}

void GridSceneMap::findTilesInAnnulus(std::vector<GridPos>& out_NodeIndexes,const GridPos& GPos, int minRange, int maxRange) const
{
	out_NodeIndexes.clear();

	if (maxRange < minRange) return;

	if (maxRange > TilesByDistance.size()) return;

	for (int i = minRange; i <= maxRange; i++)
	{
		for (int j = 0 ; j < TilesByDistance[i].size();++j)
		{
			auto offset = TilesByDistance[i][j];
			GridPos t(offset.x + GPos.X,offset.y + GPos.Y);
			if (t.X < SizeNumX && t.X >= 0 && t.Y < SizeNumY && t.Y >= 0)
			{
				out_NodeIndexes.push_back(t);
			}
		}
	}
}

void GridSceneMap::FindTilesInCircle(std::vector<GridPos>& out_NodeIndexes,const GridPos& GPos,int maxRange, int minRange) const
{
	findTilesInAnnulus(out_NodeIndexes,GPos, minRange, maxRange);
}

void GridSceneMap::GetGridPos( int index,GridPos& out_GPos ) const
{
	assert(index != -1);

	int y = index / SizeNumX;
	int x = index - y * SizeNumX;
	//
	out_GPos.SetTo(x,y);
}

void GridSceneMap::GetIndex( const GridPos& GPos,int& out_index ) const
{
	if (GPos.Y<0 ||GPos.Y >= SizeNumY ||GPos.X < 0 || GPos.X >= SizeNumX) out_index = -1;
	else out_index = (GPos.Y) * SizeNumX + GPos.X;
}

void GridSceneMap::GridPosToWorldPos( const GridPos& GPos,Vector2D& out_Pos ) const
{
	float x = GPos.X * TileWidth;
	float y = GPos.Y * TileHeight;
	out_Pos.x = x + BaseLT_Pos.x;
	out_Pos.y = y + BaseLT_Pos.y;
}

void  GridSceneMap::GetNearestGridPos(const Vector2D& worldPos,GridPos& out_GPos) const
{
	int gx = GetRound(worldPos.x - BaseLT_Pos.x, TileWidth);
	int gy = GetRound(worldPos.y- BaseLT_Pos.y, TileHeight);
	gx = MaxOf(0, MinOf(gx / TileWidth, SizeNumX));
	gy = MaxOf(0, MinOf(gy / TileHeight, SizeNumY));
	//
	out_GPos.SetTo(gx,gy);

}

void GridSceneMap::WorldPosToGridPos( const Vector2D& WPos,GridPos& out_Pos ) const
{
	GetNearestGridPos(WPos,out_Pos);
}

void GridSceneMap::WorldPosToIndex( const Vector2D& WPos,int& out_index ) const
{
	GridPos out_Pos;
	GetNearestGridPos(WPos,out_Pos);
	GetIndex(out_Pos,out_index);
}

void GridSceneMap::GetRandomNodeLocation(GridPos& out_GPos) const
{
	NavGraph::ConstNodeIterator NodeItr(*MapGraph);
	int RandIndex = RandInt(0, MapGraph->NumActiveNodes()-1);
	const NavGraph::NodeType* pN = NodeItr.begin();
	while (--RandIndex > 0)
	{
		pN = NodeItr.next();
	}

	GetGridPos(pN->Index(),out_GPos);
}

NavGraphNode<void*>& GridSceneMap::GetNode(const  GridPos& GPos ) const
{
	int index = 0;
	
	GridPosToIndex(GPos,index);

	return MapGraph->GetNode(index);
}


