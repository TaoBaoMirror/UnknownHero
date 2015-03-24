#include "MyTMXMap.h"


MyTMXMap::MyTMXMap(std::string tmxFile) :
TMXTiledMap(tmxFile)
{
}


MyTMXMap::~MyTMXMap()
{
}

bool MyTMXMap::CheckPropertiesForGID(int gid)
{
	cocos2d::Value* pVa = nullptr;
	bool bret = this->getPropertiesForGID(gid, &pVa);

	return bret;
}

bool MyTMXMap::CheckPropertyNamed(std::string name)
{
	cocos2d::Value pValue = this->getProperty(name);

	if (pValue.isNull())
	{
		return false;
	}

	return true;
}
