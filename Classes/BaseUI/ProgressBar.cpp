#include "ProgressBar.h"
#include "ResDef.h"
#include "Common\CommonMethod.h"

USING_NS_CC;

//---------------------------------------------------------------------------

const std::string ProgressBar::cellSpriteFile = "images/foot.png";//foot图片
const int ProgressBar::MaxSprites = 10;

ProgressBar::ProgressBar(int maxProgress, int currentProgress, std::string spriteName)
{
	setBatchNode(NULL);

	CurrentProgress = new ProgressCount;

	MaxProgress = maxProgress;
	CurrentProgress->setCount(currentProgress);

	Director::getInstance()->getTextureCache()->addImage(ResDef::g_BlankTextureFile);
    bool isok = initWithFile(ResDef::g_BlankTextureFile);

	this->setAnchorPoint(Vec2(0, 0.5f));    //左边中心是锚点    

	//Director::getInstance()->getTextureCache()->addImage(cellSpriteFile);
    for (int i = 0; i < MaxSprites;++i )
    {
		Sprite* cell = Sprite::create(cellSpriteFile);

		//if (spriteName != "")
  //      {
		//	cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
		//	if(frame != NULL)
		//	{
		//		cell = Sprite::createWithSpriteFrame(frame);
		//	}
		//	
  //      }
  //      else
  //      {
		//	cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(cellSpriteFile);
		//	cell = Sprite::createWithSpriteFrame(frame);

  //      }

		cell->setAnchorPoint(Vec2(0, 0.5f));
		cell->setBatchNode(NULL);
        //
        addChild(cell);
		mSprites.pushBack(cell);
		cell->setPosition(Vec2(width, 0));
		cell->setVisible(false);
        //
		cellWidth = cell->getTexture()->getPixelsWide();
		cellHeight = cell->getTexture()->getPixelsHigh();
        //

        width = width + cellWidth;
        height = cellHeight;
        //
                             
    }
}

void ProgressBar::SetCurrentProgress(int g)
{
	CurrentProgress->setCount(g);
}
        //
void ProgressBar::update(float dt)
{
	int pole = (int)(CurrentProgress->getCurPercentage() * MaxSprites);
    for (int i = 0; i < MaxSprites; ++i)
    {
		Sprite* pSp = mSprites.at(i);
		if(pSp != NULL)
		{
			if (i < pole)
			{
				pSp->setVisible(true);
			}
			else
			{
				pSp->setVisible(false);
			}
		}
    }
}