/********************************************************************
	created:	2015/03/14
	created:	14:3:2015   12:41
	filename: 	E:\cyvasse\TestAI\CreatureBase.h
	file path:	E:\cyvasse\TestAI
	file base:	CreatureBase
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Creature_h__
#define Creature_h__

class CreatureBase
{
public:
	CreatureBase();	
	//
	int	     MaxViewRadius;			//�����Ұ
	int	     CurViewRadius;			//��ǰ��Ұ
	int      MaxHP;					//���HP
	int      CurHP;					//��ǰHP
	int		 MaxMP;					//���MP
	int		 CurMP;					//��ǰMP
	int		 MaxSpeed;				//����ƶ��ٶ�
	int      CurSpeed;				//��ǰ�ƶ��ٶ�
	//
	int		 RecoverHP;				//ÿ�غϻָ�HP
	int      RecoverMP;				//ÿ�غϻָ�MP
	
private:

};

class AIProperty
{
public:
	AIProperty();
	//
	float	Explore_LowRangeOfBias;
	float	Explore_HighRangeOfBias;
	//
	float	AttackTarget_LowRangeOfBias;
	float	AttackTarget_HighRangeOfBias;

};



#endif // Creature_h__
