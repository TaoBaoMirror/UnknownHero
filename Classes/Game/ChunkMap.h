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
/*
	��ͼ�����Ƿֲ�ģ����ﵥ���������ݲ�

	1��ͨ��Tiled��ͼ��ȥˢ���ݣ���һ����ɫ��ȥˢ�ر������磬��ɫ��tile��ζ����GridMap���нڵ㣬
	�ǿ��������򣬺�ɫ��û�нڵ�ġ�Ȼ��������ɫ����ˢ �ر�ڵ�ļ�ֵ
	2����ͼ�����Obj ͨ��Obj��ȥ���ã�Ȼ���ڣ�Soldier���ɵ�ʱ��ȥ������������~

	���ChunkMap������һֱ���ڵģ�Ȼ��ͨ��initȥ�任Map�е����ݣ�Ȼ��MapManager���ʵ��ȥ�õ���ǰ
	��ChunkMap��Ȼ���������ͨ����������ȥ���ʵ�ǰ�����ChunkMap�����ݲ���





*/
class ChunkMap : public cocos2d::TMXTiledMap
{
public:
	ChunkMap();
	~ChunkMap();
	//
	bool	InitChunkMap(std::string tmxFile);
	//
protected:
	GridSceneMap		mGridMap;
	GameInfluenceMap	mIM;
	std::vector<MapNodeData>	MapNodeDataList;
private:
};

#endif // ChunkMap_h__
