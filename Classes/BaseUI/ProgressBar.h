#ifndef __PROGRESSBAR_BASEUI_H__
#define __PROGRESSBAR_BASEUI_H__

#include "cocos2d.h"
#include <string.h>
#include "Common\CommonMethod.h"

NS_CC_BEGIN

class ProgressBar : public cocos2d::Sprite
{
public:
	int MaxProgress;
	//int CurrentProgress;
	ProgressCount* CurrentProgress;

	int width;
	int height;
	int cellWidth;
	int cellHeight;
private:
	static const std::string ProgressBar::cellSpriteFile;
	static const int MaxSprites;
	  
	cocos2d::Vector<Sprite*> mSprites;

public:
	ProgressBar(int maxProgress, int currentProgress,std::string spriteName);
	~ProgressBar(void){}

	void SetCurrentProgress(int g);

	virtual void update(float dt) override;
};

NS_CC_END

#endif//__PROGRESSBAR_BASEUI_H__