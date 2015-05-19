/********************************************************************
	created:	2015/03/16
	created:	16:3:2015   12:02
	filename: 	E:\cyvasse\TestAI\Camp.h
	file path:	E:\cyvasse\TestAI
	file base:	Camp
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Camp_h__
#define Camp_h__

#include <map>
#include <vector>

class Soldier;

#define CampType_Player 0
#define CampType_Monster 1
#define CampType_NPC 2



class Camp
{
public:
	static const	int MaxCamps = 8;
	static void		CreateCamps(int CampsNum);
	static Camp*	GetCamp(int Flag);
	static void		GetOtherCampFlags(int flag,std::vector<int>& campFlags);
protected:
	static Camp		CampList[MaxCamps];
public:

	enum { in_use , wait_use };

	Camp();
	~Camp();
	//
	int		CampFlag;
	int		CampState;
	//
	void	Reset();
	//
	void    RegisterUnit(Soldier* unit);
	void    UnregisterUnit(int unit_id);
	Soldier*	GetUnit(int unit_id);
	int		GetUnitNumber(){ return Corps.size(); }
	//
	std::map<int,Soldier*>& GetCrops();
protected:
	std::map<int,Soldier*>	Corps;
	//

};

#endif // Camp_h__
