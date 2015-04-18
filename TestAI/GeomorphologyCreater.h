/********************************************************************
	created:	2015/03/07
	created:	7:3:2015   9:31
	filename: 	E:\cyvasse\TestAI\GeomorphologyCreater.h
	file path:	E:\cyvasse\TestAI
	file base:	GeomorphologyCreater
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef GeomorphologyCreater_h__
#define GeomorphologyCreater_h__

#include "GridSceneMap.h"
#include <map>
#include <vector>

enum GeomorphologyKeyIndex
{
	GKI_NULL = 0,//保留位置
	GKI_DOOR = 1,
	GKI_PLAYERBORN,
	GKI_SHOP,
	GKI_ENEMYBORN,
	GKI_NUM
};
//
//	地貌图块
//
class GeomorphologyField
{
public: 
	GeomorphologyField();
	~GeomorphologyField();
	//
	virtual void  Create();
	virtual void  Load();
	virtual void  Save();	
	//
	const std::vector<int>& GetResourceDatas() const {return ResourceDatas;}
	const std::vector<int>& GetFieldDatas() const {return FieldDatas;}
	//
	const int GetWidthSize()const{return WidthSize;}
	const int GetHightSize()const{return HightSize;}
	//
	const int GetResourceData(const GridPos& GPos) const ;
	const int GetFieldData(const GridPos& GPos) const ;


protected:
	int WidthSize;
	int HightSize;
	//数据内容，和资源内容是分开的~
	std::vector<int>	FieldDatas;
	std::vector<int>	ResourceDatas;
	//
	const int GPosToIndex(const GridPos& GPos)const;
};
//
//	地貌生成描述信息
//
class GeomorphologyDisc
{
	friend class GeomorphologyCreater;
public:
	typedef GridPos IntRange;

	GeomorphologyDisc():EnemyNum(0),UnwalkableNum(0)
	{
		NeedToCreateKeyList.reserve(GeomorphologyKeyIndex::GKI_NUM);
		SpecialUpperLimits.reserve(GeomorphologyKeyIndex::GKI_NUM);
		SpecialLowerLimits.reserve(GeomorphologyKeyIndex::GKI_NUM);

	}
	//
	void AddSpecialKey(GeomorphologyKeyIndex key,const IntRange& lowerLimit,const IntRange& upperLimit)
	{
		NeedToCreateKeyList.push_back(key);
		SpecialUpperLimits.push_back(upperLimit);
		SpecialLowerLimits.push_back(lowerLimit);

	}
	void SetEnemyNum(int n)
	{
		EnemyNum = n;
		//SpecialKeyNodeIDMap[GKI_ENEMYBORN].reserve(n);
	}
	void SetPlayerNum(int n)
	{
		PlayerNum = n;
		//SpecialKeyNodeIDMap[GKI_PLAYERBORN].reserve(n);
	}
	void SetUnwalkableNum(int n){UnwalkableNum = n;}

	//
	int GetEnemyNum(){return EnemyNum;}
	int	GetPlayerNum(){return PlayerNum;}
	int GetUnwalkableNum(){return UnwalkableNum;}

protected:
	int											EnemyNum;		//敌人的数量
	int											PlayerNum;
	int											UnwalkableNum;	//不可走路点的数量
	//
	//
	//std::vector<int>							EnemySpawnNodeIDList;		//敌人出生位置
	//
	std::vector<GeomorphologyKeyIndex>			NeedToCreateKeyList;	//哪些特殊点需要生成
	std::vector<IntRange>								SpecialUpperLimits;		//GPos随机位置的上限
	std::vector<IntRange>								SpecialLowerLimits;		//GPos随机位置下限
	std::map<GeomorphologyKeyIndex,std::vector<int> >	SpecialKeyNodeIDMap;   //特殊点的GPos

	//
public: 
	void CopyFromSpecialKeyNodeIDMap(std::map<GeomorphologyKeyIndex,std::vector<int> >& m)
	{
		m = SpecialKeyNodeIDMap;
	}
	//
};

//
//	地貌生成器
//
class GeomorphologyCreater
{
public:
	GeomorphologyCreater(GridSceneMap* gridSceneMap);
	~GeomorphologyCreater();
	//生成地貌
	virtual void CreateGeomorphology(GeomorphologyDisc& disc);
	//
	bool CanPasteField(const GeomorphologyField& field,const GridPos& GPos);
	//
	void PasteField(const GeomorphologyField& field,const GridPos& GPos);
	//
	void CreateBornPos(int PosType,int num ,const std::vector<int>& unwalkables,GeomorphologyDisc& disc);
protected:
	GridSceneMap*	m_pGridSceneMap;
private:
};

#endif // GeomorphologyCreater_h__
