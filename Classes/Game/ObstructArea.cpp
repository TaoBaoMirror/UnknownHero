#include "ObstructArea.h"
#include "CommonFunc.h"
#include "MapNodeData.h"

ObstructArea::ObstructArea():GridPosArea()
{

}

void ObstructArea::SetObstruct( int GPosAreaIndex )
{
	int nSize = GPosArea.size();
	if(GPosAreaIndex >= nSize || GPosAreaIndex < 0)  return;
	//
	G_GetSceneMap().GetNode(GPosArea[GPosAreaIndex]);
	//
	NavGraphNode<void*>& node = G_GetSceneMap().GetNode(GPosArea[GPosAreaIndex]);
	node.SetWalkable(false);
}

void ObstructArea::ClearObstruct( int GPosAreaIndex )
{
	int nSize = GPosArea.size();
	if(GPosAreaIndex >= nSize || GPosAreaIndex < 0)  return;
	//
	G_GetSceneMap().GetNode(GPosArea[GPosAreaIndex]);
	//
	NavGraphNode<void*>& node = G_GetSceneMap().GetNode(GPosArea[GPosAreaIndex]);
	node.SetWalkable(true);
}

void ObstructArea::EnableObstruct( bool b )
{
	if(GPosArea.size() == 0) return;

	for (int i = 0;i< GPosArea.size() ;++i)
	{
		if(b) SetObstruct(i);
		else ClearObstruct(i);
	}
}
