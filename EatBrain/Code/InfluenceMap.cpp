#include "InfluenceMap.h"
#include "PFPotentialField.h"
#include <xutility>

InfluenceMap::InfluenceMap()
{
	NextID = 0;

	nSizeXNum	= 0;
	nSizeYNum	= 0;

	nWorldX	= 0;
	nWorldY	= 0;

	nTileWidth	= 0;
	nTileHeight	= 0;

}

InfluenceMap::~InfluenceMap()
{
	
}

int InfluenceMap::AddDynamicField( PFPotentialField* field )
{
	int id = NextID;
	field->Id = id;
	Fields.insert(std::make_pair(id,field));
	NextID++;
	return id;
}

void InfluenceMap::RemoveDynamicField( PFPotentialField* field )
{
	RemoveDynamicField(field->Id);
}

void InfluenceMap::RemoveDynamicField( int id )
{
	Fields.erase(id);
}

void InfluenceMap::RemoveAllDynamicFields()
{
	Fields.clear();
}

PFPotentialField* InfluenceMap::GetDynamicField( int id )
{
	std::map<int,PFPotentialField*>::iterator it = Fields.find(id);
	if (it != Fields.end())
	{
		return it->second;
	}

	return 0;
}

void InfluenceMap::Init( int WorldX,int WorldY,int TileWidth,int TileHeight )
{

	nWorldX	= WorldX;
	nWorldY	= WorldY;

	nTileWidth	= TileWidth;
	nTileHeight	= TileHeight;

	nSizeXNum	= nWorldX / nTileWidth;
	nSizeYNum	= nWorldY / nTileHeight;

	StaticMap.resize(nSizeXNum);

	for (int col = 0;col<nSizeXNum;col++)
	{
		StaticMap[col].resize(nSizeYNum,0);
	}
}

void InfluenceMap::AddStaticField( PFPotentialField* field )
{
	addStaticField(field,1);
}

void InfluenceMap::RemoveStaticField( PFPotentialField* field )
{
	addStaticField(field,-1);
}

void InfluenceMap::addStaticField( PFPotentialField* field,float multiplier )
{
	for (int x = std::max(0,field->position.X - field->PotentialBoundsHalfWidth());
		x<=std::min(nSizeXNum-1,field->position.X + field->PotentialBoundsHalfWidth());
		++x)
	{
		for (int y = std::max(0,field->position.Y - field->PotentialBoundsHalfHeight());
			x<=std::min(nSizeYNum-1,field->position.Y + field->PotentialBoundsHalfHeight());
			++y)
		{
			StaticMap[x][y] += multiplier * field->GetLocalPotential(x-field->position.X,y-field->position.Y);
		}
	}
}

int InfluenceMap::GetDynamicPotential( int mapX,int mapY )
{
	int potential = 0;
	//这个是动态的field
	for (auto it = Fields.begin();it != Fields.end();it++)
	{
		PFPotentialField* field = it->second;
		potential += field->GetLocalPotential(mapX - field->position.X, mapY - field->position.Y);
	}
	//
	return potential;
}

int InfluenceMap::GetPotential( int mapX,int mapY )
{
	int valueD = GetDynamicPotential(mapX,mapY);
	int valueS = GetStaticPotential(mapX,mapY);

	return valueS + valueD;

}

int InfluenceMap::GetStaticPotential( int mapX,int mapY )
{
	return StaticMap[mapX][mapY];
}
//////////////////////////////////////////////////////////////////////////
GridPos InfluenceMap::NextPosition( InfluenceMap* IM,PFPotentialField* field,int x_order /*= 1*/, int y_order /*= 1*/ )
{
	bool subtractSelfPotentialFromDynamicsMapSum = true;
	int staticPotential = IM->GetStaticPotential(field->position.X, field->position.Y);
	int agentsPotential = IM->GetDynamicPotential(field->position.X, field->position.Y);
	int selfPotential = field->GetPotential(field->position.X, field->position.Y);
	int trailPotential = /*GetTrailPotential(field->position.X, field->position.Y)*/0;
	GridPos _cachedPoint(field->position.X, field->position.Y);

	int bestAttractPotential = staticPotential + agentsPotential - (subtractSelfPotentialFromDynamicsMapSum?selfPotential:0) + trailPotential;

	for (int x = -1; x <= 1; x++) 
	{
		int xx = field->position.X + x * x_order;
		if (xx >= 0 && xx < IM->nSizeXNum) 
		{

			for (int y = -1; y <= 1; y++)
			{
				if (x == 0 && y == 0) 
				{
					continue;
				}

				int yy = field->position.Y + y * y_order;
				if (yy >= 0 && yy < IM->nSizeYNum) 
				{
					int comparingPotential = 
						IM->GetStaticPotential(xx, yy) + 
						IM->GetDynamicPotential(xx, yy) - 
						(subtractSelfPotentialFromDynamicsMapSum?field->GetPotential(xx, yy):0) + 
						/*getTrailPotential(xx, yy)*/0;

					if (comparingPotential < bestAttractPotential) 
					{
						bestAttractPotential = comparingPotential;
						_cachedPoint.SetTo(xx, yy);
					}
				}
			}
		}
	}
	/*
	if (_cachedPoint.X == field->position.X && _cachedPoint.Y == field->position.Y) 
	{
		if (_trails.length > trailLength) 
		{// zapewnia stala dlugosc listy sladow i reuzywa ponownie starego sladu
			PFAgentTrail recycledTrail = _trails.head;
			_trails.removeNode(recycledTrail);// usuwa go z poczatku listy
			recycledTrail.worldX = position.x;
			recycledTrail.worldY = position.y;
			_trails.appendNode(recycledTrail);// dodaje go na koniec listy
		}
		else if (trailLength > 0) {
			_trails.appendNode(new PFAgentTrail(position.x, position.y, type * potential));
		}
		_cachedPoint.setTo(position.x,  position.y);
	}
	*/
	return _cachedPoint;
}