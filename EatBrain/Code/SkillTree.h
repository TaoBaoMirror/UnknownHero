/********************************************************************
	created:	2015/04/05
	created:	5:4:2015   11:38
	filename: 	E:\cyvasse\EatBrain\Code\SkillTree.h
	file path:	E:\cyvasse\EatBrain\Code
	file base:	SkillTree
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef SkillTree_h__
#define SkillTree_h__

#include <vector>
#include <map>
#include <list>

#define  BaseTreeNodeKidsNum 4

typedef class _BaseTreeNode
{
public:
	static const int RootID = 0;	//默认RootID的
	static const int InvalidID = -1;	//无效ID


	_BaseTreeNode();
	virtual ~_BaseTreeNode();
	//父节点
	_BaseTreeNode* mParent;
	//子节点
	std::vector<_BaseTreeNode*> mKids;
	//技能的ID
	int		mID;
	//激活状态,默认是false
	bool mActive;
	//是否是尚未解锁的技能
	bool mLocked;
	//附带的Value
	void*	mValue;
	//加入一个孩子节点
	virtual void AddKid(_BaseTreeNode* node);
	//移除一个孩子节点
	virtual void RemoveKid(_BaseTreeNode* node);
	//如果父节点是激活的，子节点才可以激活
	virtual void SetActive(bool active);
	virtual void OnActive(){}
	//
	virtual bool SetLocked();
	virtual bool SetUnLocked();



} BaseTreeNode;

//////////////////////////////////////////////////////////////////////////
//
//	Skill 可以当 buff ， 是一套的
//
//////////////////////////////////////////////////////////////////////////
template<class creature>
class _BaseSkillTreeNode:public BaseTreeNode
{
public:
	//
	creature* Owner;				//技能的拥有者
	/////
	virtual void OnMoveBegin(){}
	virtual void OnMoveStep(){}
	virtual void OnMoveEnd(){}
	//
	virtual void OnAttackBegin(){}
	virtual void OnAttackStep(){}
	virtual void OnAttackEnd(){}
	//
	virtual void OnGetDamage(){}
	virtual void OnBeHit(){}
	//
	virtual void OnDefenseBegin(){}
	virtual void OnDefenseStep(){}
	virtual void OnDefenseEnd(){}
	//////////////////////////////////////////////////////////////////////////

	virtual void OnUpdateStep(){}
	virtual void OnDoAttach(){}
	virtual void OnDoDettach(){}
	//

};

template<class TNode>
class BaseSkillTree
{
public:


	BaseSkillTree()
	{
		TNode* root = new TNode();
		root->mID = TNode::RootID;
		root->mActive = true;

		Nodes.insert(std::make_pair(root->mID,root));
	}
	virtual ~BaseSkillTree()
	{
		auto it = Nodes.begin();
		while (it != Nodes.end())
		{
			delete it->second;
			it++;
		}
		//
		Nodes.clear();
	}
	//
	bool	InsertTreeNode(TNode* node,int ParentID)
	{
		auto parent = GetNode(ParentID);
		if(node && !GetNode(node->mID) && parent)
		{
			Nodes.insert(std::make_pair(node->mID,node));
			//
			parent->AddKid(node);
			//
			return true;
		}
		return false;
	}
	bool	RemoveTreeNode(int NodeID)
	{
		if(NodeID == RootID) return false;
		auto it = Nodes.find(id);
		if (it != Nodes.end())
		{
			TNode* node = it->second;

			Nodes.remove(it);
			//
			if (node->mParent)
			{
				node->mParent->RemoveKid(node);
			}
			//
			return true;
		}
		return false;
	}
	TNode*	GetRoot(){return Nodes[0];}
	TNode*	GetNode(int id)
	{
		auto it = Nodes.find(id);
		if (it != Nodes.end())
		{
			return it->second;
		}
		return 0;
	}
	bool	GetSiblings(TNode* node,std::vector<TNode*>& siblings)
	{
		if (node->mID == RootID)
		{
			assert(0 && "The Node is Root");
			return false;
		}
		//
		if (node->mParent)
		{
			siblings = node->mParent->mKids;
			return true;
		}
		//
		return false;
	}

protected:
	std::map<int,TNode*> Nodes;	
private:
};
//////////////////////////////////////////////////////////////////////////

template<class creature>
class _BaseBuffNode : public _BaseSkillTreeNode<creature>
{
public:
	float BuffTime;		//buff的持续时间，可以是回合数
	creature* Bearer;	//承受者
	bool  Alive;
	//
	_BaseBuffNode():_BaseSkillTreeNode<creature>(),BuffTime(1),Bearer(0),Alive(true)
	{

	}
	//
	void CountdownAround()
	{
		Countdown(1);
	}
	//
	void Countdown(float d)
	{
		if (Alive)
		{
			BuffTime -=d;

			if (BuffTime<= 0)
			{
				Alive = false;
			}
		}
	}
private:

};

template<class TBuff>
class BaseBuffSet
{
public:
	BaseBuffSet();
	~BaseBuffSet();
	//
	std::list<TBuff*>	Buffs;
	//
	virtual void OnMoveBegin() override
	{
		for each (TBuff* t in Buffs)
		{
			t->OnMoveBegin();
		}
	}
	virtual void OnMoveStep() override	{

		for each (TBuff* t in Buffs)
		{
			t->OnMoveStep();
		}
	}
	virtual void OnMoveEnd()override	{

		for each (TBuff* t in Buffs)
		{
			t->OnMoveEnd();
		}
	}
	//
	virtual void OnAttackBegin()override	{

		for each (TBuff* t in Buffs)
		{
			t->OnAttackBegin();
		}
	}
	virtual void OnAttackStep()override	{

		for each (TBuff* t in Buffs)
		{
			t->OnAttackStep();
		}
	}
	virtual void OnAttackEnd()override	{

		for each (TBuff* t in Buffs)
		{
			t->OnAttackEnd();
		}
	}
	//
	virtual void OnGetDamage()override	{

		for each (TBuff* t in Buffs)
		{
			t->OnGetDamage();
		}
	}
	virtual void OnBeHit()override	{

		for each (TBuff* t in Buffs)
		{
			t->OnBeHit();
		}
	}
	//
	virtual void OnDefenseBegin()override	{

		for each (TBuff* t in Buffs)
		{
			t->OnDefenseBegin();
		}
	}
	virtual void OnDefenseStep()override	{

		for each (TBuff* t in Buffs)
		{
			t->OnDefenseStep();
		}
	}
	virtual void OnDefenseEnd()override	{

		for each (TBuff* t in Buffs)
		{
			t->OnDefenseEnd();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	virtual void OnDoBuffStep()override	
	{
		std::list<TBuff*>::iterator it;
		std::list<TBuff*>::iterator it_end = Buffs.end();

		for (it = Buffs.begin();it != it_end;)
		{
			if (it->Alive)
			{
				it->OnUpdateStep();
				it->CountdownAround();
				it++;
			}
			else
			{
				it->OnDoDettach();
				TBuff* buff = *it;
				it = Buffs.erase(it);
				delete buff;
				buff = 0;
			}
		}
	}
	//
	virtual bool AddBuff(TBuff* buff)
	{
		for each (TBuff* t in Buffs)
		{
			if (t->mID == buff->mID)
			{
				return false;
			}
		}
		//
		Buffs.push_back(buff);
		buff->OnDoAttach();
		return true;
	}
	virtual bool RemoveBuff(int buffID)
	{
		std::list<TBuff*>::iterator it;
		std::list<TBuff*>::iterator it_end = Buffs.end();

		for (it = Buffs.begin();it != it_end;)
		{
			if (it->mID == buffID)
			{
				it->OnDoDettach();
				TBuff* buff = *it;
				it = Buffs.erase(it);
				delete buff;
				buff = 0;
				return true;
			}
		}

		return false;
	}

private:
};

template<class TNode>
BaseBuffSet<TNode>::~BaseBuffSet()
{
	//删除所有的
	for each (TBuff* t in Buffs)
	{
		delete t;
	}
	Buffs.clear();
}

template<class TNode>
BaseBuffSet<TNode>::BaseBuffSet()
{

}

#endif // SkillTree_h__
