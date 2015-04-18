#include "AttackData.h"

AttackDataBase::AttackDataBase()
	:	ID(-1),
		AttackPt(0),		//��󹥻���
		CritPt(0),				//����ֵ
		CritRate(0),			//������
		SputteringRadius(0),	//���䷶Χ
		SputteringFallout(1),	//����˥��
		AtkType(0),				//��������
		HasEmitter(false)		//
{

}
//////////////////////////////////////////////////////////////////////////

AttackData::AttackData()
	:AttackDataBase(),		
	ProviderID(-1),			//�ṩ�˺���SoldierID
	BearerID(-1)			//�����˺���SoldierID
{

}

AttackData::AttackData( const AttackDataBase& ADB,int P_Id,int B_Id )
	:AttackDataBase(ADB),ProviderID(P_Id),BearerID(B_Id)
{
	
}
