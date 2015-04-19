#include "AttackData.h"

AttackDataBase::AttackDataBase()
	:	ID(-1),
		AttackPt(0),		//最大攻击力
		CritPt(0),				//暴击值
		CritRate(0),			//暴击率
		SputteringRadius(0),	//溅射范围
		SputteringFallout(1),	//溅射衰减
		AtkType(0),				//攻击类型
		HasEmitter(false)		//
{

}
//////////////////////////////////////////////////////////////////////////

AttackData::AttackData()
	:AttackDataBase(),		
	ProviderID(-1),			//提供伤害的SoldierID
	BearerID(-1)			//承受伤害的SoldierID
{

}

AttackData::AttackData( const AttackDataBase& ADB,int P_Id,int B_Id )
	:AttackDataBase(ADB),ProviderID(P_Id),BearerID(B_Id)
{
	
}
