#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H
#pragma warning (disable:4786)
#include <set>
#include <string>
#include "Messaging/Telegram.h"


class MessageListener;


#define Dispatcher MessageDispatcher::Instance()

const double SEND_MSG_IMMEDIATELY = 0.0;
const int    NO_ADDITIONAL_INFO   = 0;
const int    SENDER_ID_IRRELEVANT = -1;


class MessageDispatcher
{
private:  
  
  //a std::set is used as the container for the delayed messages
  //because of the benefit of automatic sorting and avoidance
  //of duplicates. Messages are sorted by their dispatch time.
  std::set<Telegram> PriorityQ;

  void Discharge(MessageListener* pReceiver, const Telegram& msg);

  MessageDispatcher() { CurTime = 0; }

  //copy ctor and assignment should be private
  MessageDispatcher(const MessageDispatcher&);
  MessageDispatcher& operator=(const MessageDispatcher&);

  //
  double CurTime;

public:

  static MessageDispatcher* Instance();

  //������Ϣ������listener. Receiving ��listener������ID.
  void DispatchMsg(double      delay,
                   int         sender,
                   int         receiver,
                   int         msg,
				   double	   curTime,
                   void*       ExtraInfo
				   );	//curTime ����Ϸʱ��

  //�����ӳٵ���Ϣ������Ϸ����ѭ�����ã�
  void DispatchDelayedMessages(double curtime);
};



#endif