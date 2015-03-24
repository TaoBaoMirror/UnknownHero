#ifndef __MY_TMXMAP_H__
#define __MY_TMXMAP_H__

#include "cocos2d.h"

class MyTMXMap : public cocos2d::TMXTiledMap
{
public:
	MyTMXMap(std::string tmxFile);
	~MyTMXMap();

	bool CheckPropertiesForGID(int gid);

	bool CheckPropertyNamed(std::string name);
};

#endif //__MY_TMXMAP_H__