#include "SkillTree.h"

_BaseTreeNode::_BaseTreeNode() :mValue(0),mParent(0),mID(-1),mActive(false),mLocked(false)
{
	mKids.resize(BaseTreeNodeKidsNum,0);
}

_BaseTreeNode::~_BaseTreeNode()
{
	for (int i = 0;i< mKids.size();++i)
	{
		delete mKids[i];
		mKids[i] = 0;
	}
	//
	delete mValue;// weather delete????
}

void _BaseTreeNode::AddKid( _BaseTreeNode* node )
{
	for (int i = 0;i< mKids.size();++i)
	{
		if (mKids[i] == 0)
		{
			mKids[i] = node;
			node->mParent = this;
		}
	}
}

void _BaseTreeNode::RemoveKid( _BaseTreeNode* node )
{
	for (int i = 0;i< mKids.size();++i)
	{
		if(mKids[i] == node)
		{
			delete node;
			mKids[i] = 0;
		}
		//
	}
}

void _BaseTreeNode::SetActive( bool active )
{
	mActive= active;
}

bool _BaseTreeNode::SetLocked()
{
	//
	mLocked = true;
	//
	for (int i = 0;i< mKids.size();++i)
	{
		if(mKids[i]) (mKids[i])->SetLocked();
	}
	//
	return true;
}

bool _BaseTreeNode::SetUnLocked()
{
	if (mParent && mParent->mLocked)
	{
		return false;
	}
	//
	mLocked = false;
	//
	for (int i = 0;i< mKids.size();++i)
	{
		if(mKids[i]) (mKids[i])->SetUnLocked();
	}
	//
	return true;
}


//////////////////////////////////////////////////////////////////////////
