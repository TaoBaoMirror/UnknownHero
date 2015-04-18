/********************************************************************
	created:	2015/03/14
	created:	14:3:2015   13:19
	filename: 	E:\cyvasse\TestAI\AttackData.h
	file path:	E:\cyvasse\TestAI
	file base:	AttackData
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef AttackData_h__
#define AttackData_h__



struct AttackDataBase
{ 
public:
	AttackDataBase();
	int		ID;					//ID
	int		AtkType;			//攻击类型

	int		AttackPt;			//最大攻击力
	int		CritPt;				//暴击值
	float   CritRate;			//暴击率
	int		SputteringRadius;	//溅射范围
	float   SputteringFallout;	//溅射衰减
	//
	bool	HasEmitter;			//是否有发射器
};

struct AttackData : public AttackDataBase
{
public:
	AttackData();
	AttackData(const AttackDataBase& ADB,int P_Id,int B_Id);
	int		ProviderID;			//提供伤害的SoldierID
	int		BearerID;			//承受伤害的SoldierID
};

#endif // AttackData_h__
