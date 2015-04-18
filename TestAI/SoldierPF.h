/********************************************************************
	created:	2015/03/16
	created:	16:3:2015   10:31
	filename: 	E:\cyvasse\TestAI\SoldierPF.h
	file path:	E:\cyvasse\TestAI
	file base:	SoldierPF
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef SoldierPF_h__
#define SoldierPF_h__

#include "PFRadialPotentialField.h"
#include <vector>
#include "GridPos.h"


class GameInfluenceMap;
class Soldier;
class Camp;
class SoldierPF : public PFRadialPotentialField
{
	friend class GameInfluenceMap;
public:
	SoldierPF(Soldier* s);
	~SoldierPF();
	//
	void	SetPerceiveRadius(int r);
	int		GetPerceiveRadius() const ;
	void		PreUpdate();
	void		SetCampPFType(Camp* camp ,int type = PF_TYPE_ATTRACT);

	//�õ��߽��ߣ��߽��ߵ����þ��ǌţ�
	std::vector<GridPos>	GetCrossoverIndexs() const;
	std::vector<GridPos>	GetPerceiveRange() const;
	/////////////////////////////////
protected:
	int						PerceiveRadius;	//��֪�뾶
	std::vector<int>		PerceiveValueRange;	//��֪�����ֵ�б�
	std::vector<GridPos>	PerceiveRange;
	std::vector<GridPos>	CrossOverGPosList;
	//
	Soldier*	pOwner;
public:
	bool	DebugRender;
	void	Render();

};

#endif // SoldierPF_h__
