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

class SkillList;

class GameSkill;
//

//�ϻ�����������

class Soldier:public MessageListener,public CreatureBase ,public AIProperty
{
	friend class SoldierManager;
public: 
	enum
	{
		Human,Orc
	};
public:

	static int NextCreateID;

	Soldier(int race);
	virtual ~Soldier();

	// add by Hitman [7/8/2015]
	virtual void Init();

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
	virtual void Attack(Soldier* other , int number);
	virtual void Attack(const GridPos& gPos , int number);
	virtual void GetHurt(const DamageData& damageData);//���ﴫ�ݵ����ã����Ҫ������Ӧ��memcpy

	//virtual void UseDeputyWeapon(Soldier* other, int DWeaponNumber);
	/* ������� */
	virtual void CallBack_AttackFinish();
	/* �����ɹ� */
	virtual void CallBack_AttackSuccess(const DamageData& damageData); //���ﴫ�ݵ����ã����Ҫ������Ӧ��memcpy
	/* ������һ���غ� */
	virtual void FinishRound(){}
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
	//��ʾ�ƶ�·��
	void SetShowMovePath(bool s){bShowMovePath = s;}
	bool IsShowMovePath(){return bShowMovePath;}
	//ǿ���ƶ���GPos��,������ֱ��ʹ��
	void SetToGPos(const GridPos& GPos);
	bool CanSetTo(const GridPos& GPos){return canStay(GPos);}
	//�Ƿ�����ڴ�GPos��ͣ��
	virtual bool canStay(const GridPos& GPos);
	//Soldier* canAttack( const GridPos& GPos );
	bool canSelect( const GridPos& GPos );


	const GridPos& GetStayGPos() const {return StayGridPos;}
	const GridPos& GetLastStayGPos() const {return LastStayGridPos;}
	const Vector2D& GetPosition() const {return Position;}


	virtual void InitSkills(){}
	virtual void CancleSkill(){}
	bool IsUsingSkill();
	//GameSkill* GetAttackSystem() {return pMainWeapon;}
	SkillList* GetSkillList() 
	{
		return pSkillList;
	}
	ShieldSystem* GetShieldSystem() { return pShieldSystem;}
	TargetingSystem* GetTargetingSystem() {return pTargetingSystem;}
	Goal_SoldierThink* GetBrain() {return pBrain;}
	SoldierPF*		GetSoldierPF() {return pSoldierPF;}
	// add by Hitman [7/7/2015]
	void RecreateBrain();
	/*
		Override
	*/
	virtual bool HandleMessage(const Telegram& telegram) override;
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
	//����ʱ��ɾ��nodedata�õ�
	void ClearNodeWithGPos();
	//����PFλ��
	void UpdateSoldierPFPosition();

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
	bool	bShowMovePath;

	//GameSkill*	pCurUsingSkill;
	SkillList*  pSkillList;

	ShieldSystem*   pShieldSystem;
	TargetingSystem* pTargetingSystem;
	Goal_SoldierThink*  pBrain;

	//
	SoldierPF*	pSoldierPF;

};

#endif // Soldier_h__
