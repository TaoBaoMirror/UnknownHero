/********************************************************************
	created:	2015/04/05
	created:	5:4:2015   13:47
	filename: 	E:\cyvasse\TestAI\Skill\SkillSystem.h
	file path:	E:\cyvasse\TestAI\Skill
	file base:	SkillSystem
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef SkillSystem_h__
#define SkillSystem_h__

#include "SkillTree.h"
#include "BaseSkill.h"
//////////////////////////////////////////////////////////////////////////
//
//	ֻ��Ϊ�˽�ɫ���ϵļ��ܹ���ÿһ����ɫ�����or���ˣ��������������ϵͳ���������ϵͳ�ǹ����ܵ�
//	���������ܣ����Ҽ��ܣ�Ȼ���ȡ�ͱ��漼�ܣ�
//
///////////////////////////////////////////////////////////////////////////
class SkillSystem : public BaseSkillTree<BaseSkill>
{
public:
	SkillSystem();
	virtual ~SkillSystem();
	//
	bool	Load(std::ifstream& is);
	bool	Save(std::ofstream& os);
	//

protected:
	
private:
};

#endif // SkillSystem_h__
