#include "CreatureSpawnArea.h"
#include "ChunkMap.h"
bool CreatureSpawnArea::Init( int AreaID , int CreatureType , float TimeGap , const GridPos& Pos,int w,int h,ChunkMap& Chunk )
{
	if(cocos2d::CCNode::init())
	{
		autorelease();
		GridPosArea::Init(Pos,w,h,Chunk.GetGridSceneMap());
		if(CreatureType != -1)RegisterCreatureType(CreatureType);
		nAreaID = AreaID;
		fTimeGap = TimeGap;
		pChunkMap = &Chunk;
		return true;
	}

	return false;
}

CreatureSpawnArea::CreatureSpawnArea()
{
	CreateTypes.reserve(8);
}

void CreatureSpawnArea::RegisterCreatureType( int CType )
{
	CreateTypes.push_back(CType);
}

void CreatureSpawnArea::UnregisterCreatureType( int CType )
{
	auto it = CreateTypes.begin();
	while (it != CreateTypes.end())
	{
		if (*it == CType)
		{
			CreateTypes.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void CreatureSpawnArea::update( float dt )
{

}

void CreatureSpawnArea::StartSpawn()
{
	cocos2d::DelayTime* dt = cocos2d::DelayTime::create(fTimeGap);
	cocos2d::CallFunc*  cf = cocos2d::CallFunc::create(CC_CALLBACK_0(CreatureSpawnArea::OnSpawn,this));
	cocos2d::Sequence*  seq = cocos2d::Sequence::create(dt,cf);
	cocos2d::RepeatForever* rf = cocos2d::RepeatForever::create(seq);
	rf->setTag(SPAWN_ACTION);
	this->runAction(rf);
}

void CreatureSpawnArea::PauseSpawn()
{
	this->pause();
}

void CreatureSpawnArea::StopSpawn()
{
	this->stopActionByTag(SPAWN_ACTION);
}

void CreatureSpawnArea::OnBegineSpawn()
{

}

void CreatureSpawnArea::OnEndSpawn()
{

}

void CreatureSpawnArea::OnSpawn()
{
	OnBegineSpawn();
	//
	ExecuteSpawn();
	//
	OnEndSpawn();
}

void CreatureSpawnArea::ExecuteSpawn()
{

}

void CreatureSpawnArea::ResumeSpawn()
{
	this->resume();
}

int CreatureSpawnArea::GetRandomCreatureID()
{
	if (CreateTypes.size())
	{
		int i = RandInt(0,CreateTypes.size());
		return CreateTypes[i];
	}

	return -1;

}

GridPos CreatureSpawnArea::GetRandomGPos()
{
	const int MAX_RAND_NUM = 10;
	if (GPosArea.size())
	{
		for (int i = 0;i < MAX_RAND_NUM; ++i)
		{
			int index = RandInt(0,GPosArea.size());
			auto node = pChunkMap->GetGridSceneMap().GetNode(index);
			if (node.Index() != invalid_node_index)
			{
				if(IsSpawnGPosLegit(GPosArea[i]))
				{
					return GPosArea[i];
				}
			}
		}

	}
	
	return GridPos(-1,-1);

}

bool CreatureSpawnArea::IsSpawnGPosLegit(const GridPos& GPos)
{
	auto node = pChunkMap->GetGridSceneMap().GetNode(GPos);
	auto data = Cast_MapNodeData(node.ExtraInfo());
	if (data && data->Creature == NULL)
	{
		return true;
	}

	return false;

}

int CreatureSpawnArea::ParseCreatureIDs( const std::string& szParam ,std::vector<int>& szVec)
{
	char *token = strtok(const_cast<char *>(szParam.c_str()), ",");  
	while (token)  
	{  
		std::string strTemp = token; 
		int id = atoi(strTemp.c_str());
		szVec.push_back(id);  
		token = strtok(NULL, ",");  
	}  

	return szVec.size();  
}

