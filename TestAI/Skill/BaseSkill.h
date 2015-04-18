/********************************************************************
	created:	2015/04/05
	created:	5:4:2015   13:27
	filename: 	E:\cyvasse\TestAI\Skill\BaseSkill.h
	file path:	E:\cyvasse\TestAI\Skill
	file base:	BaseSkill
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef BaseSkill_h__
#define BaseSkill_h__

#include "SkillTree.h"
//////////////////////////////////////////////////////////////////////////
#include "..\Soldier.h"


class BaseSkill : public _BaseSkillTreeNode<Soldier>
{
public:
	BaseSkill();
	~BaseSkill();
	//�ͷż���ǰ��Ҫ����
	virtual bool	CanUseSkill() {return true;}
	//
	virtual bool	Load(std::ifstream& is);
	virtual bool	Save(std::ofstream& os);
	virtual bool	LoadData(std::ifstream& is);
	virtual bool	SaveData(std::ofstream& os);
	//
	void CountDownCD(float var)
	{
		if (mCDCounter > 0 )
		{
			mCDCounter -= var;
		}
	}
	void ResetCD()
	{
		mCDCounter = mMaxCD;
	}
	//
	bool CostValue(float& var)
	{
		if (var >= mCost)
		{
			var =  var - mCost;
			return true;
		}
		return false;
	}

protected:
	float   mMaxCD;			//�����ǻغ���
	float   mCDCounter;		//�����ǻغ���
	float	mCost;			//��������һЩʲô~
private:
};

#endif // BaseSkill_h__
