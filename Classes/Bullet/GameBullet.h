/********************************************************************
	created:	2015/05/21
	created:	21:5:2015   16:59
	filename: 	E:\UnknownHero\Classes\Bullet\GameBullet.h
	file path:	E:\UnknownHero\Classes\Bullet
	file base:	GameBullet
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef GameBullet_h__
#define GameBullet_h__

#include "Game/BulletSystem.h"
#include <cocos2d.h>

class MapNodeData;
class GameBullet : public BulletBase , public cocos2d::Sprite
{
public:

	~GameBullet();
	//
	virtual void Init(int bullet_data_id,AttackData* pAtkData) override;
	//����������ʱ��
	virtual void OnEmitStart()override;
	//ÿ֡ѭ��ִ��OnFly,����� �������˵ĸ��� �ͳ��� ,ײ����������ڵ�ʿ��
	virtual void OnFly()override;
	//����Ŀ�ĵ�
	virtual void OnArriveDestination()override;
	//������ը��
	virtual void OnHit() override;
	//�ӵ�����ִ��
	virtual void OnDestroy()override;
	//
	void PlayFlyAnimation();
	void PlayExplodeAnimation();
	// ÿһ�غ�ִ��
	virtual void UpdateRound();
	//�����ӵ�
	void Destroy();
	//����,�����յ�
	bool Emit(const cocos2d::Vec2& start,const cocos2d::Vec2& end);
	//������Դ
	void SetResource(const std::string& ani_name,const std::string& explode_name);
	//
	MapNodeData*	GetMapNodeDataWhereExploded();
protected:
	std::map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>> m_framesDict;
	//
	GameBullet();




private:
};

#endif // GameBullet_h__
