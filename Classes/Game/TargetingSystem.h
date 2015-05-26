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

	//�Ƿ�ָ���˶���
	bool       isTargetPresent()const{return m_pCurrentTarget != 0;}

	//�Ƿ��ڹ�����Χ
	bool       isTargetWithinAttackRange()const;

	//�ͷſ��Թ���  ����һЩ��˵Ķ���
	bool       isTargetShootable()const;

	//�����ڷ�Χ�ڲ���ʱ��
	double      GetTimeTargetHasBeenVisible()const;

	//����Target��ʧ�ڷ�Χ��
	double      GetTimeTargetHasBeenOutOfView()const;

	Soldier*  GetTarget()const{return m_pCurrentTarget;}

	void       ClearTarget(){m_pCurrentTarget=0;}
protected:
	
private:
	Soldier*  m_pOwner;

	Soldier*  m_pCurrentTarget;
};

#endif // TargetingSystem_h__
