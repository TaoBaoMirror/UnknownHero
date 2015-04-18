/********************************************************************
	created:	2015/03/13
	created:	13:3:2015   11:59
	filename: 	E:\cyvasse\EatBrain\Code\Messaging\MessageListenerManager.h
	file path:	E:\cyvasse\EatBrain\Code\Messaging
	file base:	MessageListenerManager
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef MessageListenerManager_h__
#define MessageListenerManager_h__
#include <map>

class MessageListener;

class MessageListenerManager
{
public:
	static MessageListenerManager* Instance();
	//
	bool RegisterMessageListener(MessageListener* MListener);
	bool UnregisterMessageListene(MessageListener* MListener);
	bool UnregisterMessageListene(int id);
	MessageListener*	GetMessageListenerFromID(int id);
	void Clear();
	//
protected:
	std::map<int,MessageListener*>	MessageListenerDict;
	int		NextListenerID;
private:
	MessageListenerManager():NextListenerID(0){}	//
	MessageListenerManager(const MessageListenerManager&);
	MessageListenerManager& operator=(const MessageListenerManager&);
};

#endif // MessageListenerManager_h__
