/********************************************************************
	created:	2015/06/06
	created:	6:6:2015   0:06
	filename: 	E:\UnknownHero\Classes\Game\Trigger\TriggerBase.h
	file path:	E:\UnknownHero\Classes\Game\Trigger
	file base:	TriggerBase
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef TriggerBase_h__
#define TriggerBase_h__

#include <hash_map>

#include "Game/GridPosArea.h"
#include "Game/Soldier.h"
#include "Game/ChunkMap.h"

enum TriggerState
{
	TriggerBorn,TriggerActive,TriggerDestory,TriggerSleep,
};

class TriggerData
{
public:
	int mID;
	int mType;
	int mW;
	int mH;
	//
	char	mTriggerNormalTex[32];
	int		mNormalAnimationFrameNum;
	char	mTriggerExplodeTex[32];
	int		mExplodeAnimationFrameNum;


};

class TriggerDataManager
{
	static TriggerDataManager* instance;
public:
	static TriggerDataManager* GetInstance();
	~TriggerDataManager();
	//
	void ReadCSV(const std::string& csvName);
	void FreeAll();
	//
	bool	GetTriggerData(int Id,const TriggerData*& BData) const;
protected:
	std::string		mCSVFile;
	TriggerDataManager();
	//里面存的是 实体，注意
	std::hash_map<int,TriggerData>	TriggerDataDict;
private:
};

class TriggerManager;

class TriggerBase : public GridPosArea
{
	friend class TriggerManager;
public:
	TriggerBase();
	~TriggerBase();
	//
	virtual void Init(const TriggerData* TD, const GridPos& Pos,ChunkMap* Chunk);
	//
	virtual void Born(){}

	virtual void Sleep(){}
	virtual void Awake(){}


protected:
	bool			mActive;
	Soldier*		mCollideCreature;
	int				mState;					//TriggerState
	int				mID;
	const TriggerData*	mTriggerData;
	//
	virtual void EnterTrigger(Soldier*		soldier){}
	virtual void InsideTrigger(Soldier*		soldier){}
	virtual void ExitTrigger(Soldier*		soldier){}

	virtual void OnDestory(){}
	//
	virtual void UpdateTriggerRound(){}
	virtual void UpdateTriggerFrame(float dt){}

private:
};



#endif // TriggerBase_h__
