#include "AttackData.h"

AttackDataBase::AttackDataBase()
	:	ID(-1),
		AttackPt(1),		//��󹥻���
		CritPt(1),				//����ֵ
		CritRate(0.5f),			//������
		SputteringRadius(1),	//���䷶Χ
		SputteringFallout(1),	//����˥��
		SputteringType(1),
		AtkType(0),				//��������
		HasEmitter(false)		//
{

}
//////////////////////////////////////////////////////////////////////////

AttackData::AttackData()
	:AttackDataBase(),		
	ProviderID(-1),			//�ṩ�˺���SoldierID
	BearerID(-1)		//�����˺���SoldierID
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
