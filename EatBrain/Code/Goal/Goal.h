#ifndef Goal_h__
#define Goal_h__


struct Telegram;

template <class entity_type>
class Goal
{
public: 
	enum {active, inactive, completed, failed};
public:
	//
	Goal(entity_type*  pE, int type):m_iType(type),
		m_pOwner(pE),
		m_iStatus(inactive)
	{}

	virtual ~Goal(){}

	virtual void Activate() = 0;

	virtual int  Process() = 0;

	virtual void Terminate() = 0;

	virtual bool HandleMessage(const Telegram& msg){return false;}

	virtual void AddSubgoal(Goal<entity_type>* g)
	{throw std::runtime_error("Cannot add goals to atomic goals");}


	bool         isComplete()const{return m_iStatus == completed;} 
	bool         isActive()const{return m_iStatus == active;}
	bool         isInactive()const{return m_iStatus == inactive;}
	bool         hasFailed()const{return m_iStatus == failed;}
	int          GetType()const{return m_iType;}

protected:
	int             m_iType;

	entity_type*    m_pOwner;

	//(active, inactive,completed, failed)
	int             m_iStatus;

	void ActivateIfInactive();
	void ReactivateIfFailed();


private:
};

template <class entity_type>
void  Goal<entity_type>::ReactivateIfFailed()
{
	if (hasFailed())
	{
		m_iStatus = inactive;
	}
}


template <class entity_type>
void  Goal<entity_type>::ActivateIfInactive()
{
	if (isInactive())
	{
		Activate();   
	}
}
#endif // Tactics_h__
