#include "SkillFactory.h"
#include "BaseSkill.h"

BaseSkill* SkillFactory::CreateSkill( int id )
{
	BaseSkill* skill = 0;

	switch (id)
	{
	case BaseSkill::RootID:
	case BaseSkill::InvalidID:
		{
			return NULL;
		}
	case 1:
		{
			skill = new BaseSkill();
		}
	default:
		break;
	}
	//
	return skill;
}
