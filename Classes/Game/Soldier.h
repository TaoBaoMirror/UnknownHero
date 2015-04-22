/********************************************************************
	created:	2015/01/19
	created:	19:1:2015   0:03
	filename: 	E:\cyvasse\TestAI\Soldier.h
	file path:	E:\cyvasse\TestAI
	file base:	Soldier
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Soldier_h__
#define Soldier_h__



#include "Vector2D.h"
#include "GridPos.h"

//
#include "Messaging/MessageListener.h"
#include "CreatureBase.h"

class Goal_SoldierThink;
class AttackSystem;
class ShieldSystem;
class TargetingSystem;
//
class SoldierPF;
//

class Soldier:public MessageListener,public CreatureBase
{
	friend class SoldierManager;
public: 
	enum
	{
		Human,Orc
	};
public:
	Soldier(int atk,int race);
	virtual ~Soldier();

	int	GetCampIndex(){return CampIndex;}
	void SetCampIndex(int c){CampIndex = c;}
	int	GetRaceIndex(){return RaceIndex;}
	void SetRaceIndex(int r){RaceIndex = r;}


	int	GetID(){return ID;}
	void SetID(int id){ ID = id;}//不要轻易用！！！



	virtual void Update();
	virtual void Render();
	//
	virtual void BeginMove();
	virtual void EndMove();


	bool MoveForward(int step = 1);
	bool MoveBackward(int step = 1);
	bool MoveLeft(int step = 1);
	bool MoveRight(int step = 1);
	bool MoveTo(const GridPos& GPos);
	void SetPath();

	void GetPathToTarget(const GridPos& A,const GridPos& B,std::vector<GridPos>& path);
	void MoveCloseToGPos(const GridPos& other,GridPos& out_nextGPos);
	void MoveAwayFromGPos(const GridPos& other,GridPos& out_nextGPos);
	void FindSoldiersInRange(int RangeSize, bool ExceptSelf , int RType ,std::vector<Soldier*>&	out_SoldierList);

	void SetShowAttackRange(bool s){bShowAttackRange = s;}
	bool IsShowAttackRange(){return bShowAttackRange;}

	void SetToGPos(const GridPos& GPos);
	bool CanSetTo(const GridPos& GPos){return canStay(GPos);}

	const GridPos& GetStayGPos() const {return StayGridPos;}
	const GridPos& GetLastStayGPos() const {return LastStayGridPos;}
	const Vector2D& GetPosition() const {return Position;}

	AttackSystem* GetAttackSystem() {return pAttackSystem;}
	ShieldSystem* GetShieldSystem() { return pShieldSystem;}
	TargetingSystem* GetTargetingSystem() {return pTargetingSystem;}
	Goal_SoldierThink* GetBrain() {return pBrain;}
	SoldierPF*		GetSoldierPF() {return pSoldierPF;}


	void Attack(Soldier* other);

public:
	bool    bPossessed;
	bool    IsPossessed(){return bPossessed;}
	void    TakePossession();
	void    Exorcise();
public:
	void UpdatePosition();
	void UpdateNodeWithGPos();
	void UpdateSoldierPFPosition();
protected:

	void showAttackRange(const std::vector<GridPos>&	AttackGPosList);
	bool canStay(const GridPos& GPos);
private:
	Vector2D Position;				//所在的世界位置
	int		 ID;					//ID
	int		 RaceIndex;					//种族
	int		 CampIndex;					//阵营
	GridPos	 StayGridPos;			//所在的网格位置
	GridPos	 LastStayGridPos;		//上次所在的网格位置
	//
	bool	bShowAttackRange;

	AttackSystem*	pAttackSystem;
	ShieldSystem*   pShieldSystem;
	TargetingSystem* pTargetingSystem;
	Goal_SoldierThink*  pBrain;

	//
	SoldierPF*	pSoldierPF;

};

#endif // Soldier_h__
