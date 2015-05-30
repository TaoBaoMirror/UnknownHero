/********************************************************************
	created:	2015/05/30
	created:	30:5:2015   9:45
	filename: 	E:\UnknownHero\Classes\Actor\ActorPathFinderCalculateFunc.h
	file path:	E:\UnknownHero\Classes\Actor
	file base:	ActorPathFinderCalculateFunc
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef ActorPathFinderCalculateFunc_h__
#define ActorPathFinderCalculateFunc_h__

class ActorPathFinderCalculateFunc
{
public:
	ActorPathFinderCalculateFunc(){}
	//
	template <class graph_type>
	static double Calculate(const graph_type& G, int nd1, int nd2,void* owner)
	{
		return Vec2DDistance(G.GetNode(nd1).Pos(), G.GetNode(nd2).Pos());
	}

	template <class graph_type,class edge_type>
	static double CalculateEdgeCost(const graph_type& G, const edge_type* edge,void* owner)
	{
		return edge->Cost();
	}


protected:
	
private:
};

#endif // ActorPathFinderCalculateFunc_h__
