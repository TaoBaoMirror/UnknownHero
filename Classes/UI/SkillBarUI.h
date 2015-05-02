/********************************************************************
	created:	2015/05/02
	created:	2:5:2015   23:29
	filename: 	E:\UnknownHero\Classes\UI\SkillBarUI.h
	file path:	E:\UnknownHero\Classes\UI
	file base:	SkillBarUI
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef SkillBarUI_h__
#define SkillBarUI_h__

#include "UICommon.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class SkillBarUI : public cocos2d::Layer
{
public:
	SkillBarUI();
	~SkillBarUI();
	//
	bool init();
	void touchEvent(Ref* pSender, Widget::TouchEventType type);

	void configureGUIScene();
	//
	UI_LAYER_CREATE_FUNC(SkillBarUI);

protected:
	Layer* _touchGroup;
	Layout* _layout;
private:
};

#endif // SkillBarUI_h__
