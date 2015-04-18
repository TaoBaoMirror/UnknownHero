#ifndef GOAL_COMPOSITE_H
#define GOAL_COMPOSITE_H


#include <list>
#include "Goal.h"


template <class entity_type>
class Goal_Composite : public Goal<entity_type>
{
private:

    typedef std::list<Goal<entity_type>* > SubgoalList;

protected:

  //子意图
  SubgoalList   m_SubGoals;


  //执行子意图
  int  ProcessSubgoals();

  //将消息传递到最前面的子意图
  bool ForwardMessageToFrontMostSubgoal(const Telegram& msg);


public:

  Goal_Composite(entity_type* pE, int type):Goal<entity_type>(pE,type){}

  virtual ~Goal_Composite(){RemoveAllSubgoals();}

  //当意图已经激活的逻辑
  virtual void Activate() = 0;

  //在每次updata都执行的逻辑
  virtual int  Process() = 0;

  //在意图被析构之前的逻辑
  virtual void Terminate() = 0;

  virtual bool HandleMessage(const Telegram& msg)
  { return ForwardMessageToFrontMostSubgoal(msg);}

  //增加一个子意图到意图列表的最前面
  void         AddSubgoal(Goal<entity_type>* g);

  void         RemoveAllSubgoals();
};





//---------------------- RemoveAllSubgoals ------------------------------------
//-----------------------------------------------------------------------------
template <class entity_type>
void Goal_Composite<entity_type>::RemoveAllSubgoals()
{
  for (SubgoalList::iterator it = m_SubGoals.begin();
       it != m_SubGoals.end();
       ++it)
  {  
    (*it)->Terminate();
    
    delete *it;
  }

  m_SubGoals.clear();
}
 

//-------------------------- ProcessSubGoals ----------------------------------
//
//  这个方法首先会移除子意图列表中‘合成的意图’. 然后会执行列表中的下一个意图 (如果有的话)
//-----------------------------------------------------------------------------
template <class entity_type>
int Goal_Composite<entity_type>::ProcessSubgoals()
{ 
  //移除子意图里面中所有完成或者失败的意图
  while (!m_SubGoals.empty() &&
         (m_SubGoals.front()->isComplete() || m_SubGoals.front()->hasFailed()))
  {    
    m_SubGoals.front()->Terminate();
    delete m_SubGoals.front(); 
    m_SubGoals.pop_front();
  }

  //如果子意图列表还有剩余, 执行他的第一个意图
  if (!m_SubGoals.empty())
  { 
    //得到最前面子意图的状态
    int StatusOfSubGoals = m_SubGoals.front()->Process();

    //我们会测试释放这个最前面的子意图会返回'completed'
    //而且同时会判断 子意图列表的情况.当
    //是这种情况, 为了确保他的父级会保持他的进度
    //我们一定会返回 'active' 状态.
    if (StatusOfSubGoals == completed && m_SubGoals.size() > 1)
    {
      return active;
    }

    return StatusOfSubGoals;
  }
  
  //没有其他子意图被执行 - 返回 'completed'
  else
  {
    return completed;
  }
}

//----------------------------- AddSubgoal ------------------------------------
template <class entity_type>
void Goal_Composite<entity_type>::AddSubgoal(Goal<entity_type>* g)
{   
  //加到最前面
  m_SubGoals.push_front(g);
}


template <class entity_type>
bool Goal_Composite<entity_type>::ForwardMessageToFrontMostSubgoal(const Telegram& msg)
{
  if (!m_SubGoals.empty())
  {
    return m_SubGoals.front()->HandleMessage(msg);
  }

  return false;
}
#endif

