#include "MainControllerPanel.h"
#include "Action/GameAction.h"
#include "Action/GameActionSystem.h"
//

const std::string WheelIcon::IconDict[9] = { 
	"item_5.png" , 
	"item_4.png" , 
	"item_8.png" , 
	"item_0.png" , 
	"item_2.png" , 
	"item_1.png" , 
	"item_7.png" , 
	"item_3.png" , 
	"item_6.png"};
const std::string WheelIcon::IconDict_HighLight[9] = { 
	"item_5.png" , 
	"item_4.png" , 
	"item_8.png" , 
	"item_0.png" , 
	"item_2.png" , 
	"item_1.png" , 
	"item_7.png" , 
	"item_3.png" , 
	"item_6.png"};



const std::string& WheelIcon::GetIconName( int iconID )
{
	return IconDict[iconID];
}

const std::string& WheelIcon::GetIconName_HighLight( int iconID )
{
	return IconDict_HighLight[iconID];
}


//
WheelIcon::WheelIcon():
	Sprite(),
	pNormalSpriteFrame(nullptr),
	pHighlightSpriteFrame(nullptr),
	mNum(1),
	mIconID(-1)
{

}

WheelIcon::~WheelIcon()
{

}


void WheelIcon::SetResource( int num,int iconID )
{
	if(pNormalSpriteFrame) pNormalSpriteFrame = nullptr;
	pNormalSpriteFrame  = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(WheelIcon::GetIconName(iconID));
	if(pHighlightSpriteFrame) pHighlightSpriteFrame = nullptr;
	pHighlightSpriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(WheelIcon::GetIconName_HighLight(iconID));
	//
	initWithSpriteFrame(pNormalSpriteFrame);
	//
	mNum = num;
	mIconID = iconID;
}

void WheelIcon::Init( int num,int iconID )
{
	SetResource(num,iconID);
	//
	autorelease();
}

void WheelIcon::Init( GameAction* gameAction )
{
	Init(1,gameAction->GetIconID());
}

bool WheelIcon::PickOne()
{
	return (mNum--) > 0;
}

void WheelIcon::TurnOn()
{
	if (pHighlightSpriteFrame != nullptr)
	{
		setSpriteFrame(pHighlightSpriteFrame);
	}
}

void WheelIcon::TurnOff()
{
	if (pNormalSpriteFrame != nullptr)
	{
		setSpriteFrame(pNormalSpriteFrame);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void ActionWheel::Init()
{
	int a[4]={0,1,2,0};  
	std::vector<int>  ids(a,a+4);
	ActionWheel::Init( ids );
}

void ActionWheel::Init( const std::vector<int>& IconIDs )
{
	if(!Layer::init()) return;
	//
	const int ShowIconNum = 3;
	auto SFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(WheelIcon::GetIconName(0));
	cocos2d::Vec2 BaseIconPos(SFrame->getRect().size.width * 0.5f , SFrame->getRect().size.height * 3.5f);
	mIconBasePos = BaseIconPos;
	//建立一个 clipperNode
	auto clipper = cocos2d::ClippingNode::create();
	clipper->setTag( ActionWheel::ClipperTag );
	clipper->setContentSize(  cocos2d::Size(SFrame->getRect().size.width, SFrame->getRect().size.height * ShowIconNum) );
	clipper->setAnchorPoint(  cocos2d::Vec2( 0.5,0.5 ) );
	clipper->setPosition( 0,0 );
	this->addChild(clipper);
	//设置蒙版
	auto stencil = cocos2d::DrawNode::create();
	cocos2d::Vec2 rectangle[4];
	rectangle[0] = cocos2d::Vec2(0, 0);
	rectangle[1] = cocos2d::Vec2(clipper->getContentSize().width, 0);
	rectangle[2] = cocos2d::Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
	rectangle[3] = cocos2d::Vec2(0, clipper->getContentSize().height);
	cocos2d::Color4F white(1, 1, 1, 1);
	stencil->drawPolygon(rectangle, 4, white, 1, white);
	clipper->setStencil(stencil);

	//传递好IconsID
	mIconIDs = IconIDs;
	//icon 的排列为 后后，后，现，前
	//				0 , 1 , 2 , 3
	mCurrentIconIndex = 2;
	mNeedResetIconIndex = 3;
	//
	int wheelIconNum = IconIDs.size();  //must be 4
	for (int i = 0;i<wheelIconNum;++i)
	{
		WheelIcon* icon = new WheelIcon();
		icon->Init(1,IconIDs[i]);
		//位置是clipperNode上面的位置
		icon->setPosition(mIconBasePos.x, mIconBasePos.y - icon->getContentSize().height * i);
		mWheelIcons.pushBack(icon);
		clipper->addChild(icon);
	}
	//////////////
	//		增加一个事件监听
	/////////////
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ActionWheel::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ActionWheel::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ActionWheel::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//_eventDispatcher->addEventListenerWithFixedPriority(listener, -11);
	//////////////////////////////////////////////////////////////////////////
	mBlurWheel = BlurWheel::create("images/item_wheel_0.png");
	mBlurWheelBasePos = mIconBasePos + cocos2d::Vec2(0,mBlurWheel->getContentSize().height*0.5f + SFrame->getRect().size.height * 0.5f);
	mBlurWheel->setPosition(mBlurWheelBasePos);
	mBlurWheel->setVisible(false);
	clipper->addChild(mBlurWheel);

	//动画变量初始化
	mRollNextIconTime = 1.0f;

	mSlowdownTime = 1.3f;

	mRollTime = 3.0f;

	mAccelerateTime = 1.0f;

}

void ActionWheel::RollToNextIcon()
{
	// 判断当前状态是否符合运动
	if (mState != WheelIdle)
	{
		return;
	}
	// 改变状态
	mState = WheelRollNext;
	// iconID 已经设置完毕,next next icon 随机得到新的iconID,数据层面
	mCurrentIconIndex--;
	if(mCurrentIconIndex == -1) mCurrentIconIndex = 3;

	// 播放向下转动的动画
	PlayRollToNextIconAniamtion();
}

void ActionWheel::PlayRollToNextIconAniamtion()
{
	//向下运动
	for (int i = 0;i<mWheelIcons.size();++i)
	{
		WheelIcon* icon = mWheelIcons.at(i);
		auto moveby = cocos2d::MoveBy::create(mRollNextIconTime,cocos2d::Vec2(0,-icon->getContentSize().height));
		auto eei = cocos2d::EaseElasticOut::create(moveby);
		auto func = cocos2d::CallFuncN::create(CC_CALLBACK_0(ActionWheel::CallBack_RollToNextIcon , this ));
		auto seq = cocos2d::Sequence::create(eei,func,nullptr);
		icon->runAction(seq);
	}
}

void ActionWheel::CallBack_RollToNextIcon()
{
	// 改变状态,此时数据和画面已经一致了
	if(mState == WheelRollNext)
	{
		mState = WheelIdle;
		// 将最下面之前位置的icon设置到最上方,并且配置在动画前随机的iconID
		WheelIcon* icon = mWheelIcons.at(mNeedResetIconIndex);
		//
		icon->setPosition(mIconBasePos);
		//
		int iconID = cocos2d::random(0,2);

		GameActionSystem::GetInstance()->RollGroup(mGroupID);

		iconID = GameActionSystem::GetInstance()->GetAction(mGroupID,NextNextAction)->GetIconID();
		//
		mIconIDs[mNeedResetIconIndex] = iconID;

		icon->SetResource(1,iconID);
		//
		mNeedResetIconIndex--;
		if(mNeedResetIconIndex == -1) mNeedResetIconIndex = 3;
	}

}

void ActionWheel::RandomRoll()
{

	// 判断当前状态是否符合运动
	if (mState != WheelIdle) return;

	// 改变状态
	mState = WheelAccelerate;
	// 所有的iconID已经设置Ok

	AssetIconIDs();


	// 播放动画
	PlayRandomRollAnimation();
}

void ActionWheel::PlayRandomRollAnimation()
{
	// 1- 开始向下运动
	mBlurWheel->setPosition(mBlurWheelBasePos);
	mBlurWheel->setVisible(true);
	mBlurWheel->PlayAccelerateAnimation();
	//
	int iconNum = mWheelIcons.size();
	int moveby_dis = 0;
	for (int i = 0;i<iconNum;++i)
	{
		WheelIcon* icon = mWheelIcons.at(i);
		moveby_dis = -icon->getContentSize().height * iconNum;
		auto moveby = cocos2d::MoveBy::create(mAccelerateTime,cocos2d::Vec2(0,moveby_dis));
		auto eei = cocos2d::EaseIn::create(moveby,2);
		auto func = cocos2d::CallFuncN::create(CC_CALLBACK_0(ActionWheel::CallBack_AccelerateRollOver , this ));
		auto seq = cocos2d::Sequence::create(eei,func,nullptr);
		icon->runAction(seq);
	}
	//
	auto moveby = cocos2d::MoveBy::create(mAccelerateTime,cocos2d::Vec2(0,moveby_dis));
	auto eei = cocos2d::EaseIn::create(moveby,2);
	auto func = cocos2d::CallFuncN::create(CC_CALLBACK_0(ActionWheel::CallBack_AccelerateRollOver , this ));
	auto seq = cocos2d::Sequence::create(eei,func,nullptr);
	seq->setTag(BlurWheel::MoveByTag);
	mBlurWheel->runAction(seq);
}


void ActionWheel::CallBack_AccelerateRollOver()
{
	if (mState == WheelAccelerate)
	{
		mState = WheelRoll;
		// 1-
		mBlurWheel->stopActionByTag(BlurWheel::MoveByTag);
		// 2- 模糊一段时间
		mBlurWheel->StopAccelerateAnimation();
		mBlurWheel->PlayRollAnimation();
		auto delay = cocos2d::DelayTime::create(mRollTime);
		auto func = cocos2d::CallFuncN::create(CC_CALLBACK_0(ActionWheel::CallBack_RollOver , this ));
		auto seq = cocos2d::Sequence::create(delay,func,nullptr);
		runAction(seq);
	}

}


void ActionWheel::CallBack_RollOver()
{
	if (mState == WheelRoll)
	{
		//
		mBlurWheel->StopRollAnimation();
		mBlurWheel->PlaySlowdownAnimation();
		//
		auto delay = cocos2d::DelayTime::create(3);
		auto func = cocos2d::CallFuncN::create(CC_CALLBACK_0(ActionWheel::CallBack_SlowdownRollOver , this ));
		auto seq = cocos2d::Sequence::create(delay,func,nullptr);
		runAction(seq);
	}
}


void ActionWheel::CallBack_SlowdownRollOver()
{
	if (mState == WheelRoll)
	{
		mState = WheelSlowdown;
		//
		mBlurWheel->StopSlowdownAnimation();
		//
		// 1- 继续开始向下运动
		//
		// 1- 装配新的icon，设置他们的位置
		mCurrentIconIndex = 2;
		mNeedResetIconIndex = 3;
		int iconNum = mWheelIcons.size();
		int moveby_dis = 0;
		for (int i = 0;i<iconNum;++i)
		{
			WheelIcon* icon = mWheelIcons.at(i);
			icon->SetResource(1,mIconIDs[i]);
			//位置是clipperNode上面的位置
			icon->setPosition(mIconBasePos.x, 
				mIconBasePos.y - icon->getContentSize().height * i + icon->getContentSize().height * (iconNum - 1));
			moveby_dis = -icon->getContentSize().height * (iconNum - 1);
			auto moveby = cocos2d::MoveBy::create(mSlowdownTime,cocos2d::Vec2(0,moveby_dis));
			auto eei = cocos2d::EaseOut::create(moveby,2);
			auto func = cocos2d::CallFuncN::create(CC_CALLBACK_0(ActionWheel::CallBack_RandomRollOver , this ));
			auto seq = cocos2d::Sequence::create(eei,func,nullptr);
			icon->runAction(seq);
		}
		//
		auto moveby = cocos2d::MoveBy::create(mSlowdownTime,cocos2d::Vec2(0,moveby_dis));
		auto eei = cocos2d::EaseOut::create(moveby,2);
		auto func = cocos2d::CallFuncN::create(CC_CALLBACK_0(ActionWheel::CallBack_RandomRollOver , this ));
		auto seq = cocos2d::Sequence::create(eei,func,nullptr);
		seq->setTag(BlurWheel::MoveByTag);
		mBlurWheel->runAction(seq);
	}
}


void ActionWheel::CallBack_RandomRollOver()
{
	if (mState == WheelSlowdown)
	{
		// 改变状态,此时数据和画面已经一致了
		//
		mState = WheelIdle;
		//
		mBlurWheel->setVisible(false);
	}
}


int ActionWheel::Pick()
{
	return mIconIDs[mCurrentIconIndex];
}

bool ActionWheel::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto clipper = this->getChildByTag(ActionWheel::ClipperTag);
	cocos2d::Vec2 point = clipper->convertToNodeSpace(cocos2d::Director::getInstance()->convertToGL(touch->getLocationInView()));
	auto rect = GetTouchRect();
	if (rect.containsPoint(point))
	{
		mPickedID = Pick();
		//点亮选择的icon
		WheelIcon* icon = mWheelIcons.at(mCurrentIconIndex);
		icon->TurnOn();

		return true;
	}

	return false;
}

void ActionWheel::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
}

void ActionWheel::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if(mState != WheelIdle) return;
	//已经选中了一个ID
	if (mPickedID != -1)
	{
		//判断释放的位置


		//是否轮盘上还有数量
		auto icon = mWheelIcons.at(mCurrentIconIndex);
		//这里应该有个对数据层的判断
		if (icon->PickOne())
		{
			icon->TurnOff();
			//
			//RollToNextIcon();

			GameActionSystem::GetInstance()->UseAction(mGroupID);
		}
		//
		mPickedID = -1;
	}
}
//
//void ActionWheel::onTouchesBegan( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
//{
//	if(mState != WheelIdle) return;
//	cocos2d::Touch *touch = touches[0];
//	auto clipper = this->getChildByTag(ActionWheel::ClipperTag);
//	cocos2d::Vec2 point = clipper->convertToNodeSpace(cocos2d::Director::getInstance()->convertToGL(touch->getLocationInView()));
//	auto rect = GetTouchRect();
//	if (rect.containsPoint(point))
//	{
//		mPickedID = Pick();
//		//点亮选择的icon
//		WheelIcon* icon = mWheelIcons.at(mCurrentIconIndex);
//		icon->TurnOn();
//	}
//}
//
//void ActionWheel::onTouchesMoved( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
//{
//
//}
//
//void ActionWheel::onTouchesEnded( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
//{
//	if(mState != WheelIdle) return;
//	//已经选中了一个ID
//	if (mPickedID != -1)
//	{
//		//判断释放的位置
//
//
//		//是否轮盘上还有数量
//		auto icon = mWheelIcons.at(mCurrentIconIndex);
//		if (icon->PickOne())
//		{
//			icon->TurnOff();
//			//
//			//RollToNextIcon();
//
//			GameActionSystem::GetInstance()->UseAction(mGroupID);
//		}
//		//
//		mPickedID = -1;
//	}
//}

cocos2d::Rect ActionWheel::GetTouchRect()
{
	WheelIcon* icon = mWheelIcons.at(mCurrentIconIndex);
	float w = icon->getContentSize().width;
	float h = icon->getContentSize().height;
	return cocos2d::Rect(0,icon->getPositionY() - h * 0.5f,w,h);
}


void ActionWheel::AssetIconIDs()
{
	//GameActionSystem::GetInstance()->RollMachine();
	GameActionSystem::GetInstance()->RollRandomGroup(mGroupID);
	//
	mIconIDs[NextNextAction] = GameActionSystem::GetInstance()->GetAction(mGroupID,NextNextAction)->GetIconID();
	mIconIDs[NextAction] = GameActionSystem::GetInstance()->GetAction(mGroupID,NextAction)->GetIconID();
	mIconIDs[CurAction] = GameActionSystem::GetInstance()->GetAction(mGroupID,CurAction)->GetIconID();
	mIconIDs[PreAction] = GameActionSystem::GetInstance()->GetAction(mGroupID,PreAction)->GetIconID();
}


ActionWheel::ActionWheel():
	Layer(),
	mPickedID(-1),
	mCurrentIconIndex(-1),
	mNeedResetIconIndex( -1 ),
	mState(WheelIdle),
	mAccelerateTime(1),
	mRollTime(2),
	mSlowdownTime(1),
	mRollNextIconTime(1),
	mGroupID(-1)
{

}

ActionWheel::~ActionWheel()
{
	mWheelIcons.clear();
}

int ActionWheel::GetState() const
{
	return mState;
}

int ActionWheel::ClipperTag = 0;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

MainControllerPanel::MainControllerPanel()
{

}

MainControllerPanel::~MainControllerPanel()
{

}

void MainControllerPanel::Init()
{
	if(!Layer::init()) return;
	this->autorelease();

	//
	mWheelHandle = cocos2d::Sprite::createWithSpriteFrameName("wheel_handle_normal.png");
	mWheelHandle->setPosition(190,0);
	addChild(mWheelHandle);
	//
	mWheelBoxBtn = cocos2d::ui::Button::create("wheel_handle_normal.png","wheel_handle_hover.png");
	mWheelBoxBtn->setPosition(cocos2d::Vec2(190,0));
	mWheelBoxBtn->addTouchEventListener(CC_CALLBACK_2(MainControllerPanel::touchEvent, this));
	addChild(mWheelBoxBtn);
	//
	mWheelBoxBG = cocos2d::Sprite::createWithSpriteFrameName("wheelbox.png");
	mWheelBoxBG->setPosition(mWheelBoxBG->getContentSize().width / 2,mWheelBoxBG->getContentSize().height / 2);
	addChild(mWheelBoxBG,0);
	//
	//
	for (int i = 0 ;i < WheelsNum;++i)
	{
		ActionWheel* wheel = new ActionWheel();
		wheel->autorelease();
		wheel->setPosition(i * 45,0);
		wheel->SetGroupID(i);
		addChild(wheel,1);
		//
		//
		mWheelList.pushBack(wheel);
	}
	//
	GameActionSystem::GetInstance()->RollMachine();
	//
	const int IconNum = 4;
	for (int i = 0 ;i < mWheelList.size();++i)
	{
		std::vector<int>  ids(IconNum,-1);

		for (int k = 0;k < IconNum;++k)
		{
			auto act = GameActionSystem::GetInstance()->GetAction(i,k);
			ids[k] = act->GetIconID();  // GetIconID()   ?
		}

		mWheelList.at(i)->Init(ids);
		mWheelList.at(i)->SetRollTime(2 + i);
	}
	//



	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(MainControllerPanel::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MainControllerPanel::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainControllerPanel::onTouchEnded, this);
	//mWheelHandle->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

void MainControllerPanel::touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;

	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;

	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			bool canRoll = true;
			//
			for (int i = 0;i< mWheelList.size();++i)
			{
				if(mWheelList.at(i)->GetState() != WheelIdle)
				{
					canRoll = false;
					break;
				}
			}
			//
			if(canRoll)
			{
				for (int i = 0;i< mWheelList.size();++i)
				{
					mWheelList.at(i)->RandomRoll();
				}
			}
		}
		break;

	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;

	default:
		break;
	}
}

void MainControllerPanel::RollAll()
{
	bool canRoll = true;
	//
	for (int i = 0;i< mWheelList.size();++i)
	{
		if(mWheelList.at(i)->GetState() != WheelIdle)
		{
			canRoll = false;
			break;
		}
	}
	//
	if(canRoll)
	{
		for (int i = 0;i< mWheelList.size();++i)
		{
			mWheelList.at(i)->RandomRoll();
		}
	}
}

void MainControllerPanel::RollWheel(int index)
{
	bool canRoll = true;
	//
	for (int i = 0;i< mWheelList.size();++i)
	{
		if(mWheelList.at(i)->GetState() != WheelIdle)
		{
			canRoll = false;
			break;
		}
	}
	//
	if(canRoll)
	{
		for (int i = 0;i< mWheelList.size();++i)
		{
			mWheelList.at(i)->RandomRoll();
		}
	}
}

bool MainControllerPanel::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event)
{
	cocos2d::Vec2 point = mWheelHandle->convertToNodeSpace(cocos2d::Director::getInstance()->convertToGL(touch->getLocationInView()));
	auto rect = GetWheelHandleRect();
	if (rect.containsPoint(point))
	{
		RollAll();

		return true;
	}

	return false;
}
void MainControllerPanel::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event)
{
	;
}
void MainControllerPanel::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event)
{
	;
}

cocos2d::Rect MainControllerPanel::GetWheelHandleRect()
{
	float w = mWheelHandle->getContentSize().width;
	float h = mWheelHandle->getContentSize().height;
	return cocos2d::Rect(0,0,w,h);
}

bool MainControllerPanel::init()
{
	mTouchGroup = Layer::create();
	addChild(mTouchGroup); 
	mLayout = static_cast<Layout*>(CSLoader::createNode("ui/Skill_UI.csb"));
	mTouchGroup->addChild(mLayout);
	//
	ConfigureGUIScene();
	//
	//
	for (int i = 0 ;i < WheelsNum;++i)
	{
		ActionWheel* wheel = new ActionWheel();
		wheel->autorelease();
		//wheel->setPosition(i * 45,0);
		wheel->setPosition(mWheelNodeList.at(i)->getPosition());	
		wheel->SetGroupID(i);
		addChild(wheel,1);
		//
		//
		mWheelList.pushBack(wheel);
	}
	//
	GameActionSystem::GetInstance()->RollMachine();
	//
	const int IconNum = 4;
	for (int i = 0 ;i < mWheelList.size();++i)
	{
		std::vector<int>  ids(IconNum,-1);

		for (int k = 0;k < IconNum;++k)
		{
			auto act = GameActionSystem::GetInstance()->GetAction(i,k);
			ids[k] = act->GetIconID();  // GetIconID()   ?
		}

		mWheelList.at(i)->Init(ids);
		mWheelList.at(i)->SetRollTime(2 + i);
	}
	//



	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(MainControllerPanel::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MainControllerPanel::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainControllerPanel::onTouchEnded, this);
	//mWheelHandle->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void MainControllerPanel::ConfigureGUIScene()
{
	Layout* root = static_cast<Layout*>(mLayout->getChildByName("wheelbox"));

	mWheelBoxBtn = static_cast<Button*>(Helper::seekWidgetByName(root, "wheelhandle"));
	mWheelBoxBtn->addTouchEventListener(CC_CALLBACK_2(MainControllerPanel::touchEvent, this));
	//
	mWheelNodeList.pushBack(static_cast<Node*>(mLayout->getChildByName("wheel_0")));
	mWheelNodeList.pushBack(static_cast<Node*>(mLayout->getChildByName("wheel_1")));
	mWheelNodeList.pushBack(static_cast<Node*>(mLayout->getChildByName("wheel_2")));

	//

	mCoinEnterBtnList.pushBack(static_cast<Button*>(Helper::seekWidgetByName(root,"coin_enter_0")));
	mCoinEnterBtnList.pushBack(static_cast<Button*>(Helper::seekWidgetByName(root,"coin_enter_1")));
	mCoinEnterBtnList.pushBack(static_cast<Button*>(Helper::seekWidgetByName(root,"coin_enter_2")));
	//
	mCoinEnterBtnList.at(0)->addTouchEventListener(CC_CALLBACK_2(MainControllerPanel::CoinEnter_0_TouchEvent, this));
	mCoinEnterBtnList.at(1)->addTouchEventListener(CC_CALLBACK_2(MainControllerPanel::CoinEnter_1_TouchEvent, this));
	mCoinEnterBtnList.at(2)->addTouchEventListener(CC_CALLBACK_2(MainControllerPanel::CoinEnter_2_TouchEvent, this));



}

void MainControllerPanel::CoinEnter_0_TouchEvent( cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type )
{

}

void MainControllerPanel::CoinEnter_1_TouchEvent( cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type )
{

}

void MainControllerPanel::CoinEnter_2_TouchEvent( cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type )
{

}

int MainControllerPanel::WheelsNum = 3;
//////////////////////////////////////////////////////////////////////////
//
//			BlurWheel
//
//////////////////////////////////////////////////////////////////////////

BlurWheel::~BlurWheel()
{

}

bool BlurWheel::initWithTexture( cocos2d::Texture2D* texture, const cocos2d::Rect& rect )
{
	_blurRadiusX = 0;
	_blurSampleNumX = 1;
	_blurRadiusY = 0;
	_blurSampleNumY = 1;
	//
	mAnimation = nullptr;

	if( cocos2d::Sprite::initWithTexture(texture, rect) ) 
	{
#if CC_ENABLE_CACHE_TEXTURE_DATA
		auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
			setGLProgram(nullptr);
			initGLProgram();
		});

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif

		initGLProgram();

		return true;
	}

	return false;
}

void BlurWheel::initGLProgram()
{
	GLchar * fragSource = (GLchar*) cocos2d::String::createWithContentsOfFile(
		cocos2d::FileUtils::getInstance()->fullPathForFilename("Shaders/example_Blur.fsh").c_str())->getCString();  
	auto program = cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert, fragSource);

	auto glProgramState = cocos2d::GLProgramState::getOrCreateWithGLProgram(program);
	setGLProgramState(glProgramState);

	auto size = getTexture()->getContentSizeInPixels();
	getGLProgramState()->setUniformVec2("resolution", size);
	getGLProgramState()->setUniformFloat("XRadius", _blurRadiusX);
	getGLProgramState()->setUniformFloat("YRadius", _blurRadiusY);

	getGLProgramState()->setUniformFloat("sampleNumX", _blurSampleNumX);
	getGLProgramState()->setUniformFloat("sampleNumY", _blurSampleNumY);

}

BlurWheel* BlurWheel::create( const char *SpriteFrameName )
{
	BlurWheel* pRet = new BlurWheel();
	if (pRet && pRet->initWithFile(SpriteFrameName))
	{
		pRet->Init();
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

void BlurWheel::setBlurRadiusX( float radius )
{
	_blurRadiusX = radius;
	getGLProgramState()->setUniformFloat("XRadius", _blurRadiusX);
}

void BlurWheel::setBlurSampleNumX( float num )
{
	_blurSampleNumX = num;
	getGLProgramState()->setUniformFloat("sampleNumX", _blurSampleNumX);
}

void BlurWheel::setBlurRadiusY( float radius )
{
	_blurRadiusY = radius;
	getGLProgramState()->setUniformFloat("YRadius", _blurRadiusY);
}

void BlurWheel::setBlurSampleNumY( float num )
{
	_blurSampleNumY = num;
	getGLProgramState()->setUniformFloat("sampleNumY", _blurSampleNumY);
}

void BlurWheel::Init()
{
	cocos2d::SpriteFrame* sf_0 = cocos2d::SpriteFrame::create("images/item_wheel_0.png",cocos2d::Rect(0,0,35,84));
	cocos2d::SpriteFrame* sf_1 = cocos2d::SpriteFrame::create("images/item_wheel_1.png",cocos2d::Rect(0,0,35,84));
	cocos2d::SpriteFrame* sf_2 = cocos2d::SpriteFrame::create("images/item_wheel_2.png",cocos2d::Rect(0,0,35,84));
	cocos2d::SpriteFrame* sf_3 = cocos2d::SpriteFrame::create("images/item_wheel_3.png",cocos2d::Rect(0,0,35,84));
	cocos2d::SpriteFrame* sf_4 = cocos2d::SpriteFrame::create("images/item_wheel_4.png",cocos2d::Rect(0,0,35,84));
	cocos2d::SpriteFrame* sf_5 = cocos2d::SpriteFrame::create("images/item_wheel_5.png",cocos2d::Rect(0,0,35,84));

	mAnimFrames.pushBack(sf_0);
	mAnimFrames.pushBack(sf_1);
	mAnimFrames.pushBack(sf_2);
	mAnimFrames.pushBack(sf_3);
	mAnimFrames.pushBack(sf_4);
	mAnimFrames.pushBack(sf_5);

}

void BlurWheel::PlayRollAnimation()
{
	//图片闪动
	playWink();
	//此时，继续加速blur
	ValueBy* vb = ValueBy::create(rollTime,maxAccelerateBlur,maxBlur - maxAccelerateBlur,&_blurRadiusY);
	vb->setTag(ValueByTag);
	runAction(vb);
}

void BlurWheel::StopRollAnimation()
{
	stopActionByTag(ValueByTag);
}

void BlurWheel::PlayAccelerateAnimation()
{
	//模糊X
	blurX();
	//差值模糊加速
	ValueBy* vb = ValueBy::create(accelerateTime,0,maxAccelerateBlur,&_blurRadiusY);
	vb->setTag(ValueByTag);
	runAction(vb);
	//开始更新update，用于blur设置
	scheduleUpdate();
}

void BlurWheel::StopAccelerateAnimation()
{
	stopActionByTag(ValueByTag);
}

void BlurWheel::PlaySlowdownAnimation()
{
	ValueBy* vb = ValueBy::create(slowdownTime,maxBlur,-maxBlur,&_blurRadiusY);
	vb->setTag(ValueByTag);
	runAction(vb);
}

void BlurWheel::StopSlowdownAnimation()
{
	stopActionByTag(AnimationTag);
	stopActionByTag(ValueByTag);
	//取消更新update
	unscheduleUpdate();
	//清除X的blur
	clearX();
	//
	mAnimation = nullptr;
}

void BlurWheel::playWink()
{
	if(mAnimation == nullptr)
	{
		auto animation = cocos2d::Animation::createWithSpriteFrames(mAnimFrames, 0.2f);
		auto animate = cocos2d::Animate::create(animation);
		mAnimation = cocos2d::RepeatForever::create(animate);
		mAnimation->setTag(AnimationTag);
	}
	if (getActionByTag(AnimationTag) == nullptr)
	{
		runAction(mAnimation);
	}

}


void BlurWheel::update( float delta )
{
	setBlurRadiusY(_blurRadiusY);
	setBlurSampleNumY(8);

}


void BlurWheel::blurX()
{
	setBlurRadiusX(2);
	setBlurSampleNumX(3);
}

void BlurWheel::clearX()
{
	setBlurRadiusX(0);
	setBlurSampleNumX(1);
}



float BlurWheel::rollTime = 1.2f;

float BlurWheel::slowdownTime = 1.7f;

float BlurWheel::accelerateTime = 0.4f;

int BlurWheel::maxAccelerateBlur = 3.0f;

int BlurWheel::maxBlur = 24;

int BlurWheel::AnimationTag = 1;

int BlurWheel::ValueByTag = 2;

int BlurWheel::MoveByTag = 3;




//////////////////////////////////////////////////////////////////////////
//
//		ValueBy
//
//////////////////////////////////////////////////////////////////////////


ValueBy* ValueBy::create( float duration, float startValue , float deltaValue , float* pValue )
{
	ValueBy *ret = new ValueBy();
	ret->initWithDuration(duration, startValue , deltaValue, pValue);
	ret->autorelease();

	return ret;
}

ValueBy* ValueBy::clone() const 
{
	return nullptr;
}

void ValueBy::startWithTarget( cocos2d::Node *target )
{
	ActionInterval::startWithTarget(target);
	mPreviousValue = mStartValue;
}

void ValueBy::update( float time )
{
	if (_target)
	{
		float currentFloat = *mValue;
		float diff = currentFloat - mPreviousValue;
		mStartValue = mStartValue + diff;
		float newfloat =  mStartValue + (mDeltaValue * time);
		*mValue = newfloat;
		mPreviousValue = newfloat;
	}
}

bool ValueBy::initWithDuration( float duration, float startValue , float deltaValue, float* pValue )
{
	if (ActionInterval::initWithDuration(duration))
	{
		mStartValue = startValue;
		mDeltaValue = deltaValue;
		mValue = pValue;
		return true;
	}

	return false;
}
