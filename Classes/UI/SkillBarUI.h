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
	//
	void Skill_0_touchEvent(Ref* pSender, Widget::TouchEventType type);
	void Skill_1_touchEvent(Ref* pSender, Widget::TouchEventType type);
	void Skill_2_touchEvent(Ref* pSender, Widget::TouchEventType type);
	void Skill_3_touchEvent(Ref* pSender, Widget::TouchEventType type);

	void configureGUIScene();
	//
	UI_LAYER_CREATE_FUNC(SkillBarUI);

protected:
	Layer* _touchGroup;
	Layout* _layout;
	//
	Button* skill_button_0;
	Button* skill_button_1;
	Button* skill_button_2;
	Button* skill_button_3;
	//
	Text*	hero_level_label;
	ImageView* mini_hero_head_pic;

private:
};

#endif // SkillBarUI_h__
