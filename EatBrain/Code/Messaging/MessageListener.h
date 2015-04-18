/********************************************************************
	created:	2015/03/13
	created:	13:3:2015   11:29
	filename: 	E:\cyvasse\EatBrain\Code\Messaging\MessageListener.h
	file path:	E:\cyvasse\EatBrain\Code\Messaging
	file base:	MessageListener
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef MessageListener_h__
#define MessageListener_h__

#include "Messaging/Telegram.h"

class MessageListener
{
	friend class MessageListenerManager;
public:
	MessageListener():m_ListenerID(-1){}
	virtual ~MessageListener(){}
	//
	virtual bool HandleMessage(const Telegram& telegram)
	{
		return false;
	}
	//
	int		GetListenerID(){return m_ListenerID;}
protected:
	int		m_ListenerID;
	void	SetListenerID(int id){ m_ListenerID = id; }
private:
};

#endif // MessageListener_h__
