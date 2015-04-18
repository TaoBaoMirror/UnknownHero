#include "GeomorphologyCreater.h"
#include "MapNodeData.h"

GeomorphologyCreater::GeomorphologyCreater(GridSceneMap* gridSceneMap)
{
	m_pGridSceneMap = gridSceneMap;
}

GeomorphologyCreater::~GeomorphologyCreater()
{

}

bool GeomorphologyCreater::CanPasteField( const GeomorphologyField& field,const GridPos& GPos )
{
	int FW = field.GetWidthSize();
	int FH = field.GetHightSize();
	//
	int insideW = m_pGridSceneMap->GetSizeNumX() - FW;
	int insideH = m_pGridSceneMap->GetSizeNumY() - FH;

	if (GPos.X >= 0 && GPos.X < insideW && GPos.Y >= 0 && GPos.Y < insideH)
	{
		return true;
	}

	return false;



}

void GeomorphologyCreater::PasteField( const GeomorphologyField& field,const GridPos& GPos )
{
	if(CanPasteField(field,GPos) == false) return ;
	//
	int FW = field.GetWidthSize();
	int FH = field.GetHightSize();
	GridPos BaseGPos(0,0);
	//
	for (int i = 0;i< FW;++i)
	{
		for (int k = 0;k< FH;++k)
		{
			BaseGPos.SetTo(i,k);
			int index = InvalidID;
			m_pGridSceneMap->GridPosToIndex(GPos + BaseGPos,index);
			auto node = m_pGridSceneMap->GetNode(index);
			//
			MapNodeData* pMND = Cast_MapNodeData(node.ExtraInfo());

			if (pMND != NULL)
			{
				int resID = field.GetResourceData(BaseGPos);
				int fieldID = field.GetFieldData(BaseGPos);
				if(resID != InvalidID) pMND->ResouceID = resID;
				if(resID != InvalidID) pMND->SpecialID = fieldID;
			}
			
		}
	}
}

void GeomorphologyCreater::CreateGeomorphology(GeomorphologyDisc& disc)
{
	//随机生成的一些参数
	int unwalkableNodeNumber = disc.GetUnwalkableNum();
	int enemyNum = disc.GetEnemyNum();
	std::vector<int>	unwalkableNodeIDList(unwalkableNodeNumber);
	//std::vector<int>&   EnemySpawnNodeIDList = disc.EnemySpawnNodeIDList;
	//生成一些unwalk的点
	for (int i = 0;i<unwalkableNodeNumber;++i)
	{
		GridPos		unwalkableGPos;

		unwalkableGPos.SetTo(RandInt(0,m_pGridSceneMap->GetSizeNumX() - 1),
			RandInt(0,m_pGridSceneMap->GetSizeNumY() - 1));
		//将unwalk的点设置到sceneMap里面
		int index = InvalidID;
		m_pGridSceneMap->GridPosToIndex(unwalkableGPos,index);
		//
		if (index != InvalidID)
		{
			unwalkableNodeIDList[i] = index;
			NavGraphNode<void*>& node = m_pGridSceneMap->GetNode(index);
			node.SetWalkable(false);
		}
		else
		{
			assert(index != InvalidID && "ERROR!!!----InvalidID");
		}
	}

	//
	//随机其他点--- Door & Player & Shop 应该是固定点,但是也可以生成

	for (int i = 0 ; i< disc.NeedToCreateKeyList.size();++i)
	{
		switch(disc.NeedToCreateKeyList[i])
		{
		case GKI_ENEMYBORN:
			{
				CreateBornPos(GKI_ENEMYBORN,disc.GetEnemyNum(),unwalkableNodeIDList,disc);
			}
			break;
		case GKI_PLAYERBORN:
			{
				CreateBornPos(GKI_PLAYERBORN,disc.GetPlayerNum(),unwalkableNodeIDList,disc);
			}
			break;
		case GKI_SHOP:
		case GKI_DOOR:
			{
				GridPos GPos;
				auto UpperLimit = disc.SpecialUpperLimits[i];
				auto LowerLimit = disc.SpecialLowerLimits[i];
				GPos.SetTo(RandInt(LowerLimit.X,UpperLimit.X),RandInt(LowerLimit.Y,UpperLimit.Y));
				int index = InvalidID;
				m_pGridSceneMap->GridPosToIndex(GPos,index);
				if (index != InvalidID)
				{
					std::vector<int>	indexList;
					NavGraphNode<void*>& node = m_pGridSceneMap->GetNode(index);
					node.SetWalkable(true);
					indexList.push_back(index);
					disc.SpecialKeyNodeIDMap.insert(std::make_pair(disc.NeedToCreateKeyList[i],indexList));

				}

			}
			break;
		}

	}

}

void GeomorphologyCreater::CreateBornPos( int PosType,int num ,const std::vector<int>& unwalkables,GeomorphologyDisc& disc )
{
	if(num != NULL)
	{
		std::vector<int> SpawnNodeIDList;
		SpawnNodeIDList.reserve(num);
		while(num > 0)
		{		
			//
			int BornNodeID = -1;
			GridPos		BornGPos;
			BornGPos.SetTo(RandInt(0,m_pGridSceneMap->GetSizeNumX() - 1),
				RandInt(0,m_pGridSceneMap->GetSizeNumY() - 1));
			m_pGridSceneMap->GridPosToIndex(BornGPos,BornNodeID);
			//
			bool AtSameGPos = false;
			for(int i = 0 ; i< SpawnNodeIDList.size();++i)
			{
				const int otherNodeID = SpawnNodeIDList[i];
				if (BornNodeID == otherNodeID)
				{
					AtSameGPos = true;
					break;
				}
			}
			if (AtSameGPos)
			{
				continue;
			}
			//
			for(int i = 0 ; i< unwalkables.size();++i)
			{
				const int otherNodeID = unwalkables[i];
				if (BornNodeID == otherNodeID)
				{
					AtSameGPos = true;
					break;
				}
			}
			if (AtSameGPos)
			{
				continue;
			}
			//
			auto it_b = disc.SpecialKeyNodeIDMap.begin();
			auto it_e = disc.SpecialKeyNodeIDMap.end();

			for (;it_b != it_e;++it_b)
			{
				auto indexList = it_b->second;
				for (int k = 0;k< indexList.size();++k)
				{
					if (indexList[k] == BornNodeID)
					{
						continue;
					}
				}

			}
			SpawnNodeIDList.push_back(BornNodeID);
			num--;
		} 
		//
		disc.SpecialKeyNodeIDMap[(GeomorphologyKeyIndex)PosType] = SpawnNodeIDList;
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
GeomorphologyField::GeomorphologyField()
	:WidthSize(0),HightSize(0)
{
	FieldDatas.resize(WidthSize*HightSize,InvalidID);
	ResourceDatas.resize(WidthSize*HightSize,InvalidID);
}

GeomorphologyField::~GeomorphologyField()
{

}

void GeomorphologyField::Create()
{
	//测试，自己定义一些微妙的点阵
	WidthSize = 3;
	HightSize = 3;

	int g[9]={1,1,1,
			  1,0,1,
			  1,1,1};

	FieldDatas = std::vector<int>(g,g+9);
}

void GeomorphologyField::Load()
{

}

void GeomorphologyField::Save()
{

}

const int GeomorphologyField::GetResourceData( const GridPos& GPos ) const
{
	int index = GPosToIndex(GPos);
	//
	assert(index != InvalidID && index < ResourceDatas.size());
	//
	if (index != InvalidID)
	{
		return ResourceDatas[index];
	}

	return InvalidID;

}

const int GeomorphologyField::GetFieldData( const GridPos& GPos ) const
{
	int index = GPosToIndex(GPos);
	//
	assert(index != -1 && index < FieldDatas.size());
	//
	if (index != InvalidID)
	{
		return FieldDatas[index];
	}
	//
	return InvalidID;
}
const int GeomorphologyField::GPosToIndex( const GridPos& GPos ) const
{
	if(GPos.X >= 0 && GPos.X < WidthSize && GPos.Y >= 0 && GPos.X < HightSize)
	{
		int i = GPos.X + GPos.Y * WidthSize;
		return i;
	}
	//
	return InvalidID;
}
