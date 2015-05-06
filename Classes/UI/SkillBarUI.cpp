#include "SkillBarUI.h"
#include "ui/CocosGUI.h"

#define BtnClickActionTag 1
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

	_layout = static_cast<Layout*>(CSLoader::createNode("ui/Skill_UI.csb"));
	_touchGroup->addChild(_layout);
	//
	ConfigureGUIScene();
		//
	return true;
}

void SkillBarUI::ConfigureGUIScene()
{
	Layout* root = static_cast<Layout*>(_layout->getChildByName("SkillBar_BG"));

	Button* skill_button_0 = static_cast<Button*>(Helper::seekWidgetByName(root, "Skill_0_Button"));
	skill_button_0->addTouchEventListener(CC_CALLBACK_2(SkillBarUI::Skill_0_touchEvent, this));

	Button* skill_button_1 = static_cast<Button*>(Helper::seekWidgetByName(root, "Skill_1_Button"));
	skill_button_1->addTouchEventListener(CC_CALLBACK_2(SkillBarUI::Skill_1_touchEvent, this));

	Button* skill_button_2 = static_cast<Button*>(Helper::seekWidgetByName(root, "Skill_2_Button"));
	skill_button_2->addTouchEventListener(CC_CALLBACK_2(SkillBarUI::Skill_2_touchEvent,this));

	Button* skill_button_3 = static_cast<Button*>(Helper::seekWidgetByName(root, "Skill_3_Button"));
	skill_button_3->addTouchEventListener(CC_CALLBACK_2(SkillBarUI::Skill_3_touchEvent,this));

	skill_button.pushBack(skill_button_0);
	skill_button.pushBack(skill_button_1);
	skill_button.pushBack(skill_button_2);
	skill_button.pushBack(skill_button_3);

	button_click_effect.pushBack(ScaleTo::create(0.15f,0.9f));
	button_click_effect.pushBack(ScaleTo::create(0.15f,0.9f));
	button_click_effect.pushBack(ScaleTo::create(0.15f,0.9f));
	button_click_effect.pushBack(ScaleTo::create(0.15f,0.9f));
	button_click_effect.at(0)->setTag(BtnClickActionTag);
	button_click_effect.at(1)->setTag(BtnClickActionTag);
	button_click_effect.at(2)->setTag(BtnClickActionTag);
	button_click_effect.at(3)->setTag(BtnClickActionTag);



	hero_level_label = static_cast<Text*>(Helper::seekWidgetByName(root, "PlayerLevelLabel"));

	mini_hero_head_pic = static_cast<ImageView*>(Helper::seekWidgetByName(root, "PlayerMiniHead"));


}

void SkillBarUI::Skill_0_touchEvent( Ref* pSender, Widget::TouchEventType type )
{
	Button*	btn = dynamic_cast<Button*>(pSender);
	auto skill = btn->getUserData();
	ScaleTo* st = button_click_effect.at(0);
	//
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		{
			auto act = btn->getActionByTag(BtnClickActionTag);
			if ((act != nullptr && act->isDone()) || act == nullptr)
			{
				btn->runAction(st);
			}
			break;
		}
	case Widget::TouchEventType::MOVED:
		{


			break;
		}
	case Widget::TouchEventType::CANCELED:
		{
			btn->stopActionByTag(BtnClickActionTag);
			btn->setScale(1);
			break;

		}
	case Widget::TouchEventType::ENDED:
		{
			btn->stopActionByTag(BtnClickActionTag);
			btn->setScale(1);
			break;
		}
	}
}

void SkillBarUI::Skill_1_touchEvent( Ref* pSender, Widget::TouchEventType type )
{
	Button*	btn = dynamic_cast<Button*>(pSender);
	auto skill = btn->getUserData();
	ScaleTo* st = button_click_effect.at(1);
	//
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		{
			auto act = btn->getActionByTag(BtnClickActionTag);
			if ((act != nullptr && act->isDone()) || act == nullptr)
			{
				btn->runAction(st);
			}
			break;
		}
	case Widget::TouchEventType::MOVED:
		{


			break;
		}
	case Widget::TouchEventType::CANCELED:
		{
			btn->stopActionByTag(BtnClickActionTag);
			btn->setScale(1);
			break;
			
		}
	case Widget::TouchEventType::ENDED:
		{
			btn->stopActionByTag(BtnClickActionTag);
			btn->setScale(1);
			break;
		}
	}
}

void SkillBarUI::Skill_2_touchEvent( Ref* pSender, Widget::TouchEventType type )
{
	Button*	btn = dynamic_cast<Button*>(pSender);
	auto skill = btn->getUserData();
	ScaleTo* st = button_click_effect.at(2);
	//
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		{
			auto act = btn->getActionByTag(BtnClickActionTag);
			if ((act != nullptr && act->isDone()) || act == nullptr)
			{
				btn->runAction(st);
			}
			break;
		}
	case Widget::TouchEventType::MOVED:
		{


			break;
		}
	case Widget::TouchEventType::CANCELED:
		{
			btn->stopActionByTag(BtnClickActionTag);
			btn->setScale(1);
			break;

		}
	case Widget::TouchEventType::ENDED:
		{
			btn->stopActionByTag(BtnClickActionTag);
			btn->setScale(1);
			break;
		}
	}
}

void SkillBarUI::Skill_3_touchEvent( Ref* pSender, Widget::TouchEventType type )
{
	Button*	btn = dynamic_cast<Button*>(pSender);
	auto skill = btn->getUserData();
	ScaleTo* st = button_click_effect.at(3);
	//
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		{
			auto act = btn->getActionByTag(BtnClickActionTag);
			if ((act != nullptr && act->isDone()) || act == nullptr)
			{
				btn->runAction(st);
			}
			break;
		}
	case Widget::TouchEventType::MOVED:
		{


			break;
		}
	case Widget::TouchEventType::CANCELED:
		{
			btn->stopActionByTag(BtnClickActionTag);
			btn->setScale(1);
			break;

		}
	case Widget::TouchEventType::ENDED:
		{
			btn->stopActionByTag(BtnClickActionTag);
			btn->setScale(1);
			break;
		}
	}
}

void SkillBarUI::SetMiniHeroHead( const std::string& picName )
{
	mini_hero_head_pic->loadTexture(picName);
}

void SkillBarUI::SetHeroLevel( int lvl )
{
	std::string t = StringUtils::toString(lvl);
	t = "Lv." + t;
	hero_level_label->setString(t);
	//
	DoSetHeroLevelEffect();
}

void SkillBarUI::SetSkillIcon( int skill_slot,const std::string& picName )
{
	const std::string szFilePath = "ui/";

	Button*	skill_icon = skill_button.at(skill_slot);

	std::string normalName = szFilePath + picName + "_normal" + ".png";
	std::string disableName = szFilePath + picName + "_disabled" +  + ".png";

	skill_icon->loadTextureNormal(normalName);
	skill_icon->loadTexturePressed(normalName);
	skill_icon->loadTextureDisabled(disableName);


}

void SkillBarUI::SetSkillEnable( int skill_slot,bool enable )
{
	Button*	skill_icon = skill_button.at(skill_slot);

	skill_icon->setEnabled(enable);

	if (enable)
	{
		DoSetSkillEnableEffect();
	}
}

void SkillBarUI::DoSetHeroLevelEffect()
{

}

void SkillBarUI::DoSetSkillIconEffect()
{

}

void SkillBarUI::SetSkill( int skill_slot,int skillID )
{
	if (skillID == -1)
	{
		RemoveSkillSlot(skill_slot);
	}
	else
	{
		//设置userdata为skill的指针
		Button*	skillbtn = skill_button.at(skill_slot);
		skillbtn->setUserData(nullptr);


		std::string SkillResPathName = "ui/";
		SetSkillIcon(skill_slot,SkillResPathName);
	}
}

void SkillBarUI::RemoveSkillSlot( int skill_slot )
{
	const std::string szNullIcon = "ui/Skill_-1.png";

	Button*	skill_icon = skill_button.at(skill_slot);

	skill_icon->loadTextureNormal(szNullIcon);
	skill_icon->loadTextureDisabled(szNullIcon);
	skill_icon->setEnabled(false);
	skill_icon->setUserData(nullptr);	//清除btn的userdata的skill制作
}

void SkillBarUI::DoSetSkillEnableEffect()
{

}

