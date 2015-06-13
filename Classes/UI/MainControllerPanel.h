/********************************************************************
	created:	2015/06/10
	created:	10:6:2015   12:46
	filename: 	E:\UnknownHero\Classes\UI\MainControllerPanel.h
	file path:	E:\UnknownHero\Classes\UI
	file base:	MainControllerPanel
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef MainControllerPanel_h__
#define MainControllerPanel_h__

#include "cocos2d.h"

enum ActionWheelState
{
	WheelIdle,WheelRollNext,WheelAccelerate,WheelRoll,WheelSlowdown
};
//这个icon的大小是一定的
class WheelIcon : public cocos2d::Sprite
{
public:
	static const std::string  IconDict[];	
	static const std::string  IconDict_HighLight[];	
	static const std::string& GetIconName(int iconID);
	static const std::string& GetIconName_HighLight(int iconID);

public:
	WheelIcon();
	~WheelIcon();
	//
	void Init(int num,int iconID);
	void SetResource(int num,int iconID);
	//如果返回false 说明，已经没有这个icon道具了
	bool PickOne();
	//
	void TurnOn();
	void TurnOff();

protected:
	int  mNum;
	int  mIconID;
	//字体

	//
	cocos2d::SpriteFrame*		pHighlightSpriteFrame;
	cocos2d::SpriteFrame*		pNormalSpriteFrame;

private:
};

class BlurWheel : public cocos2d::Sprite
{
public:
	static int AnimationTag;
	static int ValueByTag;
	static int MoveByTag;
	//
	~BlurWheel();
	bool initWithTexture(cocos2d::Texture2D* texture, const cocos2d::Rect&  rect);
	void initGLProgram();

	static BlurWheel* create(const char *SpriteFrameName);
	void setBlurRadiusX(float radius);
	void setBlurSampleNumX(float num);
	void setBlurRadiusY(float radius);
	void setBlurSampleNumY(float num);

	void Init();
	void virtual update(float delta) override ;

	void PlayAccelerateAnimation();
	void StopAccelerateAnimation();

	void PlayRollAnimation();
	void StopRollAnimation();

	void PlaySlowdownAnimation();
	void StopSlowdownAnimation();

protected:
	float _blurRadiusX;
	float _blurSampleNumX;
	float _blurRadiusY;
	float _blurSampleNumY;

	static int  maxAccelerateBlur;
	static int  maxBlur;

	static float accelerateTime;
	static float slowdownTime;
	static float rollTime;

	//
	cocos2d::RepeatForever*	mAnimation;



	void playWink();
	void blurX();
	void clearX();

	cocos2d::Sequence*	mAccelerate;

	cocos2d::RepeatForever*	mSlowdown;

	//
	cocos2d::Vector<cocos2d::SpriteFrame*> mAnimFrames;



};

class ActionWheel : public cocos2d::Layer
{
public:
	static int ClipperTag;
public:
	ActionWheel();
	~ActionWheel();

	//滚动到下一个
	void  RollToNextIcon();
	void  PlayRollToNextIconAniamtion();
	void  CallBack_RollToNextIcon();
	//随机滚动
	void  RandomRoll();
	void  PlayRandomRollAnimation();
	void  CallBack_AccelerateRollOver();
	void  CallBack_RollOver();
	void  CallBack_SlowdownRollOver();
	void  CallBack_RandomRollOver();

	//
	void  Init();
	void  Init(const std::vector<int>& IconIDs);
	//
	int	  Pick();
	cocos2d::Rect	GetTouchRect();
	/* 监听 */
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

protected:
	//
	float  mAccelerateTime;		//开始加速
	float  mRollTime;			//滚动时间
	float  mSlowdownTime;		//减速
	float  mRollNextIconTime;	//滚动到下一个icon
	//
	int		mState;
	//
	int		mCurrentIconIndex;
	int		mNeedResetIconIndex;
	int		mPickedID;
	//
	// 应该是显示3个 ，但是 应该有4个
	cocos2d::Vector<WheelIcon*>  mWheelIcons;
	std::vector<int>			 mIconIDs;
	cocos2d::Vec2			     mIconBasePos;
	/*  */
	BlurWheel*		mBlurWheel;
	cocos2d::Vec2	mBlurWheelBasePos;

private:
};
/*
	如果是个拉霸 窗口 ，需要的配件有 
	1、拉霸的窗体框架图片   2、金币显示的地方  3、拉动的扳手
	4、 拉霸内部的转盘三个
*/

class MainControllerPanel : public cocos2d::Layer
{
	static int WheelsNum;
public:
	MainControllerPanel();
	~MainControllerPanel();
	//
	void Init();
	cocos2d::Rect	GetWheelHandleRect();
	//
	/* 监听 */
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
protected:
	cocos2d::Vector<ActionWheel*>	mWheelList;	
	cocos2d::Sprite*				mWheelHandle;
private:
};


//////////////////////////////////////////////////////////////////////////
//
////

class ValueBy : public cocos2d::ActionInterval
{
public:
	/** creates the action */
	static ValueBy* create(float duration, float startValue , float deltaValue , float* pValue);

	//
	// Overrides
	//
	virtual ValueBy* clone() const override;
	virtual void startWithTarget(cocos2d::Node *target) override;
	virtual void update(float time) override;

protected:
	ValueBy() {}
	virtual ~ValueBy() {}

	/** initializes the action */
	bool initWithDuration(float duration, float startValue ,float deltaValue, float* pValue);

protected:
	float*		mValue;
	float		mDeltaValue;
	float		mPreviousValue;
	float		mStartValue;


private:
	ValueBy(const ValueBy &); 
	ValueBy &operator =(const ValueBy &);
};

#endif // MainControllerPanel_h__
