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
//	只是为了角色身上的技能管理，每一个角色（玩家or敌人），都有这个技能系统，这个技能系统是管理技能的
//	（解锁技能，查找技能，然后读取和保存技能）
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
