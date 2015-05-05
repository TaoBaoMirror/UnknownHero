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
	//
	void Skill_0_touchEvent(Ref* pSender, Widget::TouchEventType type);
	void Skill_1_touchEvent(Ref* pSender, Widget::TouchEventType type);
	void Skill_2_touchEvent(Ref* pSender, Widget::TouchEventType type);
	void Skill_3_touchEvent(Ref* pSender, Widget::TouchEventType type);

	void ConfigureGUIScene();
	//
	UI_LAYER_CREATE_FUNC(SkillBarUI);
public:
	void	SetMiniHeroHead(const std::string& picName);
	void	SetHeroLevel(int lvl);
	void	SetSkill(int skill_slot,int skillID);
	void	SetSkillIcon(int skill_slot,const std::string& picName);
	void	SetSkillEnable(int skill_slot,bool enable);
	void	RemoveSkillSlot(int skill_slot );




protected:
	Layer* _touchGroup;
	Layout* _layout;

	Vector<Button*>	skill_button;
	//
	Text*	hero_level_label;
	ImageView* mini_hero_head_pic;

private:
	void	DoSetHeroLevelEffect();
	void	DoSetSkillIconEffect();
	void	DoSetSkillEnableEffect();

};

#endif // SkillBarUI_h__
