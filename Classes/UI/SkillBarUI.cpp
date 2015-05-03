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

	_layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("ui/Skill_UI.csb"));
	_touchGroup->addChild(_layout);
	//
	return true;
}

void SkillBarUI::touchEvent( Ref* pSender, Widget::TouchEventType type )
{

}

void SkillBarUI::configureGUIScene()
{

}

