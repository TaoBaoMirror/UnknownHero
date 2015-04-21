#include "BaseSkill.h"
#include <fstream>
BaseSkill::BaseSkill()
{

}

BaseSkill::~BaseSkill()
{

}

bool BaseSkill::Load( std::ifstream& is )
{
	return true;
}

bool BaseSkill::Save( std::ofstream& os )
{
	return true;

	
}

bool BaseSkill::LoadData( std::ifstream& is )
{
	char buff[32];

	is >> buff >> mID >> buff >> mActive >> buff >> mLocked;

	return is;
}

bool BaseSkill::SaveData( std::ofstream& os )
{
	os<<"mID: "<<mID<<" mActive: "<<mActive<<" mLocked: "<<mLocked<<std::endl;

	os<<std::endl;

	return true;
}
