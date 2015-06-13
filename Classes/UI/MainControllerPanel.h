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
//���icon�Ĵ�С��һ����
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
	//�������false ˵�����Ѿ�û�����icon������
	bool PickOne();
	//
	void TurnOn();
	void TurnOff();

protected:
	int  mNum;
	int  mIconID;
	//����

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

	//��������һ��
	void  RollToNextIcon();
	void  PlayRollToNextIconAniamtion();
	void  CallBack_RollToNextIcon();
	//�������
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
	/* ���� */
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

protected:
	//
	float  mAccelerateTime;		//��ʼ����
	float  mRollTime;			//����ʱ��
	float  mSlowdownTime;		//����
	float  mRollNextIconTime;	//��������һ��icon
	//
	int		mState;
	//
	int		mCurrentIconIndex;
	int		mNeedResetIconIndex;
	int		mPickedID;
	//
	// Ӧ������ʾ3�� ������ Ӧ����4��
	cocos2d::Vector<WheelIcon*>  mWheelIcons;
	std::vector<int>			 mIconIDs;
	cocos2d::Vec2			     mIconBasePos;
	/*  */
	BlurWheel*		mBlurWheel;
	cocos2d::Vec2	mBlurWheelBasePos;

private:
};
/*
	����Ǹ����� ���� ����Ҫ������� 
	1�����ԵĴ�����ͼƬ   2�������ʾ�ĵط�  3�������İ���
	4�� �����ڲ���ת������
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
	/* ���� */
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
