/********************************************************************
	created:	2015/03/14
	created:	14:3:2015   15:36
	filename: 	E:\cyvasse\TestAI\ShieldDataManager.h
	file path:	E:\cyvasse\TestAI
	file base:	ShieldDataManager
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef ShieldDataManager_h__
#define ShieldDataManager_h__

#include <hash_map>

struct ShieldDataBase;

class ShieldDataManager
{
public:
	static ShieldDataManager* Instance();
	//
	void Init();
	void Release();
	//
	void Load();
	//
	bool	GetShieldData(int id , ShieldDataBase& data) const ;
protected:
	std::hash_map<int,ShieldDataBase>	ShieldDataDict;	
private:
	ShieldDataManager();
	~ShieldDataManager();
};

#endif // ShieldDataManager_h__
