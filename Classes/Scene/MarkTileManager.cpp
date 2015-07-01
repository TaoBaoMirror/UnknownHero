#include "MarkTileManager.h"
#include "Game\MapManager.h"
#include "2d\CCTMXLayer.h"

//------------------------------------------------------------
MarkTileManager* MarkTileManager::m_Instance = nullptr;

MarkTileManager* MarkTileManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new MarkTileManager();
	}

	return m_Instance;
}
//------------------------------------------------------------
MarkTileManager::MarkTileManager(void)
{
}

MarkTileManager::~MarkTileManager(void)
{
}
//------------------------------------------------------------
void MarkTileManager::Init()
{
	;
}

void MarkTileManager::Update(float dt)
{
}

void MarkTileManager::SetMarkTiles(MarkTileType type ,std::string key, const std::vector<GridPos>&	PointList)
{
	auto pChunk = MapManager::GetInstance()->GetCurChunkMap();

	auto pRangeLayer = pChunk->GetRangeLayer();

	if (pChunk == nullptr)
	{
		return;
	}

	std::string frameName = "";
	switch (type)
	{
	case MarkTile_Move:
		frameName = "ShowGrid.tga";
		break;
	case MarkTile_Attack:
		frameName = "ShowGrid.tga";
		break;
	default:
		break;
	}

	if (m_ShowMarkTiles.find(key) != m_ShowMarkTiles.end())
	{
		ClearMarkTiles(key);
	}

	cocos2d::SpriteFrame* spriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
	if (spriteframe != nullptr)
	{
		MarkTileVec* tilevec = new MarkTileVec;
		for (int i=0; i<PointList.size(); ++i)
		{	
			GridPos grid = PointList[i];
			Vector2D posVec2D;

			pChunk->GetGridSceneMap().GridPosToWorldPos(grid,posVec2D);
			
			cocos2d::Vec2 finalPos(posVec2D.x,posVec2D.y);
			cocos2d::Sprite* pSp = cocos2d::Sprite::createWithSpriteFrame(spriteframe);
			if (pSp != nullptr)
			{
				pSp->setPosition(finalPos);

				pChunk->addChild(pSp, /*pRangeLayer->getTag()*/  0xa3);

				tilevec->pushBack(pSp);
			}	
		}

		m_ShowMarkTiles[key] = tilevec;
	}
}

void MarkTileManager::ClearMarkTiles(std::string key)
{
	std::map<std::string,MarkTileVec*>::iterator it = m_ShowMarkTiles.find(key);
	if (it != m_ShowMarkTiles.end())
	{
		MarkTileVec* tilevec = it->second;
		MarkTileVec::iterator itVec = tilevec->begin();
		for ( ; itVec!=tilevec->end(); ++itVec)
		{
			cocos2d::Sprite* pSp = *itVec;
			if (pSp != nullptr)
			{
				pSp->setVisible(false);
				pSp->removeFromParentAndCleanup(true);
			}
		}

		tilevec->clear();

		m_ShowMarkTiles.erase(it);
	}	
}

void MarkTileManager::ClearAllTiles()
{
	std::map<std::string,MarkTileVec*>::iterator it  = m_ShowMarkTiles.begin();
	for ( ; it!= m_ShowMarkTiles.end(); ++it)
	{
		MarkTileVec* tilevec = it->second;
		MarkTileVec::iterator itVec = tilevec->begin();
		for ( ; itVec!=tilevec->end(); ++itVec)
		{
			cocos2d::Sprite* pSp = *itVec;
			if (pSp != nullptr)
			{
				pSp->removeFromParentAndCleanup(true);
			}
		}

		tilevec->clear();
	}

	m_ShowMarkTiles.clear();
}
//------------------------------------------------------------
