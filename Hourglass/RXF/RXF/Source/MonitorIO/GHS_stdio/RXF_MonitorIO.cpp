/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/MonitorIO/GHS_stdio/RXF_MonitorIO.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_CriticalSection.h"
#include "RXF_MonitorIO.h"
#include <stdio.h>
#include <indsyscl.h>
#include <indos.h>
namespace RXF {
    std::uint8_t MonitorIO::sendBuffer[MIO_SEND_BUFFER_SIZE];
    
    std::uint32_t MonitorIO::sendBufferReadPtr(0U);
    
    std::uint32_t MonitorIO::sendBufferWritePtr(0U);
    
    void MonitorIO::init(void)
    {
    }
    
    std::uint8_t MonitorIO::read(void)
    {
        uint8_t data;
        data = ( static_cast<uint8_t>( getchar() ) - 65 ) + ( ( static_cast<uint8_t>( getchar() ) - 65 ) << 4 );
        return data;
    }
    
    bool MonitorIO::checkDataAvailable(void)
    {
        bool retVal = false;
        if( __ghs_syscall(SYSCALL_BYTES_TO_READ, 0) > 0 )
        {
        	retVal = true;
        }
        return retVal;
    }
    
    void MonitorIO::sendData(void)
    {
    }
    
    bool MonitorIO::addCommand(const std::uint32_t size, const std::uint8_t* const data)
    {
        for(uint32_t i = 0; i < size; i++)
        {
        	if( data[ i ] == 0U )
        	{
        		putchar( 0x01 );
        		putchar( 0x02 );
        	}
        	else if( data[ i ] == 1U )
        	{
        		putchar( 0x01 );
        		putchar( 0x03 );
        	}
        	else
        	{
        		putchar( data[ i ] );
        	}
        }
        return true;
    }
    
    void MonitorIO::addResetCommand(const std::uint32_t size, std::uint8_t data)
    {
    }
}

/*********************************************************************
	File Path	: ../Source/MonitorIO/GHS_stdio/RXF_MonitorIO.cpp
*********************************************************************/
