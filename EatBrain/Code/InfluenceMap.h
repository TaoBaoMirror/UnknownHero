/********************************************************************
	created:	2014/11/30
	created:	30:11:2014   11:38
	filename: 	E:\BunkerAI\BunkerAI\Code\InfluenceMap.cpp
	file path:	E:\BunkerAI\BunkerAI\Code
	file base:	InfluenceMap
	file ext:	cpp
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef InfluenceMap_h__
#define InfluenceMap_h__

#include <map>
#include <vector>

#include "GridPos.h"

class PFPotentialField;

class InfluenceMap
{
	static const int DefaultSize = 128;


	typedef std::map<int,PFPotentialField*>::iterator FieldsIter;

	//


public:
	int	nSizeXNum;
	int nSizeYNum;

	int nWorldX;
	int nWorldY;

	int nTileWidth;
	int nTileHeight;



public:
	InfluenceMap();
	~InfluenceMap();
	//
	void Init(int WorldX,int WorldY,int TileWidth,int TileHeight);

	void AddStaticField(PFPotentialField* field);
	void RemoveStaticField(PFPotentialField* field);
	///----------------------------
	int AddDynamicField(PFPotentialField* field);
	void RemoveDynamicField(PFPotentialField* field);
	void RemoveDynamicField(int id);
	void RemoveAllDynamicFields();
	PFPotentialField* GetDynamicField(int id);
	int GetDynamicPotential(int mapX,int mapY);
	int GetStaticPotential(int mapX,int mapY);

	int GetPotential(int mapX,int mapY);


	//////////////////////////////////////////////////////////////////////////
	virtual void Update(){}


protected:
	void addStaticField(PFPotentialField* field,float multiplier);

	std::vector< std::vector<int> >	StaticMap;
	std::map<int,PFPotentialField*>	Fields;

private:
	int		NextID;


public:
	static GridPos	NextPosition(InfluenceMap* IM,PFPotentialField* field,int x_order = 1, int y_order = 1);
};

#endif // InfluenceMap_h__
