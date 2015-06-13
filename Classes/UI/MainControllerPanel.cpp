#include "MainControllerPanel.h"
//

const std::string WheelIcon::IconDict[3] = { "rateme_normal.png" , "sound_normal.png" , "help_normal.png"};
const std::string WheelIcon::IconDict_HighLight[3] = { "rateme_hover.png" , "sound_hover.png" , "help_hover.png"};



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
	auto listener = cocos2d::EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(ActionWheel::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(ActionWheel::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(ActionWheel::onTouchesEnded, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, -11);
	//////////////////////////////////////////////////////////////////////////
	mBlurWheel = BlurWheel::create("images/wheel_0.png");
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
	mState = WheelRoll;
	// 所有的iconID已经设置Ok
	int a[4]={0,1,2,0};  
	mIconIDs.assign(a,a+4);
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
		icon->runAction(eei);
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
	// 1- 装配新的icon，设置他们的位置
	mCurrentIconIndex = 2;
	mNeedResetIconIndex = 3;
	//
	int iconNum = mWheelIcons.size();
	for (int i = 0;i<iconNum;++i)
	{
		WheelIcon* icon = mWheelIcons.at(i);
		icon->SetResource(1,mIconIDs[i]);
		//位置是clipperNode上面的位置
		icon->setPosition(mIconBasePos.x, 
			mIconBasePos.y - icon->getContentSize().height * i + icon->getContentSize().height * (iconNum - 1));
	}
	// 2- 模糊一段时间
	mBlurWheel->StopAccelerateAnimation();
	mBlurWheel->PlayRollAnimation();
	auto delay = cocos2d::DelayTime::create(mRollTime);
	auto func = cocos2d::CallFuncN::create(CC_CALLBACK_0(ActionWheel::CallBack_RollOver , this ));
	auto seq = cocos2d::Sequence::create(delay,func,nullptr);
	runAction(seq);
}


void ActionWheel::CallBack_RollOver()
{
	mBlurWheel->StopRollAnimation();
	mBlurWheel->PlaySlowdownAnimation();
	//
	auto delay = cocos2d::DelayTime::create(3);
	auto func = cocos2d::CallFuncN::create(CC_CALLBACK_0(ActionWheel::CallBack_SlowdownRollOver , this ));
	auto seq = cocos2d::Sequence::create(delay,func,nullptr);
	runAction(seq);
}


void ActionWheel::CallBack_SlowdownRollOver()
{
	mBlurWheel->StopSlowdownAnimation();
	//
	// 1- 继续开始向下运动
	//
	int iconNum = mWheelIcons.size();
	int moveby_dis = 0;
	for (int i = 0;i<iconNum;++i)
	{
		WheelIcon* icon = mWheelIcons.at(i);
		moveby_dis = -icon->getContentSize().height * (iconNum - 1);
		auto moveby = cocos2d::MoveBy::create(mSlowdownTime,cocos2d::Vec2(0,moveby_dis));
		auto eei = cocos2d::EaseOut::create(moveby,2);
		icon->runAction(eei);
	}
	//
	auto moveby = cocos2d::MoveBy::create(mSlowdownTime,cocos2d::Vec2(0,moveby_dis));
	auto eei = cocos2d::EaseOut::create(moveby,2);
	auto func = cocos2d::CallFuncN::create(CC_CALLBACK_0(ActionWheel::CallBack_RandomRollOver , this ));
	auto seq = cocos2d::Sequence::create(eei,func,nullptr);
	seq->setTag(BlurWheel::MoveByTag);
	mBlurWheel->runAction(seq);
}


void ActionWheel::CallBack_RandomRollOver()
{
	if (mState == WheelRoll)
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
		//点亮选择的icon
		WheelIcon* icon = mWheelIcons.at(mCurrentIconIndex);
		icon->TurnOn();
	}
}

void ActionWheel::onTouchesMoved( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
{

}

void ActionWheel::onTouchesEnded( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
{
	if(mState != WheelIdle) return;
	//已经选中了一个ID
	if (mPickedID != -1)
	{
		//判断释放的位置


		//是否轮盘上还有数量
		auto icon = mWheelIcons.at(mCurrentIconIndex);
		if (icon->PickOne())
		{
			icon->TurnOff();
			//
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
	mWheelIcons.clear();
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
	for (int i = 0 ;i < WheelsNum;++i)
	{
		ActionWheel* wheel = new ActionWheel();
		wheel->Init();
		wheel->autorelease();
		wheel->setPosition(i * 60,0);
		addChild(wheel);
		//
		mWheelList.pushBack(wheel);
	}
	//
	mWheelHandle = cocos2d::Sprite::createWithSpriteFrameName("play_normal.png");
	mWheelHandle->setPosition(190,0);
	addChild(mWheelHandle);
	//
	auto listener = cocos2d::EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(MainControllerPanel::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(MainControllerPanel::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(MainControllerPanel::onTouchesEnded, this);
	mWheelHandle->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

void MainControllerPanel::onTouchesBegan( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
{
	cocos2d::Touch *touch = touches[0];
	cocos2d::Vec2 point = mWheelHandle->convertToNodeSpace(cocos2d::Director::getInstance()->convertToGL(touch->getLocationInView()));
	auto rect = GetWheelHandleRect();
	if (rect.containsPoint(point))
	{
		for (int i = 0;i< mWheelList.size();++i)
		{
			mWheelList.at(i)->RandomRoll();
		}	
	}
}

void MainControllerPanel::onTouchesMoved( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
{

}

void MainControllerPanel::onTouchesEnded( const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event )
{

}

cocos2d::Rect MainControllerPanel::GetWheelHandleRect()
{
	float w = mWheelHandle->getContentSize().width;
	float h = mWheelHandle->getContentSize().height;
	return cocos2d::Rect(0,0,w,h);
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
	cocos2d::SpriteFrame* sf_0 = cocos2d::SpriteFrame::create("images/wheel_0.png",cocos2d::Rect(0,0,42,129));
	cocos2d::SpriteFrame* sf_1 = cocos2d::SpriteFrame::create("images/wheel_1.png",cocos2d::Rect(0,0,42,129));
	cocos2d::SpriteFrame* sf_2 = cocos2d::SpriteFrame::create("images/wheel_2.png",cocos2d::Rect(0,0,42,129));
	//
	mAnimFrames.reserve(3);
	mAnimFrames.pushBack(sf_0);
	mAnimFrames.pushBack(sf_1);
	mAnimFrames.pushBack(sf_2);
}

void BlurWheel::PlayRollAnimation()
{
	//图片闪动
	playWink();
	//此时，继续加速blur
	ValueBy* vb = ValueBy::create(rollTime,maxAccelerateBlur,maxBlur - maxAccelerateBlur,&_blurRadiusY);
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
	setBlurSampleNumY(6);

}


void BlurWheel::blurX()
{
	setBlurRadiusX(3);
	setBlurSampleNumX(6);
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

int BlurWheel::maxBlur = 11;

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
