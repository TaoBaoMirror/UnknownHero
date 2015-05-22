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
	//发射启动的时候
	virtual void OnEmitStart()override;
	//每帧循环执行OnFly,这个是 遇到敌人的格子 就出发 ,撞击这个格子内的士兵
	virtual void OnFly()override;
	//到达目的地
	virtual void OnArriveDestination()override;
	//触发爆炸了
	virtual void OnHit() override;
	//子弹销毁执行
	virtual void OnDestroy()override;
	//
	void PlayFlyAnimation();
	void PlayExplodeAnimation();
	// 每一回合执行
	virtual void UpdateRound();
	//销毁子弹
	void Destroy();
	//发射,起点和终点
	bool Emit(const cocos2d::Vec2& start,const cocos2d::Vec2& end);
	//设置资源
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
