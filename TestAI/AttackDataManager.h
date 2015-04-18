/********************************************************************
	created:	2015/03/14
	created:	14:3:2015   14:21
	filename: 	E:\cyvasse\TestAI\AttackDataManager.h
	file path:	E:\cyvasse\TestAI
	file base:	AttackDataManager
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef AttackDataManager_h__
#define AttackDataManager_h__

#include <hash_map>

struct AttackDataBase;

class AttackDataManager
{
public:
	static AttackDataManager* Instance();
	//
	void Init();
	void Release();
	//
	void Load();
	//
	bool	GetAttackData(int id , AttackDataBase& data) const ;

protected:
	std::hash_map<int,AttackDataBase>	AttackDataDict;
private:
	AttackDataManager();
	~AttackDataManager();
};

#endif // AttackDataManager_h__
