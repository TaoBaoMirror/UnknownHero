#include "MessageListenerManager.h"
#include "MessageListener.h"

MessageListenerManager* MessageListenerManager::Instance()
{
	static MessageListenerManager instance; 

	return &instance;
}

bool MessageListenerManager::RegisterMessageListener( MessageListener* MListener )
{
	if (MListener->GetListenerID() == -1)
	{
		MListener->SetListenerID(NextListenerID);
		MessageListenerDict.insert(std::make_pair(NextListenerID,MListener));
		NextListenerID++;
		return true;
	}
	//
	return false;
}

bool MessageListenerManager::UnregisterMessageListene( MessageListener* MListener )
{
	return UnregisterMessageListene(MListener->GetListenerID());
}

bool MessageListenerManager::UnregisterMessageListene( int id )
{
	return MessageListenerDict.erase(id);
}

MessageListener* MessageListenerManager::GetMessageListenerFromID( int id )
{
	auto it = MessageListenerDict.find(id);
	//
	if (it != MessageListenerDict.end())
	{
		return it->second;
	}
	//
	return NULL;
}

void MessageListenerManager::Clear()
{
	MessageListenerDict.clear();
	//
	NextListenerID = 0;
}