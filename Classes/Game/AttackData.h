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
	int		AtkType;			//��������

	int		AttackPt;			//��󹥻���
	int		CritPt;				//����ֵ
	float   CritRate;			//������
	int		SputteringRadius;	//���䷶Χ
	float   SputteringFallout;	//����˥��
	//
	bool	HasEmitter;			//�Ƿ��з�����
};

struct AttackData : public AttackDataBase
{
public:
	AttackData();
	AttackData(const AttackDataBase& ADB,int P_Id,int B_Id);
	int		ProviderID;			//�ṩ�˺���SoldierID
	int		BearerID;			//�����˺���SoldierID
};

#endif // AttackData_h__
