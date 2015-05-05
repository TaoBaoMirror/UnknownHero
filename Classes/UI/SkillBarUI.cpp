#include "SkillBarUI.h"
#include "ui/CocosGUI.h"

SkillBarUI::SkillBarUI():_touchGroup(nullptr),_layout(nullptr)
{

}

SkillBarUI::~SkillBarUI()
{

}

bool SkillBarUI::init()
{
	_touchGroup = Layer::create();
	addChild(_touchGroup); 
	//_layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("ui/Skill_UI.csb"));
	//_touchGroup->addChild(_layout);

	Node* n = CSLoader::createNode("ui/Skill_UI.csb");
	_touchGroup->addChild(n);
	//
	return true;
}

void SkillBarUI::touchEvent( Ref* pSender, Widget::TouchEventType type )
{

}

void SkillBarUI::configureGUIScene()
{
	Layout* root = static_cast<Layout*>(_layout->getChildByName("SkillBar_BG"));

	skill_button_0 = static_cast<Button*>(Helper::seekWidgetByName(root, "Skill_0_Button"));
	skill_button_0->addTouchEventListener(CC_CALLBACK_2(SkillBarUI::Skill_0_touchEvent, this));

	skill_button_1 = static_cast<Button*>(Helper::seekWidgetByName(root, "Skill_1_Button"));
	skill_button_1->addTouchEventListener(CC_CALLBACK_2(SkillBarUI::Skill_1_touchEvent, this));

	skill_button_2 = static_cast<Button*>(Helper::seekWidgetByName(root, "Skill_2_Button"));
	skill_button_2->addTouchEventListener(CC_CALLBACK_2(SkillBarUI::Skill_2_touchEvent,this));

	skill_button_3 = static_cast<Button*>(Helper::seekWidgetByName(root, "Skill_3_Button"));
	skill_button_3->addTouchEventListener(CC_CALLBACK_2(SkillBarUI::Skill_3_touchEvent,this));

	hero_level_label = static_cast<Text*>(Helper::seekWidgetByName(root, "PlayerLevelLabel"));

	mini_hero_head_pic = static_cast<ImageView*>(Helper::seekWidgetByName(root, "PlayerMiniHead"));


}

void SkillBarUI::Skill_0_touchEvent( Ref* pSender, Widget::TouchEventType type )
{

}

void SkillBarUI::Skill_1_touchEvent( Ref* pSender, Widget::TouchEventType type )
{

}

void SkillBarUI::Skill_2_touchEvent( Ref* pSender, Widget::TouchEventType type )
{

}

void SkillBarUI::Skill_3_touchEvent( Ref* pSender, Widget::TouchEventType type )
{

}

