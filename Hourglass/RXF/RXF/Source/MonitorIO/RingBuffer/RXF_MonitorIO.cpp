/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/MonitorIO/RingBuffer/RXF_MonitorIO.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/
 
#include <cstdint>
#include "RXF_Config.h"

std::uint8_t hostToTargetBuffer[MIO_RECEIVE_BUFFER_SIZE];

std::uint32_t hostToTargetReadPtr(0U);

std::uint32_t hostToTargetWritePtr(0U);

std::uint8_t targetToHostBuffer[MIO_SEND_BUFFER_SIZE];

std::uint32_t targetToHostReadPtr(0U);

std::uint32_t targetToHostWritePtr(0U);

#include "RXF_CriticalSection.h"
#include "RXF_MonitorIO.h"
namespace RXF {
    void MonitorIO::init(void) const
    {
    }
    
    std::uint8_t MonitorIO::read(void) const
    {
        uint8_t recChar;   
        
        while ( hostToTargetReadPtr == hostToTargetWritePtr ){}	/* wait until data has received from the host (!!blocking!!) */
        
        recChar = hostToTargetBuffer[ hostToTargetReadPtr ];
        
        hostToTargetReadPtr++;
        
        if( hostToTargetReadPtr == MIO_RECEIVE_BUFFER_SIZE )
        {
        	hostToTargetReadPtr = 0U;
        }
        
        return recChar;
    }
    
    bool MonitorIO::checkDataAvailable(void) const
    {
        return ( hostToTargetReadPtr != hostToTargetWritePtr );
    }
    
    void MonitorIO::sendData(void) const
    {
    }
    
    bool MonitorIO::addCommand(const std::uint32_t size, const std::uint8_t* const data) const
    {
        bool retVal = false;
        CriticalSection criticalSection;
        criticalSection.lock();
        uint32_t dataAvailable = MIO_SEND_BUFFER_SIZE - ( targetToHostWritePtr - targetToHostReadPtr );
        if( dataAvailable > MIO_SEND_BUFFER_SIZE )
        {
        	dataAvailable -= MIO_SEND_BUFFER_SIZE;
        }
        if( dataAvailable >= ( size + ( 2U + MONITOR_DATA_OFFSET ) ) )
        {   	
        	uint32_t tmpIndex = targetToHostWritePtr;
        	uint32_t index = 0;	
        	while( index != size ) 
        	{
        		targetToHostBuffer[ tmpIndex ] = data[ index ];
        		tmpIndex++;
        		if( tmpIndex == MIO_SEND_BUFFER_SIZE )
        		{
        			tmpIndex = 0U;
        		}
        		index++;
        	}
        	targetToHostWritePtr += size;
        	if( targetToHostWritePtr >= MIO_SEND_BUFFER_SIZE )
        	{
        		targetToHostWritePtr -= MIO_SEND_BUFFER_SIZE;
        	}
        	criticalSection.unlock();
        	retVal = true;
        }
        else
        {      
        	criticalSection.unlock();
        }                       
        return retVal;
    }
    
    void MonitorIO::addResetCommand(const std::uint32_t size, const std::uint8_t* const data) const
    {
        CriticalSection criticalSection;
        criticalSection.lock();
        for( uint32_t i = 0U; i < size; i++)
        {    
        	targetToHostBuffer[ targetToHostWritePtr ] = data[ i ];
        	targetToHostWritePtr++;
        	if( targetToHostWritePtr == MIO_SEND_BUFFER_SIZE )
        	{
        		targetToHostWritePtr = 0U;
        	}
        } 
        criticalSection.unlock();
        
    }
}

/*********************************************************************
	File Path	: ../Source/MonitorIO/RingBuffer/RXF_MonitorIO.cpp
*********************************************************************/
