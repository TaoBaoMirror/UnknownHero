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

  //����ͼ
  SubgoalList   m_SubGoals;


  //ִ������ͼ
  int  ProcessSubgoals();

  //����Ϣ���ݵ���ǰ�������ͼ
  bool ForwardMessageToFrontMostSubgoal(const Telegram& msg);


public:

  Goal_Composite(entity_type* pE, int type):Goal<entity_type>(pE,type){}

  virtual ~Goal_Composite(){RemoveAllSubgoals();}

  //����ͼ�Ѿ�������߼�
  virtual void Activate() = 0;

  //��ÿ��updata��ִ�е��߼�
  virtual int  Process() = 0;

  //����ͼ������֮ǰ���߼�
  virtual void Terminate() = 0;

  virtual bool HandleMessage(const Telegram& msg)
  { return ForwardMessageToFrontMostSubgoal(msg);}

  //����һ������ͼ����ͼ�б����ǰ��
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
//  ����������Ȼ��Ƴ�����ͼ�б��С��ϳɵ���ͼ��. Ȼ���ִ���б��е���һ����ͼ (����еĻ�)
//-----------------------------------------------------------------------------
template <class entity_type>
int Goal_Composite<entity_type>::ProcessSubgoals()
{ 
  //�Ƴ�����ͼ������������ɻ���ʧ�ܵ���ͼ
  while (!m_SubGoals.empty() &&
         (m_SubGoals.front()->isComplete() || m_SubGoals.front()->hasFailed()))
  {    
    m_SubGoals.front()->Terminate();
    delete m_SubGoals.front(); 
    m_SubGoals.pop_front();
  }

  //�������ͼ�б���ʣ��, ִ�����ĵ�һ����ͼ
  if (!m_SubGoals.empty())
  { 
    //�õ���ǰ������ͼ��״̬
    int StatusOfSubGoals = m_SubGoals.front()->Process();

    //���ǻ�����ͷ������ǰ�������ͼ�᷵��'completed'
    //����ͬʱ���ж� ����ͼ�б�����.��
    //���������, Ϊ��ȷ�����ĸ����ᱣ�����Ľ���
    //����һ���᷵�� 'active' ״̬.
    if (StatusOfSubGoals == completed && m_SubGoals.size() > 1)
    {
      return active;
    }

    return StatusOfSubGoals;
  }
  
  //û����������ͼ��ִ�� - ���� 'completed'
  else
  {
    return completed;
  }
}

//----------------------------- AddSubgoal ------------------------------------
template <class entity_type>
void Goal_Composite<entity_type>::AddSubgoal(Goal<entity_type>* g)
{   
  //�ӵ���ǰ��
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

