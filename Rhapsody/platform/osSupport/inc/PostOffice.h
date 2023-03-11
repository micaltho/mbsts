/**
 *  \brief     Distribution of mails and messages.
 *  \details   The post office registers mail boxes and message boxes for the tasks.
 *             Mails and messages send to a task are send to these tasks and a event is generated
 *             for the receiving task.
 *             The Post office is a singleton in the system!\n
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      24.09.2015
 *  \pre       First initialize the system, based on a CMSIS RTOS API compliant RTOS
 *  \copyright HS Osnabrueck
 */

#ifndef POSTOFFICE_H_
#define POSTOFFICE_H_

/** \file */

#define OWNMAP
#ifdef OWNMAP
#include <Embmap.h>
template <typename T, typename U>
using Map = RTOS::Embmap<T, U>;
#else
#include <map>
template <typename T, typename U>
using Map = std::map<T, U>;
#endif
#include <cmsis_os.h>



namespace RTOS
{

class Task;  // forward declaration for RTOS::Task


/**
 * \enum RTOS::mailNumber_e
 * \brief enum for message numbers to enable receiver to identify different content (data type) of message.
 */
enum mailNumber_e
   {message1, message2, message3, message4, message5, message6};


/**
 * \class  PostOffice inc/PostOffice.h
 * This class handles the distribution of mails and messages between tasks.
 * Tasks register their mailboxes and messageboxes at the post office, mails and messages
 * can be send to tasks using the post office.\n
 * Sending tasks must know the receiving task but not their mailbox / messagebox.\n
 * Limitation: Each task can only register one mailbox and one messagebox.\n\n\n
 * Definition of "message":\n
 * A message is a pointer or a uint32_t value. The receiver just gets the pointer/value and
 * must know what to do with it. A message must not be free'd.\n\n
 * Definition of "mail":\n
 * A mail is wrapped in a \ref mailStruct_t envelope, the receiver gets this envelope.\n
 * The mail itself might be a pointer (sender is responsible for memory) or a fixed data chunk.
 * If a data chunk is received, the receiver must free the memory.\n
 * In any case, the memory for the envelope must be free'd by calling \ref freeMail .\n\n

 * The base class \ref Task handles the a lot of the interface to the PostOffice.
 *
 *
 */

class PostOffice
{
public:
    /**
     * \enum mailType_e
     * identifies if sender or receiver is responsible for message memory
     */
    enum mailType_e
    {
       PointerMail = 0,  ///< just a pointer is send. sender is responsible for memory.
       MemoryMail        ///< memory will be allocated for mail and must be freed after usage by receiver!
    };

    struct mailStruct_t           ///< structure of mail which is send
    {
       osThreadId   sender;        ///< who sent the message?
       osThreadId   receiver;      ///< receiver of message
       mailType_e   messageType;   ///< do we need to free message data block? see \ref mailType_e
       mailNumber_e messageNumber; ///< defines data structure of message. see messageNumber_e
       void *       message;       ///< pointer to mail data
    } ;

   /**
    * Set global timeout for message delivery and mail memory allocation.
    * @param timeout  new timeout in milliseconds
    */
   void setTimeout(uint32_t timeout) { m_timeout = timeout;}

   /// Register mailbox.
   /// \param[in]     obj   reference to task which holds mailbox (receiver)
   /// \param[in]     mailBoxId  Mailbox ID (obtained by \ref osMailCreate).
   /// \param[in]     size       size of Mail (same as in \ref osMailCreate).
   /// \return
   bool registerMailBox(const Task& obj, osMailQId mailBoxId, size_t size);

   /**
    * send a mail to task.
    * @param [in] receiver_id receiving thread
    * @param [in] sender_id   sending thread
    * @param [in] mail        mail to send
    * @param [in] number      identifier of message data type, see RTOS::mailNumber_e.
    * @param [in] type        pointer or memory message?
    * @return   true if success
    */
   bool sendMail(osThreadId   receiver_id,
                 osThreadId   sender_id,
                 void*        mail,
                 mailNumber_e number,
                 mailType_e   type) const;

   /**
    * \brief gives memory for mail back to PostOffice (e.g. RTOS)
    *
    * @param [in] mboxOwner owner of mailbox, in case mail data is not trustworthy
    * @param [in] mail  pointer to /ref mailStruct_t envelope
    * @param [in] withData if memory was allocated for mail, the memory can also free'd
    *             Default: the memory is not free'd
    * @return true is success
    */
   bool freeMail(osThreadId mboxOwner,
                 mailStruct_t * mail,
                 bool withData = false) const;


   /// \brief Register mailbox.
   ///
   /// \param[in]     obj          pointer to task which holds messagebox (receiver)
   /// \param[in]     messageBoxId Messagebox ID (obtained by \ref osMessageCreate).
   /// \return
   bool registerMessageBox(const Task& obj, osMessageQId messageBoxId);

   /**
    * \brief send a message to task.
    *
    * @param thread_id  receiving thread
    * @param message    message to send, pointer or uint32 value
    * @return           true if success
    */
   bool sendMessage(osThreadId thread_id, uint32_t message) const;

   /**
    * \brief Creates singleton and returns reference to it.
    *
    * @return reference to singleton
    */
   static PostOffice& getInstance(void);

   /**
    * \brief sets max number of mails in PostOffice Mail pool.
    *
    * This number defines the maximum number of messages which can hold in the systems.
    * A message must be free'd before reusing the memory in pool again.\n
    * \note This function must be called before \ref getInstance to have an effect.
    *       The default value is 10.
    * @param systemMailNumber  max. number of mails in pool (pool size).
    */
   static void setMaxSystemMailNumber(uint32_t systemMailNumber)
   {m_maxSystemMailNumber = systemMailNumber;}

   /**
    * get max. number of mails in PostOffice mail pool.
    * @return
    */
   static uint32_t getMaxSystemMailNumber()  {return m_maxSystemMailNumber;}
private:
   struct MboxData_t
   {
       MboxData_t(osMailQId _id = 0, size_t _size = 0):id(_id), size(_size) {}

       osMailQId id;
       size_t    size;
   };

   PostOffice();
   PostOffice(const PostOffice&) = delete;
   PostOffice operator = (const PostOffice&) = delete;
   ~PostOffice() {};

   // map Containers for task/xxBox Pair
   Map<osThreadId, MboxData_t>   m_mailBoxMap;
   Map<osThreadId, osMessageQId> m_messageBoxMap;

   uint32_t m_timeout;

   osPoolId m_mailPool;     ///< pool for \ref mailStruct_t message headers

   static uint32_t   m_maxSystemMailNumber;
};

}  // namespace RTOS


#endif /* POSTOFFICE_H_ */
