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
class AttackData;
class DamageData;
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

	static int NextCreateID;

	Soldier(int atk,int race);
	virtual ~Soldier();

	int	GetCampIndex(){return CampIndex;}
	void SetCampIndex(int c){CampIndex = c;}
	int	GetRaceIndex(){return RaceIndex;}
	void SetRaceIndex(int r){RaceIndex = r;}


	int	GetID(){return ID;}
	void SetID(int id){ ID = id;}//��Ҫ�����ã�����



	virtual void Update();
	virtual void Render();
	//���move��˲�Ƶ�
	bool MoveForward(int step = 1);
	bool MoveBackward(int step = 1);
	bool MoveLeft(int step = 1);
	bool MoveRight(int step = 1);
	virtual void BeginMove();
	virtual void EndMove();
	bool MoveTo(const GridPos& GPos);
	//���move�Ƕ����ƶ���,��Ҫcocos2dx��֧��
	virtual void BeginTraval() {}
	virtual void EndTraval();
	virtual bool TravalTo(const GridPos& GPos);
	//��������
	//����������ɺ�ȥ���㹥������
	virtual void Attack(Soldier* other);
	virtual void GetHurt(DamageData* damageData);
	//�õ�һ����Ŀ���·��
	void GetPathToTarget(const GridPos& A,const GridPos& B,std::vector<GridPos>& path);
	//�������GPos�㿿��һ��
	void MoveCloseToGPos(const GridPos& other,GridPos& out_nextGPos);
	//�������GPos��Զ��һ��
	void MoveAwayFromGPos(const GridPos& other,GridPos& out_nextGPos);

	/*
		Ѱ���ڷ�Χ�ڵ�Soldier
	//	����	@ RangeSize			��Χ�ߴ�
	//		@ ExceptSelf		�ͷ��ȥ�Լ�
			@ RType				��Χ��Type
			@ out_SoldierList	����б�

	*/
	void FindSoldiersInRange(int RangeSize, bool ExceptSelf , int RType ,std::vector<Soldier*>&	out_SoldierList);
	//�ͷ���ʾ������Χ
	void SetShowAttackRange(bool s){bShowAttackRange = s;}
	bool IsShowAttackRange(){return bShowAttackRange;}
	//ǿ���ƶ���GPos��,������ֱ��ʹ��
	void SetToGPos(const GridPos& GPos);
	bool CanSetTo(const GridPos& GPos){return canStay(GPos);}
	//�Ƿ�����ڴ�GPos��ͣ��
	virtual bool canStay(const GridPos& GPos);
	Soldier* canAttack( const GridPos& GPos );
	bool canSelect( const GridPos& GPos );


	const GridPos& GetStayGPos() const {return StayGridPos;}
	const GridPos& GetLastStayGPos() const {return LastStayGridPos;}
	const Vector2D& GetPosition() const {return Position;}



	AttackSystem* GetAttackSystem() {return pAttackSystem;}
	ShieldSystem* GetShieldSystem() { return pShieldSystem;}
	TargetingSystem* GetTargetingSystem() {return pTargetingSystem;}
	Goal_SoldierThink* GetBrain() {return pBrain;}
	SoldierPF*		GetSoldierPF() {return pSoldierPF;}


public:
	//��Ҳ���ʱ���õ�
	bool    bPossessed;
	bool    IsPossessed(){return bPossessed;}
	//Soldier �ܵ�����
	void    TakePossession();
	//Soldier �뿪����
	void    Exorcise();
public:
	//����λ�� WorldPos
	void UpdatePosition();
	//����GPos
	void UpdateNodeWithGPos();
	//����PFλ��
	void UpdateSoldierPFPosition();
protected:
	virtual void showAttackRange(const std::vector<GridPos>&	AttackGPosList);
private:
	Vector2D Position;				//���ڵ�����λ��
	int		 ID;					//ID
	int		 RaceIndex;					//����
	int		 CampIndex;					//��Ӫ
	GridPos	 StayGridPos;			//���ڵ�����λ��
	GridPos	 LastStayGridPos;		//�ϴ����ڵ�����λ��
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
