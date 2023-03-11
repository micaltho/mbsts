/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Monitor/Full/RXF_Monitor.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Monitor_H
#define RXF_Monitor_H

#include "RXF_Types.h"
#include "RXF_Task.h"
namespace RXF {
    class Event;
    
    class MonitorIO;
    
    class Reactive;
    
    class WSTMonitorEventCreate;
    
    class WSTMonitorEventEnd;
    
    class WSTMonitorEventStart;
    
    class WSTMonitorTimeout;
    
    class Monitor : public Task {
    public :
    
        class WSTMonitorBreakPoint;
        
        class WSTMonitorOperationCall;
        
        class WSTMonitorTimeOffset;
    
    private :
    
        enum receiveIds
        {
            MONITOR_COMMAND_SUSPEND = 0U,
            MONITOR_COMMAND_RESUME = 1U,
            MONITOR_COMMAND_REQUEST_ATTRIBUTE = 2U,
            MONITOR_COMMAND_REQUEST_STATE = 3U,
            MONITOR_COMMAND_RECEIVE_EVENT = 4U,
            MONITOR_COMMAND_ADD_BREAKPOINT = 5U,
            MONITOR_COMMAND_REMOVE_BREAKPOINT = 6U,
            MONITOR_COMMAND_INSTANCE_FILTER = 7U,
            MONITOR_COMMAND_TIME_SYNC = 8U,
            MONITOR_COMMAND_DEBUG_INT_FILTER = 9U
        };
    
    public :
    
        typedef std::uint8_t WSTMonitorStateType;
        
        class WSTMonitorBreakPoint {
            ////    Attributes    ////
            
        public :
        
            Reactive* destination;
            
            std::uint16_t state;
            
            std::int16_t eventID;
            
            WSTMonitorBreakPoint* next;
        };
        
        class WSTMonitorOperationCall {
        public :
        
            inline WSTMonitorOperationCall(const void * source, const void * destination, const std::uint16_t id, const std::uint8_t currentTick) : source(source),destination(destination),id(id),currentTick(currentTick)
            {
            }
            
            ////    Attributes    ////
        
        private :
        
            const void* source;
            
            const void* destination;
            
            std::uint16_t id;
            
            std::uint8_t currentTick;
            
            #define MONITOR_OPERATION_CALL_CONTENT_SIZE static_cast<uint8_t>(sizeof(void*) + sizeof(void*) + sizeof(uint16_t) + sizeof(uint8_t))
        };
        
         class WSTMonitorTimeOffset {
            ////    Attributes    ////
            
        private :
        
            std::uint32_t offset;
        };
    
    private :
    
        void sendEventCreate(const WSTMonitorEventCreate* const pEventData, const std::uint8_t parameterSize, const std::uint8_t* const parameter);
        
        void sendEventStart(const WSTMonitorEventStart* const pEventData);
        
        void sendEventEnd(const WSTMonitorEventEnd* const pEventData);
        
        void sendTimeOut(const WSTMonitorTimeout* const pEventData);
        
        void performCmd(void);
        
        void resumeRxf(void);
        
        void suspendRxf(void);
        
        inline std::uint16_t increaseEventID(void);
    
    public :
    
        void sendEventCreate(Event* const event, const void * const source, Reactive* const destination);
        
        void sendEventStart(const Event* const event);
        
        void sendEventEnd(const Event* const event);
        
        inline void setMonitorStopFlag(const bool p_monitorStopFlag)
        {
            monitorStopFlag = p_monitorStopFlag;
        }
        
        inline bool getMonitorStopFlag(void) const
        {
            return monitorStopFlag;
        }
        
        const WSTMonitorBreakPoint* getFirstBreakPoint(void) const;
        
        #ifdef MON_USE_SEND_INT
        void addObjectToSendIntList(const void * const object) const;
        #endif /* MON_USE_SEND_INT */     
        
        
        #ifdef MON_USE_SEND_INT
        void removeObjectToSendIntList(const void * const object) const;
        #endif /* MON_USE_SEND_INT */     
        
        
        void sendDestroy(const void * const me);
        
        void sendError(void);
        
        void sendInit(const void * const me, const std::uint16_t id, const void * const firstAttributeAddress);
    
    private :
    
        void sendStateSize(void);
        
        void sendTypeSize(void);
    
    public :
    
        void initImplementation(void);
        
        void sendOpCall(const void * const source, const void * const destination, const std::uint16_t id, const RXF::char_t* const paramStart, const RXF::char_t* const paramEnd);
    
    private :
    
        void sendTimeOffset(void);
        
        void sendTimeReset(void);
    
    public :
    
        #ifdef MON_USE_SEND_INT
        void sendIntValue(const void * const destination, const std::uint32_t value);
        #endif /* MON_USE_SEND_INT */     
        
        
        void sendBufferFull(void) const;
        
        void consoleMessage(const RXF::char_t* const message);
    
    protected :
    
        #ifdef RXF_Priority_H
        virtual void execute(void);
        #endif /* RXF_Priority_H */
    
    public :
    
        void executeOnceMon(void);
        
        static void init(void);
        
        static void cleanup(void);
    
    private :
    
        void sendVersion(void);
        
        void addCommand(const std::uint32_t size, const std::uint8_t* const data);
    
    public :
    
        inline static Monitor& getMonitor(void);
    
    private :
    
        Monitor(void);
    
    public :
    
        virtual void * getStackMemory(void);
        
        ////    Attributes    ////
    
    private :
    
        static const std::uint8_t MONITOR_COMMAND_SEND_ATTRIB;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_BUFFER_RESET;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_CONSOLE_MESSAGE;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_DESTROY;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_ERROR;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_EVENT_CREATE;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_EVENT_END;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_EVENT_START;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_EVENT_TRACE;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_INIT;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_INT_VALUE;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_OPERATION;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_STATE;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_STATESIZE;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_TIMEOUT;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_TIMEOUT_TRACE;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_TIME_OFFSET;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_TIME_RESET;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_TYPES;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_VERSION;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_VERSION_LENGTH;
        
        static const std::uint8_t MONITOR_MAJOR_VERSION;
        
        // This size is used to store the parameter data into a object array which is then passed to the send command methods. It is necessary to create space for the parameter data which can an should not be dynamic inside the send methods.
        // 
        // This value is intended to be defined by the simplifier lateron to set it to a maximum value which can be determined by the generating model.
        static const std::uint32_t MONITOR_MAX_PARAMETER_SIZE;
        
        static const std::uint8_t MONITOR_TEST_VERSION;
        
        static const std::uint8_t MONITOR_VERSION;
        
        bool bufferFull;
        
        std::uint16_t eventID;
        
        static bool initDone;
        
        static Monitor instance;
        
        static MonitorIO & itsMonitorIO;
        
        bool monitorStopFlag;
        
        std::int8_t receivedByteCount;
        
        std::uint32_t syncTick;
        
        std::uint32_t timeOffset;
        
        ////    Relations and components    ////
        
        WSTMonitorBreakPoint* firstBreakPoint;
    };
    
    inline std::uint16_t Monitor::increaseEventID(void)
    {
        return eventID++;
    }
    
    inline Monitor& Monitor::getMonitor(void)
    {
        return instance;
    }
}

#endif
/*********************************************************************
	File Path	: ../Source/Monitor/Full/RXF_Monitor.h
*********************************************************************/
