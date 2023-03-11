/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Monitor/Trace/RXF_Monitor.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_Monitor.h"
#include "RXF_Config.h"
#include "RXF_CriticalSection.h"
#include "RXF_Event.h"
#include "RXF_EventQueue.h"
#include "RXF_MonitorIO.h"
#include "RXF_Reactive.h"
#include <string.h>
#include "RXF_Tick.h"
#include "RXF_MonitorContainer.h"
namespace RXF {
    
    static MonitorIO itsMonitorIO_Object; 
    
    #ifdef MON_USE_SEND_INT
    static void * printIntObjectArray[MON_MAX_PRINT_INT_OBJECTS];
    static uint32_t printIntPosition;
    #endif /* MON_USE_SEND_INT */
    
    #ifdef MONITOR_MULTI
     static const uint8_t MONITOR_IMPLEMENTATIONTYPE = 1U;
    #else
     static const uint8_t MONITOR_IMPLEMENTATIONTYPE = 0U;
    #endif
    
    #ifndef MONITOR_DATA_OFFSET
     #ifdef MONITOR_MULTI
      static const uint32_t MONITOR_DATA_OFFSET = 1U;
     #else
      static const uint32_t MONITOR_DATA_OFFSET = 0U;
     #endif  
    #endif
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_ATTRIB(5U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_BUFFER_RESET(1U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_CONSOLE_MESSAGE(19U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_DESTROY(8U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_ERROR(2U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_EVENT_CREATE(9U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_EVENT_END(11U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_EVENT_START(10U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_EVENT_TRACE(14U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_INIT(7U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_INT_VALUE(16U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_OPERATION(13U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_STATE(6U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_STATESIZE(3U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_TIMEOUT(12U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_TIMEOUT_TRACE(17U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_TIME_OFFSET(15U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_TIME_RESET(18U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_TYPES(4U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_VERSION(0U);
    
    const std::uint8_t Monitor::MONITOR_COMMAND_SEND_VERSION_LENGTH(5U);
    
    const std::uint8_t Monitor::MONITOR_MAJOR_VERSION(0U);
    
    const std::uint32_t Monitor::MONITOR_MAX_PARAMETER_SIZE(42U);
    
    const std::uint8_t Monitor::MONITOR_TEST_VERSION(6U);
    
    const std::uint8_t Monitor::MONITOR_VERSION(0U);
    
    bool Monitor::initDone(false);
    
    Monitor Monitor::instance;
    
    MonitorIO & Monitor::itsMonitorIO(itsMonitorIO_Object);
    
    void Monitor::performCmd(void)
    {
        uint16_t	i = 0U;
        uint16_t	length ;
        uint8_t		command;
        uint8_t 	commandBuffer[MON_RECEIVE_COMMAND_BUFFER_SIZE];
        
        length = itsMonitorIO.read();
        command = itsMonitorIO.read();
        
        if(length != 0U){
        	for( i = 0U; i < length; i++ )
        	{
        		commandBuffer[i] = itsMonitorIO.read();
        	}
        }
        
        switch( command )
        {
        
        	case MONITOR_COMMAND_INSTANCE_FILTER:
        	{
        		/* @MISRA_5-2-7=OFF XD-0001: Cast from pointer to pointer to accesses received data from byte stream. */
        		Reactive *destination = *reinterpret_cast<Reactive**>(commandBuffer); 
        		/* @MISRA_5-2-7=ON (end of XD-0001) */
        		if( commandBuffer[ sizeof(void*) ] == 1U )
        		{
        			destination->setObjectFilterd( false );
        		}
        		else
        		{
        			destination->setObjectFilterd( true );
        		}
        		break;
        	}   
        
        	case MONITOR_COMMAND_TIME_SYNC:
        	{     
        		sendTimeReset();       
        		syncTick = Tick::getTicks();
        		break;
        	}  
        
        #ifdef MON_USE_SEND_INT
        	case MONITOR_COMMAND_DEBUG_INT_FILTER:
        	{         
        		void *object = *reinterpret_cast<void**>(commandBuffer);
        		if( commandBuffer[ sizeof(void*) ] == 1U )
        		{
        			addObjectToSendIntList( object );
        		}
        		else
        		{
        			removeObjectToSendIntList( object );
        		}
        		
        		break;
        	}  
        #endif /* MON_USE_SEND_INT */ 
        
        
        	default:
        	{ 
        		break;
        	}
        }	
    }
    
    void Monitor::sendEventStart(Event* const event)
    {
        const RXF::Event::Id_t id = event->getId();
        uint32_t timeStamp = Tick::getTicks() - syncTick;
        if( (timeStamp & 0xFFFFFF00U) != timeOffset )
        {
            timeOffset = timeStamp & 0xFFFFFF00U;
            sendTimeOffset();
        }	
        if( id == RXF::Event::DefaultEventIds::TIMEOUT_EVENT_ID )
        {
        	WSTMonitorTraceTimeout monitorTraceTimeoutMessage(event->getDestination(), static_cast<uint8_t>(timeStamp));
        	event->getDestination()->getActiveState( monitorTraceTimeoutMessage.getCurrentState(), 0U );
        	sendTimeOut(&monitorTraceTimeoutMessage);
        }
        else
        {
        	WSTMonitorTraceEvent monitorTraceEventMessage( event->getSource(), event->getDestination(), event->getId(), static_cast<uint8_t>(timeStamp));
          event->getDestination()->getActiveState( monitorTraceEventMessage.getCurrentState(), 0U );	
            /* @MISRA_5-2-7,5-0-15=OFF XD-0001: Cast from pointer to pointer to accesses received data from byte stream. */
        	uint8_t* eventArgument = reinterpret_cast<uint8_t*>(event + 1); // event arguments are always located after the event
        	/* @MISRA_5-2-7,5-0-15=ON (end of XD-0001) */
        	    	
        	sendTraceEvent(&monitorTraceEventMessage, event->getSize(), eventArgument);
        }
    }
    
    void Monitor::sendTimeOut(const WSTMonitorTraceTimeout* const pEventData)
    {
        // command header + data offset (e.g. for target ID) + message content size
        uint8_t buffer[ 2U + MONITOR_DATA_OFFSET + MONITOR_TRACE_TIMEOUT_CONTENT_SIZE ]; 
        uint32_t dataIndex;
        
        buffer[ 0U ] = MONITOR_TRACE_TIMEOUT_CONTENT_SIZE + MONITOR_DATA_OFFSET;
        buffer[ 1U ] = MONITOR_COMMAND_SEND_TIMEOUT_TRACE;
        #ifdef MONITOR_MULTI
        buffer[ 2U ] = MONITOR_TARGET_ID;
        #endif
        // copy eventData to buffer beginning at the current buffer index
        for( dataIndex = 0U; dataIndex < MONITOR_TRACE_TIMEOUT_CONTENT_SIZE; dataIndex++ )
        {
        	/* @MISRA_5-0-15,5-2-5,5-2-7=OFF XD-0001: Cast from pointer to uint8_t required eventData. */
        	buffer[ 2U + MONITOR_DATA_OFFSET + dataIndex ] = (reinterpret_cast<uint8_t*>(const_cast<WSTMonitorTraceTimeout*>(pEventData)))[ dataIndex ];
        	/* @MISRA_5-0-15,5-2-5,5-2-7=ON (end of XD-0001) */
        }  
         
        addCommand( static_cast<uint32_t>(sizeof(buffer)), &buffer[ 0 ] );
    }
    
    void Monitor::sendTraceEvent(const WSTMonitorTraceEvent* const pEventData, const std::uint8_t parameterSize, const std::uint8_t* const parameter)
    {
        // command header + data offset (e.g. for target ID) + message content size + parametersize
        #ifdef MONITOR_SENDPARAMETERS
        uint8_t buffer[ 2U + MONITOR_DATA_OFFSET + MONITOR_TRACE_EVENT_CONTENT_SIZE + MONITOR_MAX_PARAMETER_SIZE ]; 
        #else
        // create array without space for parameter data
        uint8_t buffer[ 2U + MONITOR_DATA_OFFSET + MONITOR_TRACE_EVENT_CONTENT_SIZE ]; 
        #endif
        
        uint32_t dataIndex; 
        
        buffer[ 0U ] = MONITOR_TRACE_EVENT_CONTENT_SIZE + parameterSize + MONITOR_DATA_OFFSET;
        buffer[ 1U ] = MONITOR_COMMAND_SEND_EVENT_TRACE;
        #ifdef MONITOR_MULTI
        buffer[ 2U ] = MONITOR_TARGET_ID; 
        #endif
        
        // copy eventData to buffer beginning at the current buffer index
        for( dataIndex = 0U; dataIndex < MONITOR_TRACE_EVENT_CONTENT_SIZE; dataIndex++ )
        {
        	/* @MISRA_5-0-15,5-2-5,5-2-7=OFF XD-0001: Cast from pointer to uint8_t required eventData. */
        	buffer[ 2U + MONITOR_DATA_OFFSET + dataIndex ] = (reinterpret_cast<uint8_t*>(const_cast<WSTMonitorTraceEvent*>(pEventData)))[ dataIndex ];
        	/* @MISRA_5-0-15,5-2-5,5-2-7=ON (end of XD-0001) */
        }
        
        #ifdef MONITOR_SENDPARAMETERS
        // copy parameterData to buffer beginning at the current buffer index (after TraceEvent)  
        for( dataIndex = 0U; dataIndex < parameterSize; dataIndex++ )
        {      
        	/* @MISRA_5-0-15,5-2-5=OFF XD-0001: Cast from pointer to uint8_t required eventData. */
        	buffer[ 2U + MONITOR_DATA_OFFSET + MONITOR_TRACE_EVENT_CONTENT_SIZE + dataIndex ] = parameter[ dataIndex ];
        	/* @MISRA_5-0-15,5-2-5=ON (end of XD-0001) */	
        }
        #endif
        
        // pass only the actual size of the data instead of the whole array size because not all array data needs to be send              
        #ifdef MONITOR_SENDPARAMETERS
        addCommand( 2U + MONITOR_DATA_OFFSET + MONITOR_TRACE_EVENT_CONTENT_SIZE + static_cast<uint32_t>(parameterSize), &buffer[ 0 ] );
        #else     
        (void)parameter;
        // send without parameterSize 
        addCommand( 2U + MONITOR_DATA_OFFSET + MONITOR_TRACE_EVENT_CONTENT_SIZE, &buffer[ 0 ] );
        #endif
    }
    
    #ifdef MON_USE_SEND_INT
    void Monitor::addObjectToSendIntList(const void * const object) const
    {
        #ifdef MON_USE_SEND_INT
        printIntObjectArray[ printIntPosition ] = object;
        printIntPosition = ( printIntPosition + 1U ) % MON_MAX_PRINT_INT_OBJECTS;
        #else
        (void)object;
        #endif /* MON_USE_SEND_INT */
    }
    
    #endif /* MON_USE_SEND_INT */ 
    
    
    #ifdef MON_USE_SEND_INT
    void Monitor::removeObjectToSendIntList(const void * const object) const
    {
        for( uint32_t i = 0U; i < MON_MAX_PRINT_INT_OBJECTS; i++)
        {
        	if( printIntObjectArray[ i ] == object )
        	{
        		printIntObjectArray[ i ] = nullptr;
        	}                        
        }
    }
    
    #endif /* MON_USE_SEND_INT */ 
    
    
    void Monitor::sendDestroy(const void * const me)
    {
        uint8_t buffer[ sizeof(void*) + 2U + MONITOR_DATA_OFFSET ]; 
        uint32_t i;
        
        buffer[ 0U ] = static_cast<uint8_t>(sizeof(void*)) + MONITOR_DATA_OFFSET;
        buffer[ 1U ] = MONITOR_COMMAND_SEND_DESTROY;
        #ifdef MONITOR_MULTI
        buffer[ 2U ] = MONITOR_TARGET_ID;
        #endif
        for( i = 0U; i < sizeof(void*); i++ )
        {      
        	/* @MISRA_5-2-5,5-2-7,5-0-15=OFF XD-0001: Cast from pointer to uint8_t to serialize this Ptr. */
        	buffer[ i + 2U + MONITOR_DATA_OFFSET ] = (reinterpret_cast<uint8_t*>(const_cast<void**>(&me)))[ i ];
        	/* @MISRA_5-2-5,5-2-7,5-0-15=ON (end of XD-0001) */
        } 
        
        addCommand( static_cast<uint8_t>(sizeof(void*)) + 2U + MONITOR_DATA_OFFSET, &buffer[ 0 ] ); 
    }
    
    void Monitor::sendError(void)
    {
        uint8_t buffer[ 2U + MONITOR_DATA_OFFSET ];
         
        buffer[ 0U ] = MONITOR_DATA_OFFSET;
        buffer[ 1U ] = MONITOR_COMMAND_SEND_ERROR;
        #ifdef MONITOR_MULTI
        buffer[ 2U ] = MONITOR_TARGET_ID;
        #endif
        addCommand( 2U + MONITOR_DATA_OFFSET, &buffer[ 0 ] );
    }
    
    void Monitor::sendInit(const void * const me, const std::uint16_t id, const void * const firstAttributeAddress)
    {
        uint8_t buffer[ 4U + MONITOR_DATA_OFFSET + ( 2U * sizeof(void*) )  ]; 
        uint32_t i;
        
        if( !initDone )
        {
        	sendVersion();
        	initImplementation();
        	initDone = true; 
        }
        
        buffer[ 0U ] = 2U + MONITOR_DATA_OFFSET + static_cast<uint8_t>( 2U * sizeof(void*) );
        buffer[ 1U ] = MONITOR_COMMAND_SEND_INIT;
        #ifdef MONITOR_MULTI
        buffer[ 2U ] = MONITOR_TARGET_ID;
        #endif
        buffer[ 2U + MONITOR_DATA_OFFSET ] = static_cast<uint8_t>(id);
        buffer[ 3U + MONITOR_DATA_OFFSET ] = static_cast<uint8_t>(id>>8U);
        for( i = 0U; i < sizeof( void* ); i++ )
        {    
        	/* @MISRA_5-0-15,5-2-5,5-2-7=OFF XD-0001: Cast from pointer to uint8_t to serialize this ptr. */
        	buffer[ i + 4U + MONITOR_DATA_OFFSET ] = (reinterpret_cast<uint8_t*>(const_cast<void**>(&me)))[ i ];
        	/* @MISRA_5-0-15,5-2-5,5-2-7=ON (end of XD-0001) */
        } 
        for( i = 0U; i < sizeof( void* ); i++ )
        {
        	/* @MISRA_5-0-15,5-2-5,5-2-7=OFF XD-0001: Cast from pointer to pointer to serialize first attribute address. */
        	buffer[ i + 4U + MONITOR_DATA_OFFSET + static_cast<uint32_t>(sizeof( void* ) ) ] = (reinterpret_cast<uint8_t*>(const_cast<void**>(&firstAttributeAddress)))[ i ];
        	/* @MISRA_5-0-15,5-2-5,5-2-7=ON (end of XD-0001) */
        }  
        
        addCommand( 4U + MONITOR_DATA_OFFSET + ( 2U * static_cast<uint32_t>(sizeof(void*)) ), &buffer[ 0 ] );
    }
    
    void Monitor::sendStateSize(void)
    {
        uint8_t buffer[ 4U + MONITOR_DATA_OFFSET ]; 
        
        buffer[ 0U ] = 2U + MONITOR_DATA_OFFSET;
        buffer[ 1U ] = MONITOR_COMMAND_SEND_STATESIZE;
        #ifdef MONITOR_MULTI  
        buffer[ 2U ] = MONITOR_TARGET_ID;
        #endif
        buffer[ 2U + MONITOR_DATA_OFFSET ] = MON_MAX_PARALLEL_STATES;
        buffer[ 3U + MONITOR_DATA_OFFSET ] = static_cast<uint8_t>(sizeof(WSTMonitorStateType));
        
        addCommand( 4U + MONITOR_DATA_OFFSET, &buffer[ 0 ] );
    }
    
    void Monitor::initImplementation(void)
    {
        #ifdef MON_USE_SEND_INT
        printIntPosition = 0U;
        #endif /* MON_USE_SEND_INT */
        
        sendStateSize();
        sendTypeSize();
    }
    
    void Monitor::sendOpCall(const void * const source, const void * const destination, const std::uint16_t id, const RXF::char_t* const paramStart, const RXF::char_t* const paramEnd)
    {
        /* @MISRA_5-0-15,5-0-15+5-0-17+5-0-18=OFF XD-0001: Cast from pointer to uint8_t to calculate parametersize. */
        uint8_t parameterSize = paramEnd - paramStart;
        /* @MISRA_5-0-15,5-0-15+5-0-17+5-0-18=ON (end of XD-0001) */
        uint8_t buffer[ MONITOR_OPERATION_CALL_CONTENT_SIZE + MONITOR_MAX_PARAMETER_SIZE ]; 
        uint32_t i;
        
        uint32_t timeStamp = Tick::getTicks() - syncTick;
        if( ( timeStamp & 0xFFFFFF00U ) != timeOffset )
        {
            timeOffset = timeStamp & 0xFFFFFF00U;
            sendTimeOffset();
        }
        WSTMonitorOperationCall opData( source, destination, id, static_cast<uint8_t>(timeStamp) );
        
        buffer[ 0U ] = MONITOR_OPERATION_CALL_CONTENT_SIZE + MONITOR_DATA_OFFSET + parameterSize;
        buffer[ 1U ] = MONITOR_COMMAND_SEND_OPERATION;
        #ifdef MONITOR_MULTI
        buffer[ 2U ] = MONITOR_TARGET_ID;
        #endif
        for( i = 0U; i < MONITOR_OPERATION_CALL_CONTENT_SIZE; i++ )
        {    
        	/* @MISRA_5-0-15,5-2-7=OFF XD-0001: Cast from pointer to uint8_t to accesses monitor data from operation. */
        	buffer[ i + 2U + MONITOR_DATA_OFFSET ] = (reinterpret_cast<uint8_t*>(const_cast<WSTMonitorOperationCall*>(&opData)))[ i ];
        	/* @MISRA_5-0-15,5-2-7=ON (end of XD-0001) */
        } 
        for( i = 0U; i < parameterSize; i++ )
        {  
        	/* @MISRA_5-0-15,5-2-5,5-2-7=OFF XD-0001: Cast from pointer to uint8_t to accesses data from operation arguments. */
        	buffer[ i + 2U + MONITOR_DATA_OFFSET + MONITOR_OPERATION_CALL_CONTENT_SIZE ] = (reinterpret_cast<uint8_t*>(const_cast<char_t*>(paramStart)))[ i ];
        	/* @MISRA_5-0-15,5-2-5,5-2-7=ON (end of XD-0001) */
        }  
        
        addCommand( 2U + MONITOR_DATA_OFFSET + MONITOR_OPERATION_CALL_CONTENT_SIZE + static_cast<uint32_t>(parameterSize), &buffer[ 0 ] );
    }
    
    void Monitor::sendTimeOffset(void)
    {
        uint8_t buffer[ 6U + MONITOR_DATA_OFFSET];
         
        buffer[ 0U ] = 4U + MONITOR_DATA_OFFSET;
        buffer[ 1U ] = MONITOR_COMMAND_SEND_TIME_OFFSET;
        #ifdef MONITOR_MULTI
        buffer[ 2U ] = MONITOR_TARGET_ID;
        #endif
        buffer[ 2U + MONITOR_DATA_OFFSET ] = static_cast<uint8_t>( timeOffset);
        buffer[ 3U + MONITOR_DATA_OFFSET ] = static_cast<uint8_t>( timeOffset >> 8 );
        buffer[ 4U + MONITOR_DATA_OFFSET ] = static_cast<uint8_t>( timeOffset >> 16 );
        buffer[ 5U + MONITOR_DATA_OFFSET ] = static_cast<uint8_t>( timeOffset >> 24 );
        
        addCommand( 6U + MONITOR_DATA_OFFSET, &buffer[ 0 ] );
    }
    
    void Monitor::sendTimeReset(void)
    {
        uint8_t buffer[ 2U + MONITOR_DATA_OFFSET ];
         
        buffer[ 0U ] = MONITOR_DATA_OFFSET;
        buffer[ 1U ] = MONITOR_COMMAND_SEND_TIME_RESET;
        #ifdef MONITOR_MULTI
        buffer[ 2U ] = MONITOR_TARGET_ID;          
        #endif
        
        addCommand( 2U + MONITOR_DATA_OFFSET, &buffer[ 0 ] );
        
    }
    
    #ifdef MON_USE_SEND_INT
    void Monitor::sendIntValue(const void * const destination, const std::uint32_t value)
    {
        uint8_t buffer[ 6U + MONITOR_DATA_OFFSET + ( sizeof(void*) )  ]; 
        uint32_t i;
        bool isFiltered = false;
        for( i = 0U; i < MON_MAX_PRINT_INT_OBJECTS; i++)
        {
        	if( printIntObjectArray[ i ] == destination )
        	{
        		isFiltered = true;
        			break;
        	}
        }	
        
        if( isFiltered )
        {
        	buffer[ 0U ] = 4U + MONITOR_DATA_OFFSET + static_cast<uint8_t>( sizeof(void*) );
        	buffer[ 1U ] = MONITOR_COMMAND_SEND_INT_VALUE;
        	#ifdef MONITOR_MULTI
        	buffer[ 2U ] = MONITOR_TARGET_ID;
        	#endif
        	for( i = 0U; i < sizeof( void* ); i++ )
        	{   
        		/* @MISRA_5-0-15,5-2-5,5-2-7=OFF XD-0001: Cast from pointer to uint8_t to serilize destination. */
        		buffer[ i + 2U + MONITOR_DATA_OFFSET ] = (reinterpret_cast<uint8_t*>(const_cast<void**>(&destination)))[ i ];
        		/* @MISRA_5-0-15,5-2-5,5-2-7=ON (end of XD-0001) */
        	} 
        	for( i = 0U; i < 4U; i++ )
        	{   
        		/* @MISRA_5-0-15,5-2-5,5-2-7=OFF XD-0001: Cast from pointer to uint8_t to serialize uint data. */
        		buffer[ i + 2U + MONITOR_DATA_OFFSET + sizeof( void* ) ] = (reinterpret_cast<uint8_t*>(const_cast<uint32_t*>(&value)))[ i ];
        		/* @MISRA_5-0-15,5-2-5,5-2-7=ON (end of XD-0001) */
        	}  
        	
        	addCommand( 6U + MONITOR_DATA_OFFSET + ( sizeof(void*) ), &buffer[ 0 ] );
        }
    }
    
    #endif /* MON_USE_SEND_INT */ 
    
    
    void Monitor::sendBufferFull(void) const
    {
        #ifdef MONITOR_MULTI
        static uint8_t cmdBuff[ 3 ] = { 1U, MONITOR_COMMAND_SEND_BUFFER_RESET, MONITOR_TARGET_ID};
        #else
        static uint8_t cmdBuff[ 2 ] = { 0U, MONITOR_COMMAND_SEND_BUFFER_RESET};
        #endif
        itsMonitorIO.addResetCommand( static_cast<uint32_t>(sizeof( cmdBuff )), &cmdBuff[ 0 ] );
    }
    
    void Monitor::consoleMessage(const RXF::char_t* const message)
    {
        uint8_t data[255]; 
        /* @MISRA_18-0-5=OFF XD-0001: Need to use string operations */
        data[0] = static_cast<uint8_t>(strlen( message ));
        /* @MISRA_18-0-5=ON (end of XD-0001) */ 
        data[1] = MONITOR_COMMAND_SEND_CONSOLE_MESSAGE;
        /* @MISRA_5-2-7,18-0-5=OFF XD-0001: Cast from pointer to pointer to prepare for strcpy. Need to use string operations */
        strcpy(reinterpret_cast<char_t*>(&data[2]),message);
        /* @MISRA_5-2-7,18-0-5=ON (end of XD-0001) */ 
        addCommand( static_cast<uint32_t>( data[0] ) + 2U, &data[ 0 ] );
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
    bufferFull(false), receivedByteCount(0), syncTick(0U), timeOffset(0U)
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
	File Path	: ../Source/Monitor/Trace/RXF_Monitor.cpp
*********************************************************************/
