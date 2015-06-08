/********************************************************************
	created:	2015/06/06
	created:	6:6:2015   23:18
	filename: 	E:\UnknownHero\Classes\Game\Trigger\GameTrigger.h
	file path:	E:\UnknownHero\Classes\Game\Trigger
	file base:	GameTrigger
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef GameTrigger_h__
#define GameTrigger_h__

#include "cocos2d.h"
#include "TriggerBase.h"

class Soldier;
class MapNodeData;

class GameTrigger : public TriggerBase ,public cocos2d::Sprite
{
	friend class TriggerManager;
public:
	GameTrigger();
	~GameTrigger();
	//
	virtual void Init(const TriggerData* TD, const GridPos& Pos,ChunkMap* Chunk);

	void SetResource(const std::string& NormalName,const std::string& ExplodeName);

	void PlayNormalAnimation();
	void PlayExplodeAnimation();

	virtual void Born() override;
	virtual void Sleep() override;
	virtual void Awake() override;

protected:
	std::map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>> m_framesDict;
	Soldier*	mOwner;
	//
	//
	virtual void EnterTrigger(Soldier*		soldier){}
	virtual void InsideTrigger(Soldier*		soldier){}
	virtual void ExitTrigger(Soldier*		soldier){}

	virtual void OnDestory();
	//
	virtual void UpdateTriggerRound(){}
	virtual void UpdateTriggerFrame(float dt){}

private:

};


class TriggerManager
{
public:
	static TriggerManager* GetInstance()
	{
		static TriggerManager T;
		return &T;
	}
	~TriggerManager();
	//
public:
	void ReleaseAllTrigger();
	void RemoveTrigger(GameTrigger* trigger);
	GameTrigger* CreateTrigger(Soldier* owner,int triggerType ,const GridPos& GPos);
	GameTrigger* GetTrigger(int triggerID);
	//
	void Update(float dt);
	//每一个单位移动之后，都要判断
	void UpdateRound();
	//
protected:
	TriggerManager();
	//
	std::list<GameTrigger*>	TriggerPool;
	//
	int		NextID;

private:
};



//////////////////////////////////////////////////////////////////////////
//
//		**************Other Trigger********************
//
//////////////////////////////////////////////////////////////////////////

class Poison_GameTrigger : public GameTrigger
{
public:
	Poison_GameTrigger(){}
	~Poison_GameTrigger(){}
protected:
	virtual void EnterTrigger(Soldier*		soldier) override;
	virtual void InsideTrigger(Soldier*		soldier) override {}
	virtual void ExitTrigger(Soldier*		soldier) override {}
	//
	virtual void UpdateTriggerRound() override {}
	virtual void UpdateTriggerFrame(float dt) override {}
private:
};


#endif // GameTrigger_h__
