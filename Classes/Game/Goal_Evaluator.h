/********************************************************************
	created:	2015/03/13
	created:	13:3:2015   14:57
	filename: 	E:\cyvasse\TestAI\Goal_Evaluator.h
	file path:	E:\cyvasse\TestAI
	file base:	Goal_Evaluator
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Goal_Evaluator_h__
#define Goal_Evaluator_h__

class Soldier;
struct Vector2D;

template <class entity_type>
class Goal_Evaluator
{
protected:

	//��ɫ��ƫ��ֵ
	double       m_dCharacterBias;

public:

	Goal_Evaluator(double CharacterBias):m_dCharacterBias(CharacterBias){}

	virtual ~Goal_Evaluator(){}

	//����0-1ֱ��������Ĳ���
	virtual double CalculateDesirability(entity_type* pBot)=0;

	//���������ͼָ����� Soldier's ����
	virtual void  SetGoal(entity_type* pBot) = 0;
};

#endif // Goal_Evaluator_h__
