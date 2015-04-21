/********************************************************************
	created:	2015/01/20
	created:	20:1:2015   11:50
	filename: 	E:\cyvasse\TestAI\MapNodeData.h
	file path:	E:\cyvasse\TestAI
	file base:	MapNodeData
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef MapNodeData_h__
#define MapNodeData_h__

#include <fstream>

class Soldier;

#define InvalidID -1

class MapNodeData
{
public:
	MapNodeData():ID(InvalidID),Creature(0),ResouceID(InvalidID),SpecialID(InvalidID)
	{

	}
	MapNodeData(const MapNodeData& mnd)
	{
		ID = mnd.ID;
		ResouceID = mnd.ResouceID;
		SpecialID = mnd.SpecialID;
		Creature = mnd.Creature;
	}
	MapNodeData(std::ifstream& stream):
		Creature(NULL)
	{
		char buffer[50];
		stream >> buffer >> ID >> buffer >> ResouceID >> buffer >> SpecialID;

	}
	//需要序列化的
	int				ID;
	int				ResouceID;
	int				SpecialID;
	int				Type;
	//
	Soldier*		Creature;

	//
	friend std::ostream& operator<<(std::ostream& os, const MapNodeData& n)
	{
		os << 
			"ID: " << n.ID << 
			" ResouceID: " << n.ResouceID << 
			" SpecialID: " << n.SpecialID << 
			std::endl;

		return os;
	}

};

inline MapNodeData* Cast_MapNodeData(void* t)
{
	if(t == NULL) return NULL;
	auto pMND = (MapNodeData*)t;
	return pMND;
}



#endif // MapNodeData_h__
