#include "MainControllerPanel.h"
//

const std::string WheelIcon::IconDict[4] = { "rateme_normal.png" , "sound_normal.png" , "help_normal.png" ,"help_hover.png"};


const std::string& WheelIcon::GetIconName( int iconID )
{
	return IconDict[iconID];
}



//
WheelIcon::WheelIcon()
{

}

WheelIcon::~WheelIcon()
{

}


void WheelIcon::SetResource( int num,int iconID )
{
	initWithSpriteFrameName(WheelIcon::GetIconName(iconID));
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

bool WheelIcon::PickOne()
{
	return (mNum--) > 0;
}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void ActionWheel::Init()
{
	int a[4]={0,1,2,3};  
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
	//����һ�� clipperNode
	auto clipper = cocos2d::ClippingNode::create();
	clipper->setTag( ActionWheel::ClipperTag );
	clipper->setContentSize(  cocos2d::Size(SFrame->getRect().size.width, SFrame->getRect().size.height * ShowIconNum) );
	clipper->setAnchorPoint(  cocos2d::Vec2( 0.5,0.5 ) );
	clipper->setPosition( 0,0 );
	this->addChild(clipper);
	//�����ɰ�
	auto stencil = cocos2d::DrawNode::create();
	cocos2d::Vec2 rectangle[4];
	rectangle[0] = cocos2d::Vec2(0, 0);
	rectangle[1] = cocos2d::Vec2(clipper->getContentSize().width, 0);
	rectangle[2] = cocos2d::Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
	rectangle[3] = cocos2d::Vec2(0, clipper->getContentSize().height);
	cocos2d::Color4F white(1, 1, 1, 1);
	stencil->drawPolygon(rectangle, 4, white, 1, white);
	clipper->setStencil(stencil);

	//���ݺ�IconsID
	mIconIDs = IconIDs;
	//icon ������Ϊ ��󣬺��֣�ǰ
	//				0 , 1 , 2 , 3
	mCurrentIconIndex = 2;
	mNeedResetIconIndex = 3;
	//
	int wheelIconNum = IconIDs.size();  //must be 4
	for (int i = 0;i<wheelIconNum;++i)
	{
		WheelIcon* icon = new WheelIcon();
		icon->Init(1,IconIDs[i]);
		//λ����clipperNode�����λ��
		icon->setPosition(mIconBasePos.x, mIconBasePos.y - icon->getContentSize().height * i);
		mWheelIcons.pushBack(icon);
		clipper->addChild(icon);
	}
	//////////////
	//		����һ���¼�����
	/////////////
	auto listener = cocos2d::EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(ActionWheel::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(ActionWheel::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(ActionWheel::onTouchesEnded, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, -11);

}

void ActionWheel::RollToNextIcon()
{
	// �жϵ�ǰ״̬�Ƿ�����˶�
	if (mState != WheelIdle)
	{
		return;
	}
	// �ı�״̬
	mState = WheelRollNext;
	// iconID �Ѿ��������,next next icon ����õ��µ�iconID,���ݲ���
	mCurrentIconIndex--;
	if(mCurrentIconIndex == -1) mCurrentIconIndex = 3;

	// ��������ת���Ķ���
	PlayRollToNextIconAniamtion();
}

void ActionWheel::PlayRollToNextIconAniamtion()
{
	//�����˶�
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
	// �ı�״̬,��ʱ���ݺͻ����Ѿ�һ����
	if(mState == WheelRollNext)
	{
		mState = WheelIdle;
		// ��������֮ǰλ�õ�icon���õ����Ϸ�,���������ڶ���ǰ�����iconID
		WheelIcon* icon = mWheelIcons.at(mNeedResetIconIndex);
		//
		icon->setPosition(mIconBasePos);
		//
		int iconID = cocos2d::random(0,3);
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
	// �жϵ�ǰ״̬�Ƿ�����˶�

	// �ı�״̬

	// ���е�iconID�Ѿ�����Ok

	// ���Ŷ���
}

void ActionWheel::PlayRandomRollAnimation()
{
	// 1- ��ʼ�����˶�

	// 2- ģ��һ��ʱ��

	// 3- ����ģ��,��ʼ����,Ȼ��ֹͣ
}

void ActionWheel::CallBack_RandomRollAnimation()
{
	// �ı�״̬,��ʱ���ݺͻ����Ѿ�һ����
}

int ActionWheel::Pick()
{
	return mIconIDs[mCurrentIconIndex];
}

void ActionWheel::onTouchesBegan( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
{
	if(mState != WheelIdle) return;
	cocos2d::Touch *touch = touches[0];
	auto clipper = this->getChildByTag(ActionWheel::ClipperTag);
	cocos2d::Vec2 point = clipper->convertToNodeSpace(cocos2d::Director::getInstance()->convertToGL(touch->getLocationInView()));
	auto rect = GetTouchRect();
	if (rect.containsPoint(point))
	{
		mPickedID = Pick();
	}
}

void ActionWheel::onTouchesMoved( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
{

}

void ActionWheel::onTouchesEnded( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
{
	if(mState != WheelIdle) return;
	//�Ѿ�ѡ����һ��ID
	if (mPickedID != -1)
	{
		//�ж��ͷŵ�λ��


		//�Ƿ������ϻ�������
		auto wheel = mWheelIcons.at(mCurrentIconIndex);
		if (wheel->PickOne())
		{
			RollToNextIcon();
		}
		//
		mPickedID = -1;
	}
}

cocos2d::Rect ActionWheel::GetTouchRect()
{
	WheelIcon* icon = mWheelIcons.at(mCurrentIconIndex);
	float w = icon->getContentSize().width;
	float h = icon->getContentSize().height;
	return cocos2d::Rect(0,icon->getPositionY() - h * 0.5f,w,h);
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
	mRollNextIconTime(1)
{

}

ActionWheel::~ActionWheel()
{

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
	ActionWheel* wheel = new ActionWheel();
	wheel->Init();
	wheel->autorelease();
	addChild(wheel);
	//
	auto listener = cocos2d::EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(MainControllerPanel::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(MainControllerPanel::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(MainControllerPanel::onTouchesEnded, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, -12);

}

void MainControllerPanel::onTouchesBegan( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
{

}

void MainControllerPanel::onTouchesMoved( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
{

}

void MainControllerPanel::onTouchesEnded( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
{

}
