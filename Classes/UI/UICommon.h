/********************************************************************
	created:	2015/05/02
	created:	2:5:2015   23:54
	filename: 	E:\UnknownHero\Classes\UI\UICommon.h
	file path:	E:\UnknownHero\Classes\UI
	file base:	UICommon
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef UICommon_h__
#define UICommon_h__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"

#define UI_LAYER_CREATE_FUNC(UILayer_Class) \
public: \
static Layer* CreateWithTag(int nTag) \
{ \
	UILayer_Class* uiLayer = new UILayer_Class(); \
	if (uiLayer && uiLayer->init()) \
	{ \
		uiLayer->autorelease(); \
		uiLayer->setTag(nTag); \
	} \
	else \
	{ \
		CC_SAFE_DELETE(uiLayer); \
	} \
	return uiLayer; \
}

#endif // UICommon_h__
