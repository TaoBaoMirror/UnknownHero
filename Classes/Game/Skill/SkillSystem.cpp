#include "SkillSystem.h"
#include "SkillFactory.h"
//
#include <iosfwd>
#include <fstream>
using namespace std;

SkillSystem::SkillSystem():BaseSkillTree<BaseSkill>()
{

}

SkillSystem::~SkillSystem()
{

}

bool SkillSystem::Load( std::ifstream& is )
{
	char buf[32];
	is>>buf;
	//
	auto root = GetRoot();
	//
	int nodeNum = -1;
	is>>buf>>nodeNum;
	//first是技能ID，后面是ParentID
	std::vector< std::pair<int,int> >	Skill_ID_List(nodeNum,std::pair<int,int>(-1,-1));
	std::vector<BaseSkill*>	Skills;	Skills.reserve(nodeNum);
	int counter = 0;
	while(nodeNum)
	{
		is>>buf>>Skill_ID_List[counter].first;
		is>>buf>>Skill_ID_List[counter].second;
		counter++;
		nodeNum--;
	}
	//生成这些技能，从SkillFactory创建的技能
	for (int i = 0; i<= counter;++i)
	{
		BaseSkill* skill = SkillFactory::CreateSkill(Skill_ID_List[i].first);
		Skills.push_back(skill);
	}

	for(int i = 0;i< Skills.size();++i)
	{
		auto skill = Skills[i];
		//
		if (skill &&
			skill->mID != BaseSkill::RootID &&
			Skill_ID_List[counter].second != BaseSkill::InvalidID)
		{
			InsertTreeNode(skill,Skill_ID_List[counter].second);
		}		
	}

	auto it = Nodes.begin();
	while (it != Nodes.end())
	{
		auto skill = it->second;

		skill->LoadData(is);

		it++;
	}


	root->LoadData(is);
	return true;
}

bool SkillSystem::Save( std::ofstream& os )
{
// 	os<<"==SkillSystem=="<<std::endl;
// 
// 	os<<"NodesNum: "<<Nodes.size()<<std::endl;
// 
// 	auto root = GetRoot();
// 	
// 	auto it = Nodes.begin();
// 
// 	while (it != Nodes.end())
// 	{
// 		auto skill = it->second;
// 		os<<"SkillID: "<<skill->mID<<std::endl;
// 		if (skill->mID != BaseSkill::RootID)
// 		{
// 			os<<"ParentID: "<<skill->mParent->mID<<std::endl;
// 		}
// 		else
// 		{
// 			os<<"ParentID: "<<BaseSkill::InvalidID<<std::endl;
// 		}
// 				
// 		it++;
// 	}
// 
// 	it = Nodes.begin();
// 
// 	while(it != Nodes.end())
// 	{
// 		auto skill = it->second;
// 
// 		skill->SaveData(os);
// 
// 		it++;
// 	}

	return true;

}
