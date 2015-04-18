#include "GameInfluenceMap.h"
#include "SoldierPF.h"

void GameInfluenceMap::Update()
{
	for (auto it = Fields.begin();it != Fields.end();it++)
	{
		SoldierPF* field =static_cast<SoldierPF*>(it->second);
		if (field)
		{
			field->PreUpdate();

			updateSoldierPF(field);
		}
	}
}

void GameInfluenceMap::updateSoldierPF( SoldierPF* S_PF , bool ExceptSelf)
{
	InfluenceMap* IM = this;

	S_PF->PerceiveValueRange.clear();
	S_PF->PerceiveRange.clear();
	S_PF->CrossOverGPosList.clear();


	const GridPos& Position = S_PF->position;
	int Radius = S_PF->PerceiveRadius;

	for (int i = Position.X - Radius ; i<= Position.X + Radius ; ++i)
	{
		for (int k = Position.Y - Radius ; k<= Position.Y + Radius ; ++k)
		{
			GridPos GPos(i,k);

			if (GPos.X >= 0 && GPos.X< IM->nSizeXNum && GPos.Y >= 0 && GPos.Y < IM->nSizeYNum)
			{
				
				int sp = IM->GetStaticPotential(GPos.X, GPos.Y);
				int dp = IM->GetDynamicPotential(GPos.X, GPos.Y);
				int mp = (ExceptSelf? S_PF->GetPotential(GPos.X, GPos.Y) : 0);
				int comparingPotential = sp + dp - mp;
				S_PF->PerceiveValueRange.push_back(comparingPotential);
				S_PF->PerceiveRange.push_back(GPos);	//ÊÀ½çGrid×ø±ê
			}

		}
	}
	//
	if (S_PF->PerceiveRange.size())
	{
		const GridPos& LTGPos = S_PF->PerceiveRange.front();
		const GridPos& RBGPos = S_PF->PerceiveRange.back();
		int W = abs(RBGPos.X - LTGPos.X) + 1;
		int H = abs(RBGPos.Y - LTGPos.Y) + 1;
		int X_lower = std::min(LTGPos.X,RBGPos.X);
		int X_upper = std::max(LTGPos.X,RBGPos.X);
		int Y_lower = std::min(LTGPos.Y,RBGPos.Y);
		int Y_upper = std::max(LTGPos.Y,RBGPos.Y);
		const static int DirNum = 4;
		const static GridPos DirGPos[DirNum] = {GridPos(-1,0),GridPos(1,0),GridPos(0,-1),GridPos(0,1)};
		//
		int		TheMinValue = 999999;
		int		TheMinValueIndex = 0;

		for (int i = 0; i< S_PF->PerceiveRange.size() ; ++i)
		{
			if (S_PF->PerceiveValueRange[i] < TheMinValue)
			{
				TheMinValue = S_PF->PerceiveValueRange[i];
				TheMinValueIndex = i;
			}

			if (S_PF->PerceiveValueRange[i] <= 0)
			{
				for (int k = 0 ;k < DirNum; ++k)
				{
					GridPos NewGPos = S_PF->PerceiveRange[i] + DirGPos[k];

					if (NewGPos.X >= X_lower && 
						NewGPos.X <= X_upper && 
						NewGPos.Y >= Y_lower && 
						NewGPos.Y <= Y_upper)
					{
						NewGPos = NewGPos - LTGPos;

						int index = std::max(0,NewGPos.X) * H + NewGPos.Y;

						if(S_PF->PerceiveValueRange[index] > 0)
						{
							S_PF->CrossOverGPosList.push_back(S_PF->PerceiveRange[i]);
							break;
						}
					}
				}
			}

		}
	}
}

void GameInfluenceMap::Render()
{
	for (auto it = Fields.begin();it != Fields.end();it++)
	{
		SoldierPF* field =static_cast<SoldierPF*>(it->second);
		field->Render();
	}
}
