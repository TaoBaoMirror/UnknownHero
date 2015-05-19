#include "AttackData.h"

AttackDataBase::AttackDataBase()
	:	ID(-1),
		AttackPt(1),		//最大攻击力
		CritPt(1),				//暴击值
		CritRate(0.5f),			//暴击率
		SputteringRadius(1),	//溅射范围
		SputteringFallout(1),	//溅射衰减
		SputteringType(1),
		AtkType(0),				//攻击类型
		HasEmitter(false)		//
{

}
//////////////////////////////////////////////////////////////////////////

AttackData::AttackData()
	:AttackDataBase(),		
	ProviderID(-1),			//提供伤害的SoldierID
	BearerID(-1)		//承受伤害的SoldierID
{

}

AttackData::AttackData( const AttackDataBase& ADB,int P_Id,int B_Id )
	:AttackDataBase(ADB),ProviderID(P_Id),BearerID(B_Id)
{
	TargetGPos.SetTo(-1,-1);
}

AttackData::AttackData( const AttackDataBase& ADB,int P_Id,const GridPos& GPos )
	:AttackDataBase(ADB),ProviderID(P_Id),TargetGPos(GPos)
{
	BearerID = -1;
}
//
//
//
DamageData::DamageData( int damage,int P_Id,int B_Id )
	:ProviderID(P_Id),BearerID(B_Id),DamagePt(damage)
{

}
