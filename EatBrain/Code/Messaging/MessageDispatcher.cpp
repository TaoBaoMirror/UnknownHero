#include "MessageDispatcher.h"
#include "MessageListener.h"
#include "MessageListenerManager.h"

using std::set;

//--------------------------- Instance ----------------------------------------
//
//   this class is a singleton
//-----------------------------------------------------------------------------
MessageDispatcher* MessageDispatcher::Instance()
{
  static MessageDispatcher instance; 
  
  return &instance;
}

//----------------------------- Dispatch ---------------------------------
//  
//  see description in header
//------------------------------------------------------------------------
void MessageDispatcher::Discharge(MessageListener* pReceiver, const Telegram& telegram)
{
	if (pReceiver)
	{
		if (!pReceiver->HandleMessage(telegram))
		{

		}
	}

}

//---------------------------- DispatchMsg ---------------------------
//
//  given a message, a receiver, a sender and any time delay, this function
//  routes the message to the correct agent (if no delay) or stores
//  in the message queue to be dispatched at the correct time
//------------------------------------------------------------------------
void MessageDispatcher::DispatchMsg(double       delay,
                                    int          sender,
                                    int          receiver,
                                    int          msg,
									double	     curTime,
                                    void*        AdditionalInfo = NULL)
{

  //�õ������ߵ�ָ��
  MessageListener* pReceiver = MessageListenerManager::Instance()->GetMessageListenerFromID(receiver);

  //make sure the receiver is valid
  if (pReceiver == NULL)
  {
    return;
  }
  
  //����һ���籨
  Telegram telegram(0, sender, receiver, msg, AdditionalInfo);
  
  //���û���ӳ٣���ֱ�ӷ���                    
  if (delay <= 0.0)                                                        
  {
    Discharge(pReceiver, telegram);
  }

  //������ӳپͱ��������籨
  else
  {
    double CurrentTime = curTime; 

    telegram.DispatchTime = CurrentTime + delay;

    //�������
    PriorityQ.insert(telegram);   

  }
}

//---------------------- DispatchDelayedMessages -------------------------
//
//  This function dispatches any telegrams with a timestamp that has
//  expired. Any dispatched telegrams are removed from the queue
//------------------------------------------------------------------------
void MessageDispatcher::DispatchDelayedMessages(double curtime)
{ 
  //
  double CurrentTime = curtime; 
  //�ҵ�����ʱ��ĵ籨
  while( !PriorityQ.empty() &&
	     (PriorityQ.begin()->DispatchTime < CurrentTime) && 
         (PriorityQ.begin()->DispatchTime > 0) )
  {
    const Telegram& telegram = *PriorityQ.begin();

    MessageListener* pReceiver = MessageListenerManager::Instance()->GetMessageListenerFromID(telegram.Receiver);

    Discharge(pReceiver, telegram);
	//�ӱ���Ķ�����ɾ��
    PriorityQ.erase(PriorityQ.begin());
  }
}



