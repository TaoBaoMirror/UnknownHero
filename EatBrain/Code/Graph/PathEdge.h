/********************************************************************
	created:	2015/03/15
	created:	15:3:2015   9:52
	filename: 	E:\cyvasse\EatBrain\Code\Graph\PathEdge.h
	file path:	E:\cyvasse\EatBrain\Code\Graph
	file base:	PathEdge
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef PathEdge_h__
#define PathEdge_h__

#include "GridPos.h"

class PathEdge
{
private:

	GridPos m_vSource;
	GridPos m_vDestination;

	int      m_iBehavior;

	int      m_iDoorID;

public:

	PathEdge(	const GridPos& Source,
		const GridPos& Destination,
		int      Behavior,
		int      DoorID = 0):m_vSource(Source),
		m_vDestination(Destination),
		m_iBehavior(Behavior),
		m_iDoorID(DoorID)
	{}

	GridPos Destination()const{return m_vDestination;}
	void     SetDestination(const GridPos& NewDest){m_vDestination = NewDest;}

	GridPos Source()const{return m_vSource;}
	void     SetSource(const GridPos& NewSource){m_vSource = NewSource;}

	int      DoorID()const{return m_iDoorID;}
	int      Behavior()const{return m_iBehavior;}
};

#endif // PathEdge_h__
