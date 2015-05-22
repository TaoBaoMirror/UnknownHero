/********************************************************************
	created:	2015/05/21
	created:	21:5:2015   10:36
	filename: 	E:\UnknownHero\Classes\Game\BulletSystem.h
	file path:	E:\UnknownHero\Classes\Game
	file base:	BulletSystem
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef BulletSystem_h__
#define BulletSystem_h__

#include <string>
#include <vector>
#include <map>
#include <hash_map>

#include "Vector2D.h"

class AttackData;

class BulletData
{
public:
	int				mId;						//
	int				mAliveRoundNum;				//�����Ļغ���,������������������
	int				mSpeed;						//�����ٶ�
	char			mBulletSpriteName[32];		//�ӵ�����ͼ������
	int				mNormalFrameNum;			//֡��
	char			mBulletExplodeName[32];
	int				mExplodeFrameNum;
	//
	bool			mHitIfCollide;

	
};

class BulletBase
{
public:
	~BulletBase();
	//
	virtual void Init(int bullet_data_id , AttackData* pAtkData);
	virtual void StepRound();
	bool IsAlive(){return mAlive;}
	//
	virtual void OnEmitStart(){}
	virtual void OnFly(){}
	virtual void OnArriveDestination(){}
	virtual void OnHit(){}
	//
	virtual void OnDestroy(){}
	//
	const BulletData*	GetBulletData(){return mBulletDataPtr;}
	const AttackData*	GetAttackData(){return mAttackDataPtr;}

protected:
	bool				mAlive;
	int					mRoundCounter;
	const BulletData*	mBulletDataPtr;
	const AttackData*	mAttackDataPtr;
	BulletBase();


private:
};

class BulletDataManager
{
	static BulletDataManager* instance;
public:
	static BulletDataManager* GetInstance();
	~BulletDataManager();
	//
	void ReadCSV(std::string& csvName);
	void FreeAll();
	//
	bool	GetBulletData(int Id,const BulletData* BData) const;
protected:
	std::string		mCSVFile;
	BulletDataManager();
	//�������� ʵ�壬ע��
	std::hash_map<int,BulletData>	BulletDataDict;
private:
};

#endif // BulletSystem_h__
