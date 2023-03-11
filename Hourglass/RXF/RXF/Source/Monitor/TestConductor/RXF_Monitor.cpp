/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Monitor/TestConductor/RXF_Monitor.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/
 
 #include "RXF_Config.h"
  extern char GlobalTestCaseVar[ MON_RECEIVE_COMMAND_BUFFER_SIZE ];

#include "RXF_Monitor.h"
#include "RXF_CriticalSection.h"
#include "RXF_EventQueue.h"
#include "RXF_MonitorIO.h"
namespace RXF {
    
    static MonitorIO itsMonitorIO_Object;
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_VERSION(0U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_VERSION_LENGTH(5U);
    
    const std::uint8_t Monitor::MONITOR_MAJOR_VERSION(0U);
    
    const std::uint8_t Monitor::MONITOR_TEST_VERSION(6U);
    
    const std::uint8_t Monitor::MONITOR_VERSION(0U);
    
    bool Monitor::initDone(false);
    
    Monitor Monitor::instance;
    
    MonitorIO & Monitor::itsMonitorIO(itsMonitorIO_Object);
    
    void Monitor::performCmd(void)
    {
        uint16_t				 i = 0U;
        uint16_t				 length ;
        
        length = itsMonitorIO.read();
        (void)itsMonitorIO.read();
        
        if(length != 0U){
        	for( i = 0U; i < length; i++ )
        	{
        		GlobalTestCaseVar[i] = itsMonitorIO.read();
        	}
        }
    }
    
    void Monitor::initImplementation(void)
    {
    }
    
    void Monitor::sendBufferReset(void)
    {
    }
    
    void Monitor::sendRTCInfo(const std::uint32_t e, const std::uint32_t ln, const std::uint32_t nr)
    {
        uint8_t buffer[ 14 ];
        uint32_t i;
        buffer[ 0U ] = MONITOR_COMMAND_SEND_RTC_INFO_LENGTH; 
        buffer[ 1U ] = MONITOR_COMMAND_SEND_RTC_MSG; 
        
        for( i = 0U; i < 4U; i++ )
        {
        	buffer[ i + 2U ] = (reinterpret_cast<const uint8_t*>(&e))[ i ];
        }
        for( i = 0U; i < 4U; i++ )
        {
        	buffer[ i + 6U ] = (reinterpret_cast<const uint8_t*>(&ln))[ i ];
        } 
        for( i = 0U; i < 4U; i++ )
        {
        	buffer[ i + 10U ] = (reinterpret_cast<const uint8_t*>(&nr))[ i ];
        } 
        
        addCommand( 14U, buffer );
        
    }
    
    void Monitor::sendRTCCovInfo(char* c, const std::uint32_t i, const std::uint32_t j)
    {
        uint8_t buffer[ 42U ];
        uint32_t iter;
        uint32_t len = static_cast<uint32_t>(strlen(c)) + 1U;
        buffer[ 0U ] = MONITOR_COMMAND_SEND_RTC_COV_LENGTH + len; 
        buffer[ 1U ] = MONITOR_COMMAND_SEND_RTC_COV_MSG; 
        
        for( iter = 0U; iter < 4U; iter++ )
        {
        	buffer[ iter + 2U ] = (reinterpret_cast<const uint8_t*>(&i))[ iter ];
        }
        for( iter = 0U; iter < 4U; iter++ )
        {
        	buffer[ iter + 6U ] = (reinterpret_cast<const uint8_t*>(&j))[ iter ];
        }  
        for( iter = 0U; iter < len; iter++ )
        {
        	buffer[ iter + 10U ] = (reinterpret_cast<uint8_t*>(c))[iter];
        }
        buffer[ iter + 10U ] = 0;
        
        addCommand( MONITOR_COMMAND_SEND_RTC_COV_LENGTH + len +3U, buffer );
    }
    
    void Monitor::RTC_Exit(void)
    {
        uint8_t cmdBuff[ 2 ] = { 0 , MONITOR_COMMAND_SEND_RTC_EXIT };
        addCommand( 2U, cmdBuff );
    }
    
    void Monitor::sendBufferFull(void)
    {
        static uint8_t cmdBuff[ 2 ] = { 0U, MONITOR_COMMAND_SEND_BUFFER_RESET};
        
        itsMonitorIO.addResetCommand( sizeof( cmdBuff ), cmdBuff );
    }
    
    void Monitor::executeOnce(void)
    {
        executeOnceMon();
    }
    
    #ifdef RXF_Priority_H
    void Monitor::execute(void)
    {
        while( isRunning() )
        {
        	executeOnceMon();
        }
    }
    
    #endif /* RXF_Priority_H */ 
    
    
    void Monitor::executeOnceMon(void)
    {
        itsMonitorIO.sendData(); 
        if( itsMonitorIO.checkDataAvailable() )
        {
        	performCmd();
        }
    }
    
    void Monitor::init(void)
    {
        itsMonitorIO.init();
        
        if( !initDone )
        {
        	instance.sendVersion();
        	instance.initImplementation();
        	initDone = true; 
        }
        itsMonitorIO.sendData(); 
        
        #ifdef RXF_Priority_H
        instance.startTask();
        #endif /* RXF_Priority_H */
    }
    
    void Monitor::cleanup(void)
    {
        #ifdef RXF_Priority_H
        instance.endTask();
        #endif /* RXF_Priority_H */
    }
    
    void Monitor::sendVersion(void)
    {
        uint8_t cmdBuffVersion[ 7U ]= { MONITOR_COMMAND_SEND_VERSION_LENGTH, 
                                      MONITOR_COMMAND_SEND_VERSION, 
                                      MONITOR_TEST_VERSION, 
                                      MONITOR_MAJOR_VERSION, 
                                      MONITOR_VERSION, 
                                      MONITOR_IMPLEMENTATIONTYPE,
                                      MONITOR_TARGET_ID };
        
        addCommand( 7U, &cmdBuffVersion[ 0 ] );
    }
    
    void Monitor::addCommand(const std::uint32_t size, const std::uint8_t* const data)
    {
        if( !itsMonitorIO.addCommand( size, data ) )
        {   
        	if( !bufferFull ) 
        	{
        		bufferFull = true;
        		sendBufferFull();
        	} 	
        }
        else
        {
        	bufferFull = false;
        }
        
    }
    
    Monitor::Monitor(void) : 
    #ifdef RXF_Priority_H
    /* @MISRA_12-8-1=OFF XD-0001: Access global data. Needed to get Task priority. */
    Task(MON_TASK_NAME, MON_TASK_PRIORITY, MON_TASK_STACK_SIZE),
    /* @MISRA_12-8-1=ON (end of XD-0001) */
    #endif /* NO_RTOS */
    bufferFull(false), receivedByteCount(0)
    {
    }
    
    void * Monitor::getStackMemory(void)
    {
        #ifdef TSK_STACK_MEMORY_ATTRIBUTE
        static void * monitorStackMemory[((MON_TASK_STACK_SIZE+sizeof(void*))-1U)/sizeof(void*)];
        return monitorStackMemory;                                                                
        #else /* TSK_STACK_MEMORY_ATTRIBUTE */
        return nullptr;
        #endif
        
    }
}

/*********************************************************************
	File Path	: ../Source/Monitor/TestConductor/RXF_Monitor.cpp
*********************************************************************/
