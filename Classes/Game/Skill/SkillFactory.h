/********************************************************************
	created:	2015/04/08
	created:	8:4:2015   1:18
	filename: 	E:\cyvasse\TestAI\Skill\SkillFactory.h
	file path:	E:\cyvasse\TestAI\Skill
	file base:	SkillFactory
	file ext:	h
	author:		SkillFactory
	
	purpose:	
*********************************************************************/
#ifndef SkillFactory_h__
#define SkillFactory_h__

class BaseSkill;
class SkillFactory
{
public:
	static BaseSkill*	CreateSkill(int id);
};

#endif // SkillFactory_h__
