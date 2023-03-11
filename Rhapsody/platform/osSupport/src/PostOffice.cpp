/*
 * PostOffice.cpp
 *
 *  Created on: 15.09.2015
 *      Author: Wuebbelmann
 */

/** \file */

#include <cstring>

#include <PostOffice.h>
#include <TaskBase.h>

#ifdef DEBUG
#define DEBUG_RTOS_POSTOFFICE
#endif
#ifdef DEBUG_RTOS_POSTOFFICE
#include <cstdio>
#endif


namespace RTOS
{


uint32_t PostOffice::m_maxSystemMailNumber = 10;   ///< default for number of message in system

PostOffice::PostOffice():
#ifdef OWNMAP
   m_mailBoxMap(MAXMAILBOXES),
   m_messageBoxMap(m_maxSystemMailNumber),
#endif
#ifdef DEBUG_RTOS_POSTOFFICE
   m_timeout(2000),
#else
   m_timeout(osWaitForever),
#endif
   m_mailPool(0)

{
   if (m_maxSystemMailNumber)
   {
      osPoolDef_t messagePool = {m_maxSystemMailNumber,
                                 sizeof(mailStruct_t),
                                 0};
     m_mailPool = osPoolCreate(&messagePool);
   }
}


PostOffice& PostOffice::getInstance()
{
   static PostOffice m_instance;
   return m_instance;
}

// param:
//
bool PostOffice::registerMailBox(const Task& obj, osMailQId mailBoxId, size_t size)
{
    bool xcode = true;
    osThreadId taskHandle = obj.getTaskHandle();

    if (0 != mailBoxId)
    {
       MboxData_t  data = {mailBoxId, size};
       m_mailBoxMap[taskHandle] = data;
    }
    else // deregister the message box...
    {
        auto delObj = m_mailBoxMap.erase(taskHandle);
        if (0 == delObj)
        {
#ifdef DEBUG_RTOS_POSTOFFICE
        	fprintf(stderr, "*** %s Line %d: couldn't deregister Mailbox for task %s\n",
            __FILE__, __LINE__, obj.getTaskName());
#endif
            xcode = false;
        }
    }
    return xcode;
}

bool PostOffice::sendMail(osThreadId      receiver_id,
                          osThreadId      sender_id,
                          void*           mail,
                          mailNumber_e number,
                          mailType_e   type) const
{
    bool          xcode        = true;
    mailStruct_t* messageFrame = 0;
    MboxData_t    mailBoxData  = {0, 0};
    void*         data         =  0;
    if (0 == m_mailPool)  xcode = false;

    if (xcode)
    {
       // we need to allocate memory for a message frame:
       messageFrame =  (mailStruct_t*) osPoolAlloc( m_mailPool);
       if (0 != messageFrame)
       {
          messageFrame->receiver      = receiver_id;
          messageFrame->sender        = sender_id;
          messageFrame->messageNumber = number;
          messageFrame->messageType   = type;
       }
       else
       {
#ifdef DEBUG_RTOS_POSTOFFICE
           fprintf(stderr, "*** %s Line %d: couldn't allocate memory for Mail struct\n",
           __FILE__, __LINE__);
#endif
    	   xcode = false;
       }
    }
    auto it = m_mailBoxMap.find(receiver_id);
    if (xcode)
    {
       if ((it == m_mailBoxMap.end()) || (0 == (it->second).id))  xcode = false;
    }
    if (xcode)
    {
       mailBoxData = it->second;
       if (PointerMail == type)  // Pointer Mail: just set pointer as message
       {
         messageFrame->message = mail;
       }
       else   // we need to allocate memory for message and copy content
       {
         // get memory for mail
         data = osMailAlloc (mailBoxData.id, m_timeout);
         if (0 == data)
         {
#ifdef DEBUG_RTOS_POSTOFFICE
        	fprintf(stderr, "*** %s Line %d: couldn't allocate memory for mail content\n",
            __FILE__, __LINE__);
#endif
        	xcode = false;
         }
         if (xcode)
         {
            // and copy mail content in data.
            memcpy(data, mail, mailBoxData.size );
            messageFrame->message = data;
         }
       }   // if MemoryMail
    }
    if (xcode)
    {
       if (osOK != osMailPut (mailBoxData.id, (void *)messageFrame)) xcode = false;
    }
    if (xcode)  // and now inform receiver about message!
    {
       osSignalSet(receiver_id, MAILBOXEVENT);
    }
    else
    {
       if (data)         osMailFree(mailBoxData.id, data);
       if (messageFrame) osPoolFree(m_mailPool, messageFrame);
    }
    return xcode;
}


bool PostOffice::freeMail(osThreadId mboxOwner, mailStruct_t* mail, bool withData) const
{
    bool xcode = true;
    if (0 == mail) xcode = false;

    if (xcode)
    {
       if (withData && MemoryMail == mail->messageType)
       {
          auto it = m_mailBoxMap.find(mboxOwner);
          if ((it == m_mailBoxMap.end()) || (0 == (it->second).id))
          {
#ifdef DEBUG_RTOS_POSTOFFICE
        	 fprintf(stderr, "*** %s Line %d: couldn't find mailbox owner\n",
             __FILE__, __LINE__);
#endif
        	 xcode = false;
          }
          if (xcode)
          {
        	  MboxData_t mailBoxData = it->second;
        	  if (osOK != osMailFree(mailBoxData.id,  mail->message) )
        	  {
#ifdef DEBUG_RTOS_POSTOFFICE
        	     fprintf(stderr, "*** %s Line %d: couldn't free mail memory\n",
                 __FILE__, __LINE__);
#endif
        		 xcode = false;
        	  }
          }
       }
       if (osOK != osPoolFree(m_mailPool, mail) )
       {
#ifdef DEBUG_RTOS_POSTOFFICE
           fprintf(stderr, "*** %s Line %d: couldn't free mail struct memory\n",
           __FILE__, __LINE__);
#endif
           xcode = false;
       }
    }
    return xcode;
}


bool PostOffice::registerMessageBox(const Task& obj, osMessageQId messageBoxId)
{
    bool xcode = true;
    osThreadId taskHandle = obj.getTaskHandle();
    if (0 != messageBoxId)
    {
       m_messageBoxMap[taskHandle] = messageBoxId;
    }
    else // deregister the message box...
    {
        auto delObj = m_messageBoxMap.erase(taskHandle);
        if (0 == delObj)
        {
#ifdef DEBUG_RTOS_POSTOFFICE
        	fprintf(stderr, "*** %s Line %d: couldn't deregister Messagebox for task %s\n",
            __FILE__, __LINE__, obj.getTaskName());
#endif
            xcode = false;
        }
    }
    return xcode;
}


bool PostOffice::sendMessage(osThreadId thread_id, uint32_t message) const
{
    bool xcode  = false;
    auto it     = m_messageBoxMap.find(thread_id);
    if ((it == m_messageBoxMap.end())  || (0 == it->second))
    {
#ifdef DEBUG_RTOS_POSTOFFICE
        	fprintf(stderr, "*** %s Line %d: couldn't find messagebox\n",
            __FILE__, __LINE__);
#endif
        return false;
    }

    if (osOK == osMessagePut (it->second , message, m_timeout))
    {
        xcode = true;
        // notify receiver
        osSignalSet(thread_id, MESSAGEBOXEVENT);
    }
#ifdef DEBUG_RTOS_POSTOFFICE
    else
    {
        fprintf(stderr, "*** %s Line %d: couldn't put message\n",
        __FILE__, __LINE__);
    }
#endif

    return xcode;
}

}  // namespace RTOS
