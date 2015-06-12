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
	static const std::string& GetIconName(int iconID);
public:
	WheelIcon();
	~WheelIcon();
	//
	void Init(int num,int iconID);
	void SetResource(int num,int iconID);
	//�������false ˵�����Ѿ�û�����icon������
	bool PickOne();

protected:
	int  mNum;
	int  mIconID;
	//����

private:
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
	void  CallBack_RandomRollAnimation();
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

private:
};
/*
	����Ǹ����� ���� ����Ҫ������� 
	1�����ԵĴ�����ͼƬ   2�������ʾ�ĵط�  3�������İ���
	4�� �����ڲ���ת������
*/

class MainControllerPanel : public cocos2d::Layer
{
public:
	MainControllerPanel();
	~MainControllerPanel();
	//
	void Init();
	//
	/* ���� */
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
protected:
	
private:
};

#endif // MainControllerPanel_h__
