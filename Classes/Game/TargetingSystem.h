/********************************************************************
	created:	2015/03/13
	created:	13:3:2015   22:26
	filename: 	E:\cyvasse\TestAI\TargetingSystem.h
	file path:	E:\cyvasse\TestAI
	file base:	TargetingSystem
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef TargetingSystem_h__
#define TargetingSystem_h__

class Soldier;
struct Vector2D;

class TargetingSystem
{
public:
	TargetingSystem(Soldier* owner);
	~TargetingSystem();
	//
	void       Update();

	//是否指定了对象
	bool       isTargetPresent()const{return m_pCurrentTarget != 0;}

	//是否在攻击范围
	bool       isTargetWithinAttackRange()const;

	//释放可以攻击  比如一些相克的东西
	bool       isTargetShootable()const;

	//返回在范围内部的时间
	double      GetTimeTargetHasBeenVisible()const;

	//返回Target消失在范围内
	double      GetTimeTargetHasBeenOutOfView()const;

	Soldier*  GetTarget()const{return m_pCurrentTarget;}

	void       ClearTarget(){m_pCurrentTarget=0;}
protected:
	
private:
	Soldier*  m_pOwner;

	Soldier*  m_pCurrentTarget;
};

#endif // TargetingSystem_h__
