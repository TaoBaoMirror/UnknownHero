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
	int	     MaxViewRadius;			//最大视野
	int	     CurViewRadius;			//当前视野
	int      MaxHP;					//最大HP
	int      CurHP;					//当前HP
	int		 MaxMP;					//最大MP
	int		 CurMP;					//当前MP
	int		 MaxSpeed;				//最大移动速度
	int      CurSpeed;				//当前移动速度
	//
	int		 RecoverHP;				//每回合恢复HP
	int      RecoverMP;				//每回合恢复MP
	
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
