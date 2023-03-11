/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Monitor/TestConductor/RXF_Monitor.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Monitor_H
#define RXF_Monitor_H

#include "RXF_Types.h"
#include "RXF_Task.h"
#include <string.h>
namespace RXF {
    class MonitorIO;
    
    class Monitor : public Task {
    private :
    
        #define MONITOR_IMPLEMENTATIONTYPE 2U
        #define MONITOR_COMMAND_SEND_BUFFER_RESET_LENGTH	1U
        #define MONITOR_COMMAND_SEND_RTC_INFO_LENGTH		12U
        #define MONITOR_COMMAND_SEND_RTC_COV_LENGTH			8U
        enum sendIds
        {
            MONITOR_COMMAND_SEND_BUFFER_RESET = 2U,
            MONITOR_COMMAND_SEND_RTC_MSG = 3U,
            MONITOR_COMMAND_SEND_RTC_EXIT = 4U,
            MONITOR_COMMAND_SEND_RTC_COV_MSG = 5U
        };
        
        #define MONITOR_TARGET_ID 0
    
    public :
    
        #define WSTMonitor_sendRTCInfo RXF::Monitor::getMonitor().sendRTCInfo
        #define WSTMonitor_sendRTCCovInfo RXF::Monitor::getMonitor().sendRTCCovInfo
        #define WSTMonitor_RTC_Exit RXF::Monitor::getMonitor().RTC_Exit
        #define WSTMonitor_executeOnce RXF::Monitor::getMonitor().executeOnce
        void performCmd(void);
        
        void initImplementation(void);
        
        void sendBufferReset(void);
        
        void sendRTCInfo(const std::uint32_t e, const std::uint32_t ln, const std::uint32_t nr);
        
        void sendRTCCovInfo(char* c, const std::uint32_t i, const std::uint32_t j);
        
        void RTC_Exit(void);
        
        void sendBufferFull(void);
        
        virtual void executeOnce(void);
    
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
    
        static const std::uint8_t MONITOR_COMMAND_SEND_VERSION;
        
        static const std::uint8_t MONITOR_COMMAND_SEND_VERSION_LENGTH;
        
        static const std::uint8_t MONITOR_MAJOR_VERSION;
        
        static const std::uint8_t MONITOR_TEST_VERSION;
        
        static const std::uint8_t MONITOR_VERSION;
        
        bool bufferFull;
        
        static bool initDone;
        
        static Monitor instance;
        
        static MonitorIO & itsMonitorIO;
        
        std::int8_t receivedByteCount;
    };
    
    // For V6 backward compatibility 
    #define monitorNbCmd 1
    #define WSTMonitor_pollIncomingData()
    #define WSTMonitor_performCmd RXF::Monitor::getMonitor().executeOnce
    
    inline Monitor& Monitor::getMonitor(void)
    {
        return instance;
    }
}

#endif
/*********************************************************************
	File Path	: ../Source/Monitor/TestConductor/RXF_Monitor.h
*********************************************************************/
